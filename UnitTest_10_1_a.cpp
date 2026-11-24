#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TESTING
#include "Lab_10_1_a.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101a
{
    TEST_CLASS(UnitTest101a)
    {
    public:
        TEST_METHOD(TestCountHighAverage)
        {
            const int N = 3;
            Student students[N] = {
                { "Іваненко", 1, KN, 5, 5, 5 },      // сер. бал = 5.00 (> 4.5)
                { "Петренко", 2, INF, 4, 4, 5 },     // сер. бал = 4.33 (<= 4.5)
                { "Сидоренко", 1, ME, 5, 4, 5 }      // сер. бал = 4.67 (> 4.5)
            };

            Assert::AreEqual(2, CountHighAverage(students, N));
            Assert::AreEqual(5.0, AverageGrade(students[0]), 1e-6);
        }

        TEST_METHOD(TestBestSubject)
        {
            const int N = 3;
            Student students[N] = {
                { "Іваненко", 1, KN, 5, 4, 5 },
                { "Петренко", 2, INF, 4, 4, 5 },
                { "Сидоренко", 1, ME, 4, 5, 5 }
            };

            // Фізика: 4.33, Математика: 4.33, Інформатика: 5.00
            Assert::AreEqual(string("Інформатика"), BestSubject(students, N));
        }
    };
}
