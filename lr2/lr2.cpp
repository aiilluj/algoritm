#include <iostream>
#include <stdexcept>
#include <stack>
#include <chrono>

using namespace std;

// Шаблонный класс Stack
template <typename T>
class Stack {
private:
    T* data;        // Массив для хранения элементов
    int topIndex;   // Индекс верхнего элемента
    int capacity;   // Текущая ёмкость

    // Вспомогательная функция для расширения массива
    // Сложность: O(n) — копируем все элементы в новый массив
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    // Конструктор
    // Сложность: O(1) — выделение памяти фиксированного размера
    Stack(int initialCapacity = 10) {
        capacity = initialCapacity;
        topIndex = -1;
        data = new T[capacity];
    }

    // Деструктор
    // Сложность: O(1) — освобождение памяти
    ~Stack() {
        delete[] data;
    }

    // Добавление элемента
    // Сложность: O(1) амортизированная, O(n) при расширении
    void push(const T& value) {
        if (topIndex >= capacity - 1) {
            resize(); // редкий случай O(n)
        }
        data[++topIndex] = value; // обычный случай O(1)
    }

    // Удаление элемента
    // Сложность: O(1) — сдвигаем индекс
    void pop() {
        if (isEmpty()) throw out_of_range("Stack is empty");
        topIndex--;
    }

    // Получение верхнего элемента
    // Сложность: O(1) — доступ по индексу
    T top() const {
        if (isEmpty()) throw out_of_range("Stack is empty");
        return data[topIndex];
    }

    // Проверка на пустоту
    // Сложность: O(1)
    bool isEmpty() const {
        return topIndex == -1;
    }

    // Получение размера
    // Сложность: O(1)
    int size() const {
        return topIndex + 1;
    }
};

// Функция для замера времени (в микросекундах)
template <typename Func>
long long measureTime(Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");
    const int N = 1000000; // Количество операций для теста

    cout << "=== Сравнение производительности ===" << endl;
    cout << "Количество операций: " << N << endl << endl;

    // 1. Замер времени для собственной реализации стека
    // Общая сложность блока: O(N)
    long long myTime = measureTime([&]() {
        Stack<int> myStack;
        for (int i = 0; i < N; i++) myStack.push(i);
        for (int i = 0; i < N; i++) myStack.pop();
        });

    // 2. Замер времени для стандартного стека STL
    // Общая сложность блока: O(N)
    long long stlTime = measureTime([&]() {
        stack<int> stlStack;
        for (int i = 0; i < N; i++) stlStack.push(i);
        for (int i = 0; i < N; i++) stlStack.pop();
        });

    cout << "Свой Stack<T>:    " << myTime << " мкс" << endl;
    cout << "Стандартный STL:  " << stlTime << " мкс" << endl;

    return 0;
}