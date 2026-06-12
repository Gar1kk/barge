#pragma once
#include "stack.h"

/*
 * Симулятор баржи.
 * Управляет K отсеками (каждый — стек) и отслеживает
 * текущее число бочек, максимум и флаг ошибки.
 */
class Barge {
private:
    int    K_;
    int    P_;
    Stack* compartments_;
    int    total_;
    int    maxTotal_;
    bool   hasError_;

public:
    Barge(int K, int P);
    ~Barge();

    Barge(const Barge&)            = delete;
    Barge& operator=(const Barge&) = delete;

    // Погрузка: положить бочку с топливом fuelType в отсек compartment (1-based)
    void load(int compartment, int fuelType);

    // Выгрузка: извлечь крайнюю бочку из отсека compartment, ожидая expectedFuel
    void unload(int compartment, int expectedFuel);

    // Проверить что баржа пуста после всех доков
    void checkEmpty();

    bool hasError()   const;
    int  maxBarrels() const;
    int  getK()       const;
};