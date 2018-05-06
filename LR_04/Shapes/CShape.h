#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& color);
	~CShape() = default;
	std::string GetOutlineColor() const override;

private:
	std::string m_outlineColor;
};
