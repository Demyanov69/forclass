# Обработка команд в терминале

#include <iostream> // Подключение библиотеки для ввода-вывода
#include <string> // Подключение библиотеки для работы со строками
#include <vector> // Подключение библиотеки для работы с векторами
#include <fstream> // Подключение библиотеки для работы с файлами
#include <sstream> // Подключение библиотеки для работы с потоками строк
#include <cstdlib> // Подключение библиотеки для работы с функциями C стандартной библиотеки
#include <sys/wait.h> // Подключение библиотеки для работы с процессами
#include <unistd.h> // Подключение библиотеки для работы с системными вызовами
#include <signal.h> // Подключение библиотеки для работы с сигналами

using namespace std;

// Обработчик сигнала SIGHUP
void sigupHandler(int sig) {
    cout << "Configuration reloaded" << endl; // Вывод сообщения о перезагрузке конфигурации
}

// Проверка валидности команды
bool isCommandValid(const string& command) {
    return (command == "echo" || command == "exit" || command == "\\q" || command == "\\e" || command == "\\l" || command == "\\cron" || command == "\\mem"); // Проверка, является ли команда допустимой
}

// Функция для выполнения команды echo
void executeEcho(stringstream& ss) {
    string arg;
    while (ss >> arg) { // Чтение аргументов из потока
        cout << arg << " "; // Вывод аргументов на экран
    }
    cout << endl; // Переход на новую строку
}

// Функция для вывода переменной окружения
void printEnvVariable(stringstream& ss) {
    string varName;
    ss >> varName; // Чтение имени переменной из потока
    if (varName.empty()) {
        cout << "Где имя переменной?" << endl; // Сообщение об ошибке, если имя переменной не указано
    }
    else {
        const char* varValue = getenv(varName.c_str()); // Получение значения переменной окружения
        if (varValue != nullptr) {
            cout << varValue << endl; // Вывод значения переменной
        }
        else {
            cout << "Переменная окружения не найдена." << endl; // Сообщение об ошибке, если переменная не найдена
        }
    }
}

// Функция для получения информации о разделах
void listPartitions() {
    system("lsblk"); // Выполнение команды для отображения информации о разделах
}

// Функция для выполнения бинарника
void executeBinary(stringstream& ss) {
    string binary;
    ss >> binary; // Чтение имени бинарного файла из потока
    if (binary.empty()) {
        cout << "Укажите бинарник для выполнения." << endl; // Сообщение об ошибке, если имя бинарника не указано
        return;
    }
    pid_t pid = fork(); // Создание нового процесса
    if (pid == 0) {
        execlp(binary.c_str(), binary.c_str(), (char*)nullptr); // Выполнение бинарного файла
        perror("Ошибка выполнения бинарника"); // Сообщение об ошибке, если выполнение не удалось
        exit(EXIT_FAILURE); // Завершение дочернего процесса с ошибкой
    } else if (pid < 0) {
        perror("Ошибка fork"); // Сообщение об ошибке, если создание процесса не удалось
    } else {
        wait(nullptr); // Ожидание завершения дочернего процесса
    }
}

// Функция для подключения VFS
void connectVFS() {
    system("mount -t vfs /tmp/vfs"); // Выполнение команды для подключения виртуальной файловой системы
}

// Функция для получения дампа памяти процесса
void dumpMemory(stringstream& ss) {
    int procid;
    ss >> procid; // Чтение идентификатора процесса из потока
    if (procid <= 0) {
        cout << "Укажите корректный идентификатор процесса." << endl; // Сообщение об ошибке, если идентификатор некорректен
        return;
    }
    string command = "gcore " + to_string(procid); // Формирование команды для получения дампа памяти
    system(command.c_str()); // Выполнение команды
}

// Основная функция
int main() {
    string inputString; // Переменная для хранения введенной строки
    vector<string> commandHistory; // Вектор для хранения истории команд
    ifstream historyFile("history.txt"); // Открытие файла истории команд
    string line;

    // Чтение истории команд из файла
    while (getline(historyFile, line)) {
        commandHistory.push_back(line); // Добавление строки в историю команд
    }
    historyFile.close(); // Закрытие файла

    // Регистрация обработчика сигнала SIGHUP
    signal(SIGHUP, sigupHandler); // Установка обработчика сигнала

    // Основной цикл для ввода команд
    while (true) {
        cout << "> "; // Вывод приглашения для ввода команды
        if (!getline(cin, inputString)) {
            break; // Выход по Ctrl+D
        }

        commandHistory.push_back(inputString); // Добавление введенной команды в историю

        if (inputString == "exit" || inputString == "\\q") {
            break; // Выход из программы
        }

        stringstream ss(inputString); // Создание потока для обработки введенной строки
        string command;
        ss >> command; // Чтение команды из потока

        if (isCommandValid(command)) { // Проверка валидности команды
            if (command == "echo") {
                executeEcho(ss); // Выполнение команды echo
            }
            else if (command == "\\e") {
                printEnvVariable(ss); // Вывод переменной окружения
            }
            else if (command == "\\l") {
                listPartitions(); // Вывод информации о разделах
            }
            else if (command == "\\cron") {
                connectVFS(); // Подключение VFS
            }
            else if (command == "\\mem") {
                dumpMemory(ss); // Получение дампа памяти процесса
            }
            else {
                executeBinary(ss); // Выполнение бинарного файла
            }
        }
        else {
            cerr << "Команда не найдена: " << command << endl; // Сообщение об ошибке
        }
    }

    // Сохранение истории в файл
    ofstream outFile("history.txt"); // Открытие файла для записи истории команд
    for (const auto& command : commandHistory) {
        outFile << command << endl; // Запись каждой команды в файл
    }
    outFile.close(); // Закрытие файла

    return 0; // Завершение программы
}

//---------------------

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

// Обработчик сигнала SIGHUP
void sigupHandler(int sig) {
    cout << "Configuration reloaded" << endl;
}

// Проверка валидности команды
bool isCommandValid(const string& command) {
    return (command == "echo" || command == "exit" || command == "\\q" || command == "\\e" || command == "\\l");
}

// Функция для выполнения команды echo
void executeEcho(stringstream& ss) {
    string arg;
    while (ss >> arg) {
        cout << arg << " ";
    }
    cout << endl;
}

// Функция для вывода переменной окружения
void printEnvVariable(stringstream& ss) {
    string varName;
    ss >> varName;
    if (varName.empty()) {
        cout << "Где имя переменной?" << endl;
    }
    else {
        const char* varValue = getenv(varName.c_str());
        if (varValue != nullptr) {
            cout << varValue << endl;
        }
        else {
            cout << "Переменная окружения не найдена." << endl;
        }
    }
}

// Функция для получения информации о разделах
void listPartitions() {
    system("lsblk");
}

// Основная функция
int main() {
    string inputString;
    vector<string> commandHistory;
    ifstream historyFile("history.txt");
    string line;

    // Чтение истории команд из файла
    while (getline(historyFile, line)) {
        commandHistory.push_back(line);
    }
    historyFile.close();

    // Регистрация обработчика сигнала SIGHUP
    signal(SIGHUP, sigupHandler);

    // Основной цикл для ввода команд
    while (true) {
        cout << "> ";
        if (!getline(cin, inputString)) {
            break; // Выход по Ctrl+D
        }

        commandHistory.push_back(inputString);

        if (inputString == "exit" || inputString == "\\q") {
            break; // Выход из программы
        }

        stringstream ss(inputString);
        string command;
        ss >> command;

        if (isCommandValid(command)) {
            if (command == "echo") {
                executeEcho(ss);
            }
            else if (command == "\\e") {
                printEnvVariable(ss);
            }
            else if (command == "\\l") {
                listPartitions();
            }
        }
        else {
            cerr << "Команда не найдена: " << command << endl; // Сообщение об ошибке
        }
    }

    // Сохранение истории в файл
    ofstream outFile("history.txt");
    for (const auto& command : commandHistory) {
        outFile << command << endl;
    }
    outFile.close();


    //Вроде так использовать команду
    \e $PATH shell
    //Потенциальное решение проблемы
    void printEnvVariable(stringstream& ss) {
    string varName;
    ss >> varName;

    // Удаляем символ '$', если он присутствует
    if (varName[0] == '$') {
        varName.erase(0, 1);
    }

    if (varName.empty()) {
        cout << "Где имя переменной?" << endl;
    }
    else {
        const char* varValue = getenv(varName.c_str());
        if (varValue != nullptr) {
            cout << varValue << endl;
        }
        else {
            cout << "Переменная окружения не найдена." << endl;
        }
    }
}

    return 0;
}

//-----

