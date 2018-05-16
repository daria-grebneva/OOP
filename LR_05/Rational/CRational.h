#pragma once

#include "stdafx.h"

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	const CRational operator-() const;
	const CRational operator+() const;

	CRational& operator+=(CRational const& value);
	CRational& operator-=(CRational const& value);
	CRational& operator*=(CRational const& value);
	CRational& operator/=(CRational const& value);

private:
	int m_numerator;
	int m_denominator;
	int GetNOD(int a, int b);
	void Normalize();
};

CRational const operator+(CRational const& firstValue, CRational const& secondValue);
CRational const operator-(CRational const& firstValue, CRational const& secondValue);
CRational const operator*(CRational const& firstValue, CRational const& secondValue);
CRational const operator/(CRational const& firstValue, CRational const& secondValue);

bool operator==(CRational const& firstValue, CRational const& secondValue);
bool operator!=(CRational const& firstValue, CRational const& secondValue);
bool operator<(CRational const& firstValue, CRational const& secondValue);
bool operator<=(CRational const& firstValue, CRational const& secondValue);
bool operator>(CRational const& firstValue, CRational const& secondValue);
bool operator>=(CRational const& firstValue, CRational const& secondValue);

std::ostream& operator<<(std::ostream& output, CRational const& rational);
std::istream& operator>>(std::istream& input, CRational& rational);
