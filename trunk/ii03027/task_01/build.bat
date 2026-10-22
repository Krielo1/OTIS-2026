@echo off
chcp 65001 >nul
echo [1/4] Создание директории build...
if not exist build mkdir build
cd build

echo [2/4] Запуск CMake и сборка...
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release

echo [3/4] Запуск программы...
:: Автоматически передаем 10 как количество шагов (n)
if exist Release\Lab1_Modeling.exe (
    echo 10 | Release\Lab1_Modeling.exe
) else (
    echo 10 | Lab1_Modeling.exe
)

echo [4/4] Запуск визуализации (Python)...
cd ..
python plot.py

pause