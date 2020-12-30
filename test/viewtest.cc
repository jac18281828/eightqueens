#include "gtest/gtest.h"

#include "board.h"

TEST(ViewTest, TestEveryColumnBlocked) {

    for(int j=0; j<queen::HEIGHT; ++j) {
        for(int i=0; i<queen::WIDTH; ++i) {
            const auto board = queen::generate_view(i, j);

            // test every column is blocked
            for(int k=0; k<queen::WIDTH; ++k) {
                const auto pos = queen::project(k, j);
                ASSERT_TRUE(pos & board != 0UL);
            }
        }
    }
}
