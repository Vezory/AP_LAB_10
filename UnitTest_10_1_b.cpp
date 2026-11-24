#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TESTING
#include "Lab_10_1_b.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101b
{
    TEST_CLASS(UnitTest101b)
    {
    public:
        TEST_METHOD(TestUnionAndCountHighAverage)
        {
            const int N = 3;
            Student students[N];

            students[0].prizv = "Іваненко";
            students[0].kurs = 1;
            students[0].spec = KN;
            students[0].fizyka = 5;
            students[0].matematika = 5;
            students[0].programuvannya = 5;          // сер. бал = 5.00

            students[1].prizv = "Петренко";
            students[1].kurs = 2;
            students[1].spec = INF;
            students[1].fizyka = 4;
            students[1].matematika = 4;
            students[1].chyselni_metody = 4;         // сер. бал = 4.00

            students[2].prizv = "Сидоренко";
            students[2].kurs = 1;
            students[2].spec = ME;
            students[2].fizyka = 5;
            students[2].matematika = 4;
            students[2].pedagogika = 5;              // сер. бал = 4.67

            Assert::AreEqual(5, GetThirdGrade(students[0]));
            Assert::AreEqual(4, GetThirdGrade(students[1]));
            Assert::AreEqual(5, GetThirdGrade(students[2]));
            Assert::AreEqual(2, CountHighAverage(students, N));
        }

        TEST_METHOD(TestBestSubjectUnion)
        {
            const int N = 3;
            Student students[N];

            students[0].prizv = "Іваненко";
            students[0].kurs = 1;
            students[0].spec = KN;
            students[0].fizyka = 4;
            students[0].matematika = 4;
            students[0].programuvannya = 5;

            students[1].prizv = "Петренко";
            students[1].kurs = 2;
            students[1].spec = INF;
            students[1].fizyka = 4;
            students[1].matematika = 4;
            students[1].chyselni_metody = 4;

            students[2].prizv = "Сидоренко";
            students[2].kurs = 1;
            students[2].spec = ME;
            students[2].fizyka = 4;
            students[2].matematika = 4;
            students[2].pedagogika = 3;

            Assert::AreEqual(string("Програмування"), BestSubject(students, N));
        }
    };
}
