#pragma once
#include "stdafx.h"
#include "IPerson.h"

class ITeacher : public IPerson
{
public:
	virtual std::string GetSubjectName() const = 0;
};
