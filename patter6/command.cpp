#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Базовый класс устройства
class Device {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~Device() {}
};

// Конкретное устройство: Свет
class Light : public Device {
public:
    void on() override {
        cout << "Light is ON" << endl;
    }

    void off() override {
        cout << "Light is OFF" << endl;
    }
};

// Конкретное устройство: Телевизор
class TV : public Device {
public:
    void on() override {
        cout << "TV is ON" << endl;
    }

    void off() override {
        cout << "TV is OFF" << endl;
    }
};

// Базовый класс команды
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Конкретная команда: Включить устройство
class TurnOnCommand : public Command {
public:
    TurnOnCommand(Device* device) : device(device) {}

    void execute() override {
        device->on();
    }

    void undo() override {
        device->off();
    }

private:
    Device* device;
};

// Конкретная команда: Выключить устройство
class TurnOffCommand : public Command {
public:
    TurnOffCommand(Device* device) : device(device) {}

    void execute() override {
        device->off();
    }

    void undo() override {
        device->on();
    }

private:
    Device* device;
};

// Пульт дистанционного управления
class RemoteControl {
public:
    void setCommand(Command* command) {
        commands.push_back(command);
    }

    void pressButton(int index) {
        if (index >= 0 && index < commands.size()) {
            commands[index]->execute();
            lastCommand = commands[index];
        }
    }

    void pressUndo() {
        if (lastCommand) {
            lastCommand->undo();
            lastCommand = nullptr;
        }
    }

    ~RemoteControl() {
        for (auto& command : commands) {
            delete command;
        }
    }

private:
    vector<Command*> commands;
    Command* lastCommand = nullptr;
};

// Клиентский код
int main() {
    // Создаем устройства
    Device* light = new Light();
    Device* tv = new TV();

    // Создаем команды
    Command* turnOnLight = new TurnOnCommand(light);
    Command* turnOffLight = new TurnOffCommand(light);
    Command* turnOnTV = new TurnOnCommand(tv);
    Command* turnOffTV = new TurnOffCommand(tv);

    // Создаем пульт дистанционного управления
    RemoteControl remote;

    // Назначаем команды на кнопки пульта
    remote.setCommand(turnOnLight);    // Кнопка 0: Включить свет
    remote.setCommand(turnOffLight);   // Кнопка 1: Выключить свет
    remote.setCommand(turnOnTV);       // Кнопка 2: Включить телевизор
    remote.setCommand(turnOffTV);      // Кнопка 3: Выключить телевизор

    // Управляем устройствами
    remote.pressButton(0); // Включаем свет
    remote.pressButton(2); // Включаем телевизор
    remote.pressUndo();    // Отменяем последнюю команду (выключаем телевизор)
    remote.pressButton(1); // Выключаем свет

    // Освобождаем память
    delete light;
    delete tv;

    return 0;
}