#pragma once

#include <bitset>
#include <vector>

namespace queen {

    const int MAX_QUEEN = 8;

    const int WIDTH = MAX_QUEEN;

    const int HEIGHT = MAX_QUEEN;

    const int N_SQUARE = WIDTH*HEIGHT;

    using board_t = std::bitset<N_SQUARE>;

    using position_t = std::vector<int>;

    inline int offset(int x, int y) {
        return y*WIDTH + x;
    }

    inline unsigned long project(int x, int y) {
        return 1UL<<offset(x, y);
    }

}
