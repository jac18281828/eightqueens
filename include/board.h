#pragma once

#include "queen.h"

namespace queen {


    board_t generate_view(int x, int y) {

        board_t board = 0UL;

        // entire row
        for(int i=0; i<WIDTH; ++i) {
            board |= project(i, y);
        }

        // entire column
        for(int j=0; j<HEIGHT; ++j) {
            board |= project(x, j);
        }

        // along 4 diagnols

        // upper left
        for(int i=x, j=y; i>0&&j>0; --i, --j) {
            board |= project(i, j);
        }

        // upper right
        for(int i=x, j=y; i<WIDTH&&j>0; ++i, --j) {
            board |= project(i, j);
        }

        // lower left
        for(int i=x, j=y; i>0&&j<HEIGHT; --i, ++j) {
            board |= project(i, j);
        }

        // lower right
        for(int i=x, j=y; i<WIDTH&&j<HEIGHT; ++i, ++j) {
            board |= project(i, j);
        }

        return board;

    }

}
