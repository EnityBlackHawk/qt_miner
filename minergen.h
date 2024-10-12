#ifndef MINERGEN_H
#define MINERGEN_H
#include <QList>
#include <memory>
#include "matrix.h"
#include "space.h"

class MinerGen {
public:
    MinerGen( int w, int h );

   Matrix<std::unique_ptr<Space>> generate();



private:

    void increase_if_bombed( Space* space, int& counter );

    int _w;
    int _h;

};

#endif // MINERGEN_H
