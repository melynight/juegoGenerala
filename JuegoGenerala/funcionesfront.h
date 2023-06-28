#ifndef FUNCIONESFRONT_H_INCLUDED
#define FUNCIONESFRONT_H_INCLUDED

#include <windows.h>




enum Color
{
    cNEGRO=0,
    cAZUL=1,
    cVERDE=2,
    cCIAN=3,
    cROJO=4,
    cMAGENTA=5,
    cMARRON=6,
    cGRIS_CLARO=7,
    cGRIS=8,
    cAZUL_CLARO=9,
    cVERDE_CLARO=10,
    cCIAN_CLARO=11,
    cROJO_CLARO=12,
    cMAGENTA_CLARO=13,
    cAMARILLO=14,
    cBLANCO=15
};

void imprimirDado(int dado, short iniX, short iniY);
void imprimirDados (int dados[]);
void imprimirRecuadro(short iniX, short iniY, short ancho, short alto, short colorLinea, short colorFondo);

void clrscr(void)
{
    system("cls");
}
void pause(void)
{
    system("pause >nul");
}
void gotoxy(short x, short y)
{
    COORD a;
    a.X = x;
    a.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void textcolor(short colorTexto=15, short colorFondo=0)
{
    short color = colorTexto + colorFondo * 16;
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color);
}





void imprimirRecuadro(short iniX, short iniY, short ancho, short alto, short colorLinea, short colorFondo)
{
    int i, j;
    for(i=iniX; i<=iniX+ancho; i++)
    {
        for(j=iniY; j<=iniY+alto; j++)
        {
            gotoxy(i, j);

            //Arriba izquierda
            if(i==iniX && j==iniY)
            {
                cout << (char) 201;
            }
            //Arriba derecha
            else if(i==iniX+ancho && j==iniY)
            {
                cout << (char) 187;
            }
            //Abajo izquierda
            else if(i==iniX && j==iniY+alto)
            {
                cout << (char) 200;
            }
            //Abajo derecha
            else if(i==iniX+ancho && j==iniY+alto)
            {
                cout << (char) 188;
            }
            //Lineas arriba y abajo
            else if(j==iniY || j==iniY+alto)
            {
                cout << (char) 205;
            }
            //Lineas izquierda y derecha
            else if(i==iniX || i==iniX+ancho)
            {
                cout << (char) 186;
            }
        }
    }
}
void imprimirPuntito(int posX, int posY)
{
    gotoxy(posX, posY);
    cout << (char) 254;
}


void imprimirDado(int dado, short iniX, short iniY)
{
    int i, j;
    short ancho = 10, alto = 4;
    for(i=iniX; i<=iniX+ancho; i++)
    {
        for(j=iniY; j<=iniY+alto; j++)
        {
            gotoxy(i, j);

            //Arriba izquierda
            if(i==iniX && j==iniY)
            {
                cout << (char) 201;
            }
            //Arriba derecha
            else if(i==iniX+ancho && j==iniY)
            {
                cout << (char) 187;
            }
            //Abajo izquierda
            else if(i==iniX && j==iniY+alto)
            {
                cout << (char) 200;
            }
            //Abajo derecha
            else if(i==iniX+ancho && j==iniY+alto)
            {
                cout << (char) 188;
            }
            //Lineas arriba y abajo
            else if(j==iniY || j==iniY+alto)
            {
                cout << (char) 205;
            }
            //Lineas izquierda y derecha
            else if(i==iniX || i==iniX+ancho)
            {
                cout << (char) 186;
            }
            //Dentro del recuadro
            else
            {
                switch(dado)
                {
                case 1:
                    imprimirPuntito(iniX + 5, iniY + 2);
                    break;
                case 2:
                    imprimirPuntito(iniX + 3, iniY + 3);
                    imprimirPuntito(iniX + 7, iniY + 1);
                    break;
                case 3:
                    imprimirPuntito(iniX + 3, iniY + 3);
                    imprimirPuntito(iniX + 5, iniY + 2);
                    imprimirPuntito(iniX + 7, iniY + 1);

                    break;
                case 4:
                    imprimirPuntito(iniX + 3, iniY + 1);
                    imprimirPuntito(iniX + 3, iniY + 3);
                    imprimirPuntito(iniX + 7, iniY + 1);
                    imprimirPuntito(iniX + 7, iniY + 3);
                    break;
                case 5:
                    imprimirPuntito(iniX + 3, iniY + 1);
                    imprimirPuntito(iniX + 3, iniY + 3);
                    imprimirPuntito(iniX + 5, iniY + 2);
                    imprimirPuntito(iniX + 7, iniY + 1);
                    imprimirPuntito(iniX + 7, iniY + 3);
                    break;
                case 6:
                    imprimirPuntito(iniX + 3, iniY + 1);
                    imprimirPuntito(iniX + 3, iniY + 2);
                    imprimirPuntito(iniX + 3, iniY + 3);
                    imprimirPuntito(iniX + 7, iniY + 1);
                    imprimirPuntito(iniX + 7, iniY + 2);
                    imprimirPuntito(iniX + 7, iniY + 3);

                    break;

                }

            }
        }
    }
}


void imprimirDados (int dados[])
{
    int i, posX = 5;
    for (i=0; i<CANT_DADOS; i++)
    {
        imprimirDado(dados[i],posX,3);
        posX = posX + 6 /* ancho */ + 6 /* espacio entre dados */;
        cout<<endl;
    }
}


#endif // FUNCIONESFRONT_H_INCLUDED
