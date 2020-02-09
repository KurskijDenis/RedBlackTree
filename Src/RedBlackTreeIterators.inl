template<typename KeyType, typename ValueType>
RedBlackTreeIterator<KeyType, ValueType>::RedBlackTreeIterator(
	typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* in_p, 
	typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* in_end_p)
	: p_(in_p)
	, end_p_(in_end_p)
{}

template<typename KeyType, typename ValueType>
RedBlackTreeIterator<KeyType, ValueType>::RedBlackTreeIterator(const RedBlackTreeIterator &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType>
bool RedBlackTreeIterator<KeyType, ValueType>::operator!=(RedBlackTreeIterator const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType>
bool RedBlackTreeIterator<KeyType, ValueType>::operator==(RedBlackTreeIterator const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType>
bool RedBlackTreeIterator<KeyType, ValueType>::operator!=(RedBlackTreeConstIterator<KeyType, ValueType> const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType>
bool RedBlackTreeIterator<KeyType, ValueType>::operator==(RedBlackTreeConstIterator<KeyType, ValueType> const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType>
std::pair<const KeyType, ValueType>& RedBlackTreeIterator<KeyType, ValueType>::operator*()
{
	return p_->GetPair();
}

template<typename KeyType, typename ValueType>
RedBlackTreeIterator<KeyType, ValueType>& RedBlackTreeIterator<KeyType, ValueType>::operator++()
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

template<typename KeyType, typename ValueType>
RedBlackTreeIterator<KeyType, ValueType> RedBlackTreeIterator<KeyType, ValueType>::operator++(int)
{
	auto res = *this;
	++(*this);
	return res;
}

template<typename KeyType, typename ValueType>
RedBlackTreeConstIterator<KeyType, ValueType>::RedBlackTreeConstIterator(
	const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* in_p, 
	const typename RedBlackTree<KeyType, ValueType>::RedBlackTreeNode* in_end_p)
	: p_(in_p)
	, end_p_(in_end_p)
{}

template<typename KeyType, typename ValueType>
RedBlackTreeConstIterator<KeyType, ValueType>::RedBlackTreeConstIterator(const RedBlackTreeIterator<KeyType, ValueType> &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType>
RedBlackTreeConstIterator<KeyType, ValueType>::RedBlackTreeConstIterator(const RedBlackTreeConstIterator &it)
	: p_(it->p_)
	, end_p_(it->end_p_)
{}

template<typename KeyType, typename ValueType>
bool RedBlackTreeConstIterator<KeyType, ValueType>::operator!=(RedBlackTreeConstIterator const& other) const
{
	return p_ != other.p_;
}

template<typename KeyType, typename ValueType>
bool RedBlackTreeConstIterator<KeyType, ValueType>::operator==(RedBlackTreeConstIterator const& other) const
{
	return p_ == other.p_;
}

template<typename KeyType, typename ValueType>
const std::pair<const KeyType, ValueType>& RedBlackTreeConstIterator<KeyType, ValueType>::operator*() const
{
	return p_->GetPair();
}

template<typename KeyType, typename ValueType>
RedBlackTreeConstIterator<KeyType, ValueType>& RedBlackTreeConstIterator<KeyType, ValueType>::operator++()
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

template<typename KeyType, typename ValueType>
RedBlackTreeConstIterator<KeyType, ValueType> RedBlackTreeConstIterator<KeyType, ValueType>::operator++(int)
{
	auto res = *this;
	++(*this);
	return res;
}