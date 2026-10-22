#pragma once
#include "Model.h"

// Диф. уравнение 3.2: dy/dt = b*u
// Решается методом Эйлера: y(t+1) = y(t) + dt * (b*u)
class DiffEqModel3_2 : public Model {
private:
    double b;
    double dt;
    double y_t;
public:
    DiffEqModel3_2(double _b, double _dt) : b(_b), dt(_dt), y_t(0.0) {}

    void reset() override { y_t = 0.0; }

    double step(double u) override {
        double dy_dt = b * u;
        y_t = y_t + dt * dy_dt;
        return y_t;
    }
};