#include "stdafx.h"
#include "CCircle.h"
#include "CUtils.h"
#include "Config.h"

CCircle::CCircle(const CPoint& center, const double radius, const std::string& outlineColor, const std::string& fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape(outlineColor, fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, QUADRATIC_DEGREE);
}

double CCircle::GetPerimeter() const
{
	return M_PI * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fill color:" << GetFillColor() << " outline color:" << GetOutlineColor()
		 << " center.x:" << m_center.x << " center.y:" << m_center.y
		 << " radius:" << m_radius << std::endl;

	return strm.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, CUtils::StringToUint32(GetFillColor()));
	canvas.DrawCircle(GetCenter(), GetRadius(), CUtils::StringToUint32(GetOutlineColor()));
}
