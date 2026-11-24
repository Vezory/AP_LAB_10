// ============================================================================
// Лабораторна робота № 10.2 (Рівень В)
// Дисципліна: "Алгоритмізація та програмування"
// Тема: Впорядкування та бінарний пошук в масиві структур з об'єднаннями
// Варіант: 16
// Студент: Новосад Захарій Володимирович, група РІ-13
// Викладач: Григорович В. Г.
// ============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>                // для точного порівняння дійсних середніх балів (fabs)
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
    int kurs;                   // курс навчання (ціле число від 1 до 6)
    Specialnist spec;           // спеціальність (значення переліку Specialnist)
    int fizyka;                 // оцінка з фізики (1..5)
    int matematika;             // оцінка з математики (1..5)

    // Безіменне об'єднання (union) для третього профільного предмета:
    union {
        int programuvannya;     // оцінка з програмування (KN)
        int chyselni_metody;    // оцінка з чисельних методів (INF)
        int pedagogika;         // оцінка з педагогіки (ME, FI, TN)
    };
};

// ----------------------------------------------------------------------------
// ПРОТОТИПИ ФУНКЦІЙ
// ----------------------------------------------------------------------------
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int GetThirdGrade(const Student& s);
double AverageGrade(const Student& s);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const double avg, const int thirdGrade);

// ============================================================================
// ГОЛОВНА ФУНКЦІЯ ПРОГРАМИ
// ============================================================================
#ifndef UNIT_TESTING
int main()
{                               // забезпечення відображення кирилиці:
    SetConsoleCP(1251);         // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251);   // встановлення сторінки win-cp1251 в потік виводу

    int N;                      // кількість студентів у групі

    // Введення кількості студентів із контролем помилок (N > 0)
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

    // Динамічний масив структур з об'єднаннями
    Student* p = new Student[N];
    int* I = nullptr;           // вказівник на індексний масив

    string prizv;               // ключ пошуку — прізвище
    double avg;                 // ключ пошуку — середній бал
    int thirdGrade;             // ключ пошуку — 3-я профільна оцінка
    int found;                  // результат бінарного пошуку

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - введення даних з клавіатури" << endl;
        cout << "  [2] - вивід даних на екран" << endl;
        cout << "  [3] - фізичне впорядкування даних" << endl;
        cout << "  [4] - індексне впорядкування та вивід даних" << endl;
        cout << "  [5] - бінарний пошук студента за прізвищем, сер. балом та 3-м предметом" << endl << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;

        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            menuItem = -1;
        }
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив фізично впорядковано." << endl << endl;
            Print(p, N);
            break;
        case 4:
            if (I != nullptr) {
                delete[] I;     // звільнення попереднього індексного масиву
            }
            I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;

            cin.get();          // очищуємо буфер клавіатури — бо залишаються символи
            cin.sync();         // "кінець рядка", які не дають ввести наступний літерний рядок

            cout << "    прізвище: ";
            getline(cin, prizv);

            do {
                cout << "    середній бал (1-5): ";
                cin >> avg;
                if (cin.fail() || avg < 1.0 || avg > 5.0) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "    Помилка! Введіть значення від 1 до 5." << endl;
                    avg = 0.0;
                }
            } while (avg < 1.0 || avg > 5.0);

            do {
                cout << "    оцінка з 3-го предмета (1-5): ";
                cin >> thirdGrade;
                if (cin.fail() || thirdGrade < 1 || thirdGrade > 5) {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                    thirdGrade = 0;
                }
            } while (thirdGrade < 1 || thirdGrade > 5);

            cout << endl;
            if ((found = BinSearch(p, N, prizv, avg, thirdGrade)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                    "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    // Звільнення динамічної пам'яті
    delete[] p;
    if (I != nullptr) {
        delete[] I;
    }

    return 0;
}
#endif

// ============================================================================
// РЕАЛІЗАЦІЯ ФУНКЦІЙ
// ============================================================================

// Допоміжна функція отримання 3-ї профільної оцінки з об'єднання union
int GetThirdGrade(const Student& s)
{
    switch (s.spec)
    {
    case KN:  return s.programuvannya;
    case INF: return s.chyselni_metody;
    default:  return s.pedagogika;
    }
}

// Допоміжна функція обчислення індивідуального середнього балу студента
double AverageGrade(const Student& s)
{
    return (s.fizyka + s.matematika + GetThirdGrade(s)) / 3.0;
}

// Функція формування (введення) масиву структур із контролем помилок
void Create(Student* p, const int N)
{
    int ispec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;

        cin.get();              // очищуємо буфер клавіатури — бо залишаються символи
        cin.sync();             // "кінець рядка", які не дають ввести наступний літерний рядок

        cout << "    прізвище: "; getline(cin, p[i].prizv);

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

        // Запис 3-ї оцінки у відповідне поле об'єднання union
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

// Функція виведення масиву у вигляді таблиці з 9 клітинок (Рівень В)
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

        // Заповнюється лише одна з клітинок профільної оцінки, решта — порожні
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

// ----------------------------------------------------------------------------
// 1. Фізичне впорядкування (Варіант 16, Рівень В):
//    - 1 черга: за значенням середнього балу (за зростанням);
//    - 2 черга: за значенням оцінки з 3-го предмета (union, за зростанням);
//    - 3 черга: за прізвищем за спаданням (в зворотному до алфавітного порядку).
// ----------------------------------------------------------------------------
void Sort(Student* p, const int N)
{
    const double EPS = 1e-9;
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)        // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            double avg1 = AverageGrade(p[i1]);
            double avg2 = AverageGrade(p[i1 + 1]);
            bool eqAvg = fabs(avg1 - avg2) < EPS;
            int g3_1 = GetThirdGrade(p[i1]);
            int g3_2 = GetThirdGrade(p[i1 + 1]);

            if (( !eqAvg && avg1 > avg2 )
                ||
                ( eqAvg && g3_1 > g3_2 )
                ||
                ( eqAvg && g3_1 == g3_2 &&
                  p[i1].prizv < p[i1 + 1].prizv ))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

// ----------------------------------------------------------------------------
// 2. Індексне впорядкування (Варіант 16, Рівень В):
//    Використовуємо метод вставки для формування індексного масиву:
//    - 1 черга: за значенням середнього балу (за зростанням);
//    - 2 черга: за значенням оцінки з 3-го предмета (union, за зростанням);
//    - 3 черга: за прізвищем (за зростанням — в алфавітному порядку).
// ----------------------------------------------------------------------------
int* IndexSort(Student* p, const int N)
{
    const double EPS = 1e-9;

    int* I = new int[N];        // створили індексний масив

    for (int i = 0; i < N; i++)
        I[i] = i;               // заповнили його початковими даними

    int i, j, value;            // сортування масиву індексів методом вставки
    for (i = 1; i < N; i++)
    {
        value = I[i];
        double avgVal = AverageGrade(p[value]);
        int g3Val = GetThirdGrade(p[value]);

        for (j = i - 1; j >= 0; j--)
        {
            double avgJ = AverageGrade(p[I[j]]);
            bool eqAvg = fabs(avgJ - avgVal) < EPS;
            int g3J = GetThirdGrade(p[I[j]]);

            if (( !eqAvg && avgJ > avgVal ) ||
                ( eqAvg && g3J > g3Val ) ||
                ( eqAvg && g3J == g3Val && p[I[j]].prizv > p[value].prizv ))
            {
                I[j + 1] = I[j];
            }
            else
            {
                break;
            }
        }
        I[j + 1] = value;
    }

    return I;
}

// Функція виведення масиву структур відповідно до індексного масиву I
void PrintIndexSorted(Student* p, int* I, const int N)
{   // аналогічно функції Print(), але використовуємо доступ p[I[i]]
    cout << "==============================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Програмування | Чис. методи | Педагогіка |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[I[i]].prizv
             << "| " << setw(4) << right << p[I[i]].kurs << " "
             << "| " << setw(16) << left << specStr[p[I[i]].spec]
             << "| " << setw(6) << right << p[I[i]].fizyka << " "
             << "| " << setw(10) << right << p[I[i]].matematika << " ";

        switch (p[I[i]].spec)
        {
        case KN:
            cout << "| " << setw(13) << right << p[I[i]].programuvannya << " "
                 << "| " << setw(11) << right << "" << " "
                 << "| " << setw(10) << right << "" << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(13) << right << "" << " "
                 << "| " << setw(11) << right << p[I[i]].chyselni_metody << " "
                 << "| " << setw(10) << right << "" << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << "| " << setw(13) << right << "" << " "
                 << "| " << setw(11) << right << "" << " "
                 << "| " << setw(10) << right << p[I[i]].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "==============================================================================================================" << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
// 3. Бінарний пошук (Варіант 16, Рівень В):
//    Пошук у фізично впорядкованому масиві за (avg, GetThirdGrade, prizv).
// ----------------------------------------------------------------------------
int BinSearch(Student* p, const int N, const string prizv, const double avg, const int thirdGrade)
{
    if (N <= 0) return -1;

    const double EPS = 0.01;    // допуск для порівняння з округленим середнім балом
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double curAvg = AverageGrade(p[m]);
        bool sameAvg = fabs(curAvg - avg) < EPS;
        int curThird = GetThirdGrade(p[m]);

        if (sameAvg && curThird == thirdGrade && p[m].prizv == prizv)
            return m;

        if (( !sameAvg && curAvg < avg )
            ||
            ( sameAvg && curThird < thirdGrade )
            ||
            ( sameAvg && curThird == thirdGrade && p[m].prizv > prizv ))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
