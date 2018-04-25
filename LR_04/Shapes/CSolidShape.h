#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
	, public CShape
{
public:
	CSolidShape(const std::string& outlineColor, const std::string& fillColor);
	virtual ~CSolidShape() = default;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;

private:
	std::string m_fillColor;
};
