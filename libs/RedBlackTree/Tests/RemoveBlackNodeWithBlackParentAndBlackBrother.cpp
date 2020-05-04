#include <RedBlackTree.h>
#include <gtest/gtest.h>
#include "Utils.h"

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeLeftBrotherHaveAllChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(650, 650);
	tree.AddElement(800, 800);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({600,600,B}
					({nullptr})
					({650,650,R}
						({nullptr})
						({nullptr})
					)
				)
				({800,800,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(500);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeRightBrotherHaveAllChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);
	tree.AddElement(550, 550);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({500,500,B}
				({450,450,B}
					({nullptr})
					({nullptr})
				)
				({600,600,B}
					({550,550,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
			)
	))");

	tree.DelElement(700);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeLeftBrotherHaveLeftChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(650, 650);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({650,650,B}
				({600,600,B}
					({nullptr})
					({nullptr})
				)
				({700,700,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(500);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeRightBrotherHaveRightChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(550, 550);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({550,550,B}
				({500,500,B}
					({nullptr})
					({nullptr})
				)
				({600,600,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(700);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeLeftBrotherHaveRightChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(800, 800);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({600,600,B}
					({nullptr})
					({nullptr})
				)
				({800,800,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(500);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeRightBrotherHaveLeftChild)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({100,100,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({150,150,B}
						({nullptr})
						({nullptr})
					)
				)
				({300,300,B}
					({nullptr})
					({nullptr})
				)
			)
			({500,500,B}
				({450,450,B}
					({nullptr})
					({nullptr})
				)
				({600,600,B}
					({nullptr})
					({nullptr})
				)
			)
	))");

	tree.DelElement(700);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeLeftBrotherIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(800, 800);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);
	tree.DelElement(800);

	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({50,50,B}
					({25,25,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
				({150,150,B}
					({nullptr})
					({nullptr})
				)
			)
			({400,400,B}
				({300,300,B}
					({nullptr})
					({nullptr})
				)
				({600,600,B}
					({nullptr})
					({700,700,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree.DelElement(500);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string) << result_string;
}

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeRightBrotherIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);

	tree.AddElement(50, 50);
	tree.AddElement(150, 150);
	tree.AddElement(25, 25);
	tree.DelElement(450);

	const std::string expected_string = ConvertString(R"((
		{200,200,B}
			({100,100,B}
				({50,50,B}
					({25,25,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
				({150,150,B}
					({nullptr})
					({nullptr})
				)
			)
			({400,400,B}
				({300,300,B}
					({nullptr})
					({nullptr})
				)
				({600,600,B}
					({500,500,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
			)
	))");

	tree.DelElement(700);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeLeftParentLeftBrotherIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(50, 50);
	tree.AddElement(650, 650);
	tree.AddElement(800, 800);
	tree.AddElement(900, 900);

	tree.DelElement(50);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({400,400,B}
				({200,200,B}
					({nullptr})
					({300,300,R}
						({nullptr})
						({nullptr})
					)
				)
				({500,500,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({650,650,B}
					({nullptr})
					({nullptr})
				)
				({800,800,B}
					({nullptr})
					({900,900,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree.DelElement(100);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string) << result_string;
}

TEST(TestRemoveBlackNodeWithBlackParentAndBlackBrother, NodeRightParentLeftBrotherIsLeaf)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(100, 100);
	tree.AddElement(300, 300);
	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(50, 50);
	tree.AddElement(650, 650);
	tree.AddElement(800, 800);
	tree.AddElement(900, 900);

	tree.DelElement(50);

	const std::string expected_string = ConvertString(R"((
		{600,600,B}
			({400,400,B}
				({200,200,B}
					({100,100,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
				({500,500,B}
					({nullptr})
					({nullptr})
				)
			)
			({700,700,B}
				({650,650,B}
					({nullptr})
					({nullptr})
				)
				({800,800,B}
					({nullptr})
					({900,900,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree.DelElement(300);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string) << result_string;
}