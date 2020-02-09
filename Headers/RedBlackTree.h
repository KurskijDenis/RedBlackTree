#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <map>
#include <stack>
#include <iostream>
#include <utility>

namespace RedBlackTree
{

template<typename KeyType, typename ValueType>
class RedBlackTree;

template<typename KeyType, typename ValueType>
class RedBlackTreeConstIterator;

template<typename KeyType, typename ValueType>
class RedBlackTreeIterator: public std::iterator<std::input_iterator_tag, std::pair<const KeyType, ValueType>>
{
public:
	RedBlackTreeIterator(typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* p, typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* end_p);
	RedBlackTreeIterator(const RedBlackTreeIterator &it);

	bool operator!=(const RedBlackTreeIterator& other) const;
	bool operator==(const RedBlackTreeIterator& other) const;

	bool operator!=(const RedBlackTreeConstIterator<KeyType, ValueType>& other) const;
	bool operator==(const RedBlackTreeConstIterator<KeyType, ValueType>& other) const;

	std::pair<const KeyType, ValueType>& operator*();
	RedBlackTreeIterator& operator++();
	RedBlackTreeIterator operator++(int);

private:
	friend RedBlackTreeConstIterator<KeyType, ValueType>;
	typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* p_;
	typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* const end_p_;
};

template<typename KeyType, typename ValueType>
class RedBlackTreeConstIterator: public std::iterator<std::input_iterator_tag, std::pair<const KeyType, ValueType>>
{
public:
	RedBlackTreeConstIterator(const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* p, const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* end_p);
	RedBlackTreeConstIterator(const RedBlackTreeIterator<KeyType, ValueType> &it);
	RedBlackTreeConstIterator(const RedBlackTreeConstIterator &it);

	bool operator!=(const RedBlackTreeConstIterator& other) const;
	bool operator==(const RedBlackTreeConstIterator& other) const;
	const std::pair<const KeyType, ValueType>& operator*() const;
	RedBlackTreeConstIterator& operator++();
	RedBlackTreeConstIterator operator++(int);

private:
	friend RedBlackTreeIterator<KeyType, ValueType>;
	const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* p_;
	const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* const end_p_;
};

template<typename KeyTp, typename ValueTp>
class RedBlackTree
{
public:
	using value_type = ValueTp;
	using key_type = KeyTp;

private:
enum class NodeColor
{
	Black,
	Red
};

enum class NodeSide
{
	Right,
	Left,
	None // only top
};

static std::string GetColorName(const NodeColor color);

struct RedBlackTreeNode
{
	RedBlackTreeNode(const key_type& key, const value_type& value);

	bool Equal(const key_type& value) const;
	bool Less(const key_type& value) const;
	bool More(const key_type& value) const;

	value_type& GetValue();
	const value_type& GetValue() const;
	std::pair<const key_type, value_type>& GetPair();
	const std::pair<const key_type, value_type>& GetPair() const;
	void SetValue(const value_type& value);

	void ChangeRightChild(std::unique_ptr<RedBlackTreeNode>&& node);
	void ChangeLeftChild(std::unique_ptr<RedBlackTreeNode>&& node);

	std::unique_ptr<RedBlackTreeNode> GetRightChild();
	std::unique_ptr<RedBlackTreeNode> GetLeftChild();

	void ResetRightChild();
	void ResetLeftChild();

	RedBlackTreeNode* GetRightChildRawPtr();
	const RedBlackTreeNode* GetRightChildRawPtr() const;
	RedBlackTreeNode* GetLeftChildRawPtr();
	const RedBlackTreeNode* GetLeftChildRawPtr() const;
	RedBlackTreeNode* GetGrandParent();
	RedBlackTreeNode* GetParent();
	const RedBlackTreeNode* GetParent() const;
	RedBlackTreeNode* GetUncle();
	RedBlackTreeNode* GetBrother();

	NodeColor GetColor() const;
	void SetColor(const NodeColor new_color);
	
	NodeSide GetSide() const;

	bool HasLeaf() const;
	bool HasAllLeafs() const;

	RedBlackTreeNode* GetMinSubNodeInRightSubTree();
	const RedBlackTreeNode* GetMinSubNodeInRightSubTree() const;
	RedBlackTreeNode* GetNextNode();
	const RedBlackTreeNode* GetNextNode() const;
	RedBlackTreeNode* GetMinNode();
	const RedBlackTreeNode* GetMinNode() const;

	void SetParent(RedBlackTreeNode* parent);

	std::pair<const key_type, value_type> node_info_;
	NodeColor color_ = NodeColor::Red;

	std::unique_ptr<RedBlackTreeNode> right_child_;
	std::unique_ptr<RedBlackTreeNode> left_child_;
	RedBlackTreeNode* parent_;

	friend std::ostream& operator<<(std::ostream& os, const RedBlackTreeNode& data)
	{
		os << data.node_info_.first << " " << data.node_info_.second;
		return os;
	}
};
	/*{
		os << data.node_info_.first << " " << data.node_info_.second;
		return os;
	}
	 {
		os << data.node_info_.first << " " << data.node_info_.second;
		return os;
	}*/
	friend RedBlackTreeIterator<key_type, value_type>;
	friend RedBlackTreeConstIterator<key_type, value_type>;

public:
	using iterator = RedBlackTreeIterator<key_type, value_type>;
	using const_iterator = RedBlackTreeConstIterator<key_type, value_type>;

public:
	RedBlackTree();
	/*RedBlackTree::RedBlackTree(const RedBlackTree& tree);
	RedBlackTree::operator=(const RedBlackTree& tree);


	RedBlackTree::RedBlackTree(RedBlackTree&& tree);
	RedBlackTree::operator=(RedBlackTree&& tree);*/

public:
	void DelElement(const key_type& new_value);
	void AddElement(const key_type& key_value, const value_type& new_value);

	void Print() const;
	bool CheckTree() const;

	iterator begin() const;
	iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

private:
	void DeleteLeaf(RedBlackTreeNode* node);
	void RecursiveDelete(RedBlackTreeNode* node);
	void FixTreeWhileDeleteNode(RedBlackTreeNode* const node);
	RedBlackTreeNode* ReplaceNodeToChildNode(RedBlackTreeNode* const node);

	void FixTreeAfterInsert(RedBlackTreeNode* node);

	void RightRotate(RedBlackTreeNode* const node);
	void LeftRotate(RedBlackTreeNode* const node);

	size_t GetBlackNodesInSubtree(const RedBlackTreeNode* node_ptr);

private:
	std::unique_ptr<RedBlackTreeNode> head_node_; 
	const std::unique_ptr<int> end_node_; 
};

#include "../Src/RedBlackTreeNode.inl"
#include "../Src/RedBlackTreeIterators.inl"
#include "../Src/RedBlackTree.inl"

} // namespace RedBlackTree