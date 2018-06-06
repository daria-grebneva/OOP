#include "stdafx.h"
#include "CTeacher.h"
#include "CPersonImpl.h"

CTeacher::CTeacher(const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& address,
	const std::string& subjectName)
	: CPersonImpl<ITeacher>(name, surname, patronymic, address)
	, m_subjectName(subjectName)
{
}

std::string CTeacher::GetSubjectName() const
{
	return m_subjectName;
}
