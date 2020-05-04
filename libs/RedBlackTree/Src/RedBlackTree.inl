
template<typename KeyType, typename ValueType, typename Comparator>
std::string RedBlackTree<KeyType, ValueType, Comparator>::GetColorName(const RedBlackTree<KeyType, ValueType, Comparator>::NodeColor color)
{
	static const std::map<NodeColor, std::string> colors({
		{NodeColor::Black, "B"},
		{NodeColor::Red, "R"},
	});
	const auto it = colors.find(color);
	return it != colors.cend() ? it->second : "E";
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTree()
	: end_node_(std::make_unique<int>(0))
{}


template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::DelElement(const KeyType& key_value)
{
	if (!head_node_)
	{
		return;
	}

	auto next_node = head_node_.get();

	while(next_node != nullptr)
	{
		if (next_node->Equal(key_value))
		{
			break;
		}

		if (next_node->Less(key_value))
		{
			const auto right_child = next_node->GetRightChildRawPtr();
			if (right_child == nullptr)
			{
				next_node = nullptr;
				break;
			}
			next_node = right_child;
		}
		else
		{
			const auto left_child = next_node->GetLeftChildRawPtr();
			if (left_child == nullptr)
			{
				next_node = nullptr;
				break;
			}
			next_node = left_child;
		}
	}

	if (next_node == nullptr)
	{
		return;
	}
	--size_;
	RecursiveDelete(next_node);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::AddElement(const KeyType& key_value, const ValueType& new_value)
{
	if (!head_node_)
	{
		++size_;
		head_node_ = std::make_unique<RedBlackTreeNode>(key_value, new_value);
		head_node_->SetColor(NodeColor::Black);
		return;
	}

	RedBlackTreeNode* next_node = head_node_.get();

	while(next_node != nullptr)
	{
		if (next_node->Equal(key_value))
		{
			next_node = nullptr;
			break;
		}

		if (next_node->Less(key_value))
		{
			const auto right_child = next_node->GetRightChildRawPtr();
			if (right_child == nullptr)
			{
				break;
			}
			next_node = right_child;
		}
		else
		{
			const auto left_child = next_node->GetLeftChildRawPtr();
			if (left_child == nullptr)
			{
				break;
			}
			next_node = left_child;
		}
	}
	
	if (next_node == nullptr)
	{
		return;
	}

	auto new_node = std::make_unique<RedBlackTreeNode>(key_value, new_value);
	auto new_node_raw_ptr = new_node.get();
	if (next_node->Less(key_value))
	{
		next_node->ChangeRightChild(std::move(new_node));
	}
	else
	{
		next_node->ChangeLeftChild(std::move(new_node));
	}
	++size_;
	FixTreeAfterInsert(new_node_raw_ptr);
}

template<typename KeyType, typename ValueType, typename Comparator>
std::string RedBlackTree<KeyType, ValueType, Comparator>::Print() const
{
	std::stringstream sstream;
	if (!head_node_)
	{
		return {};
	}
	std::stack<std::pair<const RedBlackTreeNode*, std::string>> nodes;
	nodes.emplace(head_node_.get(), "");
	while(!nodes.empty())
	{
		const auto [node, indent] = nodes.top();
		nodes.pop();
		sstream << indent;
		if (node != nullptr)
		{
			sstream << "- " << *node << "(" << RedBlackTree<KeyType, ValueType, Comparator>::GetColorName(node->GetColor()) << ")";
			const auto left_child = node->GetLeftChildRawPtr();
			const auto right_child = node->GetRightChildRawPtr();
			nodes.emplace(right_child, indent + "| ");
			nodes.emplace(left_child, indent + "| ");
		}
		else
		{
			sstream << "- nullptr";
		}
		sstream << std::endl;
	}
	return sstream.str();
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTree<KeyType, ValueType, Comparator>::CheckTree() const
{
	if (!head_node_)
	{
		return true;
	}

	if (head_node_->GetColor() != NodeColor::Black)
	{
		return false;
	}
	struct StackNode
	{
		StackNode(
			const RedBlackTreeNode* in_parent_node,
			const RedBlackTreeNode* in_node,
			const NodeSide in_node_side)
			: parent_node(in_parent_node)
			, node(in_node)
			, node_side(in_node_side)
			{}
		const RedBlackTreeNode* parent_node;
		const RedBlackTreeNode* node;
		NodeSide node_side;
	};

	std::stack<StackNode> items;
	std::map<const RedBlackTreeNode*, std::pair<size_t, size_t>> black_nodes;
	
	const RedBlackTreeNode* node = head_node_.get();
	auto node_side = NodeSide::None;
	const RedBlackTreeNode* parent_node = nullptr;
	const RedBlackTreeNode* last_visited_node = nullptr;

	while(node != nullptr || !items.empty())
	{
		if (node != nullptr)
		{
			items.emplace(parent_node, node, node_side);
			parent_node = node;
			node_side = NodeSide::Left;
			node = node->GetLeftChildRawPtr();
			if (node == nullptr)
			{
				black_nodes[parent_node].first = 1;
			}
			continue;
		}

		const auto item = items.top();
		if (item.node == nullptr)
		{
			return false;
		}

		auto right_node = item.node->GetRightChildRawPtr();
		if (right_node != nullptr && right_node != last_visited_node)
		{
			parent_node = item.node;
			node_side = NodeSide::Right;
			node = right_node;
		}
		else
		{
			if (right_node == nullptr)
			{
				black_nodes[item.node].second = 1;
			}
			last_visited_node = item.node;
			items.pop();
			auto it = black_nodes.find(item.node);
			if (it == black_nodes.cend())
			{
				return false;
			}

			if (it->second.first != it->second.second)
			{
				for (const auto& [inode, count_node] : black_nodes)
				{
					std::cout << "node = " << inode->GetValue() << " left = " << count_node.first << " right = " << count_node.second << std::endl; 
				}
				return false;
			}

			if (item.parent_node != nullptr)
			{
				const auto count_black_nodes = it->second.first + (item.node->GetColor() == NodeColor::Black ? 1 : 0);
				if (item.node_side == NodeSide::Left)
				{
					black_nodes[item.parent_node].first = count_black_nodes;
				}
				else
				{
					black_nodes[item.parent_node].second = count_black_nodes;
				}
			}
		}
	}
	return true;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::Clear()
{
	head_node_.reset();
	size_ = 0;
}

template<typename KeyType, typename ValueType, typename Comparator>
size_t RedBlackTree<KeyType, ValueType, Comparator>::GetSize()
{
	return size_;
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::iterator RedBlackTree<KeyType, ValueType, Comparator>::begin() const
{
	const auto end_node_ptr = reinterpret_cast<RedBlackTreeNode*>(end_node_.get());
	if (!head_node_)
	{
		return iterator(end_node_ptr, end_node_ptr);
	}
	return iterator(head_node_->GetMinNode(), end_node_ptr);
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::iterator RedBlackTree<KeyType, ValueType, Comparator>::end() const
{
	const auto end_node_ptr = reinterpret_cast<RedBlackTreeNode*>(end_node_.get());
	return iterator(end_node_ptr, end_node_ptr);
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::const_iterator RedBlackTree<KeyType, ValueType, Comparator>::cbegin() const
{
	const auto end_node_ptr = reinterpret_cast<RedBlackTreeNode*>(end_node_.get());
	if (!head_node_)
	{
		return const_iterator(end_node_.get(), end_node_ptr);
	}
	return const_iterator(head_node_->GetMinNode(), end_node_ptr);
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::const_iterator RedBlackTree<KeyType, ValueType, Comparator>::cend() const
{
	const auto end_node_ptr = reinterpret_cast<RedBlackTreeNode*>(end_node_.get());
	return const_iterator(end_node_ptr, end_node_ptr);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::DeleteLeaf(RedBlackTreeNode* node)
{
	const auto right_child = node->GetRightChildRawPtr();
	const auto left_child = node->GetLeftChildRawPtr();
	const auto parent = node->GetParent();

	const auto node_side = node->GetSide();
	const auto node_color = node->GetColor();

	assert(right_child == nullptr && left_child == nullptr);

	if (parent == nullptr)
	{
		head_node_.reset();
		return;
	}

	RedBlackTreeNode* brother = nullptr;
	if (node_side == NodeSide::Right)
	{
		parent->ResetRightChild();
		brother = parent->GetLeftChildRawPtr();
	}
	else
	{
		parent->ResetLeftChild();
		brother = parent->GetRightChildRawPtr();
	}

	if (brother == nullptr || node_color == NodeColor::Red)
	{
		return;
	}

	if (parent->GetColor() == NodeColor::Red)
	{
		assert(brother->GetColor() == NodeColor::Black);
		parent->SetColor(NodeColor::Black);

		if (!brother->HasLeaf())
		{
			brother->SetColor(NodeColor::Red);
			return; 
		}
		if (node_side == NodeSide::Right)
		{
			auto right_nephew = brother->GetRightChildRawPtr();
			if (right_nephew != nullptr)
			{
				LeftRotate(brother);
				brother = right_nephew;
				right_nephew = nullptr;
			}
			brother->SetColor(NodeColor::Red);
			RightRotate(parent);
			brother->GetLeftChildRawPtr()->SetColor(NodeColor::Black);
			brother->GetRightChildRawPtr()->SetColor(NodeColor::Black);
		}
		else
		{
			auto left_nephew = brother->GetLeftChildRawPtr();
			if (left_nephew != nullptr)
			{
				RightRotate(brother);
				brother = left_nephew;
				left_nephew = nullptr;
			}
			brother->SetColor(NodeColor::Red);
			LeftRotate(parent);
			brother->GetRightChildRawPtr()->SetColor(NodeColor::Black);
			brother->GetLeftChildRawPtr()->SetColor(NodeColor::Black);
		}
		return;
	}

	if (brother->GetColor() == NodeColor::Red)
	{
		assert(brother->HasAllLeafs());
		brother->SetColor(NodeColor::Black);
		if (node_side == NodeSide::Left)
		{
			LeftRotate(parent);
			assert(parent->GetRightChildRawPtr() != nullptr);
			auto right_node_ptr = parent->GetRightChildRawPtr();
			assert(right_node_ptr != nullptr);
			if (!right_node_ptr->HasLeaf())
			{
				parent->SetColor(NodeColor::Black);
				right_node_ptr->SetColor(NodeColor::Red);
				return;
			}
			auto right_grandson_ptr = right_node_ptr->GetRightChildRawPtr();
			if (!right_grandson_ptr)
			{
				right_node_ptr->SetColor(NodeColor::Red);
				RightRotate(right_node_ptr);
				right_node_ptr = parent->GetRightChildRawPtr();
				right_node_ptr->SetColor(NodeColor::Black);
			}
			LeftRotate(parent);
			right_node_ptr->GetRightChildRawPtr()->SetColor(NodeColor::Black);
			right_node_ptr->GetLeftChildRawPtr()->SetColor(NodeColor::Black);
			right_node_ptr->SetColor(NodeColor::Red);
		}
		else
		{
			RightRotate(parent);
			assert(parent->GetLeftChildRawPtr() != nullptr);
			auto left_node_ptr = parent->GetLeftChildRawPtr();
			assert(left_node_ptr != nullptr);
			if (!left_node_ptr->HasLeaf())
			{
				parent->SetColor(NodeColor::Black);
				left_node_ptr->SetColor(NodeColor::Red);
				return;
			}
			auto left_grandson_ptr = left_node_ptr->GetLeftChildRawPtr();
			if (!left_grandson_ptr)
			{
				left_node_ptr->SetColor(NodeColor::Red);
				LeftRotate(left_node_ptr);
				left_node_ptr = parent->GetLeftChildRawPtr();
				left_node_ptr->SetColor(NodeColor::Black);
			}
			RightRotate(parent);
			left_node_ptr->GetLeftChildRawPtr()->SetColor(NodeColor::Black);
			left_node_ptr->GetRightChildRawPtr()->SetColor(NodeColor::Black);
			left_node_ptr->SetColor(NodeColor::Red);
		}
		return;
	}
	if (brother->HasLeaf())
	{
		if (node_side == NodeSide::Left)
		{
			auto right_nephew = brother->GetRightChildRawPtr();
			if (right_nephew == nullptr)
			{
				brother->SetColor(NodeColor::Red);
				RightRotate(brother);
				brother = parent->GetRightChildRawPtr();
				right_nephew = brother->GetRightChildRawPtr();
				brother->SetColor(NodeColor::Black);
			}
			right_nephew->SetColor(NodeColor::Black);
			LeftRotate(parent);
		}
		else
		{
			auto left_nephew = brother->GetLeftChildRawPtr();
			if (left_nephew == nullptr)
			{
				brother->SetColor(NodeColor::Red);
				LeftRotate(brother);
				brother = parent->GetLeftChildRawPtr();
				left_nephew = brother->GetLeftChildRawPtr();
				brother->SetColor(NodeColor::Black);
			}
			left_nephew->SetColor(NodeColor::Black);
			RightRotate(parent);
		}
		return;
	}
	brother->SetColor(NodeColor::Red);
	FixTreeWhileDeleteNode(parent);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RecursiveDelete(RedBlackTreeNode* node)
{
	auto next_node = node;
	if (node == nullptr)
	{
		return;
	}

	while(next_node != nullptr)
	{
		const auto right_child = next_node->GetRightChildRawPtr();
		const auto left_child = next_node->GetLeftChildRawPtr();

		if (right_child == nullptr && left_child == nullptr)
		{
			DeleteLeaf(next_node);
			return;
		}

		if (right_child != nullptr && left_child != nullptr)
		{
			auto parent = next_node->GetParent();
			auto grandson = right_child->GetLeftChildRawPtr();
			if (grandson != nullptr)
			{
				while (grandson->GetLeftChildRawPtr() != nullptr)
				{
					grandson = grandson->GetLeftChildRawPtr();
				}

				if (parent == nullptr)
				{
					auto grandson_parent = grandson->GetParent();
					auto old_head_node = std::move(head_node_);
					head_node_ = grandson_parent->GetLeftChild();
					next_node->SwapColorWithChilds(*grandson);
					grandson_parent->ChangeLeftChild(std::move(old_head_node));
				}
				else
				{
					next_node->SwapNodes(*grandson);
				}
				continue;
			}
			if (parent == nullptr)
			{
				auto old_head_node = std::move(head_node_);
				head_node_ = next_node->GetRightChild();;
				next_node->SwapColorWithChilds(*right_child);
				right_child->ChangeRightChild(std::move(old_head_node));
			}
			else
			{
				next_node->SwapNodes(*right_child);
			}
			continue;
		}
		break;
	}

	assert(next_node != nullptr);

	const auto color = next_node->GetColor();
	next_node = ReplaceNodeToChildNode(next_node);
	if (next_node == head_node_.get() || color == NodeColor::Red)
	{
		return;
	}
	
	if (next_node->GetColor() == NodeColor::Red)
	{
		next_node->SetColor(NodeColor::Black);
		return;
	}

	FixTreeWhileDeleteNode(next_node);
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::FixTreeWhileDeleteNode(RedBlackTreeNode* const node)
{
	auto next_node = node;
	while(next_node != nullptr)
	{
		//todo check
		assert(next_node->GetColor() == NodeColor::Black);

		auto parent = next_node->GetParent();
		if (parent == nullptr)
		{
			next_node->SetColor(NodeColor::Black);
			return;
		}
		
		auto brother = next_node->GetBrother();
		assert(brother != nullptr);

		if (brother->GetColor() == NodeColor::Red)
		{
			parent->SetColor(NodeColor::Red);
			brother->SetColor(NodeColor::Black);

			if (next_node->GetSide() == NodeSide::Right)
			{
				RightRotate(parent);
			}
			else
			{
				LeftRotate(parent);
			}

			parent = next_node->GetParent();
			brother = next_node->GetBrother();

			assert(brother != nullptr);
			assert(parent != nullptr);
		}

		auto left_nephew = brother->GetLeftChildRawPtr();
		auto right_nephew = brother->GetRightChildRawPtr();

		if (parent->GetColor() == NodeColor::Black &&
			brother->GetColor() == NodeColor::Black &&
			(left_nephew == nullptr || left_nephew->GetColor() == NodeColor::Black) && 
			(right_nephew == nullptr || right_nephew->GetColor() == NodeColor::Black))
		{
			brother->SetColor(NodeColor::Red);
			next_node = parent;
			continue;
		}

		if (parent->GetColor() == NodeColor::Red &&
			brother->GetColor() == NodeColor::Black &&
			(left_nephew == nullptr || left_nephew->GetColor() == NodeColor::Black) && 
			(right_nephew == nullptr || right_nephew->GetColor() == NodeColor::Black))
		{
			brother->SetColor(NodeColor::Red);
			parent->SetColor(NodeColor::Black);
			return;
		}


		if (brother->GetColor() == NodeColor::Black)
		{
			if (next_node->GetSide() == NodeSide::Left && 
				(left_nephew != nullptr && left_nephew->GetColor() == NodeColor::Red) && 
				(right_nephew == nullptr || right_nephew->GetColor() == NodeColor::Black))
			{
				left_nephew->SetColor(NodeColor::Black);
				brother->SetColor(NodeColor::Red);
				RightRotate(brother);
			}
			
			if (next_node->GetSide() == NodeSide::Right && 
				(left_nephew == nullptr || left_nephew->GetColor() == NodeColor::Black) && 
				(right_nephew != nullptr && right_nephew->GetColor() == NodeColor::Red))
			{
				right_nephew->SetColor(NodeColor::Black);
				brother->SetColor(NodeColor::Red);
				LeftRotate(brother);
			}

			brother = next_node->GetBrother();
			left_nephew = brother->GetLeftChildRawPtr();
			right_nephew = brother->GetRightChildRawPtr();
		}


		if (next_node->GetSide() == NodeSide::Left && right_nephew && right_nephew->GetColor() == NodeColor::Red)
		{
			brother->SetColor(parent->GetColor());
			parent->SetColor(NodeColor::Black);
			right_nephew->SetColor(NodeColor::Black);
			LeftRotate(parent);
			return;
		}
		
		if (next_node->GetSide() == NodeSide::Right && left_nephew && left_nephew->GetColor() == NodeColor::Red)
		{
			brother->SetColor(parent->GetColor());
			parent->SetColor(NodeColor::Black);
			left_nephew->SetColor(NodeColor::Black);
			RightRotate(parent);
			return;
		}
		assert(false && "Unreachable code");
	}
	return;
}

template<typename KeyType, typename ValueType, typename Comparator>
typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* RedBlackTree<KeyType, ValueType, Comparator>::ReplaceNodeToChildNode(RedBlackTreeNode* const node)
{
	const auto right_child_raw_ptr = node->GetRightChildRawPtr();
	const auto left_child_raw_ptr = node->GetLeftChildRawPtr();
	const auto parent = node->GetParent();

	assert(left_child_raw_ptr != nullptr && right_child_raw_ptr == nullptr || 
			left_child_raw_ptr == nullptr && right_child_raw_ptr != nullptr);

	auto rc = left_child_raw_ptr != nullptr ? node->GetLeftChild() : node->GetRightChild();
	const auto return_pointer = rc.get();
	if (parent == nullptr)
	{
		assert(!return_pointer->HasLeaf());

		head_node_ = std::move(rc);
		head_node_->SetColor(NodeColor::Black);
		return return_pointer;
	}

	if (node->GetSide() == NodeSide::Right)
	{
		parent->ChangeRightChild(std::move(rc));
	}
	else
	{
		parent->ChangeLeftChild(std::move(rc));
	}
	
	return return_pointer;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::FixTreeAfterInsert(RedBlackTreeNode* node)
{
	auto next_node = node;
	while (next_node != nullptr)
	{
		assert(next_node->GetColor() == NodeColor::Red);

		auto parent = next_node->GetParent();
		if (parent == nullptr)
		{
			next_node->SetColor(NodeColor::Black);
			return;
		}

		if (parent->GetColor() == NodeColor::Black)
		{
			return;
		}
		
		const auto grand_parent = parent->GetParent();
		assert(grand_parent != nullptr);
		{
			const auto uncle = next_node->GetUncle();
			if (uncle != nullptr && uncle->GetColor() == NodeColor::Red)
			{
				grand_parent->SetColor(NodeColor::Red);
				uncle->SetColor(NodeColor::Black);
				parent->SetColor(NodeColor::Black);
				next_node = grand_parent;
				continue;
			}
		}

		if (next_node->GetSide() == NodeSide::Right && parent->GetSide() == NodeSide::Left)
		{
			LeftRotate(parent);
			std::swap(parent, next_node);
		}

		if (next_node->GetSide() == NodeSide::Left && parent->GetSide() == NodeSide::Right)
		{
			RightRotate(parent);
			std::swap(parent, next_node);
		}

		parent->SetColor(NodeColor::Black);
		grand_parent->SetColor(NodeColor::Red);

		if (next_node->GetSide() == NodeSide::Left && parent->GetSide() == NodeSide::Left)
		{
			RightRotate(grand_parent);
			return;
		}
		
		if (next_node->GetSide() == NodeSide::Right && parent->GetSide() == NodeSide::Right)
		{
			LeftRotate(grand_parent);
			return;
		}
		assert(false);
		return;
	}
	return;
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::RightRotate(RedBlackTreeNode* const node)
{
	assert(node);
	if (!node)
	{
		return;
	}
	auto left_child_raw_ptr = node->GetLeftChildRawPtr();
	const auto left_child_exist = left_child_raw_ptr != nullptr;

	assert(left_child_exist);
	if (!left_child_exist)
	{
		return;
	}

	const auto parent = node->GetParent();
	std::unique_ptr<RedBlackTreeNode> node_uptr;
	{
		auto left_child = node->GetLeftChild();
		node->ChangeLeftChild(left_child_raw_ptr->GetRightChild());

		if (parent != nullptr)
		{
			if (node->GetSide() == NodeSide::Right)
			{
				node_uptr = parent->GetRightChild();
				parent->ChangeRightChild(std::move(left_child));
			}
			else
			{
				node_uptr = parent->GetLeftChild();
				parent->ChangeLeftChild(std::move(left_child));
			}
		}
		else
		{
			node_uptr = std::move(head_node_);
			head_node_ = std::move(left_child);
		}
	}
	left_child_raw_ptr->ChangeRightChild(std::move(node_uptr));
}

template<typename KeyType, typename ValueType, typename Comparator>
void RedBlackTree<KeyType, ValueType, Comparator>::LeftRotate(RedBlackTreeNode* const node)
{
	assert(node);
	if (!node)
	{
		return;
	}
	auto right_child_raw_ptr = node->GetRightChildRawPtr();
	const auto right_child_exist = right_child_raw_ptr != nullptr;

	assert(right_child_exist);
	if (!right_child_exist)
	{
		return;
	}

	const auto parent = node->GetParent();
	std::unique_ptr<RedBlackTreeNode> node_uptr;
	{
		auto right_child = node->GetRightChild();
		node->ChangeRightChild(right_child_raw_ptr->GetLeftChild());

		if (parent != nullptr)
		{
			if (node->GetSide() == NodeSide::Right)
			{
				node_uptr = parent->GetRightChild();
				parent->ChangeRightChild(std::move(right_child));
			}
			else
			{
				node_uptr = parent->GetLeftChild();
				parent->ChangeLeftChild(std::move(right_child));
			}
		}
		else
		{
			node_uptr = std::move(head_node_);
			head_node_ = std::move(right_child);
		}
	}
	right_child_raw_ptr->ChangeLeftChild(std::move(node_uptr));
}

template<typename KeyType, typename ValueType, typename Comparator>
size_t RedBlackTree<KeyType, ValueType, Comparator>::GetBlackNodesInSubtree(const RedBlackTreeNode* node_ptr)
{
	if (node_ptr == nullptr)
	{
		return 1;
	}

	const auto left_count = GetBlackNodesInSubtree(node_ptr->GetLeftChild());
	const auto right_count = GetBlackNodesInSubtree(node_ptr->GetRightChild());
}