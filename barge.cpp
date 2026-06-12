#include "barge.h"

Barge::Barge(int K, int P)
    : K_(K), P_(P), total_(0), maxTotal_(0), hasError_(false)
{
    compartments_ = new Stack[K_];
}

Barge::~Barge() {
    delete[] compartments_;
}

void Barge::load(int compartment, int fuelType) {
    if (hasError_) return;
    if (compartment < 1 || compartment > K_) { hasError_ = true; return; }

    compartments_[compartment - 1].push(fuelType);
    ++total_;

    // сначала фиксируем максимум, потом проверяем лимит —
    // бочка уже на барже, поэтому считаем её в обоих случаях
    if (total_ > maxTotal_) maxTotal_ = total_;
    if (total_ > P_)        hasError_ = true;
}

void Barge::unload(int compartment, int expectedFuel) {
    if (hasError_) return;
    if (compartment < 1 || compartment > K_) { hasError_ = true; return; }

    Stack& s = compartments_[compartment - 1];

    // отсек — стек (LIFO): выгрузить можно только верхнюю бочку,
    // и её вид топлива должен совпасть с ожидаемым
    if (s.empty() || s.peek() != expectedFuel) {
        hasError_ = true;
        return;
    }

    s.pop();
    --total_;
}

void Barge::checkEmpty() {
    if (total_ != 0) hasError_ = true;
}

bool Barge::hasError()   const { return hasError_; }
int  Barge::maxBarrels() const { return maxTotal_; }
int  Barge::getK()       const { return K_; }