#include "stdafx.h"
#include "CAdvancedStudent.h"
#include "CPersonImpl.h"

CAdvancedStudent::CAdvancedStudent(const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& address,
	const std::string& universityName,
	size_t studentTicketNumber,
	std::string thesisTheme)
	: CStudentImpl<IAdvancedStudent>(name, surname, patronymic, address, universityName, studentTicketNumber)
	, m_dissertationTopic(thesisTheme)
{
}

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}
