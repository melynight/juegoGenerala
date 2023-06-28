#define FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <windows.h>
#include <string.h>
#include "consts.h"
#include "funcionesfront.h"

void jugar(char opc);
void cargarAleatorio(int dados[],int tam,int maxValue);
void cargaParcialAleatorio (int dados[], int p, int tam, int maxValue);
int contarNumerosRepetidos(int dados[], int numero, int tam);
int realizarLanzamiento(int puntajes[][MAX_COMBINACIONES_GANADORAS],int dados[], int tam, int ronda, char nombres[][32],int jugador, int cantTiradasTotales[], bool cargaManual);
void cargarDadosManual(int dados[], int tam);
void imprimirDetalleJugadores(int puntajes[][MAX_COMBINACIONES_GANADORAS], int ronda, char nombres[][32],int jugador, int cantTiradas, int cantTiradasTotales);
void imprimirInterfazRonda(int puntajes[][MAX_COMBINACIONES_GANADORAS], int ronda, char nombres[][32],int jugador,int cantTiradasTotales[]);
int calcularPuntajeLanzamiento(int puntajes[][MAX_COMBINACIONES_GANADORAS], int dados[], int tam, int cantTiradas, int ronda,char nombres[][32],int jugador, int cantTiradasTotales[],bool* generalaServida);
int calcularTotalPuntajes(int puntajes[][MAX_COMBINACIONES_GANADORAS],int jugador);
void juegosMenorPuntajes (int puntajes[][MAX_COMBINACIONES_GANADORAS],int valordado[], int tam, int* opcion, int puntajeEspejo[][2],int jugador);
void imprimirNombreOpc(int jugada, int opcion);
void tacharOpcion (int puntajes[][MAX_COMBINACIONES_GANADORAS],int jugador);
int imprimirGanador (char nombres[][32], int puntajes[][MAX_COMBINACIONES_GANADORAS],int cantTiradasTotales[], int jugadores, int* puntajeMax, int* cantTiradasMax, char nombreMax[]);
void imprimePuntajeMaximo (char nombreMax[32], int puntajeMax, int cantTiradasMax);


void jugar(char opc, bool* cargaManual, int* puntajeMax, int* cantTiradasMax, char nombreMax[])
{
    char nombres[2][32];
    bool generalaServida = false;
    int i, J, ronda = 0;
    int puntajes[2][MAX_COMBINACIONES_GANADORAS];
    int cantTiradas = 1, cantidadRondas, cantTiradasTotales[2], dados[CANT_DADOS];

    for (i = 0; i < MAX_COMBINACIONES_GANADORAS; i++)
    {
        puntajes[0][i] = -1;
        puntajes[1][i] = -1;
    }

    for (i=0; i < 2; i++)
    {
        cantTiradasTotales[i] = 0;
    }

    switch (opc)
    {

    case '1':
        clrscr();
        cout<< "-------Modo un jugador-------" <<endl;
        cout<< "Ingrese su nombre: " <<endl;
        cin>> nombres[0];
        cout<<"Ingrese la cantidad de rondas a jugar"<<endl;
        cin>>cantidadRondas;
        clrscr();
        for (ronda=1; ronda<=cantidadRondas; ronda++)
        {
            imprimirDetalleJugadores(puntajes, ronda, nombres, 1, cantTiradas, cantTiradasTotales[0]);
            cantTiradas = realizarLanzamiento(puntajes, dados, CANT_DADOS, ronda, nombres,1, cantTiradasTotales, *cargaManual);
            calcularPuntajeLanzamiento(puntajes,dados,CANT_DADOS,cantTiradas,ronda,nombres,1, cantTiradasTotales, &generalaServida);
            cantTiradasTotales[0]+=cantTiradas;
            cantTiradas = 1;
            if (generalaServida==true)
            {
                break;
            }

        }

        imprimirGanador(nombres,puntajes,cantTiradasTotales, 1,puntajeMax,cantTiradasMax,nombreMax);

        break;

    case '2':
        char nombreAux[2][32];
        int dado[2];
        clrscr();
        cout<< "-------Modo dos jugadores-------" <<endl;
        cout<<"Ingrese la cantidad de rondas a jugar:"<<endl;
        cin>>cantidadRondas;
        cout<< "Ingrese el nombre de un jugador: " <<endl;
        cin>> nombreAux[0];
        cout<< "Ingrese el nombre de otro jugador: " <<endl;
        cin>> nombreAux[1];

        do
        {
            clrscr();
            cout<< "-------Modo dos jugadores-------" <<endl;
            cout << "El jugador que obtenga el mayor valor, comienza" << endl;
            cout << nombreAux[0] << " arroj" << (char)162 << " el dado:" << endl;
            cargarAleatorio(dado, 2, MAX_TAM_DADO);
            imprimirDado(dado[0], 12, 3);
            cout << endl;
            cout << nombreAux[1] << " arroj" << (char)162 << " el dado:" << endl;
            imprimirDado(dado[1], 12, 9);
            cout << endl;
            if (dado[0] == dado[1])
            {
                cout << "Ambos obtuvieron el mismo dado. Se vuelve a lanzar..." << endl;
            }
            system("pause");

        }
        while (dado[0] == dado[1]);

        clrscr();
        cout<< "-------Modo dos jugadores-------" <<endl;
        if (dado[0] > dado[1])
        {
            cout << nombreAux[0] << " es el jugador 1 porque obtuvo un " << dado[0] << endl;
            cout << nombreAux[1] << " es el jugador 2 porque obtuvo un " << dado[1] << endl;
            strcpy(nombres[0], nombreAux[0]);
            strcpy(nombres[1], nombreAux[1]);
        }
        else
        {
            cout << nombreAux[1] << " es el jugador 1 porque obtuvo un " << dado[1] << endl;
            cout << nombreAux[0] << " es el jugador 2 porque obtuvo un " << dado[0] << endl;
            strcpy(nombres[0], nombreAux[1]);
            strcpy(nombres[1], nombreAux[0]);
        }
        system("pause");

        clrscr();
        for (ronda=1; ronda<=cantidadRondas; ronda++)
        {
            for (J=1; J<=2; J++)
            {
                imprimirDetalleJugadores(puntajes, ronda, nombres, J, cantTiradas, cantTiradasTotales[J-1]);
                cantTiradas = realizarLanzamiento(puntajes, dados, CANT_DADOS, ronda, nombres,J, cantTiradasTotales, *cargaManual);
                cantTiradas=calcularPuntajeLanzamiento(puntajes,dados,CANT_DADOS,cantTiradas,ronda,nombres,J, cantTiradasTotales, &generalaServida);
                cantTiradasTotales[J-1]+= cantTiradas;
                cantTiradas = 1;
                clrscr();
                imprimirInterfazRonda(puntajes,ronda,nombres,J,cantTiradasTotales);
                if (generalaServida==true)
                {
                    imprimirGanador(nombres,puntajes,cantTiradasTotales, 2,puntajeMax,cantTiradasMax,nombreMax);
                    return;

                }

            }


        }

        imprimirGanador(nombres,puntajes,cantTiradasTotales, 2,puntajeMax,cantTiradasMax,nombreMax);

        break;

    case '3':
        clrscr();
        if (*puntajeMax==-1)
        {
            cout<< "No hubieron partidas previas" <<endl;
        }
        else
        {
            imprimePuntajeMaximo(nombreMax,*puntajeMax,*cantTiradasMax);
        }
        cout<<endl<<endl<<endl<<endl<<endl<<endl;
        pause();

        break;

    case '4':
        clrscr();
        cout<< "Modo carga manual: ";
        if (*cargaManual)
        {
            cout << "activado" << endl;
        }
        else
        {
            cout << "desactivado" << endl;
        }

        char opcCargaManual;
        cout << endl << "Ingrese una opci"<<(char)162<<"n ('a': activado; 'd': desactivado): ";
        cin >> opcCargaManual;

        if (opcCargaManual == 'a')
        {
            *cargaManual = true;
        }
        else
        {
            *cargaManual = false;
        }

        break;
    case '0':
        return;
    default:
        cout << "La opcion ingresada no es valida" << endl;
        pause();
        break;
    }
}

void cargarAleatorio(int dados[], int tam, int maxValue)
{
    int i;
    srand(time(NULL));
    for(i=0; i<tam; i++)
    {
        dados[i]=(rand()%maxValue)+1;
    }
}

void cargaParcialAleatorio (int dados[], int p, int tam, int maxValue)
{
    srand(time(NULL));
    dados[p-1]=(rand()%maxValue)+1;

}


void imprimirDetalleJugadores(int puntajes[][MAX_COMBINACIONES_GANADORAS], int ronda, char nombres[][32], int jugador, int cantTiradas, int cantTiradasTotales)
{
    cout<< "Jugador: "  << nombres[jugador-1] << "\t | \t\t Puntuacion: " << calcularTotalPuntajes(puntajes,jugador)<< " pts." << "\t | \t\t Ronda n"<< (char)248<< ronda <<endl;
    cout<< "Tirada n" << (char)248 << cantTiradas << "\t | \t\t Tiradas totales: " << cantTiradasTotales + cantTiradas << endl;

}



void imprimirInterfazRonda(int puntajes[][MAX_COMBINACIONES_GANADORAS], int ronda, char nombres[][32],int jugador,int cantTiradasTotales[])
{
    imprimirRecuadro(26,4,60,13,12,71);

    gotoxy(50,8);

    cout<<"Ronda N" << (char)248 << ronda <<endl;
    gotoxy(45,9);
    if(jugador==1)
    {
        cout<<"Pr"<<(char)162<<"ximo turno: "<< nombres[1] <<endl;
    }
    else
    {
        cout<<"Pr"<<(char)162<<"ximo turno: "<< nombres[0] <<endl;
    }
    gotoxy(45,10);
    cout<< "Lanzamientos " << nombres[jugador-1] << ": " << cantTiradasTotales[jugador-1]<<endl;
    gotoxy(47,13);

    cout<< "Puntaje " << nombres[0] << ": " << calcularTotalPuntajes(puntajes,1)<<" pts."<<endl;
    gotoxy(47,14);
    cout<< "Puntaje " << nombres[1] << ": " << calcularTotalPuntajes(puntajes,2)<<" pts."<<endl;

    gotoxy(40,20);
    system("pause");
    clrscr();

}


int calcularTotalPuntajes(int puntajes[][MAX_COMBINACIONES_GANADORAS],int jugador)
{
    int total = 0;
    for (int i = 0; i < MAX_COMBINACIONES_GANADORAS; i++)
    {
        if (puntajes[jugador-1][i] != -1)
        {
            total += puntajes[jugador-1][i];
        }
    }
    return total;
}


int realizarLanzamiento(int puntajes[][MAX_COMBINACIONES_GANADORAS],int dados[], int tam, int ronda, char nombres[][32], int jugador, int cantTiradasTotales[], bool cargaManual)
{
    char respuesta1;
    int cantDados,i,cantTiradas=1,p;

    if (cargaManual)
    {
        cargarDadosManual(dados,CANT_DADOS);
        clrscr();
        imprimirDetalleJugadores(puntajes, ronda, nombres, jugador, cantTiradas, cantTiradasTotales[jugador-1]);
    }
    else
    {
        cargarAleatorio(dados,tam,MAX_TAM_DADO);
    }


    imprimirDados(dados);
    cout<<endl;

    while (cantTiradas<MAX_CANT_TIRADAS)
    {


        cout<< "Desea anotar puntaje? (s/n)" <<endl;
        cin>> respuesta1;

        if (respuesta1=='s')
        {
            return cantTiradas;
        }
        else
        {
            cantTiradas=cantTiradas+1;

            cout<< "Cuantos dados desea volver a tirar?" <<endl;
            cin>> cantDados;


            for(i=1; i<=cantDados; i++)
            {

                cout<< "Cuales dados?" <<endl;
                cin>> p;

                cargaParcialAleatorio(dados,p,cantDados,MAX_TAM_DADO);
            }
            system("cls");
            imprimirDetalleJugadores(puntajes, ronda, nombres, jugador, cantTiradas, cantTiradasTotales[jugador-1]);
            imprimirDados(dados);

        }

    }

    return cantTiradas;
}






int calcularMaxRepeticiones(int valordado[], int tam, int firstOrSecondMax)
{
    int primerMax = -1, segundoMax = -1, i;

    for (i = 0; i < tam; i++)
    {
        if (primerMax == -1 || primerMax < valordado[i])
        {
            if (primerMax != -1)
            {
                segundoMax = primerMax;
            }

            primerMax = valordado[i];
        }
        else if (segundoMax == -1 || segundoMax < valordado[i])
        {
            segundoMax = valordado[i];

        }
    }

    if (firstOrSecondMax == 1)
    {
        return primerMax;
    }
    else
    {
        return segundoMax;
    }
}



int calcularPuntajeLanzamiento(int puntajes[][MAX_COMBINACIONES_GANADORAS], int dados[], int tam, int cantTiradas, int ronda,char nombres[][32],int jugador, int cantTiradasTotales[], bool* generalaServida) ///funcion return puntajes.
{
    int valordado[MAX_TAM_DADO],i;

    for (i=0; i < MAX_TAM_DADO; i++) ///Inicializa el vector espejo en 0
    {
        valordado[i]=0;
    }

    for (i=0; i < tam; i++) ///compara el vector si hay iguales.
    {
        valordado[dados[i]-1] = valordado[dados[i]-1] + 1;

    }


    int primerMax = calcularMaxRepeticiones(valordado, MAX_TAM_DADO, 1);
    int segundoMax = calcularMaxRepeticiones(valordado, MAX_TAM_DADO, 2);

    int opcion = 1;
    int puntajeEspejo[MAX_COMBINACIONES_GANADORAS][2];
    for (i=0; i < MAX_COMBINACIONES_GANADORAS; i++) ///Inicializa el vector espejo en 0
    {
        puntajeEspejo[i][0]=-1;
        puntajeEspejo[i][1]=-1;
    }
    if (puntajes[jugador-1][9] == -1 && primerMax == 5) /// si no había tirado generala y es generala.
    {
        // si es generala servida
        if(cantTiradas == 1)
        {
            cout<< "HAS SACADO GENERALA SERVIDA :)"<<endl;
            system("pause");
            clrscr();
            *generalaServida=true;
            for (int j = 0; j < MAX_COMBINACIONES_GANADORAS; j++)
            {
                puntajes[jugador-1][j] = 0;
            }
            puntajes[jugador-1][9] = 250;
            return cantTiradas;
        }
        else
        {
            cout<< "Opcion " << opcion++ << ": GENERALA >>> 50 puntos" <<endl;
            puntajeEspejo[9][0] = 50;
            puntajeEspejo[9][1] = 1;
        }
    }
    else if (puntajes[jugador-1][8] == -1 && primerMax == 4 && segundoMax==1) /// si no había tirado poker y es poker.
    {
        cout<< "Opcion " << opcion++ << ": POKER >>> 40 puntos" <<endl;
        puntajeEspejo[8][0] = 40;
        puntajeEspejo[8][1] = 1;
    }
    else if (puntajes[jugador-1][7] == -1 && primerMax == 3 && segundoMax == 2) /// si no había tirado full y es full
    {
        cout<< "Opcion " << opcion++ << ": FULL >>> 30 puntos" <<endl;
        puntajeEspejo[7][0] = 30;
        puntajeEspejo[7][1] = 1;
    }
    else if (puntajes[jugador-1][6] == -1 && primerMax == 1 && (valordado[0] == 0 || valordado[5] == 0)) /// si no había tirado escalera y es escalera
    {
        cout<< "Opcion " << opcion++ << ": ESCALERA >>> 25 puntos" <<endl;
        puntajeEspejo[6][0] = 25;
        puntajeEspejo[6][1] = 1;
    }

    juegosMenorPuntajes(puntajes,valordado,MAX_TAM_DADO,&opcion,puntajeEspejo,jugador); ///ponemos la funcion aca abajo para que en cualquier caso calcule los puntajes menores.

    if (cantTiradas == 3)
    {
        cout<< "Opcion " << opcion++ << ": TACHAR " <<endl;
        cout<<endl;
    }

    int opcionDeseada; ///el usuario elige puntaje

    // si hay opciones
    if (opcion > 1)
    {
        cout << endl << "Ingrese la opcion deseada: ";
        cin >> opcionDeseada;

        bool opcionDeseadaEncontrada = false;
        for (i = 0; i < MAX_COMBINACIONES_GANADORAS; i++)
        {
            if (opcionDeseada == puntajeEspejo[i][1])
            {
                opcionDeseadaEncontrada = true;
                puntajes[jugador-1][i] = puntajeEspejo[i][0];
            }
        }

        if (opcionDeseadaEncontrada == false)
        {
            system("cls");
            imprimirDetalleJugadores(puntajes,ronda,nombres,jugador,cantTiradas, cantTiradasTotales[jugador-1]);
            cout<< "Estas son tus opciones disponibles para tachar puntajes " <<endl;
            tacharOpcion (puntajes,jugador);
        }
    }
    // si no hay opciones y le quedan tiradas
    else if (cantTiradas < MAX_CANT_TIRADAS)
    {
        int cantDados=0,p;

        cout<< "No tenes puntajes disponibles para anotar, debes volver a lanzar" <<endl;

        cantTiradas++;
        if (cantTiradas<MAX_CANT_TIRADAS)
        {
            cout<< "Cuantos dados desea volver a tirar?" <<endl;
            cin>> cantDados;


            for(i=1; i<=cantDados; i++)
            {

                cout<< "Cuales dados?" <<endl;
                cin>> p;

                cargaParcialAleatorio(dados,p,cantDados,MAX_TAM_DADO);
            }
        }
        system("cls");
        imprimirDetalleJugadores(puntajes, ronda, nombres, jugador, cantTiradas, cantTiradasTotales[jugador-1]);
        imprimirDados(dados);
        calcularPuntajeLanzamiento(puntajes,dados,CANT_DADOS,cantTiradas,ronda,nombres,1, cantTiradasTotales, generalaServida);


    }




    system("cls");
    return cantTiradas;
}



void juegosMenorPuntajes (int puntajes[][MAX_COMBINACIONES_GANADORAS],int valordado[], int tam, int* opcion, int puntajeEspejo[][2],int jugador)
{
    int i;
    int multiplicacion=0;

    for(i=0; i < MAX_TAM_DADO; i++) //OTRAS OPCIONES PARA ANOTAR PUNTAJE.
    {
        multiplicacion= valordado[i]*(i+1);

        if (puntajes[jugador-1][i]==-1 && multiplicacion>0)
        {
            cout<<endl;
            cout<< "Opcion " << *opcion << ": " << multiplicacion << " pts al " << i+1 <<endl;
            puntajeEspejo[i][0] = multiplicacion;
            puntajeEspejo[i][1] = *opcion;

            (*opcion)++;
        }
    }
}

void tacharOpcion ( int puntajes[][MAX_COMBINACIONES_GANADORAS],int jugador)
{
    int i,opcion=1;
    int opcionTachablesPuntajes[MAX_COMBINACIONES_GANADORAS];
    for (i=0; i<MAX_COMBINACIONES_GANADORAS; i++)
    {
        opcionTachablesPuntajes[i]=-1; //inicializandolo en -1
        if (puntajes[jugador-1][i]==-1)
        {
            imprimirNombreOpc(i+1, opcion);
            opcionTachablesPuntajes[i]=opcion;

            opcion++;
        }
    }



    int opcionDeseada;

    cout << endl << "Ingrese la opcion deseada: ";
    cin >> opcionDeseada;


    for (i = 0; i < MAX_COMBINACIONES_GANADORAS; i++)
    {
        if (opcionDeseada == opcionTachablesPuntajes[i])
        {
            puntajes[jugador-1][i] = 0;
        }
    }



}

void imprimirNombreOpc(int jugada, int opcion)
{
    cout << opcion << ". ";
    switch (jugada)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:

        cout<< "Juego de " << jugada <<endl;
        break;

    case 7:
        cout<< "ESCALERA" <<endl;
        break;
    case 8:
        cout<< "FULL" <<endl;
        break;
    case 9:
        cout<< "POKER" <<endl;
        break;
    case 10:
        cout<< "GENERALA" <<endl;

        break;
    }

}


void cargarDadosManual(int dados[], int tam)
{
    int i;

    for(i=0; i<tam; i++)
    {
        dados[i]= 0;
    }

    for (i=0; i<tam; i++)
    {
        cout<<"Dado "<< i+1 <<": ";
        cin>> dados[i];
    }
}

int imprimirGanador (char nombres[][32],int puntajes[][MAX_COMBINACIONES_GANADORAS],int cantTiradasTotales[], int jugadores, int* puntajeMax, int* cantTiradasMax, char nombreMax[])
{
    imprimirRecuadro(26,4,65,13,12,71);
    gotoxy(37,8);
    cout<< "El juego ha finalizado" <<endl;
    int jugadorGanador;
    int puntajeJugador[2];
    puntajeJugador[0] = calcularTotalPuntajes(puntajes,1);
    puntajeJugador[1] = calcularTotalPuntajes(puntajes,2);
    if (jugadores == 1 || puntajeJugador[0] > puntajeJugador[1] || (puntajeJugador[0] == puntajeJugador[1] && cantTiradasTotales[0] < cantTiradasTotales[1]))
    {
        jugadorGanador = 1;
    }
    else
    {
        jugadorGanador = 2;
    }

    gotoxy(37,10);
    cout<< (char)173 << (char)173 << (char)173 << "Felicitaciones "<< nombres[jugadorGanador-1] <<" ganaste!!!" <<endl;
    gotoxy(37,11);
    cout<< "Puntaje total: " << puntajeJugador[jugadorGanador-1]<<" pts."<<endl;
    gotoxy(37,12);
    cout<< "Lanzamientos totales: " << cantTiradasTotales[jugadorGanador-1] <<endl<<endl<<endl<<endl<<endl<<endl<<endl;


    system("pause");
    clrscr();

    if (puntajeJugador[jugadorGanador-1] > *puntajeMax || (puntajeJugador[jugadorGanador-1] == *puntajeMax && cantTiradasTotales[jugadorGanador-1] < *cantTiradasMax))
    {
        *puntajeMax = puntajeJugador[jugadorGanador-1];
        *cantTiradasMax = cantTiradasTotales[jugadorGanador-1];
        strcpy(nombreMax, nombres[jugadorGanador-1]);
    }
    return jugadorGanador;
}

void imprimePuntajeMaximo (char nombreMax[], int puntajeMax, int cantTiradasMax)
{
    imprimirRecuadro(26,4,65,13,12,71);
    gotoxy(31,8);
    cout<< "Puntaje m" <<(char)160<< "ximo: " << puntajeMax <<" pts."<<endl;
    gotoxy(31,9);
    cout<< "Con un total de " << cantTiradasMax << " lanzamiento(s)"<<endl;
    gotoxy(31,10);
    cout<< "Nombre jugador: " << nombreMax <<endl;
}
