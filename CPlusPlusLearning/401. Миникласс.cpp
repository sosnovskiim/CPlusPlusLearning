#include "tasks_4.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

static class BattleCry {

private:
    std::string text;

public:
    explicit BattleCry(const std::string& battle_cry) {
        if (battle_cry.empty()) {
            text = "Лок'тар огар!";
        } else {
            text = battle_cry;
        }
    }

    BattleCry() = delete;

    BattleCry(const BattleCry&) = default;
    BattleCry(BattleCry&&) = default;
    BattleCry& operator=(const BattleCry&) = default;
    BattleCry& operator=(BattleCry&&) = default;

    ~BattleCry() = default;

    const std::string& get_battle_cry() const {
        return text;
    }
};

void task_401() {
    SetConsoleOutputCP(1251);

    std::cout << "\nСоздание объектов:" << std::endl;
    BattleCry cry1("За Орду!");
    BattleCry cry2("");
    std::cout << "cry1: " << cry1.get_battle_cry() << std::endl;
    std::cout << "cry2: " << cry2.get_battle_cry() << std::endl;

    std::cout << "\nКонструктор копирования:" << std::endl;
    BattleCry cry3(cry1);
    std::cout << "cry3: " << cry3.get_battle_cry() << std::endl;

    std::cout << "\nКонструктор перемещения:" << std::endl;
    BattleCry cry4(std::move(cry2));
    std::cout << "cry2: " << cry2.get_battle_cry() << std::endl;

    std::cout << "\nКопирующий оператор присваивания:" << std::endl;
    BattleCry cry5("Исходный клич!");
    cry5 = cry1;
    std::cout << "cry5: " << cry5.get_battle_cry() << std::endl;

    std::cout << "\nОператор перемещения:" << std::endl;
    BattleCry cry6("Временный клич!");
    cry6 = std::move(cry3);
    std::cout << "cry3: " << cry3.get_battle_cry() << std::endl;
}
