#include <iostream>
#include <string>
#include <array>
#include <cstdio> // для popen() и pclose()
#include <stdexcept>


using namespace std;


int main() {
    array<char, 128> buffer;
    string command = "lsblk -o NAME,FSTYPE,SIZE,MOUNTPOINT"; // команда для получения информации о разделах
    FILE *stream = popen(command.c_str(), "r");

    if (stream == nullptr) {
        throw runtime_error("Ошибка при вызове popen()");
    }

    cout << "NAME\tFSTYPE\tSIZE\tMOUNTPOINT" << endl; // заголовок таблицы
    while (fgets(buffer.data(), buffer.size(), stream) != nullptr) {
        cout << buffer.data();
    }

    int returnCode = pclose(stream);
    if (returnCode == -1) {
        perror("pclose() failed");
        return 1; //Возвращаем код ошибки
    }
    if (WIFEXITED(returnCode) && WEXITSTATUS(returnCode) != 0) {
        cerr << "lsblk завершилась с кодом ошибки: " << WEXITSTATUS(returnCode) << endl;
        return 1; //Возвращаем код ошибки
    }


    return 0;
}

