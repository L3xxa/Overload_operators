#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string* _name;
    int* _age;

public:
    // Конструктор за замовчуванням
    Person() : _name(nullptr), _age(nullptr) {}

    // Конструктор з параметрами
    Person(string name, int age) {
        _name = new string(name);
        _age = new int(age);
    }

    // Конструктор переміщення
    Person(Person&& other) noexcept {
        _name = other._name;
        _age = other._age;
        other._name = nullptr;
        other._age = nullptr;
    }

    // Оператор присвоєння переміщення
    Person& operator=(Person&& other) noexcept {
        if (this != &other) {
            delete _name;
            delete _age;
            _name = other._name;
            _age = other._age;
            other._name = nullptr;
            other._age = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~Person() {
        delete _name;
        delete _age;
    }

    // Показуємо дані
    void show() const {
        if (_name && _age) {
            cout << "Name: " << *_name << ", Age: " << *_age << endl;
        } else {
            cout << "Moved person" << endl;
        }
    }
};

class Apartment {
private:
    string _adress;
    int _rooms;
    Person _owner;

public:
    Apartment() = default;

    // Конструктор з параметрами
    Apartment(string adress, int rooms, Person owner)
        : _adress(adress), _rooms(rooms), _owner(move(owner)) {}

    // Конструктор переміщення
    Apartment(Apartment&& other) noexcept
        : _adress(move(other._adress)), _rooms(other._rooms), _owner(move(other._owner)) {
        other._rooms = 0;
    }

    // Оператор присвоєння переміщення
    Apartment& operator=(Apartment&& other) noexcept {
        if (this != &other) {
            _adress = move(other._adress);
            _rooms = other._rooms;
            _owner = move(other._owner);
            other._rooms = 0;
        }
        return *this;
    }

    // Деструктор
    ~Apartment() = default;

    // Додаємо мешканця (переміщення)
    void addResident(Person&& person) {
        _owner = move(person);
    }

    // Показуємо квартиру
    void show() const {
        cout << "Apartment address: " << _adress << ", Rooms: " << _rooms << endl;
        cout << "Owner: ";
        _owner.show();
    }
};

class House {
private:
    Apartment* _apartments;
    int _size;

public:
    House(int size) : _size(size) {
        _apartments = new Apartment[_size];
    }

    House(House&& other) noexcept {
        _apartments = other._apartments;
        _size = other._size;
        other._apartments = nullptr;
        other._size = 0;
    }

    ~House() {
        delete[] _apartments;
    }

    // Додаємо квартиру
    void addApartment(Apartment&& apartment) {
        for (int i = 0; i < _size; i++) {
            _apartments[i] = move(apartment);
            break;
        }
    }

    void show() const {
        for (int i = 0; i < _size; i++) {
            _apartments[i].show();
        }
    }
};

int main() {
    House house(3);
    house.addApartment(Apartment("Kiev", 1, Person("Ivan", 25)));
    house.addApartment(Apartment("Kiev", 2, Person("Alex", 30)));
    house.addApartment(Apartment("Lviv", 3, Person("Vlad", 35)));

    cout << "=== Building Info ===" << endl;
    house.show();

    return 0;
}
