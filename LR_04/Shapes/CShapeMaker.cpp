#include "stdafx.h"
#include "CShapeMaker.h"
#include "CCanvas.h"
#include "Config.h"

CShapeMaker::CShapeMaker(std::istream& input)
	: m_input(input)
	, m_action({ { CREATE_CIRCLE, bind(&CShapeMaker::CreateCircle, this, std::placeholders::_1) },
		  { CREATE_RECTANGLE, bind(&CShapeMaker::CreateRectangle, this, std::placeholders::_1) },
		  { CREATE_TRIANGLE, bind(&CShapeMaker::CreateTriangle, this, std::placeholders::_1) },
		  { CREATE_LINE, bind(&CShapeMaker::CreateLine, this, std::placeholders::_1) },
		  { GET_MIN_PERIMETER, bind(&CShapeMaker::GetMinPerimeterShape, this, std::placeholders::_1) },
		  { GET_MAX_AREA, bind(&CShapeMaker::GetMaxAreaShape, this, std::placeholders::_1) },
		  { DRAW, bind(&CShapeMaker::DrawShapes, this, std::placeholders::_1) },
		  { SHOW_USAGE, bind(&CShapeMaker::ShowUsage, this, std::placeholders::_1) } })
{
}

void CShapeMaker::ShowUsage(std::istream& args)
{
	std::cout << "To create a circle: " << CREATE_CIRCLE << "\n"
			  << "To create a rectangle: " << CREATE_RECTANGLE << "\n"
			  << "To create a triangle: " << CREATE_TRIANGLE << "\n"
			  << "To create a line: " << CREATE_LINE << "\n"
			  << "To get min shape perimeter: " << GET_MIN_PERIMETER << "\n"
			  << "To get max shape area: " << GET_MAX_AREA << "\n"
			  << "To draw shapes: " << DRAW << "\n"
			  << "To show usage: " << SHOW_USAGE << "\n";
}

void CShapeMaker::ExecuteCommand() const
{
	std::string str;
	getline(m_input, str);
	std::istringstream strm(str);

	std::string action;
	strm >> action;

	auto it = m_action.find(action);
	if (it != m_action.end())
	{
		it->second(strm);
	}
	else
	{
		throw std::exception("Unknown command");
	}
}

bool CShapeMaker::IsValidColor(const std::string& color) const
{
	for (auto& ch : color)
	{
		if (!(ch >= '0' && ch <= '9') && !(ch >= 'a' && ch <= 'f'))
		{
			return false;
		}
	}
	return true;
}

void CShapeMaker::AddFFToColor(std::string& color) const
{
	if (color.size() == COLOR_SIZE)
	{
		color += COLOR_ADDITIVE;
	}
}

void CShapeMaker::CheckEmptyShapesArray() const
{
	if (m_savedShapes.empty())
	{
		throw std::exception("Shapes array is empty");
	}
}

void CShapeMaker::DrawShapes(std::istream&)
{
	CheckEmptyShapesArray();
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color::White);
		for (auto& shape : m_savedShapes)
		{
			shape->Draw(canvas);
		}
		window.display();
	}
}

void CShapeMaker::GetMinPerimeterShape(std::istream& args) const
{
	CheckEmptyShapesArray();

	auto it = std::min_element(m_savedShapes.begin(), m_savedShapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) {
			return shape1->GetPerimeter() < shape2->GetPerimeter();
		});

	if (it != m_savedShapes.end())
	{
		std::cout << "MIN PERIMETER: " << std::endl;
		std::cout << (*it)->ToString() << std::endl;
	}
}

void CShapeMaker::GetMaxAreaShape(std::istream& args) const
{
	CheckEmptyShapesArray();

	auto it = std::max_element(m_savedShapes.begin(), m_savedShapes.end(),
		[](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) {
			return shape1->GetArea() < shape2->GetArea();
		});
	if (it != m_savedShapes.end())
	{
		std::cout << "MAX AREA: " << std::endl;
		std::cout << (*it)->ToString() << std::endl;
	}
}

void CShapeMaker::CheckValidColor(const std::string& color)
{
	if (!IsValidColor(color))
	{
		throw std::exception("Invalid color form \nValid hex form '#ff0000'");
	}
}

void CShapeMaker::CreateCircle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint center;
	double radius;

	if (args >> center.x >> center.y >> radius >> outlineColor >> fillColor)
	{
		CheckValidColor(outlineColor);
		CheckValidColor(fillColor);

		if (radius < 0)
		{
			throw std::exception("Radius less than 0");
		}

		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);
		std::shared_ptr<IShape> circlePtr(new CCircle(center, radius, outlineColor, fillColor));
		m_savedShapes.push_back(std::move(circlePtr));
	}
	else
	{
		throw std::exception("Incorrect argument for cicle creating");
	}
}

void CShapeMaker::CreateLine(std::istream& args)
{
	std::string outlineColor;
	CPoint start;
	CPoint end;

	if (args >> start.x >> start.y >> end.x >> end.y >> outlineColor)
	{
		CheckValidColor(outlineColor);
		AddFFToColor(outlineColor);

		std::shared_ptr<IShape> linePtr(new CLineSegment(start, end, outlineColor));
		m_savedShapes.push_back(std::move(linePtr));
	}
	else
	{
		throw std::exception("Incorrect argument for line creating");
	}
}

void CShapeMaker::CreateRectangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint leftTop;
	double width;
	double height;

	if (args >> leftTop.x >> leftTop.y >> width >> height >> outlineColor >> fillColor)
	{
		CheckValidColor(outlineColor);
		CheckValidColor(fillColor);

		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);

		if (width < 0)
		{
			throw std::exception("Width less than 0");
		}

		if (height < 0)
		{
			throw std::exception("Height less than 0");
		}

		std::shared_ptr<IShape> rectanglePtr(new CRectangle(leftTop, width, height, outlineColor, fillColor));
		m_savedShapes.push_back(std::move(rectanglePtr));
	}
	else
	{
		throw std::exception("Incorrect argument for rectangle creating");
	}
}

void CShapeMaker::CreateTriangle(std::istream& args)
{
	std::string fillColor;
	std::string outlineColor;
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;

	if (args >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y >> outlineColor >> fillColor)
	{
		CheckValidColor(outlineColor);
		CheckValidColor(fillColor);

		AddFFToColor(outlineColor);
		AddFFToColor(fillColor);

		std::shared_ptr<IShape> trianglePtr(new CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor));
		m_savedShapes.push_back(std::move(trianglePtr));
	}
	else
	{
		throw std::exception("Incorrect argument for triangle creating");
	}
}
