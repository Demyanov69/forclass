#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream partitionsFile("/proc/partitions");
    string line;

    if (!partitionsFile.is_open()) {
        cerr << "Error opening /proc/partitions" << endl;
        return 1;
    }

    // Пропускаем заголовок
    getline(partitionsFile, line);

    cout << "Major Minor  #blocks  name" << endl; // Заголовок для удобства чтения

    while (getline(partitionsFile, line)) {
        stringstream ss(line);
        string major, minor, blocks, name;
        ss >> major >> minor >> blocks >> name;
        cout << major << "  " << minor << "  " << blocks << "  " << name << endl;
    }

    partitionsFile.close();
    return 0;
}

