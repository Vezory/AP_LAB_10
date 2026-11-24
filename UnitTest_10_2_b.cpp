#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TESTING
#include "Lab_10_2_b.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102b
{
    TEST_CLASS(UnitTest102b)
    {
    public:
        TEST_METHOD(TestPhysicalSortAndBinSearchUnion)
        {
            const int N = 4;
            Student students[N];

            students[0].prizv = "Антоненко"; students[0].kurs = 1; students[0].spec = KN;
            students[0].fizyka = 5; students[0].matematika = 4; students[0].programuvannya = 5;   // 4.67, 5

            students[1].prizv = "Яковенко";  students[1].kurs = 2; students[1].spec = INF;
            students[1].fizyka = 4; students[1].matematika = 5; students[1].chyselni_metody = 5;  // 4.67, 5

            students[2].prizv = "Петренко";  students[2].kurs = 1; students[2].spec = ME;
            students[2].fizyka = 5; students[2].matematika = 5; students[2].pedagogika = 4;       // 4.67, 4

            students[3].prizv = "Коваль";    students[3].kurs = 2; students[3].spec = FI;
            students[3].fizyka = 4; students[3].matematika = 4; students[3].pedagogika = 4;       // 4.00, 4

            Sort(students, N);
            Assert::AreEqual(string("Коваль"), students[0].prizv);
            Assert::AreEqual(string("Петренко"), students[1].prizv);
            Assert::AreEqual(string("Яковенко"), students[2].prizv);
            Assert::AreEqual(string("Антоненко"), students[3].prizv);

            Assert::AreEqual(2, BinSearch(students, N, "Яковенко", 4.67, 5));
            Assert::AreEqual(1, BinSearch(students, N, "Петренко", 14.0 / 3.0, 4));
            Assert::AreEqual(-1, BinSearch(students, N, "Мельник", 5.0, 5));
        }

        TEST_METHOD(TestIndexSortUnion)
        {
            const int N = 3;
            Student students[N];

            students[0].prizv = "Яковенко";  students[0].kurs = 2; students[0].spec = INF;
            students[0].fizyka = 4; students[0].matematika = 5; students[0].chyselni_metody = 5;  // 4.67, 5

            students[1].prizv = "Коваль";    students[1].kurs = 2; students[1].spec = FI;
            students[1].fizyka = 4; students[1].matematika = 4; students[1].pedagogika = 4;       // 4.00, 4

            students[2].prizv = "Антоненко"; students[2].kurs = 1; students[2].spec = KN;
            students[2].fizyka = 5; students[2].matematika = 4; students[2].programuvannya = 5;   // 4.67, 5

            int* I = IndexSort(students, N);
            Assert::AreEqual(1, I[0]); // Коваль (4.00)
            Assert::AreEqual(2, I[1]); // Антоненко (4.67, алфавіт)
            Assert::AreEqual(0, I[2]); // Яковенко (4.67, алфавіт)
            Assert::AreEqual(string("Яковенко"), students[0].prizv);
            delete[] I;
        }
    };
}
