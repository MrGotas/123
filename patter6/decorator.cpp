#include <iostream>
#include <string>
using namespace std;

// Базовый класс кофе
class Coffee {
public:
    virtual string getDescription() const = 0; // Описание кофе
    virtual double cost() const = 0;          // Стоимость кофе
    virtual ~Coffee() {}
};

// Конкретный класс базового кофе
class SimpleCoffee : public Coffee {
public:
    string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 2.0; // Базовая стоимость кофе
    }
};

// Базовый класс декоратора
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee; // Обернутый кофе

public:
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}

    string getDescription() const override {
        return coffee->getDescription();
    }

    double cost() const override {
        return coffee->cost();
    }

    ~CoffeeDecorator() {
        delete coffee;
    }
};

// Декоратор для добавления молока
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee->cost() + 0.5; // Стоимость молока
    }
};

// Декоратор для добавления сахара
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double cost() const override {
        return coffee->cost() + 0.2; // Стоимость сахара
    }
};

// Декоратор для добавления сиропа
class SyrupDecorator : public CoffeeDecorator {
public:
    SyrupDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Syrup";
    }

    double cost() const override {
        return coffee->cost() + 0.7; // Стоимость сиропа
    }
};

// Клиентский код
int main() {
    // Создаем базовый кофе
    Coffee* coffee = new SimpleCoffee();
    cout << "Order: " << coffee->getDescription() << endl;
    cout << "Cost: $" << coffee->cost() << endl;

    // Добавляем молоко
    coffee = new MilkDecorator(coffee);
    cout << "Order: " << coffee->getDescription() << endl;
    cout << "Cost: $" << coffee->cost() << endl;

    // Добавляем сахар
    coffee = new SugarDecorator(coffee);
    cout << "Order: " << coffee->getDescription() << endl;
    cout << "Cost: $" << coffee->cost() << endl;

    // Добавляем сироп
    coffee = new SyrupDecorator(coffee);
    cout << "Order: " << coffee->getDescription() << endl;
    cout << "Cost: $" << coffee->cost() << endl;

    // Освобождаем память
    delete coffee;

    return 0;
}