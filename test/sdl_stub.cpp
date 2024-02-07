#include <gtest/gtest.h>
#include <cstdio>

int main(int argc, char **argv) {
    printf_s("Running main from sdl_stub.cpp\n");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}