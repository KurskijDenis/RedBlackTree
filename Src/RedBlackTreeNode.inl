
template<typename KeyType, typename ValueType>
RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::RedBlackTreeNode(const KeyType& key, const ValueType& value)
	: node_info_(std::make_pair(key, value))
{}

template<typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::Equal(const KeyType& key) const
{
	return node_info_.first == key;
}

template<typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::Less(const KeyType& key) const
{
	return node_info_.first < key;
}

template<typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::More(const KeyType& key) const
{
	return node_info_.first > key;
}

template<typename KeyType, typename ValueType>
ValueType& RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetValue()
{
	return node_info_.second;
}

template<typename KeyType, typename ValueType>
const ValueType& RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetValue() const
{
	return node_info_.second;
}


template<typename KeyType, typename ValueType>
std::pair<const KeyType, ValueType>& RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetPair()
{
	return node_info_;
}

template<typename KeyType, typename ValueType>
const std::pair<const KeyType, ValueType>& RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetPair() const
{
	return node_info_;
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::SetValue(const ValueType& value)
{
	node_info_.second = value;
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::ChangeRightChild(std::unique_ptr<RedBlackTreeNode>&& node)
{
	right_child_ = std::move(node);
	if (right_child_)
	{
		right_child_->SetParent(this);
	}
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::ChangeLeftChild(std::unique_ptr<RedBlackTreeNode>&& node)
{
	left_child_ = std::move(node);
	if (left_child_)
	{
		left_child_->SetParent(this);
	}
}

template<typename KeyType, typename ValueType>
std::unique_ptr<typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode> RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetRightChild()
{
	if (!right_child_)
	{
		return nullptr;
	}
	right_child_->SetParent(nullptr);
	return std::move(right_child_);
}

template<typename KeyType, typename ValueType>
std::unique_ptr<typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode> RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetLeftChild()
{
	if (!left_child_)
	{
		return nullptr;
	} 
	left_child_->SetParent(nullptr);
	return std::move(left_child_);
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::ResetRightChild()
{
	if (right_child_)
	{
		right_child_.reset();
	}
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::ResetLeftChild()
{
	if (left_child_)
	{
		left_child_.reset();
	}
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetRightChildRawPtr()
{
	if (!right_child_)
	{
		return nullptr;
	}
	return right_child_.get();
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetRightChildRawPtr() const
{
	if (!right_child_)
	{
		return nullptr;
	}
	return right_child_.get();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetLeftChildRawPtr()
{
	if (!left_child_)
	{
		return nullptr;
	} 
	return left_child_.get();
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetLeftChildRawPtr() const
{
	if (!left_child_)
	{
		return nullptr;
	} 
	return left_child_.get();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetParent()
{
	return parent_;
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetParent() const
{
	return parent_;
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetGrandParent()
{
	if (parent_ == nullptr)
	{
		return nullptr;
	}
	return parent_->GetParent();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetUncle()
{
	const auto grand_parent = GetGrandParent();
	if (grand_parent == nullptr)
	{
		return nullptr;
	}

	const auto parent_side = parent_->GetSide();
	if (parent_side == NodeSide::Left)
	{
		return grand_parent->GetRightChildRawPtr();
	}

	assert(parent_side == NodeSide::Right);
	return grand_parent->GetLeftChildRawPtr();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetBrother()
{
	if (parent_ == nullptr)
	{
		return nullptr;
	}

	const auto side = GetSide();
	if (side == NodeSide::Left)
	{
		return parent_->GetRightChildRawPtr();
	}

	assert(side == NodeSide::Right);
	return parent_->GetLeftChildRawPtr();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::NodeColor RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetColor() const
{
	return color_;
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::SetColor(const NodeColor new_color)
{
	color_ = new_color;
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::NodeSide RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetSide() const
{
	if (parent_ == nullptr)
	{
		return NodeSide::None;
	}
	return parent_->GetLeftChildRawPtr() == this ? NodeSide::Left : NodeSide::Right;
}

template<typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::HasLeaf() const
{
	return left_child_ || right_child_;
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetMinSubNodeInRightSubTree()
{
	if (!right_child_)
	{
		return nullptr; 
	}

	RedBlackTreeNode* result = right_child_.get();
	while(result != nullptr)
	{
		const auto left_child = result->GetLeftChildRawPtr();
		if (left_child != nullptr)
		{
			result = left_child;
			continue;
		}
		return result;
	}

	return nullptr; 
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetMinSubNodeInRightSubTree() const
{
	if (!right_child_)
	{
		return nullptr; 
	}

	const RedBlackTreeNode* result = right_child_.get();
	while(result != nullptr)
	{
		const auto left_child = result->GetLeftChildRawPtr();
		if (left_child != nullptr)
		{
			result = left_child;
			continue;
		}
		return result;
	}

	return nullptr; 
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetNextNode()
{
	const auto new_node = GetMinSubNodeInRightSubTree();
	if (new_node != nullptr)
	{
		return new_node;
	}

	if (GetSide() == NodeSide::Right)
	{
		auto result = GetParent();
		while(result != nullptr)
		{
			if (result->GetSide() == NodeSide::Left)
			{
				return result->GetParent();
			}
			result = result->GetParent();
		}
		return result;
	}
	
	return GetParent();
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetNextNode() const
{
	const auto new_node = GetMinSubNodeInRightSubTree();
	if (new_node != nullptr)
	{
		return new_node;
	}

	if (GetSide() == NodeSide::Right)
	{
		const auto* result = GetParent();
		while(result != nullptr)
		{
			if (result->GetSide() == NodeSide::Left)
			{
				return result->GetParent();
			}
			result = result->GetParent();
		}
		return result;
	}
	
	return GetParent();
}

template<typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetMinNode()
{
	RedBlackTreeNode* result = this;
	while(result != nullptr)
	{
		const auto left_child = result->GetLeftChildRawPtr();
		if (left_child == nullptr)
		{
			break;
		}
		result = left_child;
	}
	assert(result != nullptr);
	return result;
}

template<typename KeyType, typename ValueType>
const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::GetMinNode() const 
{
	RedBlackTreeNode* result = this;
	while(result != nullptr)
	{
		const auto left_child = result->GetLeftChildRawPtr();
		if (left_child == nullptr)
		{
			break;
		}
		result = left_child;
	}
	assert(result != nullptr);
	return result;
}

template<typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::HasAllLeafs() const
{
	return left_child_ && right_child_;
}

template<typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::RedBlackTreeNode::SetParent(RedBlackTreeNode* parent)
{
	parent_ = parent;
}