template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeIterator<KeyType, ValueType, Comparator>::RedBlackTreeIterator(
	typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* in_p, 
	typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* in_end_p)
	: p_(in_p)
	, end_p_(in_end_p)
{}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeIterator<KeyType, ValueType, Comparator>::RedBlackTreeIterator(const RedBlackTreeIterator &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator!=(RedBlackTreeIterator const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator==(RedBlackTreeIterator const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator!=(RedBlackTreeConstIterator<KeyType, ValueType, Comparator> const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator==(RedBlackTreeConstIterator<KeyType, ValueType, Comparator> const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
std::pair<const KeyType, ValueType>& RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator*()
{
	return p_->GetPair();
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeIterator<KeyType, ValueType, Comparator>& RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator++()
{
	auto next_node = p_->GetNextNode();
	if (next_node)
	{
		 p_ = next_node;
		 return *this;
	}
	p_ = end_p_;
	return *this;
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeIterator<KeyType, ValueType, Comparator> RedBlackTreeIterator<KeyType, ValueType, Comparator>::operator++(int)
{
	auto res = *this;
	++(*this);
	return res;
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::RedBlackTreeConstIterator(
	const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* in_p, 
	const typename RedBlackTree<KeyType, ValueType, Comparator>::RedBlackTreeNode* in_end_p)
	: p_(in_p)
	, end_p_(in_end_p)
{}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::RedBlackTreeConstIterator(const RedBlackTreeIterator<KeyType, ValueType, Comparator> &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::RedBlackTreeConstIterator(const RedBlackTreeConstIterator &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::operator!=(RedBlackTreeConstIterator const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
bool RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::operator==(RedBlackTreeConstIterator const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType, typename Comparator>
const std::pair<const KeyType, ValueType>& RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::operator*() const
{
	return p_->GetPair();
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeConstIterator<KeyType, ValueType, Comparator>& RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::operator++()
{
	auto next_node = p_->GetNextNode();
	if (next_node)
	{
		 p_ = next_node;
		 return *this;
	}
	p_ = end_p_;
	return *this;
}

template<typename KeyType, typename ValueType, typename Comparator>
RedBlackTreeConstIterator<KeyType, ValueType, Comparator> RedBlackTreeConstIterator<KeyType, ValueType, Comparator>::operator++(int)
{
	auto res = *this;
	++(*this);
	return res;
}