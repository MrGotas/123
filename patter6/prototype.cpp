#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Базовый класс документа
class Document {
public:
    virtual Document* clone() const = 0; // Метод для клонирования
    virtual void print() const = 0;      // Метод для вывода информации
    virtual ~Document() {}
};

// Конкретный класс документа: Отчет
class Report : public Document {
public:
    Report(const string& title, const string& content) : title(title), content(content) {}

    Document* clone() const override {
        return new Report(*this); // Используем конструктор копирования
    }

    void print() const override {
        cout << "Report: " << title << endl;
        cout << "Content: " << content << endl;
    }

private:
    string title;
    string content;
};

// Конкретный класс документа: Презентация
class Presentation : public Document {
public:
    Presentation(const string& title, int slides) : title(title), slides(slides) {}

    Document* clone() const override {
        return new Presentation(*this); // Используем конструктор копирования
    }

    void print() const override {
        cout << "Presentation: " << title << endl;
        cout << "Slides: " << slides << endl;
    }

private:
    string title;
    int slides;
};

// Менеджер прототипов
class DocumentManager {
public:
    void addPrototype(const string& key, Document* document) {
        prototypes[key] = document;
    }

    Document* createDocument(const string& key) {
        if (prototypes.find(key) != prototypes.end()) {
            return prototypes[key]->clone(); // Клонируем прототип
        }
        return nullptr;
    }

    ~DocumentManager() {
        for (auto& pair : prototypes) {
            delete pair.second; // Освобождаем память
        }
    }

private:
    unordered_map<string, Document*> prototypes;
};

// Клиентский код
int main() {
    // Создаем менеджер прототипов
    DocumentManager manager;

    // Добавляем прототипы
    manager.addPrototype("Report", new Report("Monthly Report", "This is the content of the monthly report."));
    manager.addPrototype("Presentation", new Presentation("Project Update", 10));

    // Создаем новые документы, копируя прототипы
    Document* report = manager.createDocument("Report");
    Document* presentation = manager.createDocument("Presentation");

    // Выводим информацию о документах
    if (report) {
        report->print();
        delete report;
    }

    if (presentation) {
        presentation->print();
        delete presentation;
    }

    return 0;
}