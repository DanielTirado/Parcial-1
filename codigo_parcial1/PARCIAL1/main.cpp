#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

char **leer_materias(int (pensum)[46][5]){
    ifstream materias;

    char **codigo_nombre = new char*[46];

    for (int i=0; i<46; i++){
        codigo_nombre[i] = new char[26];
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

void leer_horario(int horario[6][18][7]){
    ifstream calendar;

    try {
        calendar.open("horario.txt");
        if (!calendar.is_open()) throw '2';
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

int main()
{
    ofstream archivo;
    archivo.open("prueba.txt");
    int pensum[46][5];
    // LECTURA DE LAS MATERIAS
    char **codigo_nombre = leer_materias(pensum);

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

    cout <<"\n\nImprimiendo arreglo de codigo y nombre...\n\n";
    archivo << "\n\nImprimiendo arreglo de codigo y nombre...\n\n";
    for (int i=0; i<46; i++){
        for (int j=0; j<26; j++){
            cout<<codigo_nombre[i][j];
            archivo<<codigo_nombre[i][j];
        }
        cout << endl;
        archivo << endl;
    }

    archivo.close();
    //LIBERAR MEMORIA

    for (int i=0; i<46; i++){
        delete[] codigo_nombre[i];
    }
    delete[] codigo_nombre;

        /*bool programa = true;
        while (programa){
            cout << "\t\t\t ORGANIZADOR DE HORARIO \n\nBienvenido a tu organizador de horario, Que quieres hacer primero?\n\n";

            char opcion;
            cout << "(1)Visualizar horario\n(2)Eliminar materia\n(3)Agregar horas de estudio\n(4)Salir\n";
            cin >> opcion;

            while (opcion < '1' || opcion>'4'){
                cout << "Opcion invalida, intente de nuevo\n";
                cout << "(1)Visualizar horario\n(2)Eliminar materia\n(3)Agregar horas de estudio\n(4)Salir";
                cin >> opcion;
            }

            //Imprimir horario
            if (opcion=='1'){
                //Recorrer el arreglo horario con un for y buscar el nombre de la materia en el arreglo materias
                cout << horario[0][0][0];
            }

            // Eliminar materia
            while (opcion=='2'){

                //ingresar el codigo de la materia

                //verificar si está cursando esa materia

                    //Eliminarla en caso de estar cursandola
                    //buscar cada coincidencia en el horario y quitarlo del arreglo horario y del arreglo materias

                //preguntar si quiere eliminar otra materia
                opcion='0';
            }

            while(opcion=='3'){
                // Mostrar cuántas horas de estudios hacen falta en cada materia

                // preguntar qué día quiere agregar la hora de estudio

                //Sugerir horarios en un bucle hasta que se completen las horas o hasta que el usuario quiera salir

                    // Opción para el ingreso manual de la hora de estudio y cambiar de día
                    //Actualizar las horas de estudio y mostrarlas después de cada actualización

                // Al finalizar en este apartado, 'opcion' se inicializa en 0 y vuelve al inicio.
                opcion='0';
            }


            if (opcion == '4') programa = false;

        }*/
    return 0;
}
