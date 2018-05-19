#pragma once
#include "stdafx.h"

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	const T* maxElement = &arr[0];
	for (const T& arrElem : arr)
	{
		if (less(*maxElement, arrElem))
		{
			(maxElement = &arrElem);
		}
	}

	maxValue = *maxElement;

	return true;
}
