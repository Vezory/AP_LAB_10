#define UNIT_TESTING
#include "Lab_10_1_a.cpp"
#include <cassert>
#include <iostream>

void TestLab10_1_a() {
    const int N = 3;
    Student students[N] = {
        { "Іваненко", 1, KN, 5, 5, 5 },      // avg = 5.0 (> 4.5)
        { "Петренко", 2, INF, 4, 4, 5 },     // avg = 4.33 (<= 4.5)
        { "Сидоренко", 1, ME, 5, 4, 5 }      // avg = 4.67 (> 4.5)
    };

    // Test CountHighAverage
    int count = CountHighAverage(students, N);
    assert(count == 2);
    std::cout << "[TEST PASSED] CountHighAverage: expected 2, got " << count << std::endl;

    // Test BestSubject
    // Fizyka: (5 + 4 + 5)/3 = 14/3 = 4.67
    // Matematika: (5 + 4 + 4)/3 = 13/3 = 4.33
    // Informatika: (5 + 5 + 5)/3 = 15/3 = 5.0
    // Best: "Інформатика"
    std::string best = BestSubject(students, N);
    assert(best == "Інформатика");
    std::cout << "[TEST PASSED] BestSubject: expected 'Інформатика', got '" << best << "'" << std::endl;

    // Test AverageGrade
    double avg0 = AverageGrade(students[0]);
    assert(avg0 == 5.0);
    std::cout << "[TEST PASSED] AverageGrade: expected 5.0, got " << avg0 << std::endl;

    std::cout << "\nALL UNIT TESTS FOR LAB 10.1.a PASSED SUCCESSFULLY!" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TestLab10_1_a();
    return 0;
}
