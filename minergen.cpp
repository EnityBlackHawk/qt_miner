#include "minergen.h"
#include <random>
#include <memory>
#include "matrix.h"

MinerGen::MinerGen( int w, int h ) :
    _w( w ),
    _h( h ) {}

Matrix<std::unique_ptr<Space>> MinerGen::generate() {

    Matrix<std::unique_ptr<Space>> matrix(_w, _h);
    std::random_device dev;
    std::mt19937 rng( dev() );
    std::uniform_int_distribution dist( -1, 3 );


    for ( int i = 0; i < _w; i++ ) {
        for ( int j = 0; j < _h; j++ ) {
            matrix.push_at(i, j,  std::make_unique<Space>( dist(dev) == -1 ? -1 : 0, nullptr )  );
        }
    }


    for ( int i = 0; i < _w; i++ ) {
        for ( int j = 0; j < _h; j++ ) {
            std::vector<std::unique_ptr<Space>*> val = matrix.getBoundariesOf(i, j);

            if(matrix(i, j)->getValue() == BOMBED) {
                continue;
            }

            int count = std::count_if(val.begin(), val.end(), [](auto v) -> bool {
                return ((*v)->getValue() == -1);
            });

            matrix(i, j)->setValue(count);
        }
    }

    return matrix;

}


void MinerGen::increase_if_bombed( Space* space, int& counter ) {
    if ( space->getValue() == BOMBED ) {
        counter++;
    }
}
