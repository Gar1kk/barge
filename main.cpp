#include <iostream>
#include <stdexcept>
#include "ui.h"

int main() {
    int choice;

    try {
        do {
            choice = showMenu();

            switch (choice) {
                case 1: runFromKeyboard(); break;
                case 2: runFromFile();     break;
                case 0: std::cout << "До свидания!\n"; break;
            }
        } while (choice != 0);
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
