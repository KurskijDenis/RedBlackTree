#include <RedBlackTree.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream> 

class TestAscElementsOrder : public ::testing::Test
{
protected:
	static void SetUpTestCase();
	static void TearDownTestCase();

public:
	static RedBlackTree::RedBlackTree<size_t, std::string> tree_;
	static std::vector<std::string> values_;
	static const size_t size_;
};

class TestDescElementsOrder : public ::testing::Test
{
protected:
	static void SetUpTestCase();
	static void TearDownTestCase();

public:
	static RedBlackTree::RedBlackTree<size_t, std::string> tree_;
	static std::vector<std::string> values_;
	static const size_t size_;
};

class TestStRemoveElements : public ::testing::Test
{
protected:
	void SetUp();
	void TearDown();

public:
	RedBlackTree::RedBlackTree<size_t, std::string> tree_;
	std::vector<std::string> values_;
	const size_t size_ = 10;
};

std::vector<std::string> TestAscElementsOrder::values_;
RedBlackTree::RedBlackTree<size_t, std::string> TestAscElementsOrder::tree_;
const size_t TestAscElementsOrder::size_ = 10;

std::vector<std::string> TestDescElementsOrder::values_;
RedBlackTree::RedBlackTree<size_t, std::string> TestDescElementsOrder::tree_;
const size_t TestDescElementsOrder::size_ = 20;

void TestAscElementsOrder::SetUpTestCase()
{
	values_ = {"12", "23", "2", "32145", "456", "1", "0", "100000", "-10", "45"};
	for (size_t i = 0; i < size_; ++i)
	{
		tree_.AddElement(i, values_[i]);
	}
}

void TestAscElementsOrder::TearDownTestCase()
{}

void TestDescElementsOrder::SetUpTestCase()
{
	values_ = {"12", "12", "23", "23", "2", 
	           "2", "32145", "435", "456", "45",
	           "1", "-987", "0", "56", "100000",
			   "76865", "56","-10", "98", "45"};

	for (size_t i = size_, j = size_ - 1; i > 0; --i, --j)
	{
		tree_.AddElement(j, values_[j]);
	}
}

void TestDescElementsOrder::TearDownTestCase()
{}

void TestStRemoveElements::SetUp()
{
	values_ = {"12", "23", "2", "32145", "456", "1", "0", "100000", "-10", "45"};
	for (size_t i = 0; i < size_; ++i)
	{
		tree_.AddElement(i, values_[i]);
	}
}

void TestStRemoveElements::TearDown() {}

TEST_F(TestStRemoveElements, RemoveAscAllElementsInOrder)
{
	EXPECT_EQ(size_, tree_.GetSize());
	for (size_t i = 0; i < size_; ++i)
	{
		tree_.DelElement(i);
	}
	EXPECT_EQ(0, tree_.GetSize());
}

TEST_F(TestStRemoveElements, RemoveDescAllElementsOrder)
{
	EXPECT_EQ(size_, tree_.GetSize());
	for (size_t i = size_, j = size_ - 1; i > 0; --i, --j)
	{
		tree_.DelElement(j);
	}
	EXPECT_EQ(0, tree_.GetSize());
}

TEST_F(TestStRemoveElements, RemoveUnknownElements)
{
	EXPECT_EQ(size_, tree_.GetSize());
	for (size_t i = 2 * size_; i > size_; --i)
	{
		tree_.DelElement(i);
	}
	EXPECT_EQ(size_, tree_.GetSize());
}

TEST_F(TestStRemoveElements, RemoveSeveralElements)
{
	EXPECT_EQ(size_, tree_.GetSize());
	tree_.DelElement(4);
	tree_.DelElement(5);
	tree_.DelElement(1);
	tree_.DelElement(8);
	ASSERT_EQ(6, tree_.GetSize());
	const std::string expected_values[6] = {"12", "2", "32145", "0", "100000", "45"};
	size_t expected_keys[6] = {0, 2, 3, 6, 7, 9};
	size_t i = 0;
	for (const auto& pairs : tree_)
	{
		EXPECT_EQ(expected_keys[i], pairs.first);
		EXPECT_EQ(expected_values[i], pairs.second);
		++i;
	}
}

TEST_F(TestAscElementsOrder, KeysChecker)
{
	size_t i = 0;
	EXPECT_EQ(size_, tree_.GetSize());
	for (const auto& pairs : tree_)
	{
		EXPECT_EQ(i, pairs.first);
		++i;
	}
}

TEST_F(TestAscElementsOrder, ValuesChecker)
{
	size_t i = 0;
	EXPECT_EQ(size_, tree_.GetSize());
	for (const auto& pairs : tree_)
	{
		ASSERT_GE(size_, i);
		EXPECT_EQ(values_[i], pairs.second);
		++i;
	}
}

TEST_F(TestDescElementsOrder, KeysChecker)
{
	size_t i = 0;
	EXPECT_EQ(size_, tree_.GetSize());
	for (const auto& pairs : tree_)
	{
		EXPECT_EQ(i, pairs.first);
		++i;
	}
}

TEST_F(TestDescElementsOrder, ValuesChecker)
{
	size_t i = 0;
	EXPECT_EQ(size_, tree_.GetSize());
	for (const auto& pairs : tree_)
	{
		ASSERT_GE(size_, i);
		EXPECT_EQ(values_[i], pairs.second);
		++i;
	}
}

TEST(TestRandomElementsOrder, ValuesKeysChecker)
{
	const size_t size = 10;
	const size_t keys[size] = {23, 3, 2, 1, 54, 0, 1, 78, 96, 3};
	const size_t expect_keys[size - 2] = {0, 1, 2, 3, 23, 54, 78, 96};

	const std::string values[size] = { "12", "3", "15", "28", "92", 
	                                    "20", "32", "43", "4", "5"};
	const std::string  expect_values[size - 2] = {"20", "28", "15", "3", "12", "92", "43", "4"};
	RedBlackTree::RedBlackTree<size_t, std::string> tree;
	for (size_t i = 0; i < size; ++i)
	{
		tree.AddElement(keys[i], values[i]);
	}
	size_t i = 0;
	for (const auto& [key, value] : tree)
	{
		ASSERT_GE(size, i + 2);
		EXPECT_EQ(expect_keys[i], key);
		EXPECT_EQ(expect_values[i], value);
		++i;
	}
}

TEST(TestClearElements, ClearTree)
{
	const size_t size = 10;
	RedBlackTree::RedBlackTree<size_t, size_t> tree;
	for (size_t i = 0; i < size; ++i)
	{
		tree.AddElement(i, i);
	}

	EXPECT_EQ(tree.GetSize(), size);
	tree.Clear();
	EXPECT_EQ(tree.GetSize(), 0);
}
