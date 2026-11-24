// ============================================================================
// Лабораторна робота № 10.1 (Рівень В)
// Дисципліна: "Алгоритмізація та програмування"
// Тема: Послідовний пошук в масиві структур з об’єднаннями
// Варіант: 16
// Студент: Новосад Захарій Володимирович, група РІ-13
// Викладач: Григорович В. Г.
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>            // забезпечення коректного відображення кирилиці

using namespace std;

// Перелічуваний тип для спеціальностей згідно з методичними вказівками
enum Specialnist { KN, INF, ME, FI, TN };

// Масив текстових назв спеціальностей для виводу у таблицю
const string specStr[] = { 
    "Комп. науки", 
    "Інформатика", 
    "Мат. та екон.", 
    "Фіз. та інформ.", 
    "Труд. навч." 
};

// Структура для представлення даних про студента (Рівень В - з об'єднанням union)
struct Student {
    string prizv;           // прізвище студента (літерний рядок)
    int kurs;               // курс (ціле число)
    Specialnist spec;       // спеціальність (значення з переліку Specialnist)
    int fizyka;             // оцінка з фізики (для всіх спеціальностей)
    int matematika;         // оцінка з математики (для всіх спеціальностей)
    
    // Анонімне об'єднання (union) для представлення 3-ї оцінки:
    // Усі поля всередині union займають одну й ту саму область оперативної пам'яті.
    // Розмір union дорівнює розміру найбільшого з полів (тут sizeof(int) = 4 байти).
    union {
        int programuvannya;   // 3-тя оцінка для спеціальності "Комп’ютерні науки"
        int chyselni_metody;  // 3-тя оцінка для спеціальності "Інформатика"
        int pedagogika;       // 3-тя оцінка для спеціальностей "Мат. та екон.", "Фіз. та інформ.", "Труд. навч."
    };
};

// ----------------------------------------------------------------------------
// ПРОТОТИПИ ФУНКЦІЙ
// ----------------------------------------------------------------------------
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
int GetThirdGrade(const Student& s);
double AverageGrade(const Student& s);
int CountHighAverage(const Student* p, const int N);
string BestSubject(const Student* p, const int N);

// ============================================================================
// ГОЛОВНА ФУНКЦІЯ ПРОГРАМИ
// ============================================================================
#ifndef UNIT_TESTING
int main() {
    // Встановлення кодової сторінки 1251 для коректного введення та виведення кирилиці
    SetConsoleCP(1251);       // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    int N; // кількість студентів у групі
    cout << "Введіть кількість студентів N: ";
    cin >> N;

    // Виділення динамічної пам'яті під масив структур з об'єднаннями
    Student* p = new Student[N];

    // Крок 1: Введення даних з клавіатури
    Create(p, N);

    // Крок 2: Виведення масиву у вигляді 9-колонкової таблиці з прочерками
    Print(p, N);

    // Крок 3: Виконання завдання 1 (Варіант 16) - підрахунок студентів із сер. балом > 4.5
    int countHigh = CountHighAverage(p, N);
    cout << "1. Кількість студентів, середній бал яких вищий за 4,5: " << countHigh << endl;

    // Крок 4: Виконання завдання 2 (Варіант 16) - визначення предмета з найбільшим середнім балом
    string best = BestSubject(p, N);
    cout << "2. Предмет, середній бал якого найбільший по групі: " << best << endl;

    // Звільнення динамічної пам'яті
    delete[] p;

    return 0;
}
#endif

// ============================================================================
// РЕАЛІЗАЦІЯ ФУНКЦІЙ
// ============================================================================

// Функція формування (введення) динамічного масиву структур з об'єднаннями
void Create(Student* p, const int N) {
    int ispec; // допоміжна змінна для номера спеціальності
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;

        // Очищення буфера клавіатури від залишкових символів '\n'
        cin.get();
        cin.sync();

        cout << "  прізвище: "; 
        getline(cin, p[i].prizv);

        cout << "  курс: "; 
        cin >> p[i].kurs;

        cout << "  спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Мат. та екон., 3 - Фіз. та інформ., 4 - Труд. навч.): ";
        cin >> ispec;
        p[i].spec = (Specialnist)ispec;

        cout << "  оцінка з фізики: "; 
        cin >> p[i].fizyka;

        cout << "  оцінка з математики: "; 
        cin >> p[i].matematika;

        // Залежно від спеціальності студента записуємо 3-тю оцінку у відповідне поле union
        switch (p[i].spec) {
        case KN:
            cout << "  оцінка з програмування: "; 
            cin >> p[i].programuvannya;
            break;
        case INF:
            cout << "  оцінка з чисельних методів: "; 
            cin >> p[i].chyselni_metody;
            break;
        case ME:
        case FI:
        case TN:
            cout << "  оцінка з педагогіки: "; 
            cin >> p[i].pedagogika;
            break;
        }
        cout << endl;
    }
}

// Допоміжна функція для отримання значення 3-ї оцінки з union залежно від спеціальності
int GetThirdGrade(const Student& s) {
    switch (s.spec) {
    case KN: 
        return s.programuvannya;
    case INF: 
        return s.chyselni_metody;
    default: 
        return s.pedagogika;
    }
}

// Допоміжна функція для обчислення індивідуального середнього балу студента
double AverageGrade(const Student& s) {
    // Додаємо фізику, математику та відповідну 3-тю оцінку з об'єднання
    return (s.fizyka + s.matematika + GetThirdGrade(s)) / 3.0;
}

// Функція виведення масиву у вигляді таблиці з 9 клітинками
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

        // Заповнюємо лише ту клітинку, яка відповідає профілю студента, в інші ставимо "-"
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

// Варіант 16. Завдання 1:
// Обчислення кількості студентів, чий середній бал вищий за 4.5
int CountHighAverage(const Student* p, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (AverageGrade(p[i]) > 4.5) {
            count++;
        }
    }
    return count;
}

// Варіант 16. Завдання 2:
// Визначення предмета з найбільшим середнім балом
string BestSubject(const Student* p, const int N) {
    if (N <= 0) return "Немає даних";

    double sumFiz = 0.0, sumMat = 0.0;
    double sumProg = 0.0, sumChis = 0.0, sumPed = 0.0;
    int countProg = 0, countChis = 0, countPed = 0;

    // Підсумовуємо оцінки для кожного навчального предмета
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
