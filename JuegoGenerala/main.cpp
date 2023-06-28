#include <iostream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>


using namespace std;

#include "funcutiles.h"


int main()
{
    system ("color 71");
    char opc;
    bool cargaManual = false;
    int puntajeMax = -1, cantTiradasMax = -1;
    char nombreMax[32];
    do
    {
        system("cls");


        cout<< "------------MENU JUEGO GENERALA :)------------" <<endl;
        cout<< "\t"" 1 - UN JUGADOR " <<endl;
        cout<< "\t"" 2 - DOS JUGADORES " <<endl;
        cout<< "\t"" 3 - MOSTRAR PUNTUACION MAS ALTA " <<endl;
        cout<< "\t"" 4 - MODO TIRADA MANUAL " <<endl;
        cout<< "\t"" 0 - SALIR " <<endl;
        cout<< "----------------------------------------------" <<endl;
        cout<< "Ingrese la opci"<<(char)162<<"n: " <<endl;
        cin>>opc;

        jugar(opc, &cargaManual, &puntajeMax, &cantTiradasMax, nombreMax);

    }
    while(opc!='0');

    cout << "Muchas gracias por jugar, vuelve pronto!!" << endl;


    return 0;

}
