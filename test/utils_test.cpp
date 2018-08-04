#include <gtest/gtest.h>

#include "../include/utils.h"

TEST(utils, epsilon){
    ASSERT_EQ(k_epsilon, 1E-6);
}

TEST(utils, equals){
    ASSERT_TRUE(equals(1.0, 1.000001));
    ASSERT_FALSE(equals(1.0, 1.0001));
}

