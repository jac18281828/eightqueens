#include "gtest/gtest.h"

#include "board.h"

TEST(ViewTest, TestEveryRowBlocked) {

    for(int j=0; j<queen::HEIGHT; ++j) {
        for(int i=0; i<queen::WIDTH; ++i) {
            const auto board = queen::generate_view(i, j);

            // test every row is blocked
            for(int k=0; k<queen::WIDTH; ++k) {
                const auto pos = queen::project(k, j);

                queen::board_t posvec(pos);

                posvec &= board;
                
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
    
}

TEST(ViewTest, TestEveryColBlocked) {

    for(int i=0; i<queen::WIDTH; ++i) {
        for(int j=0; j<queen::HEIGHT; ++j) {
            const auto board = queen::generate_view(i, j);

            // test every col is blocked
            for(int k=0; k<queen::HEIGHT; ++k) {
                const auto pos = queen::project(i, k);
                queen::board_t posvec(pos);

                posvec &= board;
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
}


TEST(ViewTest, TestEveryDiagULBlocked) {

    for(int i=0; i<queen::WIDTH; ++i) {
        for(int j=0; j<queen::HEIGHT; ++j) {
            const auto board = queen::generate_view(i, j);

            // test every diag is blocked
            for(int k=i, l=j; k>=0&&l>=0; --k, --l) {
                const auto pos = queen::project(k, l);
                queen::board_t posvec(pos);

                posvec &= board;
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
}

TEST(ViewTest, TestEveryDiagURBlocked) {

    for(int i=0; i<queen::WIDTH; ++i) {
        for(int j=0; j<queen::HEIGHT; ++j) {
            const auto board = queen::generate_view(i, j);

            // test every diag is blocked
            for(int k=i, l=j; k<queen::WIDTH&&l>=0; ++k, --l) {
                const auto pos = queen::project(k, l);
                queen::board_t posvec(pos);
                posvec &= board;
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
}

TEST(ViewTest, TestEveryDiagLLBlocked) {

    for(int i=0; i<queen::WIDTH; ++i) {
        for(int j=0; j<queen::HEIGHT; ++j) {
            const auto board = queen::generate_view(i, j);

            // test every diag is blocked
            for(int k=i, l=j; k>0&&l<queen::HEIGHT; --k, ++l) {
                const auto pos = queen::project(k, l);
                queen::board_t posvec(pos);
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
}

TEST(ViewTest, TestEveryDiagLRBlocked) {

    for(int i=0; i<queen::WIDTH; ++i) {
        for(int j=0; j<queen::HEIGHT; ++j) {
            const auto board = queen::generate_view(i, j);

            // test every diag is blocked
            for(int k=i, l=j; k<queen::WIDTH&&l<queen::HEIGHT; ++k, ++l) {
                const auto pos = queen::project(k, l);
                queen::board_t posvec(pos);
                ASSERT_TRUE(posvec == pos);
            }
        }
    }
}

TEST(ViewTest, ZeroNotMatchingSecondRow) {

    const auto board = queen::generate_view(0, 0);

    const auto pos = queen::project(1, 2);

    queen::board_t posvec(pos);

    posvec &= board;

    ASSERT_FALSE(posvec == pos);
}
