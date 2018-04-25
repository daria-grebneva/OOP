#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const std::string& color)
	: m_color(color)
{
}

std::string CShape::GetOutlineColor() const
{
	return m_color;
}
