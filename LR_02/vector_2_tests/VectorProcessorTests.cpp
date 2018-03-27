#include "stdafx.h"
#include "..\vector_2\vector_2.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// ������� ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// ������� ������ ������ �� ������� �������
	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}

	// ��� ��������� ������� � ����� ������
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_one_number)
		// ������ �������� ��� ����� �� ���� ����
		BOOST_AUTO_TEST_CASE(should_multiply_this_number_by_itself)
		{
			vector<double> numbers = { -1 };
			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual(numbers,
				{ (-1 * -1) }));
		}
	BOOST_AUTO_TEST_SUITE_END()

	// ��� ��������� ������� � ����������� ����������
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_several_elements)
		// ������ �������� �� ����������� ������� �� ������ ������� �������
		BOOST_AUTO_TEST_CASE(should_multiply_this_number_on_each_element)
		{
			vector<double> numbers = { -1.2, 1.2, 2.3, 3.2 };
			ProcessVector(numbers);

			const double minNumber = -1.2;
			BOOST_CHECK(VectorsAreEqual(numbers,
				{ (-1.2 * minNumber), (1.2 * minNumber), (2.3 * minNumber), (3.2 * minNumber) }));
		}
	BOOST_AUTO_TEST_SUITE_END()

	// ��� ��������� ������� � �������� ����������
	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_zero_elements)
		// ������ �������� ���� �� ������ ������� �������
		BOOST_AUTO_TEST_CASE(should_multiply_zero_on_each_element)
		{
			vector<double> numbers = { 0, 0, 0, 0 };
			ProcessVector(numbers);

			const double minNumber = 0;
			BOOST_CHECK(VectorsAreEqual(numbers,
				{ (0 * minNumber), (0 * minNumber), (0 * minNumber), (0 * minNumber) }));
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
