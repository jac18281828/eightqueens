#pragma once

namespace queen {

    using board_t = unsigned long;

    const int WIDTH = 8;

    const int HEIGHT = 8;

    inline board_t project(int x, int y) {
        const auto offset = y*WIDTH + x;

        return 1UL<<offset;
    }

}
