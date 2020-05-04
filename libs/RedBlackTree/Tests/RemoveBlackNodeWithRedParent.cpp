#include <RedBlackTree.h>
#include <gtest/gtest.h>
#include "Utils.h"

TEST(TestRemoveBlackNodeWithRedParent, NodeLeftBrotherIsLeaf)
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
		{400,400,B}
			({200,200,B}
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
	))");

	tree.DelElement(500);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedParent, NodeRightBrotherIsLeaf)
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
		{400,400,B}
			({200,200,B}
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
	))");

	tree.DelElement(700);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedParent, NodeLeftBrotherHaveAllLeafs)
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
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({650,650,R}
				({600,600,B}
					({nullptr})
					({nullptr})
				)
				({700,700,B}
					({nullptr})
					({800,800,R}
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

TEST(TestRemoveBlackNodeWithRedParent, NodeRightBrotherHaveAllLeafs)
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
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({550,550,R}
				({500,500,B}
					({450,450,R}
						({nullptr})
						({nullptr})
					)
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
	EXPECT_EQ(result_string, expected_string) << result_string;
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedParent, NodeLeftBrotherHaveLeftSon)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(650, 650);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({650,650,R}
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

TEST(TestRemoveBlackNodeWithRedParent, NodeRightBrotherHaveRightSon)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(550, 550);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({550,550,R}
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
	EXPECT_EQ(result_string, expected_string) << result_string;
}

//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedParent, NodeLeftBrotherHaveRightSon)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(800, 800);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({700,700,R}
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

TEST(TestRemoveBlackNodeWithRedParent, NodeRightBrotherHaveLeftSon)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);
	tree.AddElement(700, 700);

	tree.AddElement(450, 450);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,B}
				({nullptr})
				({nullptr})
			)
			({500,500,R}
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
	EXPECT_EQ(result_string, expected_string) << result_string;
}


//----------------------------------------------------------------------------------------------------------------------
TEST(TestRemoveBlackNodeWithRedParent, NodeLeftParentIsRoot)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);

	tree.DelElement(500);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({nullptr})
			({600,600,R}
				({nullptr})
				({nullptr})
			)
	))");

	tree.DelElement(200);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST(TestRemoveBlackNodeWithRedParent, NodeRightParentIsRoot)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree;

	tree.AddElement(400, 400);

	tree.AddElement(200, 200);
	tree.AddElement(600, 600);

	tree.AddElement(500, 500);

	tree.DelElement(500);

	const std::string expected_string = ConvertString(R"((
		{400,400,B}
			({200,200,R}
				({nullptr})
				({nullptr})
			)
			({nullptr})
	))");

	tree.DelElement(600);
	const auto result_string = tree.Print();
	EXPECT_EQ(result_string, expected_string) << result_string;
}