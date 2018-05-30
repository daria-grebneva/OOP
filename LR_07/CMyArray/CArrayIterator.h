#pragma once
#include "stdafx.h"

template <typename T, bool isReverse>
class CArrayIterator : public std::iterator<std::input_iterator_tag, T>
{
public:
	CArrayIterator()
		: m_isReverse(isReverse)
	{
	}
	CArrayIterator(T* elementPtr)
		: m_node(elementPtr)
		, m_isReverse(isReverse)
	{
	}

	T& operator*() const;
	T* operator->() const;
	CArrayIterator& operator++();
	CArrayIterator& operator--();
	const CArrayIterator operator++(int);
	const CArrayIterator operator--(int);
	bool operator==(const CArrayIterator& it);
	bool operator!=(const CArrayIterator& it);

private:
	T* m_node;
	bool m_isReverse;
};

template <typename T, bool isReverse>
T& CArrayIterator<T, isReverse>::operator*() const
{
	return *m_node;
}

template <typename T, bool isReverse>
T* CArrayIterator<T, isReverse>::operator->() const
{
	return m_node;
}

template <typename T, bool isReverse>
CArrayIterator<T, isReverse>& CArrayIterator<T, isReverse>::operator++()
{
	isReverse ? --m_node : ++m_node;
	return *this;
}

template <typename T, bool isReverse>
CArrayIterator<T, isReverse>& CArrayIterator<T, isReverse>::operator--()
{
	isReverse ? ++m_node : --m_node;
	return *this;
}

template <typename T, bool isReverse>
const CArrayIterator<T, isReverse> CArrayIterator<T, isReverse>::operator++(int)
{
	auto copy(*this);
	isReverse ? --m_node : ++m_node;
	return copy;
}

template <typename T, bool isReverse>
const CArrayIterator<T, isReverse> CArrayIterator<T, isReverse>::operator--(int)
{
	auto copy(*this);
	isReverse ? ++m_node : --m_node;
	return copy;
}

template <typename T, bool isReverse>
bool CArrayIterator<T, isReverse>::operator==(const CArrayIterator& it)
{
	return m_node == it.m_node;
}

template <typename T, bool isReverse>
bool CArrayIterator<T, isReverse>::operator!=(const CArrayIterator& it)
{
	return !(*this == it);
}
