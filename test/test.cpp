//
// Created by cppgo on 2024/2/3.
//
#include "game/game.h"
#include "gtest/gtest.h"

/**
 * 冒烟测试
 */
TEST(冒烟测试, TEST_CASE1) {
    EXPECT_EQ(1, 1);
}

TEST(冒烟测试, TEST_CASE2) {
    EXPECT_EQ(1, 1);
    auto game = std::make_unique<Game>();
    game->Init("TEST", 100, 100);
    EXPECT_NE(game->Window(), nullptr);
}
