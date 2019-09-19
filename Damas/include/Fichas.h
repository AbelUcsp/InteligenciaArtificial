#ifndef FICHAS_H
#define FICHAS_H


class Fichas
{
    public:
        int posx,posy;
        char color; ///0 red 1 blue
        //int posibilidades;
        Fichas(int x,int y,bool colo);
        virtual ~Fichas();

    protected:

    private:
};

#endif // FICHAS_H
