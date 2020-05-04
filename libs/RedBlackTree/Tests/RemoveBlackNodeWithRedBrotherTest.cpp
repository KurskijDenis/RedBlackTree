#include <RedBlackTree.h>
#include <gtest/gtest.h>
#include "Utils.h"

TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherHaveOnlySons)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(800, 800);

	tree.DelElement(800);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({400,400,B}
				({nullptr})
				({500,500,R}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({nullptr})
				({nullptr})
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherHaveOnlySons)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(50, 50);

	tree.DelElement(50);

	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({nullptr})
				({nullptr})
			)
			({400,400,B}
				({300,300,R}
					({nullptr})
					({nullptr})
				)
				({nullptr})
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherHaveAllGrandsons)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);
	tree.AddElement(550, 550);
	tree.AddElement(650, 650);
	tree.AddElement(800, 800);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({500,500,R}
				({400,400,B}
					({nullptr})
					({450,450,R}
						({nullptr})
						({nullptr})
					)
				)
				({550,550,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({650,650,R}
					({nullptr})
					({nullptr})
				)
				({800,800,R}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherHaveAllGrandsons)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(250, 250);
	tree.AddElement(350, 350);


	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({50,50,R}
					({nullptr})
					({nullptr})
				)
				({150,150,R}
					({nullptr})
					({nullptr})
				)
			)
			({300,300,R}
				({250,250,B}
					({nullptr})
					({nullptr})
				)
				({400,400,B}
					({350,350,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherLeftSonIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(650, 650);
	tree.AddElement(800, 800);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({400,400,B}
				({nullptr})
				({500,500,R}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({650,650,R}
					({nullptr})
					({nullptr})
				)
				({800,800,R}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherRightSonIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);


	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({50,50,R}
					({nullptr})
					({nullptr})
				)
				({150,150,R}
					({nullptr})
					({nullptr})
				)
			)
			({400,400,B}
				({300,300,R}
					({nullptr})
					({nullptr})
				)
				({nullptr})
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherRightSonIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);
	tree.AddElement(550, 550);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({500,500,R}
				({400,400,B}
					({nullptr})
					({450,450,R}
						({nullptr})
						({nullptr})
					)
				)
				({550,550,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({nullptr})
				({nullptr})
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherLeftSonIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(250, 250);
	tree.AddElement(350, 350);


	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({nullptr})
				({nullptr})
			)
			({300,300,R}
				({250,250,B}
					({nullptr})
					({nullptr})
				)
				({400,400,B}
					({350,350,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherRightSonIsLeafLeftSonHasLeftChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({450,450,R}
				({400,400,B}
					({nullptr})
					({nullptr})
				)
				({500,500,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({nullptr})
				({nullptr})
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherLeftSonIsLeafLeftSonHasRightChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(350, 350);


	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({nullptr})
				({nullptr})
			)
			({350,350,R}
				({300,300,B}
					({nullptr})
					({nullptr})
				)
				({400,400,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftBrotherRightSonIsLeafLeftSonHasRightChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(550, 550);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({500,500,R}
				({400,400,B}
					({nullptr})
					({nullptr})
				)
				({550,550,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({nullptr})
				({nullptr})
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightBrotherLeftSonIsLeafLeftSonHasLeftChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);

	tree.AddElement(250, 250);


	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({nullptr})
				({nullptr})
			)
			({300,300,R}
				({250,250,B}
					({nullptr})
					({nullptr})
				)
				({400,400,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}
//----------------------------------------------------------------------------------------------------------------------

TEST(TestRemoveBlackNodeWithRedBrother, NodeLeftParentNotRoot)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(30, 30);

	tree.AddElement(15, 15);
	tree.AddElement(400, 400);

	tree.AddElement(7, 7);
	tree.AddElement(18, 18);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(700, 700);

	tree.AddElement(16, 16);
	tree.AddElement(19, 19);
	tree.AddElement(20, 20);

	tree.AddElement(500, 500);
	tree.AddElement(550, 550);

	const std::string expected_string = ConvertString(R"((
		{30,30,B}
			({15,15,B}
				({7,7,B}
					({nullptr})
					({nullptr})
				)
				({18,18,R}
					({16,16,B}
						({nullptr})
						({nullptr})
					)
					({19,19,B}
						({nullptr})
						({20,20,R}
							({nullptr})
							({nullptr})
						)
					)
				)
			)
			({600,600,B}
				({500,500,R}
					({400,400,B}
						({nullptr})
						({nullptr})
					)
					({550,550,B}
						({nullptr})
						({nullptr})
					)
				)
				({700,700,B}
					({nullptr})
					({nullptr})
				)
			)
	))");
	tree.DelElement(200);

	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string) << result_string;
}

TEST(TestRemoveBlackNodeWithRedBrother, NodeRightParentNotRoot)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;
	tree.AddElement(1000, 1000);

	tree.AddElement(1500, 1500);
	tree.AddElement(400, 400);

	tree.AddElement(1250, 1250);
	tree.AddElement(2000, 2000);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);

	tree.AddElement(1150, 1150);
	tree.AddElement(1350, 1350);
	tree.AddElement(1100, 1100);

	tree.AddElement(300, 300);
	tree.AddElement(250, 250);

	const std::string expected_string = ConvertString(R"((
		{1000,1000,B}
			({200,200,B}
				({100,100,B}
					({nullptr})
					({nullptr})
				)
				({300,300,R}
					({250,250,B}
						({nullptr})
						({nullptr})
					)
					({400,400,B}
						({nullptr})
						({nullptr})
					)
				)
			)
			({1500,1500,B}
				({1250,1250,R}
					({1150,1150,B}
						({1100,1100,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({1350,1350,B}
						({nullptr})
						({nullptr})
					)
				)
				({2000,2000,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}