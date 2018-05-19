#include "stdafx.h"
#include "CStringStack.h"

CStringStack::CStringStack(CStringStack const& stack)
{
	CopyStackItems(stack);
}

CStringStack::CStringStack(CStringStack&& copyStack)
{
	m_top = copyStack.m_top;
	m_stackSize = copyStack.m_stackSize;
	copyStack.m_top = nullptr;
	copyStack.m_stackSize = 0;
}
CStringStack::~CStringStack()
{
	Clear();
}

void CStringStack::Push(std::string const& element)
{
	auto newNode = std::make_shared<StackItem>(element, m_top);
	m_top = newNode;
	m_stackSize++;
}

std::string CStringStack::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return m_top->stringContent;
}

void CStringStack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	m_top = m_top->next;
	m_stackSize--;
}

CStringStack& CStringStack::operator=(CStringStack const& copyStack)
{
	if (this != &copyStack)
	{
		Clear();
		CopyStackItems(copyStack);
	}

	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& moveStack)
{
	if (this != &moveStack)
	{
		m_stackSize = moveStack.m_stackSize;
		m_top = moveStack.m_top;
		moveStack.m_top = nullptr;
		moveStack.m_stackSize = 0;
	}

	return *this;
}

bool CStringStack::IsEmpty() const
{
	return (m_stackSize == 0);
}

void CStringStack::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

void CStringStack::CopyStackItems(CStringStack const& stack)
{
	if (!stack.IsEmpty())
	{
		std::shared_ptr<StackItem> copiedItem = stack.m_top;

		m_top = std::make_shared<StackItem>(*copiedItem);
		auto pasteItem = m_top;

		pasteItem->stringContent = copiedItem->stringContent;

		while (copiedItem->next != nullptr)
		{
			pasteItem->next = std::make_shared<StackItem>(*copiedItem->next);

			copiedItem = copiedItem->next;
			pasteItem = pasteItem->next;
		}

		m_stackSize = stack.m_stackSize;
	}
}
