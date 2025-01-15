#include <iostream>
#include <string>
using namespace std;

// Интерфейс нового устройства (HDMI)
class HDMI {
public:
    virtual void sendHDMISignal() const = 0;
    virtual ~HDMI() {}
};

// Новый телевизор, поддерживающий HDMI
class TV : public HDMI {
public:
    void sendHDMISignal() const override {
        cout << "TV is receiving HDMI signal." << endl;
    }
};

// Старое устройство (VHS-плеер)
class VHSPlayer {
public:
    void playVHSTape() const {
        cout << "VHS player is playing a tape." << endl;
    }
};

// Адаптер для подключения VHS-плеера к HDMI
class VHSToHDMIAdapter : public HDMI {
public:
    VHSToHDMIAdapter(const VHSPlayer& vhsPlayer) : vhsPlayer(vhsPlayer) {}

    void sendHDMISignal() const override {
        cout << "Adapter is converting VHS signal to HDMI." << endl;
        vhsPlayer.playVHSTape(); // Используем функциональность VHS-плеера
    }

private:
    VHSPlayer vhsPlayer;
};

// Клиентский код
int main() {
    // Создаем VHS-плеер
    VHSPlayer vhsPlayer;

    // Создаем адаптер и подключаем VHS-плеер
    VHSToHDMIAdapter adapter(vhsPlayer);

    // Создаем телевизор
    TV tv;

    // Подключаем адаптер к телевизору
    cout << "Connecting VHS player to TV using adapter..." << endl;
    tv.sendHDMISignal(); // Телевизор ожидает HDMI-сигнал
    adapter.sendHDMISignal(); // Адаптер преобразует сигнал

    return 0;
}