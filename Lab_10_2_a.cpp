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

double AverageGrade(const Student& s) {
    return (s.fizyka + s.matematika + s.informatika) / 3.0;
}

void Print(const Student* p, const int N) {
    cout << "==========================================================================================" << endl;
    cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Інформатика | Сер. бал |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        double avg = AverageGrade(p[i]);
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

// 1. Фізичне сортування (Варіант 16):
// 1 черга: за спаданням/зростанням середнього балу
// 2 черга: за значенням оцінки з 3-го предмету (інформатика)
// 3 черга: за прізвищем за спаданням (в зворотному до алфавітного порядку)
void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            double avg1 = AverageGrade(p[i1]);
            double avg2 = AverageGrade(p[i1 + 1]);

            if ((avg1 > avg2) ||
                (avg1 == avg2 && p[i1].informatika > p[i1 + 1].informatika) ||
                (avg1 == avg2 && p[i1].informatika == p[i1 + 1].informatika && p[i1].prizv < p[i1 + 1].prizv)) {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

// 2. Індексне сортування (Варіант 16):
// 1 черга: за середнім балом
// 2 черга: за оцінкою з 3-го предмету
// 3 черга: за прізвищем (за алфавітом)
int* IndexSort(const Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }
    int tmp;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            double avg1 = AverageGrade(p[I[i1]]);
            double avg2 = AverageGrade(p[I[i1 + 1]]);

            if ((avg1 > avg2) ||
                (avg1 == avg2 && p[I[i1]].informatika > p[I[i1 + 1]].informatika) ||
                (avg1 == avg2 && p[I[i1]].informatika == p[I[i1 + 1]].informatika && p[I[i1]].prizv > p[I[i1 + 1]].prizv)) {
                tmp = I[i1];
                I[i1] = I[i1 + 1];
                I[i1 + 1] = tmp;
            }
        }
    }
    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N) {
    cout << "==========================================================================================" << endl;
    cout << "| № |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Інформатика | Сер. бал |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        int idx = I[i];
        double avg = AverageGrade(p[idx]);
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(12) << left << p[idx].prizv << " "
             << "| " << setw(4) << right << p[idx].kurs << " "
             << "| " << setw(15) << left << specStr[p[idx].spec] << " "
             << "| " << setw(6) << right << p[idx].fizyka << " "
             << "| " << setw(10) << right << p[idx].matematika << " "
             << "| " << setw(11) << right << p[idx].informatika << " "
             << "| " << setw(8) << fixed << setprecision(2) << right << avg << " |" << endl;
    }
    cout << "==========================================================================================" << endl;
}

// 3. Бінарний пошук (Варіант 16):
// Шукає студента за прізвищем, середнім балом та оцінкою з 3-го предмету (інформатики)
int BinSearch(const Student* p, const int N, const string prizv, const double avg, const int thirdGrade) {
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        double curAvg = AverageGrade(p[m]);

        if (curAvg == avg && p[m].informatika == thirdGrade && p[m].prizv == prizv) {
            return m;
        }

        // Порівняння відповідно до критерію фізичного сортування
        if ((curAvg < avg) ||
            (curAvg == avg && p[m].informatika < thirdGrade) ||
            (curAvg == avg && p[m].informatika == thirdGrade && p[m].prizv > prizv)) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return -1;
}

#ifndef UNIT_TESTING
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    Student* p = new Student[N];
    int* I = nullptr;

    int menuItem;
    do {
        cout << endl << "---------------------------" << endl;
        cout << "ГОЛОВНЕ МЕНЮ" << endl;
        cout << "[1] - Введення даних з клавіатури" << endl;
        cout << "[2] - Вивід таблиці на екран" << endl;
        cout << "[3] - Фізичне впорядкування (сортування)" << endl;
        cout << "[4] - Індексне впорядкування та вивід" << endl;
        cout << "[5] - Бінарний пошук студента" << endl;
        cout << "[0] - Вихід з програми" << endl;
        cout << "Оберіть дію: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив фізично впорядковано." << endl;
            Print(p, N);
            break;
        case 4:
            if (I != nullptr) delete[] I;
            I = IndexSort(p, N);
            cout << "Масив індексно впорядковано:" << endl;
            PrintIndexSorted(p, I, N);
            break;
        case 5: {
            string searchPrizv;
            double searchAvg;
            int searchThird;
            cout << "Введіть прізвище: "; cin >> searchPrizv;
            cout << "Введіть середній бал: "; cin >> searchAvg;
            cout << "Введіть оцінку з інформатики: "; cin >> searchThird;

            int foundIdx = BinSearch(p, N, searchPrizv, searchAvg, searchThird);
            if (foundIdx != -1) {
                cout << "Студента знайдено на позиції № " << foundIdx + 1 << "!" << endl;
            } else {
                cout << "Студента з такими параметрами не знайдено." << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Некоректний вибір! Спробуйте знову." << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    if (I != nullptr) delete[] I;
    return 0;
}
#endif
