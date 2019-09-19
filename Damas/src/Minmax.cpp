#include "Minmax.h"

void printTab(board tablero)
{
    for(size_t i = 0;i < tablero.size();++i)
    {
        cout<<"|";
        for(size_t j=0;j<tablero[i].size();++j)
        {
            cout<<tablero[7-i][j]<<"|";
        }
        cout<<endl;
    }
    cout<<endl;

}

vector<board> movimientos(board t,int x,int y, bool m)
{
    vector<board> resultado;
    board aux;
    if(m)
    {
        if(x-1>=0 && y-1>=0)
        {
            if(t[x-1][y-1]=='0')
            {
                aux = t;
                aux[x][y]='0';
                aux[x-1][y-1]='2';
                resultado.push_back(aux);
            }
        }
        if(x-1>=0 && y+1<=7)
        {
            if(t[x-1][y+1]=='0')
            {
                aux = t;
                aux[x][y] ='0';
                aux[x-1][y-1]='2';
                resultado.push_back(aux);
            }
        }
    }
    else
    {
        if(x+1<=7 && y-1>=0)
        {
            if(t[x+1][y-1]=='0')
            {
                aux = t;
                aux[x][y] = '0';
                aux[x+1][y-1] = '1';
                resultado.push_back(aux);
            }
        }
        if(x+1<=7 && y+1<=7)
        {
            if(t[x+1][y+1]=='0')
            {
                aux = t;
                aux[x][y]='0';
                aux[x+1][y+1]='1';
                resultado.push_back(aux);
            }
        }
    }
    return resultado;
}


vector<board> comer(board t,int x, int y,bool m)
{
    vector<board> resultado;
    board aux;
    if(m)
    {
        if(x-2>=0 && y-2>=0)
        {
            if(t[x-1][y-1]=='1' && t[x-2][y-2]=='0')
            {
                aux = t;
                aux[x][y] ='0';
                aux[x-1][y-1] ='0';
                aux[x-2][y-2] = '2';
                resultado.push_back(aux);
            }
        }
        if(x-2>=0 && y+2<=7)
        {
            if(t[x-1][y-1]=='1' && t[x-2][y-2]=='0')
            {
                aux = t;
                aux[x][y] ='0';
                aux[x-1][y-1] ='0';
                aux[x-2][y+2]='2';
                resultado.push_back(aux);
            }
        }
    }
    else
    {
        if(x+2<=7 && y-2>=0)
        {
            if(t[x+1][y+1]=='2' && t[x+2][y+2]=='0')
            {
                aux =t;
                aux[x][y] ='0';
                aux[x+1][y-1]='0';
                aux[x+2][y+2]='1';
                resultado.push_back(aux);
            }
        }
        if(x+2<=7 && y+2<=7)
        {
            if(t[x+1][y+1]=='2' && t[x+2][y+2]=='0')
            {
                aux = t;
                aux[x][y] = '0';
                aux [x+1][y+1] ='0';
                aux[x+2][y+2] ='1';
                resultado.push_back(aux);
            }
        }
    }
    return resultado;
}


Minmax::Minmax(board b,int pro,int mpro,bool m):key(b),profundidad(pro),Max(m),mProfundidad(mpro)
{
    vector<board> opcion1,opcion2,opciones;
    vector<board> aux;
    if(profundidad<mProfundidad)
    {
        for(int i=0;i<key.size();++i)
        {
            for(int j=0;j<key.size();++j)
            {
                if(Max)
                {
                    if(key[i][j]=='2')
                    {
                        aux = movimientos(key,i,j,Max);
                        for(int i=0;i<aux.size();++i)
                        {
                            opcion1.push_back(aux[i]);
                        }
                        aux = comer(key,i,j,Max);
                        for(int i=0;i<aux.size();++i)
                        {
                            opcion2.push_back(aux[i]);
                        }
                    }
                }
                else
                {
                    if(key[i][j]=='1')
                    {
                        aux = movimientos(key,i,j,Max);
                        for(int i=0;i<aux.size();++i)
                        {
                            opcion1.push_back(aux[i]);
                        }
                        aux = comer(key,i,j,Max);
                        for(int i =0;i<key.size();++i)
                        {
                            opcion2.push_back(aux[i]);
                        }
                    }
                }
            }
        }
    }
    if(opcion2.size()!=0)
    {
        opciones = opcion2;
    }
    else
    {
        opciones = opcion1;
    }
    for(int i =0;i<opciones.size();++i)
    {
        Minmax* m = new Minmax(opciones[i],profundidad+1,mProfundidad,!Max);
        hijos.push_back(m);
    }
}

void Minmax::evalua()
{
    if(hijos.size()==0)
    {
        int resultado =0;
        for(int i = 0;i<key.size();++i)
        {
            for(int j =0;j<key[i].size();++j)
            {
                if(key[i][j]=='1')
                {
                    --resultado;
                }
                if(key[i][j]=='2')
                {
                    ++resultado;
                }
            }
        }
        valor = resultado;
    }
    else
    {
        for(int i=0;i<hijos.size();++i)
        {
            hijos[i]->evalua();
        }
        if(Max)
        {
            int m = -10000,aux;
            for(int i =0;i<hijos.size();++i)
            {
                aux = hijos[i]->valor;
                if(aux>m)
                {
                    m =aux;
                }
            }
            valor = m;

        }
        else
        {
            int m =100000,aux;
            for(int i =0;i<hijos.size();++i)
            {
                aux = hijos[i]->valor;
                if(aux<m)
                {
                    m =aux;
                }
            }
            valor =m;
        }
    }
}

board Minmax::elegir()
{
    board resultado;
    int aux = 10000;
    for(int i=0;hijos.size();++i)
    {
        if(hijos[i]->valor>aux)
        {
            aux = hijos[i]->valor;
            resultado = hijos[i]->key;
        }
    }
    return resultado;
}

Minmax::~Minmax()
{
    //dtor
}














