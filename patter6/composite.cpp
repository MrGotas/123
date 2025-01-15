#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Базовый класс компонента файловой системы
class FileSystemComponent {
public:
    virtual void display(int indent = 0) const = 0; // Метод для отображения
    virtual ~FileSystemComponent() {}
};

// Класс файла
class File : public FileSystemComponent {
public:
    File(const string& name) : name(name) {}

    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "File: " << name << endl;
    }

private:
    string name;
};

// Класс папки
class Folder : public FileSystemComponent {
public:
    Folder(const string& name) : name(name) {}

    void addComponent(FileSystemComponent* component) {
        components.push_back(component);
    }

    void display(int indent = 0) const override {
        cout << string(indent, ' ') << "Folder: " << name << endl;
        for (const auto& component : components) {
            component->display(indent + 2); // Рекурсивно отображаем содержимое
        }
    }

    ~Folder() {
        for (auto& component : components) {
            delete component; // Освобождаем память
        }
    }

private:
    string name;
    vector<FileSystemComponent*> components;
};

// Клиентский код
int main() {
    // Создаем файлы
    File* file1 = new File("Document.txt");
    File* file2 = new File("Image.jpg");
    File* file3 = new File("Spreadsheet.xlsx");

    // Создаем папки
    Folder* folder1 = new Folder("Documents");
    Folder* folder2 = new Folder("Pictures");
    Folder* rootFolder = new Folder("Root");

    // Добавляем файлы в папки
    folder1->addComponent(file1);
    folder1->addComponent(file3);
    folder2->addComponent(file2);

    // Добавляем папки в корневую папку
    rootFolder->addComponent(folder1);
    rootFolder->addComponent(folder2);

    // Отображаем всю файловую систему
    cout << "File System Structure:" << endl;
    rootFolder->display();

    // Освобождаем память
    delete rootFolder;

    return 0;
}