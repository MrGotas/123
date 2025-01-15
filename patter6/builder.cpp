#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Класс пиццы
class Pizza {
public:
    void setDough(const string& dough) {
        this->dough = dough;
    }

    void setSauce(const string& sauce) {
        this->sauce = sauce;
    }

    void addTopping(const string& topping) {
        toppings.push_back(topping);
    }

    void showPizza() const {
        cout << "Pizza with " << dough << " dough, " << sauce << " sauce, and toppings: ";
        for (const string& topping : toppings) {
            cout << topping << " ";
        }
        cout << endl;
    }

private:
    string dough;          // Тесто
    string sauce;          // Соус
    vector<string> toppings; // Начинка
};

// Абстрактный строитель для пиццы
class PizzaBuilder {
public:
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildToppings() = 0;
    virtual Pizza* getPizza() = 0;
    virtual ~PizzaBuilder() {}
};

// Конкретный строитель для Маргариты
class MargheritaBuilder : public PizzaBuilder {
public:
    MargheritaBuilder() {
        pizza = new Pizza();
    }

    void buildDough() override {
        pizza->setDough("thin crust");
    }

    void buildSauce() override {
        pizza->setSauce("tomato");
    }

    void buildToppings() override {
        pizza->addTopping("mozzarella");
        pizza->addTopping("basil");
    }

    Pizza* getPizza() override {
        return pizza;
    }

    ~MargheritaBuilder() {
        delete pizza;
    }

private:
    Pizza* pizza;
};

// Конкретный строитель для Пепперони
class PepperoniBuilder : public PizzaBuilder {
public:
    PepperoniBuilder() {
        pizza = new Pizza();
    }

    void buildDough() override {
        pizza->setDough("thick crust");
    }

    void buildSauce() override {
        pizza->setSauce("tomato");
    }

    void buildToppings() override {
        pizza->addTopping("pepperoni");
        pizza->addTopping("cheese");
    }

    Pizza* getPizza() override {
        return pizza;
    }

    ~PepperoniBuilder() {
        delete pizza;
    }

private:
    Pizza* pizza;
};

// Директор (управляет процессом создания пиццы)
class PizzaDirector {
public:
    void setBuilder(PizzaBuilder* builder) {
        this->builder = builder;
    }

    void constructPizza() {
        builder->buildDough();
        builder->buildSauce();
        builder->buildToppings();
    }

private:
    PizzaBuilder* builder;
};

// Клиентский код
int main() {
    // Создаем строителя для Маргариты
    PizzaBuilder* margheritaBuilder = new MargheritaBuilder();
    PizzaDirector director;
    director.setBuilder(margheritaBuilder);
    director.constructPizza();

    // Получаем пиццу Маргарита
    Pizza* margheritaPizza = margheritaBuilder->getPizza();
    margheritaPizza->showPizza();

    // Создаем строителя для Пепперони
    PizzaBuilder* pepperoniBuilder = new PepperoniBuilder();
    director.setBuilder(pepperoniBuilder);
    director.constructPizza();

    // Получаем пиццу Пепперони
    Pizza* pepperoniPizza = pepperoniBuilder->getPizza();
    pepperoniPizza->showPizza();

    // Освобождаем память
    delete margheritaBuilder;
    delete margheritaPizza;
    delete pepperoniBuilder;
    delete pepperoniPizza;

    return 0;
}