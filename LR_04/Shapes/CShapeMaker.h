#pragma once
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"

class CShapeMaker
{
public:
	CShapeMaker(std::istream& input);
	~CShapeMaker() = default;
	void ExecuteCommand() const;

private:
	typedef std::map<std::string, std::function<void(std::istream& args)>> Action;

	void DrawShapes(std::istream& args);
	void CreateCircle(std::istream& args);
	void CreateLine(std::istream& args);
	void CreateRectangle(std::istream& args);
	void CreateTriangle(std::istream& args);
	void GetMinPerimeterShape(std::istream& args) const;
	void GetMaxAreaShape(std::istream& args) const;
	bool IsValidColor(const std::string& color) const;
	void AddFFToColor(std::string& color) const;
	void ShowUsage(std::istream& args);
	void CheckEmptyShapesArray() const;
	void CheckValidColor(const std::string& color);

	std::vector<std::shared_ptr<IShape>> m_savedShapes;
	std::istream& m_input;
	const Action m_action;
};
