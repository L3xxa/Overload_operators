#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int *_age;
    string *_name;
public:
    Student() : _age(nullptr), _name(nullptr) {}

    Student(int age, string name) {
        _age = new int(age);
        _name = new string(name);
        cout << "Constructor called " << this << endl;
    }

    Student(Student&& other) noexcept {
        _age = other._age;
        _name = other._name;
        other._age = nullptr;
        other._name = nullptr;
        cout << "Move constructor called " << this << endl;
    }

    ~Student() {
        delete _age;
        delete _name;
        cout << "Destructor called " << this << endl;
    }
};

int main() {
    Student Alex(20, "Alex");
    Student John(21, "John");
    Student Alex2 = move(Alex);

    return 0;
}