#define UNIT_TESTING
#include "Lab_10_1_b.cpp"
#include <cassert>
#include <iostream>

void TestLab10_1_b() {
    const int N = 3;
    Student students[N];
    
    // Student 0: KN, grades: fiz=5, mat=5, prog=5 -> avg = 5.0 (> 4.5)
    students[0].prizv = "Іваненко";
    students[0].kurs = 1;
    students[0].spec = KN;
    students[0].fizyka = 5;
    students[0].matematika = 5;
    students[0].programuvannya = 5;

    // Student 1: INF, grades: fiz=4, mat=4, chis=4 -> avg = 4.0 (<= 4.5)
    students[1].prizv = "Петренко";
    students[1].kurs = 2;
    students[1].spec = INF;
    students[1].fizyka = 4;
    students[1].matematika = 4;
    students[1].chyselni_metody = 4;

    // Student 2: ME, grades: fiz=5, mat=4, pedag=5 -> avg = 4.67 (> 4.5)
    students[2].prizv = "Сидоренко";
    students[2].kurs = 1;
    students[2].spec = ME;
    students[2].fizyka = 5;
    students[2].matematika = 4;
    students[2].pedagogika = 5;

    // Test CountHighAverage
    int count = CountHighAverage(students, N);
    assert(count == 2);
    std::cout << "[TEST PASSED] CountHighAverage: expected 2, got " << count << std::endl;

    // Test GetThirdGrade
    assert(GetThirdGrade(students[0]) == 5);
    assert(GetThirdGrade(students[1]) == 4);
    assert(GetThirdGrade(students[2]) == 5);
    std::cout << "[TEST PASSED] GetThirdGrade for union variants passed" << std::endl;

    // Test AverageGrade
    double avg0 = AverageGrade(students[0]);
    assert(avg0 == 5.0);
    std::cout << "[TEST PASSED] AverageGrade: expected 5.0, got " << avg0 << std::endl;

    // Test BestSubject
    // Fizyka: (5+4+5)/3 = 4.67
    // Matematika: (5+4+4)/3 = 4.33
    // Programuvannya: 5.0
    // Chyselni: 4.0
    // Pedag: 5.0
    // Best will be Programuvannya or Pedagogy (both 5.0)
    std::string best = BestSubject(students, N);
    assert(best == "Програмування" || best == "Педагогіка");
    std::cout << "[TEST PASSED] BestSubject: got '" << best << "'" << std::endl;

    std::cout << "\nALL UNIT TESTS FOR LAB 10.1.b PASSED SUCCESSFULLY!" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    TestLab10_1_b();
    return 0;
}
