// ============================================================================
// Лабораторна робота № 10.1 (Рівень В)
// Дисципліна: "Алгоритмізація та програмування"
// Тема: Послідовний пошук в масиві структур з об'єднаннями
// Варіант: 16
// Студент: Новосад Захарій Володимирович, група РІ-13
// Викладач: Григорович В. Г.
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>               // для очищення потоку cin при помилковому вводі
#include <Windows.h>            // забезпечення відображення кирилиці в консолі

using namespace std;

// Перелічуваний тип спеціальностей згідно з умовою лабораторної роботи
enum Specialnist { KN, INF, ME, FI, TN };

// Масив текстових назв спеціальностей для виводу в таблицю
string specStr[] = {
    "Комп. науки",
    "Інформатика",
    "Мат. та екон.",
    "Фіз. та інформ.",
    "Труд. навч."
};

// Структура даних про студента (Рівень В — із безіменним об'єднанням union)
struct Student {
    string prizv;               // прізвище студента (літерний рядок)
    int kurs;                   // курс навчання (ціле число)
    Specialnist spec;           // спеціальність (значення переліку Specialnist)
    int fizyka;                 // оцінка з фізики (для всіх спеціальностей)
    int matematika;             // оцінка з математики (для всіх спеціальностей)

    // Безіменне об'єднання (union):
    // Всі три поля ділять одну й ту саму область пам'яті розміром sizeof(int),
    // адже кожен студент вивчає лише один профільний 3-й предмет залежно від spec:
    union {
        int programuvannya;     // для спеціальності "Комп'ютерні науки" (KN)
        int chyselni_metody;    // для спеціальності "Інформатика" (INF)
        int pedagogika;         // для спеціальностей ME, FI, TN
    };
};

// ----------------------------------------------------------------------------
// ПРОТОТИПИ ФУНКЦІЙ
// ----------------------------------------------------------------------------
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int GetThirdGrade(const Student& s);
double AverageGrade(const Student& s);
int CountHighAverage(Student* p, const int N);
string BestSubject(Student* p, const int N);

// ============================================================================
// ГОЛОВНА ФУНКЦІЯ ПРОГРАМИ
// ============================================================================
#ifndef UNIT_TESTING
int main()
{                               // забезпечення відображення кирилиці:
    SetConsoleCP(1251);         // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251);   // встановлення сторінки win-cp1251 в потік виводу

    int N;                      // кількість студентів у групі

    // Введення кількості студентів із контролем коректності (N > 0)
    do {
        cout << "Введіть кількість студентів N: ";
        cin >> N;
        if (cin.fail() || N <= 0) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Помилка! Кількість студентів має бути додатним цілим числом." << endl;
            N = 0;
        }
    } while (N <= 0);

    // Виділення динамічної пам'яті під масив структур з об'єднаннями
    Student* p = new Student[N];

    // 1. Введення даних з клавіатури
    Create(p, N);

    // 2. Виведення масиву у вигляді таблиці з 9 клітинками (за зразком посібника)
    Print(p, N);

    // 3. Виконання завдання 1 (Варіант 16): кількість студентів із середнім балом > 4,5
    int countHigh = CountHighAverage(p, N);
    cout << "1. Кількість студентів, середній бал яких вищий за 4,5: " << countHigh << endl;

    // 4. Виконання завдання 2 (Варіант 16): предмет із найбільшим середнім балом
    string best = BestSubject(p, N);
    cout << "2. Предмет, середній бал якого найбільший по групі: " << best << endl;

    // Звільнення динамічно виділеної пам'яті
    delete[] p;

    return 0;
}
#endif

// ============================================================================
// РЕАЛІЗАЦІЯ ФУНКЦІЙ
// ============================================================================

// Функція формування (введення) динамічного масиву структур з об'єднаннями
void Create(Student* p, const int N)
{
    int ispec;                  // тимчасова змінна для зчитування номера спеціальності
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();              // очищуємо буфер клавіатури — бо залишаються символи
        cin.sync();             // "кінець рядка", які не дають ввести наступний літерний рядок

        cout << "    прізвище: "; getline(cin, p[i].prizv);

        // Введення курсу [1..6]
        do {
            cout << "    курс (1-6): ";
            cin >> p[i].kurs;
            if (cin.fail() || p[i].kurs < 1 || p[i].kurs > 6) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "    Помилка! Введіть курс від 1 до 6." << endl;
                p[i].kurs = 0;
            }
        } while (p[i].kurs < 1 || p[i].kurs > 6);

        // Введення спеціальності [0..4]
        do {
            cout << "    спеціальність (0 - Комп. науки, 1 - Інформатика, 2 - Мат. та екон., 3 - Фіз. та інформ., 4 - Труд. навч.): ";
            cin >> ispec;
            if (cin.fail() || ispec < 0 || ispec > 4) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "    Помилка! Введіть число від 0 до 4." << endl;
                ispec = -1;
            }
        } while (ispec < 0 || ispec > 4);
        p[i].spec = (Specialnist)ispec;

        // Оцінка з фізики [1..5]
        do {
            cout << "    оцінка з фізики (1-5): ";
            cin >> p[i].fizyka;
            if (cin.fail() || p[i].fizyka < 1 || p[i].fizyka > 5) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                p[i].fizyka = 0;
            }
        } while (p[i].fizyka < 1 || p[i].fizyka > 5);

        // Оцінка з математики [1..5]
        do {
            cout << "    оцінка з математики (1-5): ";
            cin >> p[i].matematika;
            if (cin.fail() || p[i].matematika < 1 || p[i].matematika > 5) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                p[i].matematika = 0;
            }
        } while (p[i].matematika < 1 || p[i].matematika > 5);

        // Залежно від спеціальності вводимо оцінку у відповідне поле об'єднання union
        int third = 0;
        switch (p[i].spec)
        {
        case KN:
            do {
                cout << "    оцінка з програмування (1-5): ";
                cin >> third;
                if (cin.fail() || third < 1 || third > 5) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                    third = 0;
                }
            } while (third < 1 || third > 5);
            p[i].programuvannya = third;
            break;
        case INF:
            do {
                cout << "    оцінка з чисельних методів (1-5): ";
                cin >> third;
                if (cin.fail() || third < 1 || third > 5) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                    third = 0;
                }
            } while (third < 1 || third > 5);
            p[i].chyselni_metody = third;
            break;
        case ME:
        case FI:
        case TN:
            do {
                cout << "    оцінка з педагогіки (1-5): ";
                cin >> third;
                if (cin.fail() || third < 1 || third > 5) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                    third = 0;
                }
            } while (third < 1 || third > 5);
            p[i].pedagogika = third;
            break;
        }
        cout << endl;
    }
}

// Допоміжна функція вибору 3-ї профільної оцінки з union залежно від спеціальності
int GetThirdGrade(const Student& s)
{
    switch (s.spec)
    {
    case KN:  return s.programuvannya;
    case INF: return s.chyselni_metody;
    default:  return s.pedagogika;
    }
}

// Допоміжна функція для обчислення індивідуального середнього балу студента
double AverageGrade(const Student& s)
{
    return (s.fizyka + s.matematika + GetThirdGrade(s)) / 3.0;
}

// Функція виведення масиву структур у вигляді таблиці з 9 клітинок (за зразком посібника)
void Print(Student* p, const int N)
{
    cout << "==============================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Програмування | Чис. методи | Педагогіка |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[i].prizv
             << "| " << setw(4) << right << p[i].kurs << " "
             << "| " << setw(16) << left << specStr[p[i].spec]
             << "| " << setw(6) << right << p[i].fizyka << " "
             << "| " << setw(10) << right << p[i].matematika << " ";

        // Заповнюється лише одна з трьох клітинок профільної оцінки, решта — порожні (як у методичці)
        switch (p[i].spec)
        {
        case KN:
            cout << "| " << setw(13) << right << p[i].programuvannya << " "
                 << "| " << setw(11) << right << "" << " "
                 << "| " << setw(10) << right << "" << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(13) << right << "" << " "
                 << "| " << setw(11) << right << p[i].chyselni_metody << " "
                 << "| " << setw(10) << right << "" << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << "| " << setw(13) << right << "" << " "
                 << "| " << setw(11) << right << "" << " "
                 << "| " << setw(10) << right << p[i].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "==============================================================================================================" << endl;
    cout << endl;
}

// Варіант 16, завдання 1:
// Обчислення кількості студентів, середній бал яких вищий за 4,5
int CountHighAverage(Student* p, const int N)
{
    int k = 0;                  // лічильник студентів, чий середній бал > 4.5
    for (int i = 0; i < N; i++)
    {
        if (AverageGrade(p[i]) > 4.5)
        {
            k++;
        }
    }
    return k;
}

// Варіант 16, завдання 2:
// Порівнюючи середні бали для кожного предмета (з урахуванням union), визначити предмет із найбільшим середнім балом
string BestSubject(Student* p, const int N)
{
    if (N <= 0) return "Немає даних";

    double sumFiz = 0.0, sumMat = 0.0;
    double sumProg = 0.0, sumChis = 0.0, sumPed = 0.0;
    int countProg = 0, countChis = 0, countPed = 0;

    // Підсумовуємо оцінки по всіх 5 дисциплінах
    for (int i = 0; i < N; i++)
    {
        sumFiz += p[i].fizyka;
        sumMat += p[i].matematika;

        switch (p[i].spec)
        {
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

    // Обчислюємо середній бал кожного предмета серед студентів, які його вивчали
    double avgFiz = sumFiz / N;
    double avgMat = sumMat / N;
    double avgProg = (countProg > 0) ? (sumProg / countProg) : -1.0;
    double avgChis = (countChis > 0) ? (sumChis / countChis) : -1.0;
    double avgPed  = (countPed  > 0) ? (sumPed  / countPed)  : -1.0;

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
