#include "pch.h"
#include "CppUnitTest.h"

#define UNIT_TESTING
#include "Lab_10_2_a.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102a
{
    TEST_CLASS(UnitTest102a)
    {
    public:
        TEST_METHOD(TestPhysicalSortAndBinSearch)
        {
            const int N = 4;
            Student students[N] = {
                { "Антоненко", 1, KN,  5, 4, 5 },   // avg = 4.67, inf = 5
                { "Яковенко",  2, INF, 4, 5, 5 },   // avg = 4.67, inf = 5
                { "Петренко",  1, ME,  5, 5, 4 },   // avg = 4.67, inf = 4
                { "Коваль",    2, FI,  4, 4, 4 }    // avg = 4.00, inf = 4
            };

            Sort(students, N);
            // Порядок після Sort (сер. бал зр. -> 3-й предм. зр. -> прізвище спад.):
            // 0: Коваль (4.00, 4)
            // 1: Петренко (4.67, 4)
            // 2: Яковенко (4.67, 5)
            // 3: Антоненко (4.67, 5)
            Assert::AreEqual(string("Коваль"), students[0].prizv);
            Assert::AreEqual(string("Петренко"), students[1].prizv);
            Assert::AreEqual(string("Яковенко"), students[2].prizv);
            Assert::AreEqual(string("Антоненко"), students[3].prizv);

            // Пошук як за точним дробом, так і за округленим значенням 4.67
            Assert::AreEqual(1, BinSearch(students, N, "Петренко", 4.67, 4));
            Assert::AreEqual(3, BinSearch(students, N, "Антоненко", (5.0 + 4.0 + 5.0) / 3.0, 5));
            Assert::AreEqual(-1, BinSearch(students, N, "Сидоренко", 5.0, 5));
        }

        TEST_METHOD(TestIndexSort)
        {
            const int N = 4;
            Student students[N] = {
                { "Яковенко",  2, INF, 4, 5, 5 },   // 0: avg 4.67, inf 5
                { "Коваль",    2, FI,  4, 4, 4 },   // 1: avg 4.00, inf 4
                { "Антоненко", 1, KN,  5, 4, 5 },   // 2: avg 4.67, inf 5
                { "Петренко",  1, ME,  5, 5, 4 }    // 3: avg 4.67, inf 4
            };

            int* I = IndexSort(students, N);
            // Індексний порядок (сер. бал зр. -> 3-й предм. зр. -> прізвище алфавіт):
            // 1 (Коваль) -> 3 (Петренко) -> 2 (Антоненко) -> 0 (Яковенко)
            Assert::AreEqual(1, I[0]);
            Assert::AreEqual(3, I[1]);
            Assert::AreEqual(2, I[2]);
            Assert::AreEqual(0, I[3]);
            // Вихідний масив не змінився
            Assert::AreEqual(string("Яковенко"), students[0].prizv);
            delete[] I;
        }
    };
}
