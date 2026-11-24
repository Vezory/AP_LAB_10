#define UNIT_TESTING
#include "Lab_10_2_a.cpp"
#include <cassert>
#include <iostream>

void TestLab10_2_a() {
    const int N = 3;
    Student students[N] = {
        { "Сидоренко", 1, ME, 5, 5, 5 },   // avg = 5.0, inf = 5
        { "Іваненко",  2, KN, 4, 4, 4 },   // avg = 4.0, inf = 4
        { "Петренко",  1, INF, 4, 5, 5 }   // avg = 4.67, inf = 5
    };

    // Test Sort
    Sort(students, N);
    // After Sort (ascending by avg):
    // 1st: Іваненко (4.0)
    // 2nd: Петренко (4.67)
    // 3rd: Сидоренко (5.0)
    assert(students[0].prizv == "Іваненко");
    assert(students[1].prizv == "Петренко");
    assert(students[2].prizv == "Сидоренко");
    std::cout << "[TEST PASSED] Sort physical ordering verified" << std::endl;

    // Test BinSearch
    int foundIdx = BinSearch(students, N, "Петренко", (4.0 + 5.0 + 5.0) / 3.0, 5);
    assert(foundIdx == 1);
    std::cout << "[TEST PASSED] BinSearch found student at index " << foundIdx << std::endl;

    int notFound = BinSearch(students, N, "Коваль", 5.0, 5);
    assert(notFound == -1);
    std::cout << "[TEST PASSED] BinSearch returned -1 for non-existent student" << std::endl;

    // Test IndexSort
    int* I = IndexSort(students, N);
    assert(I[0] == 0 && I[1] == 1 && I[2] == 2);
    delete[] I;
    std::cout << "[TEST PASSED] IndexSort verified" << std::endl;

    std::cout << "\nALL UNIT TESTS FOR LAB 10.2.a PASSED SUCCESSFULLY!" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TestLab10_2_a();
    return 0;
}
