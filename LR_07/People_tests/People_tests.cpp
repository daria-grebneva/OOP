#include "stdafx.h"
#include "../People/CAdvancedStudent.cpp"
#include "../People/CPupil.cpp"
#include "../People/CStudent.cpp"
#include "../People/CTeacher.cpp"
#include "../People/CWorker.cpp"

struct Pupil
{
	const std::string name = "Dasha";
	const std::string surname = "Grebneva";
	const std::string patronymic = "Andreevna";
	const std::string address = "bulvar Uraeva 9a";
	const std::string schoolName = "School 28";
	const std::string schoolClass = "11B";
	CPupil pupil;
	Pupil()
		: pupil(name, surname, patronymic, address, schoolName, schoolClass)
	{
	}
};

TEST_CASE_METHOD(Pupil, "Get pupils information")
{
	SECTION("name")
	{
		REQUIRE(pupil.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(pupil.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(pupil.GetPatronymic() == patronymic);
	}
	SECTION("address")
	{
		REQUIRE(pupil.GetAddress() == address);
	}
	SECTION("school name ")
	{
		REQUIRE(pupil.GetSchoolName() == schoolName);
	}
	SECTION("school class")
	{
		REQUIRE(pupil.GetSchoolClass() == schoolClass);
	}
}

struct Student
{
	const std::string name = "Dasha";
	const std::string surname = "Grebneva";
	const std::string patronymic = "Andreevna";
	const std::string address = "bulvar Uraeva 9a";
	const std::string universityName = "PGTU";
	const size_t studentCardNumber = 1160501022;
	CStudent student;
	Student()
		: student(name, surname, patronymic, address, universityName, studentCardNumber)
	{
	}
};

TEST_CASE_METHOD(Student, "Get students information")
{
	SECTION("name")
	{
		REQUIRE(student.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(student.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(student.GetPatronymic() == patronymic);
	}
	SECTION("address")
	{
		REQUIRE(student.GetAddress() == address);
	}
	SECTION("student card number")
	{
		REQUIRE(student.GetStudentCardNumber() == studentCardNumber);
	}
	SECTION("university name")
	{
		REQUIRE(student.GetUniversityName() == universityName);
	}
}

struct AdvancedStudent
{
	const std::string name = "Dasha";
	const std::string surname = "Grebneva";
	const std::string patronymic = "Andreevna";
	const std::string address = "bulvar Uraeva 9a";
	const std::string universityName = "PGTU";
	const size_t studentCardNumber = 1160501022;
	const std::string dissertationTopic = "Compilers";
	CAdvancedStudent advancedStudent;
	AdvancedStudent()
		: advancedStudent(name, surname, patronymic, address, universityName, studentCardNumber, dissertationTopic)
	{
	}
};

TEST_CASE_METHOD(AdvancedStudent, "Get advanced students information")
{
	SECTION("name")
	{
		REQUIRE(advancedStudent.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(advancedStudent.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(advancedStudent.GetPatronymic() == patronymic);
	}
	SECTION("address")
	{
		REQUIRE(advancedStudent.GetAddress() == address);
	}
	SECTION("university name")
	{
		REQUIRE(advancedStudent.GetUniversityName() == universityName);
	}
	SECTION("student card number")
	{
		REQUIRE(advancedStudent.GetStudentCardNumber() == studentCardNumber);
	}
	SECTION("dissertation topic")
	{
		REQUIRE(advancedStudent.GetDissertationTopic() == dissertationTopic);
	}
}

struct Teacher
{
	const std::string name = "Dasha";
	const std::string surname = "Grebneva";
	const std::string patronymic = "Andreevna";
	const std::string address = "bulvar Uraeva 9a";
	const std::string subjectName = "mathematics";
	CTeacher teacher;
	Teacher()
		: teacher(name, surname, patronymic, address, subjectName)
	{
	}
};

TEST_CASE_METHOD(Teacher, "Get teachers indormation")
{
	SECTION("name")
	{
		REQUIRE(teacher.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(teacher.GetSurname() == surname);
	}
	SECTION("middle name")
	{
		REQUIRE(teacher.GetPatronymic() == patronymic);
	}
	SECTION("address")
	{
		REQUIRE(teacher.GetAddress() == address);
	}
	SECTION("subject name")
	{
		REQUIRE(teacher.GetSubjectName() == subjectName);
	}
}

struct Worker
{
	const std::string name = "Dasha";
	const std::string surname = "Grebneva";
	const std::string patronymic = "Andreevna";
	const std::string address = "bulvar Uraeva 9a";
	const std::string specialty = "programmer";
	CWorker worker;
	Worker()
		: worker(name, surname, patronymic, address, specialty)
	{
	}
};

TEST_CASE_METHOD(Worker, "Get workers information")
{
	SECTION("name")
	{
		REQUIRE(worker.GetName() == name);
	}
	SECTION("surname")
	{
		REQUIRE(worker.GetSurname() == surname);
	}
	SECTION("patronymic")
	{
		REQUIRE(worker.GetPatronymic() == patronymic);
	}
	SECTION("address")
	{
		REQUIRE(worker.GetAddress() == address);
	}
	SECTION("specialty")
	{
		REQUIRE(worker.GetSpecialty() == specialty);
	}
}
