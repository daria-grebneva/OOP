#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "ICanvas.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3, const std::string& outlineColor, const std::string& fillColor);
	~CTriangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	double GetDistanceBetweenVertices(const CPoint& vertex1, const CPoint& vertex2) const;
};
