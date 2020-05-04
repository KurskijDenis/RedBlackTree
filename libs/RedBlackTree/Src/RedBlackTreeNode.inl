
template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::RedBlackTreeNode(const KeyType& key, const ValueType& value)
	: node_info_(std::make_pair(key, value))
{}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::Equal(const KeyType& key) const
{
	return !comp_(node_info_.first, key) && !comp_(key, node_info_.first);
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::Less(const KeyType& key) const
{
	return comp_(node_info_.first, key);
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::More(const KeyType& key) const
{
	return comp_(key, node_info_.first);
}

template<typename KeyType, typename ValueType, typename Comparator>
ValueType& RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetValue()
{
	return node_info_.second;
}

template<typename KeyType, typename ValueType, typename Comparator>
const ValueType& RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetValue() const
{
	return node_info_.second;
}


template<typename KeyType, typename ValueType, typename Comparator>
std::pair<const KeyType, ValueType>& RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetPair()
{
	return node_info_;
}

template<typename KeyType, typename ValueType, typename Comparator>
const std::pair<const KeyType, ValueType>& RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetPair() const
{
	return node_info_;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::SetValue(const ValueType& value)
{
	node_info_.second = value;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::ChangeChild(std::unique_ptr<RedBlackTreeNode>&& node, const NodeSide side)
{
	if (side == NodeSide::None)
	{
		return;
	}

	if (side == NodeSide::Right)
	{
		ChangeRightChild(std::move(node));
	}
	else
	{
		ChangeLeftChild(std::move(node));
	}
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::SwapColorWithChilds(RedBlackTreeNode& node)
{
	if (&node == this)
	{
		return;
	}

	auto right_child_node = node.GetRightChild();
	auto left_child_node = node.GetLeftChild();
	std::swap(node.color_, color_);
	
	node.ChangeRightChild(GetRightChild());
	node.ChangeLeftChild(GetLeftChild());
	ChangeRightChild(std::move(right_child_node));
	ChangeLeftChild(std::move(left_child_node));
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::SwapNodes(RedBlackTreeNode& node)
{
	if (&node == this)
	{
		return;
	}
	SwapColorWithChilds(node);

	const auto node_side = node.GetSide();
	auto this_side = GetSide();

	if (node_side == NodeSide::None || this_side == NodeSide::None)
	{
		assert(false);
		return;
	}
	auto* parent = parent_;
	auto* node_parent = node.parent_;

	auto this_u_ptr = this_side == NodeSide::Right ? parent->GetRightChild() : parent->GetLeftChild();
	auto node_u_ptr = node_side == NodeSide::Right ? node_parent->GetRightChild() : node_parent->GetLeftChild();

	parent->ChangeChild(std::move(node_u_ptr), this_side);
	node_parent->ChangeChild(std::move(this_u_ptr), node_side);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::ChangeRightChild(std::unique_ptr<RedBlackTreeNode>&& node)
{
	right_child_ = std::move(node);
	if (right_child_)
	{
		right_child_->SetParent(this);
	}
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::ChangeLeftChild(std::unique_ptr<RedBlackTreeNode>&& node)
{
	left_child_ = std::move(node);
	if (left_child_)
	{
		left_child_->SetParent(this);
	}
}

template<typename KeyType, typename ValueType, typename Comparator>
std::unique_ptr<typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode> RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetRightChild()
{
	if (!right_child_)
	{
		return nullptr;
	}
	right_child_->SetParent(nullptr);
	return std::move(right_child_);
}

template<typename KeyType, typename ValueType, typename Comparator>
std::unique_ptr<typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode> RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetLeftChild()
{
	if (!left_child_)
	{
		return nullptr;
	} 
	left_child_->SetParent(nullptr);
	return std::move(left_child_);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::ResetRightChild()
{
	if (right_child_)
	{
		right_child_.reset();
	}
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::ResetLeftChild()
{
	if (left_child_)
	{
		left_child_.reset();
	}
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetRightChildRawPtr()
{
	if (!right_child_)
	{
		return nullptr;
	}
	return right_child_.get();
}

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetRightChildRawPtr() const
{
	if (!right_child_)
	{
		return nullptr;
	}
	return right_child_.get();
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetLeftChildRawPtr()
{
	if (!left_child_)
	{
		return nullptr;
	} 
	return left_child_.get();
}

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetLeftChildRawPtr() const
{
	if (!left_child_)
	{
		return nullptr;
	} 
	return left_child_.get();
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetParent()
{
	return parent_;
}

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetParent() const
{
	return parent_;
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetGrandParent()
{
	if (parent_ == nullptr)
	{
		return nullptr;
	}
	return parent_->GetParent();
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetUncle()
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

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetBrother()
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

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::NodeColor RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetColor() const
{
	return color_;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::SetColor(const NodeColor new_color)
{
	color_ = new_color;
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::NodeSide RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetSide() const
{
	if (parent_ == nullptr)
	{
		return NodeSide::None;
	}
	return parent_->GetLeftChildRawPtr() == this ? NodeSide::Left : NodeSide::Right;
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::HasLeaf() const
{
	return left_child_ || right_child_;
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetMinSubNodeInRightSubTree()
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

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetMinSubNodeInRightSubTree() const
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

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetNextNode()
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

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetNextNode() const
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

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetMinNode()
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

template<typename KeyType, typename ValueType, typename Comparator>
const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::GetMinNode() const 
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

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::HasAllLeafs() const
{
	return left_child_ && right_child_;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode::SetParent(RedBlackTreeNode* parent)
{
	parent_ = parent;
}