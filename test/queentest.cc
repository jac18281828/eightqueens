#include "gtest/gtest.h"

#include "queen.h"

TEST(QueenTest, OffsetXY) {

    ASSERT_EQ(0, queen::offset(0, 0));

    ASSERT_EQ(1, queen::offset(1, 0));

    ASSERT_EQ(queen::WIDTH, queen::offset(0, 1));

    ASSERT_EQ(queen::WIDTH+1, queen::offset(1, 1));
    
}

TEST(QueenTest, ProjectXY) {

    ASSERT_EQ(1, queen::project(0, 0));
    ASSERT_EQ(1 << queen::WIDTH, queen::project(0, 1));
    
}
