#include<cstdio>
#include"RectangleTest.hpp"
#include"UtilTest.hpp"
#include"QuadTreeTest.hpp"
#include"TileMapTest.hpp"

int main(int argc, char **argv) {
	//printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}