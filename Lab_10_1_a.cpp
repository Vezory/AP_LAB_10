#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };
const string specStr[] = { "Комп. науки", "Інформатика", "Мат. та екон.", "Фіз. та інформ.", "Труд. навч." };

struct Student {
    string prizv;
    int kurs;
    Specialnist spec;
    int fizyka;
    int matematika;
    int informatika;
};

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << "  прізвище: "; getline(cin, p[i].prizv);
        cout << "  курс: "; cin >> p[i].kurs;
        cout << "  спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Мат. та екон., 3 - Фіз. та інформ., 4 - Труд. навч.): ";
        cin >> ispec;
        p[i].spec = (Specialnist)ispec;
        cout << "  оцінка з фізики: "; cin >> p[i].fizyka;
        cout << "  оцінка з математики: "; cin >> p[i].matematika;
        cout << "  оцінка з інформатики: "; cin >> p[i].informatika;
        cout << endl;
    }
}

void Print(const Student* p, const int N) {
    cout << "==========================================================================================" << endl;
    cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Інформатика | Сер. бал |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        double avg = (p[i].fizyka + p[i].matematika + p[i].informatika) / 3.0;
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(12) << left << p[i].prizv << " "
             << "| " << setw(4) << right << p[i].kurs << " "
             << "| " << setw(15) << left << specStr[p[i].spec] << " "
             << "| " << setw(6) << right << p[i].fizyka << " "
             << "| " << setw(10) << right << p[i].matematika << " "
             << "| " << setw(11) << right << p[i].informatika << " "
             << "| " << setw(8) << fixed << setprecision(2) << right << avg << " |" << endl;
    }
    cout << "==========================================================================================" << endl;
}

double AverageGrade(const Student& s) {
    return (s.fizyka + s.matematika + s.informatika) / 3.0;
}

// Завдання 1: Обчислити кількість студентів, середній бал яких вищий за 4,5
int CountHighAverage(const Student* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (AverageGrade(p[i]) > 4.5) {
            count++;
        }
    }
    return count;
}

// Завдання 2: Порівнюючи середні бали для кожного предмету, визначити предмет, середній бал якого найбільший
string BestSubject(const Student* p, const int N) {
    if (N <= 0) return "Немає даних";
    double sumFiz = 0, sumMat = 0, sumInf = 0;
    for (int i = 0; i < N; i++) {
        sumFiz += p[i].fizyka;
        sumMat += p[i].matematika;
        sumInf += p[i].informatika;
    }
    double avgFiz = sumFiz / N;
    double avgMat = sumMat / N;
    double avgInf = sumInf / N;

    if (avgFiz >= avgMat && avgFiz >= avgInf) {
        return "Фізика";
    } else if (avgMat >= avgFiz && avgMat >= avgInf) {
        return "Математика";
    } else {
        return "Інформатика";
    }
}

#ifndef UNIT_TESTING
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    Student* p = new Student[N];
    Create(p, N);
    Print(p, N);

    int countHigh = CountHighAverage(p, N);
    cout << "Кількість студентів із середнім балом вище 4.5: " << countHigh << endl;

    string best = BestSubject(p, N);
    cout << "Предмет із найбільшим середнім балом по групі: " << best << endl;

    delete[] p;
    return 0;
}
#endif
