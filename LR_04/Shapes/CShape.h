#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& color);
	virtual ~CShape() = default;
	std::string GetOutlineColor() const override;

private:
	std::string m_color;
};
