#include "stdafx.h"
#include "CMyString.h"

using namespace std;

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

void CMyString::CreateString(const char* pString, size_t length)
{
	m_pChars = std::make_unique<char[]>(length + 1);
	memcpy(m_pChars.get(), pString, length + 1);
	m_length = length;
}

CMyString::CMyString(const char* pString, size_t length)
{
	CreateString(pString, length);
	m_pChars[length] = '\0';
}

CMyString::CMyString(const CMyString& other)
{
	if (other.m_length > 0)
	{
		CreateString(other.m_pChars.get(), other.m_length);
	}
}

CMyString::CMyString(CMyString&& other)
	: m_pChars(std::move(other.m_pChars))
	, m_length(other.m_length)
{
	other.m_length = 0;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

void CMyString::Clear()
{
	m_length = 0;
	if (m_pChars)
	{
		m_pChars.reset();
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	const char nullableString[] = "";
	if (m_pChars)
	{
		return m_pChars.get();
	}
	return nullableString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if ((!m_pChars) || (start == length))
	{
		return "";
	}
	else if (start >= m_length || start > length || start + length > m_length)
	{
		throw out_of_range("Out of range");
	}
	else if (length > m_length)
	{
		length = m_length;
	}
	return CMyString(&m_pChars[start], length);
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		swap(m_pChars, other.m_pChars);
		swap(m_length, other.m_length);
		other.Clear();
	}

	return *this;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		std::swap(m_pChars, tmp.m_pChars);
		std::swap(m_length, tmp.m_length);
	}

	return *this;
}

CMyString const CMyString::operator+(const CMyString& string) const
{
	auto tmp = std::make_unique<char[]>(m_length + string.m_length + 1);
	memcpy(tmp.get(), m_pChars.get(), m_length);
	memcpy(tmp.get() + m_length, string.m_pChars.get(), string.m_length + 1);
	tmp[m_length + string.m_length] = '\0';

	return CMyString(tmp.get(), m_length + string.m_length);
}

CMyString const operator+(const std::string& string1, const CMyString& string2)
{
	auto temp = CMyString(string1) + string2;
	return temp;
}

CMyString const operator+(const char* string1, const CMyString& string2)
{
	return CMyString(string1) + string2;
}

CMyString const CMyString::operator+=(const CMyString& string)
{
	return *this = *this + string;
}

bool CMyString::operator==(const CMyString& string) const
{
	if (m_length != string.m_length)
	{
		return false;
	}

	return memcmp(m_pChars.get(), string.m_pChars.get(), m_length) == 0;
}

bool CMyString::operator!=(const CMyString& string) const
{
	return !(*this == string);
}

char const& CMyString::operator[](size_t index) const
{
	if ((index >= m_length) || (index < 0))
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	if ((index >= m_length) || (index < 0))
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_pChars[index];
}

bool CMyString::operator<(const CMyString& string) const
{
	if (m_length == string.m_length)
	{
		return (memcmp(m_pChars.get(), string.m_pChars.get(), m_length) < 0);
	}
	return (m_length < string.m_length);
}

bool CMyString::operator>=(const CMyString& string) const
{
	return !(*this < string);
}

bool CMyString::operator>(const CMyString& string) const
{
	if (m_length == string.m_length)
	{
		return (memcmp(m_pChars.get(), string.m_pChars.get(), m_length) > 0);
	}
	return (m_length > string.m_length);
}

bool CMyString::operator<=(const CMyString& string) const
{
	return !(*this > string);
}

std::istream& operator>>(istream& strm, CMyString& string)
{
	std::string tStr;
	strm >> tStr;
	string = tStr;

	return strm;
}

std::ostream& operator<<(std::ostream& strm, const CMyString& string)
{
	strm << string.GetStringData();

	return strm;
}
