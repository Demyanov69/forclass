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

// Основная функция
int main()
{
    // Регистрация обработчика сигнала SIGHUP
    signal(SIGHUP, sigupHandler);

    string inputString;
    vector<string> commandHistory; // Вектор для хранения истории команд
    ifstream historyFile("history.txt"); // Открываем файл для чтения истории
    string line;

    // Читаем историю команд из файла
    while (getline(historyFile, line)) {
        commandHistory.push_back(line);
    }
    historyFile.close(); // Закрываем файл

    // Основной цикл для ввода команд
    while (true)
    {
        cout << "> "; // Выводим приглашение для ввода
        if (!getline(cin, inputString)) {
            break; // Выход по Ctrl+D
        }

        // Сохраняем введённую команду в историю
        commandHistory.push_back(inputString);

        // Проверяем команды на выход
        if (inputString == "exit" || inputString == "\\q")
        {
            break; // Выход из программы
        }

        stringstream ss(inputString);
        string command;
        ss >> command; // Получаем первую часть команды

        // Проверяем валидность команды
        if (isCommandValid(command))
        {
            if (command == "echo")
            {
                string arg;
                // Печатаем все аргументы после команды echo
                while (ss >> arg)
                {
                    cout << arg << " ";
                }
                cout << endl; // Переход на новую строку
            }
            else if (command == "\\e")
            {
                string varName;
                ss >> varName; // Получаем имя переменной окружения
                if (varName.empty()) {
                    cout << "Где имя переменной?" << endl; // Если имя не указано
                }
                else
                {
                    const char* varValue = getenv(varName.c_str()); // Получаем значение переменной окружения
                    if (varValue != nullptr) {
                        cout << varValue << endl; // Печатаем значение переменной
                    }
                    else {
                        cout << "Переменная окружения не найдена." << endl; // Если переменная не найдена
                    }
                }
            }
            else if (command == "\\l")
            {
                // Выполняем команду для получения информации о разделах
                system("lsblk"); // Используем system для выполнения команды
            }
        }
        else
        {
            pid_t pid = fork(); // Создаём новый процесс
            if (pid == 0) {
                // Дочерний процесс
                execlp(command.c_str(), command.c_str(), NULL); // Выполняем команду
                cerr << "Команда не найдена: " << command << endl; // Если команда не найдена
                exit(1); // Выход из дочернего процесса
            }
            else if (pid > 0) {
                // Родительский процесс
                int status;
                wait(&status); // Ожидаем завершения дочернего процесса
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    cerr << "Ошибка выполнения команды: " << command << endl; // Ошибка при выполнении
                }
            }
            else
            {
                cerr << "Ошибка при создании процесса" << endl; // Ошибка при создании процесса
            }
        }
    }

    // Сохранение истории в файл
    ofstream outFile("history.txt");
    for (const auto& command : commandHistory) {
        outFile << command << endl; // Записываем каждую команду в файл
    }
    outFile.close(); // Закрываем файл

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

    return 0;
}
