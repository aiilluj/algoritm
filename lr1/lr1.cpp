#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс "Студент" — часть в агрегации, может жить без курса
class Student {
private:
    string firstName, lastName, group; // поля студента
    static int totalCount;             // счётчик всех студентов

public:
    // Конструктор: создаёт студента и увеличивает счётчик
    Student(const string& fn, const string& ln, const string& gr)
        : firstName(fn), lastName(ln), group(gr) {
        totalCount++;
        cout << "Создан студент: " << lastName << " " << firstName
            << " (группа " << group << ")" << endl;
    }

    // Деструктор: уменьшает счётчик
    ~Student() {
        totalCount--;
        cout << "Удалён студент: " << lastName << " " << firstName << endl;
    }

    // Геттеры для доступа к полям
    string getFirstName() const { return firstName; }
    string getLastName()  const { return lastName; }
    string getGroup()     const { return group; }

    // Вывод информации о студенте
    void print() const {
        cout << "  - " << lastName << " " << firstName
            << ", группа: " << group << endl;
    }

    // Статический метод: возвращает количество студентов
    static int getTotalCount() { return totalCount; }
};

// Определение статического поля вне класса
int Student::totalCount = 0;

// Класс "Курс" — целое в агрегации, хранит указатели на студентов
class Course {
private:
    string title;              // название курса
    vector<Student*> students; // агрегация: указатели, а не копии

public:
    // Конструктор курса
    Course(const string& t) : title(t) {
        cout << "Открыт курс: " << title << endl;
    }

    // Деструктор НЕ удаляет студентов — они живут отдельно
    ~Course() {
        cout << "Закрыт курс: " << title << " (студенты остаются)" << endl;
    }

    // Добавление студента на курс с проверкой на nullptr
    void addStudent(Student* student) {
        if (student == nullptr) {
            cout << "Ошибка: пустой указатель на студента" << endl;
            return;
        }
        students.push_back(student);
        cout << "Студент " << student->getLastName()
            << " добавлен на курс \"" << title << "\"" << endl;
    }

    // Вывод списка студентов курса
    void print() const {
        cout << "Курс \"" << title << "\" содержит студентов:" << endl;
        if (students.empty()) {
            cout << "  (пусто)" << endl;
            return;
        }
        for (const auto* s : students) s->print();
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    cout << "=== Начало программы ===" << endl;
    cout << "Студентов всего: " << Student::getTotalCount() << endl << endl;

    // Создаём студентов независимо от курса
    cout << "--- Создание студентов ---" << endl;
    Student s1("Иван", "Иванов", "ИУ7-21Б");
    Student s2("Пётр", "Петров", "ИУ7-21Б");
    Student s3("Мария", "Сидорова", "ИУ7-22Б");
    cout << "Студентов всего: " << Student::getTotalCount() << endl << endl;

    // Работа с курсом в отдельном блоке, чтобы показать его уничтожение
    cout << "--- Работа с курсом ---" << endl;
    {
        Course course("Программирование на C++");
        course.addStudent(&s1);
        course.addStudent(&s2);
        course.addStudent(&s3);

        cout << endl;
        course.print();
        cout << endl;
    } // Здесь курс уничтожается, студенты — нет

    // Демонстрация: студенты живы после закрытия курса
    cout << "--- После закрытия курса ---" << endl;
    cout << "Студентов всего: " << Student::getTotalCount() << endl;
    cout << "Студенты всё ещё существуют:" << endl;
    s1.print();
    s2.print();
    s3.print();
    cout << endl;

    cout << "--- Конец программы ---" << endl;
    return 0;
}