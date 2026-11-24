// ============================================================================
// Лабораторна робота № 10.2 (Рівень А)
// Дисципліна: "Алгоритмізація та програмування"
// Тема: Впорядкування та бінарний пошук в масиві структур
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

// Структура даних про студента (Рівень А — без об'єднань)
struct Student {
    string prizv;               // прізвище студента (літерний рядок)
    int kurs;                   // курс навчання (ціле число від 1 до 6)
    Specialnist spec;           // спеціальність (значення переліку Specialnist)
    int fizyka;                 // оцінка з фізики (1..5)
    int matematika;             // оцінка з математики (1..5)
    int informatika;            // оцінка з інформатики (3-й предмет, 1..5)
};

// ----------------------------------------------------------------------------
// ПРОТОТИПИ ФУНКЦІЙ
// ----------------------------------------------------------------------------
void Create(Student* p, const int N);
void Print(Student* p, const int N);
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

    // Контроль помилки введення розміру масиву N
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

    // Виділення динамічної пам'яті під масив структур розміром N
    Student* p = new Student[N];
    int* I = nullptr;           // вказівник на індексний масив

    string prizv;               // ключ пошуку — прізвище
    double avg;                 // ключ пошуку — середній бал
    int thirdGrade;             // ключ пошуку — оцінка з 3-го предмета (інформатики)
    int found;                  // індекс знайденого елемента (-1, якщо не знайдено)

    int menuItem;               // вибраний пункт меню
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

        // Перевірка на некоректний (нечисловий) ввід пункту меню
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
                delete[] I;     // звільняємо попередній індексний масив перед новим виділенням
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

            // Контроль введення дійсного середнього балу [1..5]
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

            // Контроль введення оцінки з 3-го предмета [1..5]
            do {
                cout << "    оцінка з інформатики (1-5): ";
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

    // Звільнення всієї динамічно виділеної пам'яті
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

// Функція формування (введення) динамічного масиву структур із контролем помилок
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

        do {
            cout << "    оцінка з інформатики (1-5): ";
            cin >> p[i].informatika;
            if (cin.fail() || p[i].informatika < 1 || p[i].informatika > 5) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "    Помилка! Введіть оцінку від 1 до 5." << endl;
                p[i].informatika = 0;
            }
        } while (p[i].informatika < 1 || p[i].informatika > 5);

        cout << endl;
    }
}

// Допоміжна функція для обчислення індивідуального середнього балу студента
double AverageGrade(const Student& s)
{
    return (s.fizyka + s.matematika + s.informatika) / 3.0;
}

// Функція виведення масиву структур у вигляді таблиці з 7 клітинок (Рівень А)
void Print(Student* p, const int N)
{
    cout << "==================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Інформатика |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[i].prizv
             << "| " << setw(4) << right << p[i].kurs << " "
             << "| " << setw(16) << left << specStr[p[i].spec]
             << "| " << setw(6) << right << p[i].fizyka << " "
             << "| " << setw(10) << right << p[i].matematika << " "
             << "| " << setw(11) << right << p[i].informatika << " |" << endl;
    }
    cout << "==================================================================================" << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
// 1. Фізичне впорядкування (Варіант 16):
//    - в першу чергу:  за значенням середнього балу (за зростанням);
//    - в другу чергу:  за значенням оцінки з 3-го предмета (інформатики за зростанням);
//    - в останню чергу: за прізвищем за спаданням (в зворотному до алфавітного порядку).
// ----------------------------------------------------------------------------
void Sort(Student* p, const int N)
{
    const double EPS = 1e-9;    // похибка порівняння дійсних чисел
    Student tmp;                // тимчасова змінна для обміну структур
    for (int i0 = 0; i0 < N - 1; i0++)        // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            double avg1 = AverageGrade(p[i1]);
            double avg2 = AverageGrade(p[i1 + 1]);
            bool eqAvg = fabs(avg1 - avg2) < EPS;

            if (( !eqAvg && avg1 > avg2 )
                ||
                ( eqAvg && p[i1].informatika > p[i1 + 1].informatika )
                ||
                ( eqAvg && p[i1].informatika == p[i1 + 1].informatika &&
                  p[i1].prizv < p[i1 + 1].prizv ))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

// ----------------------------------------------------------------------------
// 2. Індексне впорядкування (Варіант 16):
//    Використовуємо метод вставки для формування індексного масиву:
//    - в першу чергу:  за значенням середнього балу (за зростанням);
//    - в другу чергу:  за значенням оцінки з 3-го предмета (за зростанням);
//    - в останню чергу: за прізвищем (за зростанням — в алфавітному порядку).
// ----------------------------------------------------------------------------
int* IndexSort(Student* p, const int N)
{
    const double EPS = 1e-9;

    int* I = new int[N];        // створили індексний масив

    for (int i = 0; i < N; i++)
        I[i] = i;               // заповнили його початковими даними

    int i, j, value;            // починаємо сортувати масив індексів методом вставки
    for (i = 1; i < N; i++)
    {
        value = I[i];           // запам'ятовуємо поточний індекс для вставки
        double avgVal = AverageGrade(p[value]);

        for (j = i - 1; j >= 0; j--)
        {
            double avgJ = AverageGrade(p[I[j]]);
            bool eqAvg = fabs(avgJ - avgVal) < EPS;

            // Умова порушення порядку: елемент з індексом I[j] більший за елемент з індексом value
            if (( !eqAvg && avgJ > avgVal ) ||
                ( eqAvg && p[I[j]].informatika > p[value].informatika ) ||
                ( eqAvg && p[I[j]].informatika == p[value].informatika && p[I[j]].prizv > p[value].prizv ))
            {
                I[j + 1] = I[j]; // зсув індексу праворуч
            }
            else
            {
                break;          // місце для вставки знайдено
            }
        }
        I[j + 1] = value;       // вставляємо індекс у відсортовану частину
    }

    return I;
}

// Функція виведення даних відповідно до порядку індексів у масиві I
void PrintIndexSorted(Student* p, int* I, const int N)
{   // аналогічно функції Print(), але замість p[i] використовуємо звертання p[I[i]]
    cout << "==================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |  Спеціальність  | Фізика | Математика | Інформатика |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[I[i]].prizv
             << "| " << setw(4) << right << p[I[i]].kurs << " "
             << "| " << setw(16) << left << specStr[p[I[i]].spec]
             << "| " << setw(6) << right << p[I[i]].fizyka << " "
             << "| " << setw(10) << right << p[I[i]].matematika << " "
             << "| " << setw(11) << right << p[I[i]].informatika << " |" << endl;
    }
    cout << "==================================================================================" << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
// 3. Бінарний пошук (Варіант 16):
//    Працює у попередньо фізично впорядкованому масиві за ключем (avg, informatika, prizv).
//    Повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній.
// ----------------------------------------------------------------------------
int BinSearch(Student* p, const int N, const string prizv, const double avg, const int thirdGrade)
{
    if (N <= 0) return -1;

    // Допуск 0.01 дозволяє однаково знаходити як точний дріб (14.0/3.0),
    // так і введений користувачем округлений до сотих бал (4.67),
    // бо крок між сусідніми можливими середніми балами становить 1/3 ≈ 0.333.
    const double EPS = 0.01;
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        double curAvg = AverageGrade(p[m]);
        bool sameAvg = fabs(curAvg - avg) < EPS;

        if (sameAvg && p[m].informatika == thirdGrade && p[m].prizv == prizv)
            return m;           // елемент знайдено

        // Згідно з порядком фізичного сортування (Sort):
        // якщо p[m] стоїть ліворуч від шуканого — зсуваємо ліву межу L праворуч
        if (( !sameAvg && curAvg < avg )
            ||
            ( sameAvg && p[m].informatika < thirdGrade )
            ||
            ( sameAvg && p[m].informatika == thirdGrade && p[m].prizv > prizv ))
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
