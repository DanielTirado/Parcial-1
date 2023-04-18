#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{

    // LECTURA DE LOS ARCHIVOS
    ifstream materias;
    ifstream matricula;
    ifstream calendar;

    try {
        materias.open("materias.txt");
        if (!materias.is_open()) throw '1';

        // ALMACENAR EL CODIGO, LOS CREDITOS Y LAS HORAS DE CADA MATERIA DEL PENSUM EN UN ARREGLO INT
        unsigned int pensum[46][5];
        for (int i=0; i<46; i++){
            for (int j=0; j<4; j++){
                pensum[i][j]=0;
            }
        }
        // Mientras se almacenan los datos se hace el cálculo de cuántas horas independientes se necesitan
        //...

        //ALMACENAR EL CODIGO Y EL NOMBRE DE LA MATERIA EN UN ARREGLO CHAR

        //...

        materias.close();

        matricula.open("matricula.txt");
        if (!matricula.is_open()) throw '2';

        calendar.open("horario.txt");
        if (!calendar.is_open()) throw '3';



        // ALMACENAR TODOS LOS BLOQUES DIA-HORA-MATERIA EN UN ARREGLO INT
        int horario[6][18][7];

        for (int i=0; i<6; i++){
            for (int j=0; j<18; j++){
                for (int k=0; k<7; k++){
                    horario[i][j][k] = 0;
                }
            }
        }
        //...

        calendar.close();

        bool programa = true;
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

        }

    }
    catch (char c){
        cout << "Error #" << c <<": ";
        if (c=='1') cout<<"Error al abrir el archivo de materias. \n";

        else if (c=='2') cout<<"Error al abrir el archivo de matricula. \n";

        else if (c=='3') cout<<"Error al abrir el archivo del horario. \n";
    }
    catch (...){
        cout << "Error no definido. \n";
    }




    return 0;
}
