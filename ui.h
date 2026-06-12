#pragma once
#include <string>

// читает int из cin, сбрасывает поток при ошибке; возвращает true если значение в [minVal, maxVal]
bool readInt(int& out, int minVal, int maxVal);
void clearInput();

int  showMenu();
void runFromKeyboard();
void runFromFile();
