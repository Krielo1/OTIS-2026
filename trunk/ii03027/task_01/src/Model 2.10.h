#pragma once
#include "Model.h"
#include <cmath>

// Нелинейная модель 2.10: y(t+1) = a*tanh(y(t)) + b*u(t)^3
class NonlinearModel2_10 : public Model {
private:
    double a, b;
    double y_t;
public:
    NonlinearModel2_10(double _a, double _b) : a(_a), b(_b), y_t(0.0) {}

    void reset() override { y_t = 0.0; }

    double step(double u) override {
        y_t = a * std::tanh(y_t) + b * std::pow(u, 3);
        return y_t;
    }
};