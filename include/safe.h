#pragma once

#include "queen.h"

namespace queen {

    class safe_handler {
    public:
        virtual void on_safe(queen::position_t const& solution) = 0;
    };

}
