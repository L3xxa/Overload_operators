// #include <iostream>
// using namespace std;
//
// class MyClass {
// public:
//     int *_data;
//
//     MyClass(int size) {
//         this->Size = size;
//         this->_data = new int (size);
//
//           for (int i = 0; i < size; i++) {
//         data[i] = i;
//         }
//         cout << "Call Constructor: " << this << endl;
//     }
//
//     MyClass(const MyClass &other) {
//         this->Size = other.Size;
//         this->_data = new int [other.Size];
//
//         for (int i = 0; i < other.Size; i++) {
//             this->_data[i] = other._data[i];
//         }
//         cout << "Call Copy Constructor: " << this << endl;
//     }
//
//     MyClass & operator = (const MyClass &other) {
//         cout << "Call Operator =  " << this << endl;
//
//         this->Size = other.Size;
//
//         if (this->_data != nullptr) {
//             delete [] this->_data;
//         }
//
//         this->_data = new int [other.Size];
//
//         for (int i = 0; i < other.Size; i++) {
//             this->_data[i] = other._data[i];
//         }
//         return *this;
//
//     }
//
//     ~MyClass() {
//         delete [] data;
//         cout << "Call Destructor: " << this << endl;
//     }
//
// private:
//     int Size;
// };
//
// void Foo(MyClass value) {
//     cout << "Call Foo: " << endl;
// }
//
// MyClass Foo2() {
//     MyClass temp(10);
//     cout << "Call Foo2: " << endl;
//     return temp;
// }
//
// int main() {
//
//     MyClass a(10);
//     MyClass b(2);
//     MyClass c(3);
//
//     c = a = b;
//
//     return 0;
// }

#include <iostream>
using namespace std;

class Date {
private:
    int *_day;
    int *_month;
    int *_year;

    // Перевірка на високисний рік
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Перевірка на кількість днів у місяці
    int daysInMonth(int m, int y) const {
        static const int daysPerMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeapYear(y)) return 29;
        return daysPerMonth[m];
    }

public:

    // Дефолтний конструктор
    Date() = default;

    // Конструктор з параметрами
    Date(int day, int month, int year) {
        this->_day = new int (day);
        this->_month = new int (month);
        this->_year = new int (year);
    }

    // Перевантаження оператора ++
Date & operator ++ () {
    if (*_day < daysInMonth(*_month, *_year)) {
        (*_day)++;
    }
    else {
        *_day = 1;
        if (*_month < 12) {
            (*_month)++;
        }
        else {
            *_month = 1;
            (*_year)++;
        }
    }
    return *this;
}

// Перевантаження оператора --
Date & operator -- () {
    if (*_day > 1) {
        (*_day)--;
    }
    else {
        if (*_month > 1) {
            *_day = daysInMonth(*_month - 1, *_year);
            (*_month)--;
        }
        else {
            *_month = 12;
            (*_year)--;
        }
    }
    return *this;
}

    int getDay() const{
         return *_day;
    }

    int getMonth() const{
         return *_month;
    }

    int getYear() const{
         return *_year;
    }

    ~Date() {
        delete _day;
        delete _month;
        delete _year;
    }
};

int main () {

    Date date(3, 2, 2025);
    ++date;
    cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
    ++date;
    cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
    ++date;
    cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
    ++date;
    cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;
    --date;
    cout << date.getDay() << "." << date.getMonth() << "." << date.getYear() << endl;

    return 0;
}