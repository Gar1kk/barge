#include "ui.h"
#include "barge.h"

#include <iostream>
#include <fstream>
#include <limits>

bool readInt(int& out, int minVal, int maxVal) {
    if (!(std::cin >> out)) {
        // clear() снимает флаг ошибки потока, ignore() выбрасывает
        // оставшийся мусор до конца строки — без обоих вызовов
        // следующая итерация цикла снова упрётся в тот же плохой ввод
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return (out >= minVal && out <= maxVal);
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int showMenu() {
    std::cout << "\nСИМУЛЯТОР БАРЖИ\n";
    std::cout << "1. Ввести данные вручную\n";
    std::cout << "2. Загрузить данные из файла\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";

    int choice = -1;
    while (!readInt(choice, 0, 2)) {
        std::cout << "Введите число от 0 до 2: ";
    }
    clearInput();
    return choice;
}

static void runSimulation(Barge& barge, std::istream& in, int N) {
    for (int i = 0; i < N; ++i) {
        char op;
        int  A, B;

        if (!(in >> op >> A >> B)) break;

        if      (op == '+') barge.load(A, B);
        else if (op == '-') barge.unload(A, B);
        else break;

        if (barge.hasError()) break;
    }
    barge.checkEmpty();
}

static void printResult(const Barge& barge) {
    std::cout << "\nРезультат: ";
    if (barge.hasError())
        std::cout << "Error\n";
    else
        std::cout << barge.maxBarrels() << "\n";
}

static void offerSave(const Barge& barge) {
    std::cout << "Сохранить результат в файл? (да/нет): ";
    std::string answer;
    std::cin >> answer;
    clearInput();

    if (answer != "да" && answer != "Да" && answer != "ДА") return;

    std::cout << "Введите имя файла: ";
    std::string filename;
    std::cin >> filename;
    clearInput();

    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "Не удалось создать файл \"" << filename << "\".\n";
        return;
    }

    if (barge.hasError())
        fout << "Error\n";
    else
        fout << barge.maxBarrels() << "\n";

    std::cout << "Результат записан в \"" << filename << "\".\n";
}

void runFromKeyboard() {
    int N, K, P;

    std::cout << "\n";
    std::cout << "N (число доков, 1-100000): ";
    while (!readInt(N, 1, 100000)) {
        std::cout << "Введите число от 1 до 100000: ";
    }
    std::cout << "K (число отсеков, 1-100000): ";
    while (!readInt(K, 1, 100000)) {
        std::cout << "Введите число от 1 до 100000: ";
    }
    std::cout << "P (лимит бочек, 1-100000): ";
    while (!readInt(P, 1, 100000)) {
        std::cout << "Введите число от 1 до 100000: ";
    }
    clearInput();

    Barge barge(K, P);

    std::cout << "\nОперации: \"+  A B\" — погрузка, \"-  A B\" — выгрузка.\n";
    std::cout << "A — отсек (1-" << K << "), B — вид топлива (1-10000).\n\n";

    for (int i = 0; i < N; ++i) {
        char op;
        int  A, B;
        bool valid = false;

        std::cout << "Операция " << (i + 1) << "/" << N << ": ";

        while (!valid) {
            if (!(std::cin >> op) || (op != '+' && op != '-')) {
                std::cout << "Ожидается '+' или '-': ";
                clearInput();
                continue;
            }
            if (!readInt(A, 1, K)) {
                std::cout << "Номер отсека от 1 до " << K << ": ";
                clearInput();
                continue;
            }
            if (!readInt(B, 1, 10000)) {
                std::cout << "Вид топлива от 1 до 10000: ";
                clearInput();
                continue;
            }
            clearInput();
            valid = true;
        }

        if (op == '+') barge.load(A, B);
        else           barge.unload(A, B);

        if (barge.hasError()) break;
    }

    barge.checkEmpty();
    printResult(barge);
    offerSave(barge);
}

void runFromFile() {
    std::string filename;

    std::cout << "\nВведите путь к файлу: ";
    std::cin >> filename;
    clearInput();

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Не удалось открыть файл \"" << filename << "\".\n";
        return;
    }

    int N, K, P;
    if (!(fin >> N >> K >> P) ||
        N < 1 || N > 100000 ||
        K < 1 || K > 100000 ||
        P < 1 || P > 100000)
    {
        std::cout << "Некорректные параметры в файле (N, K, P должны быть от 1 до 100000).\n";
        return;
    }

    Barge barge(K, P);
    runSimulation(barge, fin, N);
    printResult(barge);
    offerSave(barge);
}
