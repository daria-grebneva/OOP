#pragma once
#include "CPersonImpl.h"

template <class Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl(const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& address,
		const std::string& universityName,
		size_t studentCardNumber)
		: CPersonImpl<Base>(name, surname, patronymic, address)
		, m_universityName(universityName)
		, m_studentCardNumber(studentCardNumber)
	{
	}

	std::string GetUniversityName() const
	{
		return m_universityName;
	}

	size_t GetStudentCardNumber() const
	{
		return m_studentCardNumber;
	}

private:
	std::string m_universityName;
	size_t m_studentCardNumber;
};
