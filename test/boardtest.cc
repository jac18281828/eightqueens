#include "gtest/gtest.h"

#include "queen.h"
#include "board.h"

TEST(BoardTest, collisionTest) {

    queen::board board(8);

    queen::position_t solution;

    solution.push_back(0);

    for(int j=1; j<queen::HEIGHT; ++j) {
        solution.push_back(0);
        ASSERT_FALSE(board.is_safe(solution));
    }
    
}


TEST(BoardTest, collisionTest012) {

    queen::board board(8);

    queen::position_t solution;

    solution.push_back(0);
    solution.push_back(1);
    ASSERT_FALSE(board.is_safe(solution));
    solution.pop_back();
    solution.push_back(2);    
    ASSERT_TRUE(board.is_safe(solution));    
    
}

TEST(BoardTest, count92Test) {

    queen::board board(queen::HEIGHT);

    queen::position_t racked_queens;
    
    racked_queens.reserve(queen::HEIGHT);

    struct solution_counter: public queen::safe_handler {
        int solution_count = 0;

        virtual void on_safe(queen::position_t const& board) {
            solution_count++;
        }
    } handler;

    board.place(racked_queens, handler);

    ASSERT_EQ(92, handler.solution_count);

}
