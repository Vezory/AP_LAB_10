#define UNIT_TESTING
#include "Lab_10_2_b.cpp"
#include <cassert>
#include <iostream>

void TestLab10_2_b() {
    const int N = 3;
    Student students[N];
    
    // Student 0: KN, fiz=4, mat=4, prog=4 -> avg = 4.0, third = 4
    students[0].prizv = "Іваненко";
    students[0].kurs = 1;
    students[0].spec = KN;
    students[0].fizyka = 4;
    students[0].matematika = 4;
    students[0].programuvannya = 4;

    // Student 1: INF, fiz=5, mat=5, chis=5 -> avg = 5.0, third = 5
    students[1].prizv = "Сидоренко";
    students[1].kurs = 2;
    students[1].spec = INF;
    students[1].fizyka = 5;
    students[1].matematika = 5;
    students[1].chyselni_metody = 5;

    // Student 2: ME, fiz=4, mat=5, pedag=5 -> avg = 4.67, third = 5
    students[2].prizv = "Петренко";
    students[2].kurs = 1;
    students[2].spec = ME;
    students[2].fizyka = 4;
    students[2].matematika = 5;
    students[2].pedagogika = 5;

    // Test Sort
    Sort(students, N);
    // After Sort (ascending by avg):
    // 0: Іваненко (4.0)
    // 1: Петренко (4.67)
    // 2: Сидоренко (5.0)
    assert(students[0].prizv == "Іваненко");
    assert(students[1].prizv == "Петренко");
    assert(students[2].prizv == "Сидоренко");
    std::cout << "[TEST PASSED] Sort physical ordering with union verified" << std::endl;

    // Test BinSearch
    int foundIdx = BinSearch(students, N, "Петренко", (4.0 + 5.0 + 5.0) / 3.0, 5);
    assert(foundIdx == 1);
    std::cout << "[TEST PASSED] BinSearch found student at index " << foundIdx << std::endl;

    int notFound = BinSearch(students, N, "Мельник", 5.0, 5);
    assert(notFound == -1);
    std::cout << "[TEST PASSED] BinSearch returned -1 for non-existent student" << std::endl;

    // Test IndexSort
    int* I = IndexSort(students, N);
    assert(I[0] == 0 && I[1] == 1 && I[2] == 2);
    delete[] I;
    std::cout << "[TEST PASSED] IndexSort with union verified" << std::endl;

    std::cout << "\nALL UNIT TESTS FOR LAB 10.2.b PASSED SUCCESSFULLY!" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TestLab10_2_b();
    return 0;
}
