#include <iostream>
using namespace std;

// Абстрактный класс для продукта A
class AbstractProductA {
public:
    virtual void use() = 0; // Чисто виртуальный метод
    virtual ~AbstractProductA() {}
};

// Конкретный продукт A1
class ProductA1 : public AbstractProductA {
public:
    void use() override {
        cout << "Using Product A1" << endl;
    }
};

// Конкретный продукт A2
class ProductA2 : public AbstractProductA {
public:
    void use() override {
        cout << "Using Product A2" << endl;
    }
};

// Абстрактный класс для продукта B
class AbstractProductB {
public:
    virtual void use() = 0; // Чисто виртуальный метод
    virtual ~AbstractProductB() {}
};

// Конкретный продукт B1
class ProductB1 : public AbstractProductB {
public:
    void use() override {
        cout << "Using Product B1" << endl;
    }
};

// Конкретный продукт B2
class ProductB2 : public AbstractProductB {
public:
    void use() override {
        cout << "Using Product B2" << endl;
    }
};

// Абстрактная фабрика
class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() = 0; // Создать продукт A
    virtual AbstractProductB* createProductB() = 0; // Создать продукт B
    virtual ~AbstractFactory() {}
};

// Конкретная фабрика для семейства 1
class ConcreteFactory1 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ProductA1();
    }
    AbstractProductB* createProductB() override {
        return new ProductB1();
    }
};

// Конкретная фабрика для семейства 2
class ConcreteFactory2 : public AbstractFactory {
public:
    AbstractProductA* createProductA() override {
        return new ProductA2();
    }
    AbstractProductB* createProductB() override {
        return new ProductB2();
    }
};

// Клиентский код
int main() {
    // Создаем фабрику для семейства 1
    AbstractFactory* factory1 = new ConcreteFactory1();
    AbstractProductA* productA1 = factory1->createProductA();
    AbstractProductB* productB1 = factory1->createProductB();

    productA1->use(); // Используем Product A1
    productB1->use(); // Используем Product B1

    // Создаем фабрику для семейства 2
    AbstractFactory* factory2 = new ConcreteFactory2();
    AbstractProductA* productA2 = factory2->createProductA();
    AbstractProductB* productB2 = factory2->createProductB();

    productA2->use(); // Используем Product A2
    productB2->use(); // Используем Product B2

    // Освобождаем память
    delete productA1;
    delete productB1;
    delete factory1;
    delete productA2;
    delete productB2;
    delete factory2;

    return 0;
}