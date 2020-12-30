#pragma once

#include <exception>
#include <vector>

#include "safe.h"
#include "queen.h"

namespace queen {

    inline board_t generate_view(int x, int y) {

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
        for(int i=x, j=y; i>=0&&j>=0; --i, --j) {
            board |= project(i, j);
        }

        // upper right
        for(int i=x, j=y; i<WIDTH&&j>=0; ++i, --j) {
            board |= project(i, j);
        }

        // lower left
        for(int i=x, j=y; i>=0&&j<HEIGHT; --i, ++j) {
            board |= project(i, j);
        }

        // lower right
        for(int i=x, j=y; i<WIDTH&&j<HEIGHT; ++i, ++j) {
            board |= project(i, j);
        }

        return board_t(board);

    }


    class board {
    private:
        const int n_queen;

        const int n_square = queen::WIDTH*queen::HEIGHT;

        std::vector<board_t> queen_view;
        
    public:
        board(const int n_queen) : n_queen(n_queen) {

            queen_view.reserve(N_SQUARE);
            
            if(n_queen > queen::MAX_QUEEN) {
                throw std::runtime_error("maximum number of queens is 8");
            };

            for(int i=0; i<queen::WIDTH; ++i) {
                for(int j=0; j<queen::HEIGHT; ++j) {
                    const auto offset = queen::offset(i, j);
            
                    queen_view[offset] = queen::generate_view(i, j);
                    
                    std::cout << "View at (" << i << ", " << j << ") is " << queen_view[offset] << std::endl;
                }
            }
        }

        bool is_safe(position_t const& board) {

            const auto v_off = board.size()-1;

            if(v_off > 0) {
                const auto h_off = board[v_off];
                const auto queen_pos = queen::project(h_off, v_off);
            
                for(int j=0; j<v_off; ++j) {
                    const auto i = board[j];
                    const auto ij_offset = queen::offset(i, j);
                    const auto& ij_view = queen_view[ij_offset];

                    board_t queen_set(queen_pos);

                    queen_set &= ij_view;

                    if(queen_set == queen_pos) {
                        return false;
                    }
                }
            }
            
            return true;
            
        }

        void place(position_t& board, safe_handler &handler) {

            if(board.size() == queen::HEIGHT) {
                handler.on_safe(board);
            } else {
                for(int i=0; i<queen::WIDTH; ++i) {
                    board.push_back(i);
                    if(is_safe(board)) {
                        place(board, handler);
                    }
                    board.pop_back();
                }
            }
        }
    };
}
        
