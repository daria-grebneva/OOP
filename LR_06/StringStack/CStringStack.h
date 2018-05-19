#pragma once
#include "stdafx.h"

class CStringStack
{
public:
	CStringStack() = default;

	CStringStack(CStringStack const& stack);
	CStringStack(CStringStack&& copyStack);

	void Push(std::string const& element);
	void Pop();
	std::string GetTop() const;

	CStringStack& operator=(CStringStack const& copyStack);
	CStringStack& operator=(CStringStack&& moveStack);

	bool IsEmpty() const;
	void Clear();

	~CStringStack();

private:
	struct StackItem
	{
		StackItem(std::string const& str, std::shared_ptr<StackItem> const& nextNode)
			: stringContent(str)
			, next(nextNode)
		{
		}
		std::string stringContent;
		std::shared_ptr<StackItem> next = nullptr;
	};

	void CopyStackItems(CStringStack const& stack);

	size_t m_stackSize = 0;
	std::shared_ptr<StackItem> m_top = nullptr;
};
