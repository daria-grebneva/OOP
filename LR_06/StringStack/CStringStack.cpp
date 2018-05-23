#include "stdafx.h"
#include "CStringStack.h"

CStringStack::CStringStack()
{
	m_top = nullptr;
}

CStringStack::CStringStack(CStringStack const& stack)
{
	*(this) = stack;
}

CStringStack::CStringStack(CStringStack&& copyStack)
{
	m_top = std::move(copyStack.m_top);
	copyStack.m_top = nullptr;
}

void CStringStack::Push(const std::string& value)
{
	auto newNode = std::make_unique<StackItem>(value, std::move(m_top));
	m_top = move(newNode);
}

void CStringStack::Pop()
{
	if (!IsEmpty())
	{
		m_top = std::move(m_top->next);
	}
	else
	{
		throw std::logic_error("Stack is empty");
	}
}

std::string CStringStack::GetTop() const
{
	if (!IsEmpty())
	{
		return m_top->data;
	}
	else
	{
		throw std::logic_error("Stack is empty");
	}
}

bool CStringStack::IsEmpty() const
{
	return (m_top == nullptr);
}

void CStringStack::Clear()
{
	while (m_top)
	{
		Pop();
	}
}

CStringStack::~CStringStack()
{
	Clear();
}

CStringStack& CStringStack::operator=(const CStringStack& stack)
{
	if (stack.IsEmpty())
	{
		Clear();
		return *this;
	}

	if (this != std::addressof(stack))
	{
		StackItem* node = stack.m_top.get();
		std::unique_ptr<StackItem> element = std::make_unique<StackItem>(node->data, nullptr);
		std::unique_ptr<StackItem> top = std::make_unique<StackItem>(element->data, nullptr);

		node = node->next.get();
		while (node)
		{
			element->next = std::make_unique<StackItem>(node->data, nullptr);
			element = std::move(element->next);
			node = node->next.get();
		}
		Clear();
		m_top.swap(top);
	}
	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& stack)
{
	if (this != std::addressof(stack))
	{
		m_top.swap(stack.m_top);
		stack.Clear();
	}
	return *this;
}
