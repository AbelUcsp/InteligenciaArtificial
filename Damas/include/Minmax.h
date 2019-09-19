#ifndef MINMAX_H
#define MINMAX_H
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef vector<vector<char> > board;

class Minmax
{
        int profundidad,mProfundidad,valor;
        bool Max;
        board key;
        vector<Minmax*>hijos;
    public:

        Minmax(board b,int pro,int mpro,bool m);
        void evalua();
        board elegir();
        virtual ~Minmax();


};

#endif // MINMAX_H
