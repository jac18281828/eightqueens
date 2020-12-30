#include <iostream>

#include <cstdlib>

#include "board.h"
#include "safe.h"

using namespace queen;

class solution_handler: public queen::safe_handler {

private:
    int solution_count;

public:
    solution_handler() : solution_count(0) {
    }

    virtual void on_safe(position_t const& board) {
        std::cout << "solution " << ++solution_count << ": " << std::endl;

        for(int j=0; j<board.size(); ++j) {

            const auto qpos = board[j];
        
            for(int i=0; i<qpos-1; ++i) {
                std::cout << "- ";
            }
        
            std::cout << "* ";
        
            for(int i=qpos; i<queen::WIDTH; ++i) {
                std::cout << "- ";
            }
        
            std::cout << std::endl;
        }
    }
};


int main(int argc, char* argv[]) {

    queen::board board(queen::HEIGHT);

    solution_handler print_handler;

    queen::position_t racked_queens;
    racked_queens.reserve(queen::HEIGHT);

    board.place(racked_queens, print_handler);

    return EXIT_SUCCESS;
}
