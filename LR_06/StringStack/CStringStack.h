#pragma once
#include "stdafx.h"

class CStringStack
{
public:
	CStringStack();
	~CStringStack();

	CStringStack(CStringStack const& stack);
	CStringStack(CStringStack&& copyStack);

	CStringStack& operator=(CStringStack const& copyStack);
	CStringStack& operator=(CStringStack&& moveStack);

	void Push(const std::string& value);
	void Pop();
	std::string GetTop() const;
	bool IsEmpty() const;
	void Clear();

private:
	struct StackItem
	{
		StackItem(const std::string str, std::unique_ptr<StackItem>&& next)
			: data(str)
			, next(std::move(next))
		{
		}
		std::string data;
		std::unique_ptr<StackItem> next;
	};

	std::unique_ptr<StackItem> m_top;
};
