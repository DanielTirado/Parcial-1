#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

char **leer_materias(int (pensum)[46][5]){
    ifstream materias;

    char **codigo_nombre = new char*[46];

    for (int i=0; i<46; i++){
        codigo_nombre[i] = new char[24];
    }

    try{
        materias.open("materias.txt");
        if (!materias.is_open()) throw '1';

        // ALMACENAR EL CODIGO, LOS CREDITOS Y LAS HORAS DE CADA MATERIA DEL PENSUM EN UN ARREGLO INT

        char linea[32];
        int m=0;

        while (materias.getline(linea, 32)){
            int codigo=0;
            int creditos=0;
            int horas_docente=0;
            int horas_independientes=0;
            int horas_faltantes=0;

            for (int i=0; i<7; i++){
                codigo_nombre[m][i] = linea[i];
                codigo = codigo*10+(linea[i])-'0';
                pensum[m][0] = codigo;
            }

            for (int i=7; i<24; i++){
                codigo_nombre[m][i] = linea[i+1];
            }

            creditos = linea[26]-'0';
            pensum[m][1] = creditos;

            horas_docente = linea[28]-'0';
            pensum[m][2] = horas_docente;

            horas_independientes = 3*creditos;
            horas_faltantes = horas_independientes;
            pensum[m][3] = horas_independientes;
            pensum[m][4] = horas_faltantes;
            m++;
        }
        materias.close();
    }

    catch (char c){
        cout << "Error #" << c <<": ";
        if (c=='1') cout<<"Error al abrir el archivo de materias. \n";
    }
    catch (...){
        cout << "Error no definido\n";
    }
    return codigo_nombre;
}

void leer_horario(char (&horario)[17][6][8]){
    ifstream calendar;

    try {
        calendar.open("horario.txt");
        if (!calendar.is_open()) throw '2';

        //  ALMACENAR CADA BLOQUE HORA-DIA-MATERIA EN UN ARREGLO INT
        char linea[54];
            for (int HORA=0; HORA<17; HORA++){
                calendar.getline(linea, 54);
                int m=0;
                for (int DIA=0; DIA<6; DIA++){
                    for (int CODIGO=0; CODIGO<8; CODIGO++){
                        horario[HORA][DIA][CODIGO] = linea[m+CODIGO];
                    }
                    m+=9;
                }
            }
        calendar.close();
    }
    catch (char c){
        cout << "Error #"<<c<<": ";
        if (c=='2'){
            cout << "Error al abrir el archivo del horario.\n";
        }
    }
    catch (...){
        cout << "Error no definido\n";
    }
}

void leer_matricula(int (&materias_matricula)[15][2], int &num_materias){

    ifstream matricula;
    num_materias =0;
    try{
        char linea[10];

        matricula.open("matricula.txt");
        if (!matricula.is_open()) throw '3';

        int i=0;
        while (matricula.getline(linea,10)){
            int codigo=0;

            for (int j=0; j<7; j++){
                codigo = codigo*10+(linea[j])-'0';
            }

            materias_matricula[i][0] = codigo;
            materias_matricula[i][1] = linea[8]-'0';
            i++;
            num_materias++;
        }
        matricula.close();
    }

    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='3') cout<<"Error al abrir el archivo de matricula.\n";
    }
    catch (...){
    cout<<"Error no definido\n";
    }

}

void imprimir_horario(char (&horario)[17][6][8]){

    cout <<"\n\nImprimiendo arreglo de horario\n\n";
    cout << "\tLUNES\t\tMARTES\t\tMIERCOLES\tJUEVES\t\tVIERNES\t\tSABADO\n";
    for (int HORA=0; HORA<17; HORA++){
        cout << HORA+5 << ":00\t";
        for (int DIA=0; DIA<6; DIA++){
            for (int CODIGO=0; CODIGO<8; CODIGO++){
                cout << horario[HORA][DIA][CODIGO];
            }
            cout << "\t";
        }
        cout << endl;
    }

}

void probar_arreglo_pensum(int (&pensum)[46][5]){

    ofstream archivo;
    archivo.open("prueba.txt");

    cout << "Imprimiendo pensum...\n\n";
    archivo << "Imprimiendo pensum...\n\n";
    for (int i=0; i<46; i++){
        for (int j=0; j<5; j++){
            cout << pensum[i][j] << "\t";
            archivo << pensum[i][j] << "\t";
        }
        cout <<endl;
        archivo << endl;
    }

    archivo.close();
}

void probar_arreglo_codigo_nombre(char **codigo_nombre){

    ofstream archivo;
    archivo.open("prueba.txt");

    cout <<"\n\nImprimiendo arreglo de codigo y nombre...\n\n";
    archivo << "\n\nImprimiendo arreglo de codigo y nombre...\n\n";
    for (int i=0; i<46; i++){
        for (int j=0; j<24; j++){
            cout<<codigo_nombre[i][j];
            archivo<<codigo_nombre[i][j];
        }
        cout << endl;
        archivo << endl;
    }

    archivo.close();
}

bool materia_existe(int materia, int (&pensum)[46][5]){
    for (int i=0; i<46; i++){
        if (materia == pensum[i][0]){
            return true;
        }
    }
    cout << "La materia no existe en el pensum\n";
    return false;
}

bool materia_matriculada(int materia, int (&materias_matricula)[15][2], int num_materias){
    for (int i=0; i<num_materias; i++){
        if (materia == materias_matricula[i][0]){
            cout << "Ya matriculaste esa materia\n";
            return true;
        }
    }
    return false;
}

int creditos_matriculados(int materias_matricula[15][2], int num_materias){
    int total_creditos=0;

    for (int i=0; i<num_materias; i++){
        total_creditos+=materias_matricula[i][1];
    }

    return total_creditos;
}

int creditos_de_materia(int materia, int pensum[46][5]){
    int creditos =0;
    for (int i=0; i<46;i++){
        if (materia==pensum[i][0]){
            creditos = pensum[i][1];
        }
    }
    return creditos;
}

int hora_docente(int materia, int pensum[46][5]){
    int horas =0;
    for (int i=0; i<46;i++){
        if (materia==pensum[i][0]){
            horas = pensum[i][2];
        }
    }
    return horas;
}

void agregar_materia(int materia, int pensum[46][5]){
    ofstream matricula("matricula.txt", ios::app);
    try{

        matricula.open("matricula.txt");
        if (!matricula.is_open()) throw '4';

        matricula << endl << materia << "|" << creditos_de_materia(materia, pensum) << endl;
        matricula.close();
    }

    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='4') cout<<"Error al abrir el archivo de matricula.\n";
    }
    catch (...){
        cout<<"Error no definido\n";
    }

}

void convertir_int_a_char(int numero, char (&numero_char)[8]){

    for (int i=0; i<7; i++){
        numero_char[6-i] = numero%10+'0';
        numero/=10;
    }
    numero_char[7] = '\0';
}

void escribir_horario(char (&horario)[17][6][8]){
    ofstream calendar;

    calendar.open("horario.txt");

    for (int HORA=0; HORA<17; HORA++){
        for (int DIA=0; DIA<6; DIA++){
            for (int CODIGO=0; CODIGO<8; CODIGO++){
                calendar << horario[HORA][DIA][CODIGO];
            }
            calendar << "|";
        }
        calendar << endl;
    }

    calendar.close();
}

int main()
{
    int pensum[46][5];

    // LECTURA DEL PENSUM
    char **codigo_nombre = leer_materias(pensum);
    //probar_arreglo_pensum(pensum);
    //probar_arreglo_codigo_nombre(codigo_nombre);

    // LECTURA DE LA MATRICULA
    int num_materias=0;
    int materias_matricula[15][2];
    for (int i=0; i<15; i++){
        for (int j=0; j<2; j++){
            materias_matricula[i][j]=0;
        }
    }

    leer_matricula(materias_matricula, num_materias);

    //TOTAL DE LOS CREDITOS

    // LECTURA DEL HORARIO
    char horario[17][6][8];
    leer_horario(horario);


    bool programa = true;
    int opcion;

    while (programa){

        cout << "\n\n\t\t\t ORGANIZADOR DE HORARIO \n\nBienvenido a tu organizador de horario, Que quieres hacer primero?\n\n";

        cout << "(1)Visualizar horario\n(2)Matricular materias\n(3)Agregar horas de estudio\n(4)Salir\n";
        cin >> opcion;

        //ACCION A REALIZAR
        while (opcion < 1 || opcion > 4){
            cout << "Opcion invalida, intente de nuevo\n";
            cout << "(1)Visualizar horario\n(2)Matricular materias materia\n(3)Agregar horas de estudio\n(4)Salir";
            cin >> opcion;
        }

        //Imprimir horario
        if (opcion==1) imprimir_horario(horario);

        // Matricular materia
        while (opcion==2){

            int total_creditos = creditos_matriculados(materias_matricula, num_materias);

            bool salir=false;
            cout << "\nRecuerda que no puedes matricular mas de 24 creditos.\n";
            cout <<"\n\n Creditos matriculados = " << total_creditos << endl;
            if (total_creditos<8){
                cout<<"\n\n Necesitas matricular mas materias!!\n";
            }

            else if (total_creditos==24){
                cout << "No puedes matricular mas materias!!\n";
                break;
            }

            while (!salir){

                int materia;
                char materia_char[8];
                //ingresar el codigo de la materia
                cout << "Ingrese el codigo de la materia a matricular: ";
                cin >> materia;


                while (!materia_existe(materia, pensum) || materia_matriculada(materia, materias_matricula, num_materias)){
                    cout << "Ingrese el codigo de la materia a matricular o ingrese 'x' o '0' para salir: ";
                    cin >> materia;
                    if (materia==0) {
                        salir = true;
                        break;
                    }
                }


                if (creditos_de_materia(materia, pensum) + total_creditos > 24){
                    cout << "No puedes matricular esta materia, demasiados creditos.\n\n";
                }

                else if (!salir){

                    int horas_trabajo = hora_docente(materia, pensum);
                    convertir_int_a_char(materia, materia_char);

                    agregar_materia(materia, pensum);
                    leer_matricula(materias_matricula, num_materias);


                    for (int h=0; h<horas_trabajo; h++){
                        cout << "\n\nNecesitas matricular " << horas_trabajo << "horas de trabajo con docente, ";
                        cout << "llevas " << h << "horas matriculadas en esta materia.\n\n";

                        int DIA=0;
                        int HORA=0;

                        cout << "\n Ingrese el dia donde quiere matricular la materia. \n(0)Lunes\n(1)Martes\n(2)Miercoles\n(3)Jueves\n(4)Viernes\n(5)Sabado\n";
                        cin >> DIA;

                        bool hora_ocupada=false;

                        while (!hora_ocupada){
                        cout << "\n Ingrese la hora en formato 24h donde quiere matricular la materia. (HORARIO ESTABLECIDO DESDE LAS 5 HASTA LAS 21)\n";
                        cin >> HORA;
                        HORA -= 5;
                        if (horario[HORA][DIA][0] == '-'){
                            for (int i=0; i<7; i++){
                                horario[HORA][DIA][i] = materia_char[i];
                            }
                            horario[HORA][DIA][7] = 'D';
                            hora_ocupada=true;
                        }
                        else{
                            cout << "\nEsa hora la tienes ocupada, intenta de nuevo\n";
                        }
                        }

                        cout << "\n\n Materia matriculada!!\n";
                        escribir_horario(horario);
                        salir = true;
                    }
                }

                total_creditos = creditos_matriculados(materias_matricula, num_materias);

            }
            opcion=0;
        }

        //Agregar horas de estudio
        while(opcion==3){
            // Mostrar cuántas horas de estudios hacen falta en cada materia

            // preguntar qué día quiere agregar la hora de estudio

            //Sugerir horarios en un bucle hasta que se completen las horas o hasta que el usuario quiera salir

            // Opción para el ingreso manual de la hora de estudio y cambiar de día
            //Actualizar las horas de estudio y mostrarlas después de cada actualización

            // Al finalizar en este apartado, 'opcion' se inicializa en 0 y vuelve al inicio.
            opcion=0;
        }


        if (opcion == 4) programa = false;

    }

    for (int i=0; i<46; i++){
        delete[] codigo_nombre[i];
    }
    delete[] codigo_nombre;

    return 0;
}
