#include "stdafx.h"
#include "CRational.h"

using namespace std;

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}

	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	Normalize();
}

void CRational::Normalize()
{
	const int nod = GetNOD(abs(m_numerator), m_denominator);
	m_numerator /= nod;
	m_denominator /= nod;
}

int CRational::GetNOD(int a, int b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (static_cast<double>(m_numerator) / static_cast<double>(m_denominator));
}

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(CRational const& value)
{
	*this = *this + value;

	return *this;
}

CRational& CRational::operator-=(CRational const& value)
{
	*this += -value;

	return *this;
}

CRational& CRational::operator*=(CRational const& value)
{
	*this = *this * value;

	return *this;
}

CRational& CRational::operator/=(CRational const& value)
{
	*this = *this / value;

	return *this;
}

CRational const operator+(CRational const& value1, CRational const& value2)
{
	return CRational(value1.GetNumerator() * value2.GetDenominator() + value2.GetNumerator() * value1.GetDenominator(), value1.GetDenominator() * value2.GetDenominator());
}

CRational const operator-(CRational const& value1, CRational const& value2)
{
	return value1 + (-value2);
}

CRational const operator*(CRational const& value1, CRational const& value2)
{
	return CRational(value1.GetNumerator() * value2.GetNumerator(), value1.GetDenominator() * value2.GetDenominator());
}

CRational const operator/(CRational const& value1, CRational const& value2)
{
	return CRational(value2.GetDenominator(), value2.GetNumerator()) * value1;
}

bool operator==(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue - secondValue).GetNumerator() == 0;
}

bool operator!=(CRational const& value1, CRational const& value2)
{
	return !(value1 == value2);
}

bool operator<(CRational const& value1, CRational const& value2)
{
	return (value1.GetNumerator() * value2.GetDenominator() < value2.GetNumerator() * value1.GetDenominator());
}

bool operator<=(CRational const& value1, CRational const& value2)
{
	return (value1 < value2) || (value1 == value2);
}

bool operator>(CRational const& value1, CRational const& value2)
{
	return !(value1 <= value2);
}

bool operator>=(CRational const& value1, CRational const& value2)
{
	return !(value1 < value2);
}

std::ostream& operator<<(std::ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}

std::istream& operator>>(std::istream& input, CRational& rational)
{
	int numerator;
	int denominator;

	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit);
	}

	return input;
}
