#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void showHelp() {
    cout << "=====================================================================" << endl;
    cout << "Статистический калькулятор" << endl;
    cout << "Доступные операции:" << endl;
    cout << "  среднее арифметическое (srarif) - среднее арифметическое всех операндов" << endl;
    cout << "  медиана (median)                - медиана набора операндов" << endl;
    cout << "  справка (help)                  - выдача справки по работе программы" << endl;
    cout << "Количество операндов: от 6 до 8" << endl;
    cout << "Использование:" << endl;
    cout << "  ./Calculator -o <операция> <число1> <число2> ... <число8>" << endl;
    cout << "  ./Calculator --operation <операция> <число1> <число2> ..." << endl;
    cout << "  ./Calculator -h" << endl;
    cout << "  ./Calculator --help" << endl;
    cout << "Примеры:" << endl;
    cout << "  ./Calculator -o srarif 10 20 30 40 50 60" << endl;
    cout << "  ./Calculator --operation median 7 3 1 9 5 2 8" << endl;
    cout << "=====================================================================" << endl;
}

class Calculator {
private:
    vector<double> operands;
    double result;

public:
    Calculator() : result(0) {}

    void addOperand(double value) {
        operands.push_back(value);
    }

    int getOperandCount() {
        return operands.size();
    }

    void srarif() {
        result = 0;
        for (size_t i = 0; i < operands.size(); i++) {
            result += operands[i];
        }
        result /= operands.size();
        cout << "Результат: " << result << endl;
    }

    void median() {
        vector<double> sorted = operands;
        sort(sorted.begin(), sorted.end());
        size_t n = sorted.size();
        if (n % 2 == 1) {
            result = sorted[n / 2];
        } else {
            result = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
        }
        cout << "Результат: " << result << endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp();
        return 0;
    }

    string operation = "";
    Calculator calc;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showHelp();
            return 0;
        }

        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[i + 1];
                i++;
            }
        } else if (arg.rfind("--operation=", 0) == 0) {
            operation = arg.substr(12);
        } else if (arg.rfind("-o=", 0) == 0) {
            operation = arg.substr(3);
        } else {
            try {
                calc.addOperand(stod(arg));
            } catch (...) {
                cerr << "Ошибка. Некорректное число: " << arg << endl;
                return 1;
            }
        }
    }

    if (operation == "") {
        cerr << "Ошибка. Не указана операция!" << endl;
        showHelp();
        return 1;
    }

    if (calc.getOperandCount() < 6 || calc.getOperandCount() > 8) {
        cerr << "Ошибка. Нужно от 6 до 8 чисел! Вы ввели: " << calc.getOperandCount() << endl;
        return 1;
    }

    if (operation != "srarif" && operation != "median") {
        cerr << "Ошибка. Неизвестная операция!" << endl;
        showHelp();
        return 1;
    }

    if (operation == "srarif") {
        calc.srarif();
    } else {
        calc.median();
    }

    return 0;
}
