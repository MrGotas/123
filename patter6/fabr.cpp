#include <iostream>
using namespace std;

// Базовый класс продукта
class Product {
public:
    Product() {
        cout << "Product created" << endl;
    }
    virtual void use() = 0; // Чисто виртуальный метод
    virtual ~Product() {
        cout << "Product destroyed" << endl;
    }
};

// Конкретный продукт A
class ProductA : public Product {
public:
    ProductA() {
        cout << "ProductA created" << endl;
    }
    void use() override {
        cout << "Using Product A" << endl;
    }
    ~ProductA() {
        cout << "ProductA destroyed" << endl;
    }
};

// Конкретный продукт B
class ProductB : public Product {
public:
    ProductB() {
        cout << "ProductB created" << endl;
    }
    void use() override {
        cout << "Using Product B" << endl;
    }
    ~ProductB() {
        cout << "ProductB destroyed" << endl;
    }
};

// Базовый класс фабрики
class Factory {
public:
    Factory() {
        cout << "Factory created" << endl;
    }
    virtual Product* createProduct() = 0; // Чисто виртуальный метод
    virtual ~Factory() {
        cout << "Factory destroyed" << endl;
    }
};

// Фабрика для создания ProductA
class FactoryA : public Factory {
public:
    FactoryA() {
        cout << "FactoryA created" << endl;
    }
    Product* createProduct() override {
        return new ProductA();
    }
    ~FactoryA() {
        cout << "FactoryA destroyed" << endl;
    }
};

// Фабрика для создания ProductB
class FactoryB : public Factory {
public:
    FactoryB() {
        cout << "FactoryB created" << endl;
    }
    Product* createProduct() override {
        return new ProductB();
    }
    ~FactoryB() {
        cout << "FactoryB destroyed" << endl;
    }
};

// Клиентский код
int main() {
    // Создаем фабрику для ProductA
    Factory* factoryA = new FactoryA();
    Product* productA = factoryA->createProduct();
    productA->use(); // Используем Product A

    // Создаем фабрику для ProductB
    Factory* factoryB = new FactoryB();
    Product* productB = factoryB->createProduct();
    productB->use(); // Используем Product B

    // Освобождаем память
    delete productA;
    delete productB;
    delete factoryA;
    delete factoryB;

    return 0;
}