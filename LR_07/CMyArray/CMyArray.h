﻿#pragma once
#include "stdafx.h"
#include "CArrayIterator.h"

template <typename T>
class CMyArray
{
	template <typename T, bool isReverse>
	friend class CArrayIterator;

public:
	typedef CArrayIterator<T, false> iterator;
	typedef CArrayIterator<const T, false> const_iterator;
	typedef CArrayIterator<T, true> reverse_iterator;
	typedef CArrayIterator<const T, true> const_reverse_iterator;

	CMyArray() = default;
	CMyArray(const CMyArray& arr);
	CMyArray(CMyArray&& arr);

	void Append(const T& value);
	T& GetBack();
	const T& GetBack() const;
	size_t GetSize() const;
	size_t GetCapacity() const;
	void Resize(size_t newSize);
	void Clear();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	CMyArray& operator=(const CMyArray& arr);
	CMyArray& operator=(CMyArray&& arr);

	const_iterator begin() const
	{
		return const_iterator(m_begin);
	}
	const_iterator end() const
	{
		return const_iterator(m_end);
	}
	iterator begin()
	{
		return iterator(m_begin);
	}
	iterator end()
	{
		return iterator(m_end);
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(m_end - 1);
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(m_begin - 1);
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_end - 1);
	}
	reverse_iterator rend()
	{
		return reverse_iterator(m_begin - 1);
	}

	~CMyArray();

private:
	static void DeleteItems(T* begin, T* end);
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd);
	static void DestroyItems(T* from, T* to);
	static T* RawAlloc(size_t n);
	static void RawDealloc(T* p);

private:
	T* m_rbegin = nullptr;
	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_capacityEnd = nullptr;
};

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& arr)
{
	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_begin = RawAlloc(size);
		try
		{
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_capacityEnd = m_end;
		}
		catch (const std::exception& e)
		{
			DeleteItems(m_begin, m_end);
			throw(e.what());
		}
	}
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& arr)
	: m_begin(arr.m_begin)
	, m_end(arr.m_end)
	, m_capacityEnd(arr.m_capacityEnd)
{
	arr.m_begin = nullptr;
	arr.m_end = nullptr;
	arr.m_capacityEnd = nullptr;
}

template <typename T>
void CMyArray<T>::Append(const T& value)
{
	if (m_end == m_capacityEnd)
	{
		size_t newCapacity = std::max<int64_t>(1, GetCapacity() * 2);

		auto newBegin = RawAlloc(newCapacity);
		T* newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			new (newEnd) T(value);
			++newEnd;
		}
		catch (const std::exception& e)
		{
			DeleteItems(newBegin, newEnd);
			throw(e.what());
		}
		DeleteItems(m_begin, m_end);

		m_begin = newBegin;
		m_end = newEnd;
		m_capacityEnd = m_begin + newCapacity;
	}
	else
	{
		new (m_end) T(value);
		++m_end;
	}
}

template <typename T>
T& CMyArray<T>::GetBack()
{
	assert(GetSize() != 0);
	return m_end[-1];
}

template <typename T>
const T& CMyArray<T>::GetBack() const
{
	assert(GetSize() != 0);
	return m_end[-1];
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
	return m_end - m_begin;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_capacityEnd - m_begin;
}

template <typename T>
void CMyArray<T>::Resize(size_t newSize)
{
	size_t currentSize = GetSize();
	size_t oldSize = GetSize();
	auto endBackup = m_end;
	if (newSize < currentSize)
	{
		DestroyItems(m_begin + newSize, m_end);
		m_end = m_begin + newSize;
	}
	while (newSize > currentSize)
	{
		try
		{
			Append(T());
		}
		catch (const std::exception& e)
		{
			if (currentSize > oldSize)
			{
				DeleteItems(endBackup, endBackup + (currentSize - oldSize));
				m_end = endBackup;
			}

			throw(e.what());
		}
		currentSize++;
	}
}

template <typename T>
void CMyArray<T>::Clear()
{
	DeleteItems(m_begin, m_end);
	m_begin = nullptr;
	m_end = nullptr;
	m_capacityEnd = nullptr;
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (index >= GetSize())
		throw std::out_of_range("Index out of range");

	return *(m_begin + index);
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	if (index >= GetSize())
		throw std::out_of_range("Index out of range");

	return *(m_begin + index);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<T>& arr)
{
	if (&arr != this)
	{
		*this = move(CMyArray<T>(arr));
	}

	return *this;
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& arr)
{
	if (&arr != this)
	{
		Clear();

		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_capacityEnd = arr.m_capacityEnd;

		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_capacityEnd = nullptr;
	}

	return *this;
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

template <typename T>
void CMyArray<T>::DeleteItems(T* begin, T* end)
{
	DestroyItems(begin, end);
	RawDealloc(begin);
}

template <typename T>
void CMyArray<T>::CopyItems(const T* firstBegin, T* firstEnd, T* const secondBegin, T*& secondEnd)
{
	for (secondEnd = secondBegin; firstBegin != firstEnd; ++firstBegin, ++secondEnd)
	{
		new (secondEnd) T(*firstBegin);
	}
}

template <typename T>
void CMyArray<T>::DestroyItems(T* from, T* to)
{
	while (to != from)
	{
		--to;
		to->~T();
	}
}

template <typename T>
T* CMyArray<T>::RawAlloc(size_t n)
{
	size_t size = n * sizeof(T);
	T* p = static_cast<T*>(malloc(size));
	return p;
}

template <typename T>
void CMyArray<T>::RawDealloc(T* p)
{
	free(p);
}
