#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const std::string& outlineColor, const std::string& fillColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}
