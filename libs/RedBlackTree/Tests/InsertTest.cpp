#include <RedBlackTree.h>
#include <gtest/gtest.h>
#include "Utils.h"

class TestInsertElements : public ::testing::Test
{
protected:
	void SetUp();
	void TearDown();

public:
	RedBlackTree::RedBlackTree<size_t, size_t> tree_;
};
void TestInsertElements::SetUp()
{
	tree_.AddElement(130, 130);

	tree_.AddElement(120, 120);
	tree_.AddElement(140, 140);
	
	tree_.AddElement(110, 110);
	tree_.AddElement(125, 125);
	tree_.AddElement(135, 135);
	tree_.AddElement(150, 150);
	
	tree_.AddElement(101, 101);
	tree_.AddElement(115, 115);
	tree_.AddElement(122, 122);
	tree_.AddElement(128, 128);
	tree_.AddElement(133, 133);
	tree_.AddElement(137, 137);
	tree_.AddElement(145, 145);
	tree_.AddElement(160, 160);

	tree_.AddElement(103, 103);
	tree_.AddElement(134, 134);
}

void TestInsertElements::TearDown()
{}

TEST(InsertTest, OneElement)
{
	RedBlackTree::RedBlackTree<size_t, size_t> tree_;
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({nullptr})
			({nullptr})
		))");

	tree_.AddElement(130, 130);
	const auto print_string = tree_.Print();
	EXPECT_EQ(expected_string, print_string);
}

TEST(InsertTest, ChangeHeadElementAsc)
{

	RedBlackTree::RedBlackTree<size_t, size_t> tree_;
	tree_.AddElement(0, 0);
	tree_.AddElement(1, 1);
	tree_.AddElement(2, 2);
	tree_.AddElement(3, 3);
	tree_.AddElement(4, 4);
	tree_.AddElement(5, 5);
	tree_.AddElement(6, 6);
	tree_.AddElement(7, 7);

	const std::string expected_string = ConvertString(R"((
		{3,3,B}
			({1,1,R}
				({0,0,B}
					({nullptr})
					({nullptr})
				)
				({2,2,B}
					({nullptr})
					({nullptr})
				)
			)
			({5,5,R}
				({4,4,B}
					({nullptr})
					({nullptr})
				)
				({6,6,B}
					({nullptr})
					({7,7,R}
						({nullptr})
						({nullptr})
					)
				)
			)
		))");

	const auto print_string = tree_.Print();
	EXPECT_EQ(expected_string, print_string);
}

TEST(InsertTest, ChangeHeadElementDesc)
{

	RedBlackTree::RedBlackTree<size_t, size_t> tree_;
	tree_.AddElement(7, 7);
	tree_.AddElement(6, 6);
	tree_.AddElement(5, 5);
	tree_.AddElement(4, 4);
	tree_.AddElement(3, 3);
	tree_.AddElement(2, 2);
	tree_.AddElement(1, 1);
	tree_.AddElement(0, 0);

	const std::string expected_string = ConvertString(R"((
		{4,4,B}
			({2,2,R}
				({1,1,B}
					({0,0,R}
						({nullptr})
						({nullptr})
					)
					({nullptr})
				)
				({3,3,B}
					({nullptr})
					({nullptr})
				)
			)
			({6,6,R}
				({5,5,B}
					({nullptr})
					({nullptr})
				)
				({7,7,B}
					({nullptr})
					({nullptr})
				)
			)
		))");

	const auto print_string = tree_.Print();
	EXPECT_EQ(expected_string, print_string) << print_string;
}

TEST_F(TestInsertElements, CheckBuildedTree)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");
	const auto result_string = tree_.Print();
	EXPECT_EQ(result_string, expected_string);
}

TEST_F(TestInsertElements, ParentBlack)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({100,100,R}
							({nullptr})
							({nullptr})
						)
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B}
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree_.AddElement(100, 100);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string)<< result_string;
}

TEST_F(TestInsertElements, ParentAndUncleRedLeftLeft)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,R}
					({122,122,B}
						({121,121,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({128,128,B}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");
	tree_.AddElement(121, 121);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentAndUncleRedLeftRight)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,R}
					({122,122,B}
						({nullptr})
						({123,123,R}
							({nullptr})
							({nullptr})
						)
					)
					({128,128,B}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree_.AddElement(123, 123);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentAndUncleRedRightLeft)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,R}
					({122,122,B}
						({nullptr})
						({nullptr})
					)
					({128,128,B}
						({126,126,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree_.AddElement(126, 126);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentAndUncleRedRightRight)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,R}
					({122,122,B}
						({nullptr})
						({nullptr})
					)
					({128,128,B}
						({nullptr})
						({129,129,R}
							({nullptr})
							({nullptr})
						)
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree_.AddElement(129, 129);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentRedUncleRedRecursive)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({110,110,B}
				({101,101,R}
					({50,50,B}
						({25,25,R}
							({nullptr})
							({nullptr})
						)
						({nullptr})
					)
					({103,103,B}
						({nullptr})
						({nullptr})
					)
				)
				({120,120,R}
					({115,115,B}
						({nullptr})
						({nullptr})
					)
					({125,125,B}
						({122,122,R}
							({nullptr})
							({nullptr})
						)
						({128,128,R}
							({nullptr})
							({nullptr})
						)
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,B}
					({145,145,R}
						({nullptr})
						({nullptr})
					)
					({160,160,R}
						({nullptr})
						({nullptr})
					)
				)
			)
	))");

	tree_.AddElement(50, 50);
	tree_.AddElement(25, 25);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentRedUncleBlackRightRotate)
{
	const std::string expected_string = ConvertString(R"((
	{130,130,B}
		({110,110,B}
			({101,101,R}
				({25,25,B}
					({12,12,R}
							({nullptr})
							({nullptr})
					)
					({50,50,R}
						({nullptr})
						({nullptr})
					)
				)
				({103,103,B}
					({nullptr})
					({nullptr})
				)
			)
			({120,120,R}
				({115,115,B}
					({nullptr})
					({nullptr})
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
		)
		({140,140,B}
			({135,135,R}
				({133,133,B} 
					({nullptr})
					({134,134,R}
						({nullptr})
						({nullptr})
					)
				)
				({137,137,B}
					({nullptr})
					({nullptr})
				)
			)
			({150,150,B}
				({145,145,R}
					({nullptr})
					({nullptr})
				)
				({160,160,R}
					({nullptr})
					({nullptr})
				)
			)
		)
	))");

	tree_.AddElement(50, 50);
	tree_.AddElement(25, 25);
	tree_.AddElement(12, 12);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentRedUncleBlackLeftRotate)
{
	const std::string expected_string = ConvertString(R"((
	{130,130,B}
		({110,110,B}
			({101,101,R}
				({28,28,B}
					({25,25,R}
							({nullptr})
							({nullptr})
					)
					({50,50,R}
						({nullptr})
						({nullptr})
					)
				)
				({103,103,B}
					({nullptr})
					({nullptr})
				)
			)
			({120,120,R}
				({115,115,B}
					({nullptr})
					({nullptr})
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
		)
		({140,140,B}
			({135,135,R}
				({133,133,B} 
					({nullptr})
					({134,134,R}
						({nullptr})
						({nullptr})
					)
				)
				({137,137,B}
					({nullptr})
					({nullptr})
				)
			)
			({150,150,B}
				({145,145,R}
					({nullptr})
					({nullptr})
				)
				({160,160,R}
					({nullptr})
					({nullptr})
				)
			)
		)
	))");

	tree_.AddElement(50, 50);
	tree_.AddElement(25, 25);
	tree_.AddElement(28, 28);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentRedUncleBlackLeftRotateRightSubtree)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,R}
					({145,145,B}
						({nullptr})
						({nullptr})
					)
					({200,200,B}
						({160,160,R}
							({nullptr})
							({nullptr})
						)
						({240,240,R}
							({nullptr})
							({nullptr})
						)
					)
				)
			)
	))");

	tree_.AddElement(200, 200);
	tree_.AddElement(240, 240);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}

TEST_F(TestInsertElements, ParentRedUncleBlackRightRotateRightSubtree)
{
	const std::string expected_string = ConvertString(R"((
		{130,130,B}
			({120,120,B}
				({110,110,R}
					({101,101,B}
						({nullptr})
						({103,103,R}
							({nullptr})
							({nullptr})
						)
					)
					({115,115,B}
						({nullptr})
						({nullptr})
					)
				)
				({125,125,B}
					({122,122,R}
						({nullptr})
						({nullptr})
					)
					({128,128,R}
						({nullptr})
						({nullptr})
					)
				)
			)
			({140,140,B}
				({135,135,R}
					({133,133,B} 
						({nullptr})
						({134,134,R}
							({nullptr})
							({nullptr})
						)
					)
					({137,137,B}
						({nullptr})
						({nullptr})
					)
				)
				({150,150,R}
					({145,145,B}
						({nullptr})
						({nullptr})
					)
					({180,180,B}
						({160,160,R}
							({nullptr})
							({nullptr})
						)
						({200,200,R}
							({nullptr})
							({nullptr})
						)
					)
				)
			)
	))");

	tree_.AddElement(200, 200);
	tree_.AddElement(180, 180);
	const auto result_string = tree_.Print();
	EXPECT_EQ(expected_string, result_string);
}