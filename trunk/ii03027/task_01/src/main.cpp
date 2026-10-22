#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
#include "Model.h"
#include "Model 1.3.h"
#include "Model 2.10.h"
#include "Model 3.2.h"

double generateSignal(int type, int t) {
    switch(type) {
        case 0: return 1.0;                         
        case 1: return (t == 0) ? 1.0 : 0.0;        
        case 2: return std::sin(t);                 
        default: return 0.0;
    }
}

std::string getSignalName(int type) {
    switch(type) {
        case 0: return "Step";
        case 1: return "Impulse";
        case 2: return "Harmonic";
        default: return "Unknown";
    }
}

void runSimulation(std::shared_ptr<Model> model, int steps, int signalType, const std::string& modelName, std::ofstream& csvFile) {
    model->reset();
    std::string sigName = getSignalName(signalType);
    
    std::cout << "\n--- Модель: " << modelName << " | Сигнал: " << sigName << " ---" << std::endl;
    std::cout << std::setw(5) << "t" << std::setw(15) << "u(t)" << std::setw(15) << "y(t)" << std::endl;

    for (int t = 0; t < steps; ++t) {
        double u = generateSignal(signalType, t);
        double y = model->step(u);
        
        std::cout << std::setw(5) << t 
                  << std::setw(15) << std::fixed << std::setprecision(4) << u 
                  << std::setw(15) << std::fixed << std::setprecision(4) << y << std::endl;
                  
        csvFile << modelName << "," << sigName << "," << t << "," << u << "," << y << "\n";
    }
}

int main() {
    int steps;
    std::cout << "Введите количество шагов симуляции n: ";
    std::cin >> steps;

    std::ofstream csvFile("simulation_results.csv");
    csvFile << "Model,Signal,Step,u,y\n";

    auto linModel = std::make_shared<LinearModel13>(0.5, 0.3, 0.2);
    auto nonLinModel = std::make_shared<NonlinearModel2_10>(0.8, 0.1);
    auto diffModel = std::make_shared<DiffEqModel3_2>(0.5, 1.0);

    std::vector<std::pair<std::shared_ptr<Model>, std::string>> models = {
        {linModel, "Model_1.3"},
        {nonLinModel, "Model_2.10"},
        {diffModel, "Model_3.2"}
    };

    for (auto& pair : models) {
        for (int sigType = 0; sigType < 3; ++sigType) {
            runSimulation(pair.first, steps, sigType, pair.second, csvFile);
        }
    }

    csvFile.close();
    std::cout << "\nСимуляция завершена. Данные сохранены в simulation_results.csv" << std::endl;
    return 0;
}