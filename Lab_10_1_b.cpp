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
    union {
        int programuvannya;   // для Комп'ютерні науки
        int chyselni_metody;  // для Інформатика
        int pedagogika;       // для інших
    };
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
        switch (p[i].spec) {
        case KN:
            cout << "  оцінка з програмування: "; cin >> p[i].programuvannya;
            break;
        case INF:
            cout << "  оцінка з чисельних методів: "; cin >> p[i].chyselni_metody;
            break;
        case ME:
        case FI:
        case TN:
            cout << "  оцінка з педагогіки: "; cin >> p[i].pedagogika;
            break;
        }
        cout << endl;
    }
}

int GetThirdGrade(const Student& s) {
    switch (s.spec) {
    case KN: return s.programuvannya;
    case INF: return s.chyselni_metody;
    default: return s.pedagogika;
    }
}

double AverageGrade(const Student& s) {
    return (s.fizyka + s.matematika + GetThirdGrade(s)) / 3.0;
}

void Print(const Student* p, const int N) {
    cout << "=====================================================================================================================" << endl;
    cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Програмування | Чис. методи | Педагогіка | Сер. бал |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        double avg = AverageGrade(p[i]);
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(12) << left << p[i].prizv << " "
             << "| " << setw(4) << right << p[i].kurs << " "
             << "| " << setw(15) << left << specStr[p[i].spec] << " "
             << "| " << setw(6) << right << p[i].fizyka << " "
             << "| " << setw(10) << right << p[i].matematika << " ";

        switch (p[i].spec) {
        case KN:
            cout << "| " << setw(13) << right << p[i].programuvannya << " "
                 << "| " << setw(11) << right << "-" << " "
                 << "| " << setw(10) << right << "-" << " ";
            break;
        case INF:
            cout << "| " << setw(13) << right << "-" << " "
                 << "| " << setw(11) << right << p[i].chyselni_metody << " "
                 << "| " << setw(10) << right << "-" << " ";
            break;
        case ME:
        case FI:
        case TN:
            cout << "| " << setw(13) << right << "-" << " "
                 << "| " << setw(11) << right << "-" << " "
                 << "| " << setw(10) << right << p[i].pedagogika << " ";
            break;
        }

        cout << "| " << setw(8) << fixed << setprecision(2) << right << avg << " |" << endl;
    }
    cout << "=====================================================================================================================" << endl;
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
    double sumFiz = 0, sumMat = 0;
    double sumProg = 0, sumChis = 0, sumPed = 0;
    int countProg = 0, countChis = 0, countPed = 0;

    for (int i = 0; i < N; i++) {
        sumFiz += p[i].fizyka;
        sumMat += p[i].matematika;
        switch (p[i].spec) {
        case KN:
            sumProg += p[i].programuvannya;
            countProg++;
            break;
        case INF:
            sumChis += p[i].chyselni_metody;
            countChis++;
            break;
        default:
            sumPed += p[i].pedagogika;
            countPed++;
            break;
        }
    }

    double avgFiz = sumFiz / N;
    double avgMat = sumMat / N;
    double avgProg = (countProg > 0) ? (sumProg / countProg) : -1.0;
    double avgChis = (countChis > 0) ? (sumChis / countChis) : -1.0;
    double avgPed = (countPed > 0) ? (sumPed / countPed) : -1.0;

    double maxAvg = avgFiz;
    string bestName = "Фізика";

    if (avgMat > maxAvg) {
        maxAvg = avgMat;
        bestName = "Математика";
    }
    if (avgProg > maxAvg) {
        maxAvg = avgProg;
        bestName = "Програмування";
    }
    if (avgChis > maxAvg) {
        maxAvg = avgChis;
        bestName = "Чисельні методи";
    }
    if (avgPed > maxAvg) {
        maxAvg = avgPed;
        bestName = "Педагогіка";
    }

    return bestName;
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
