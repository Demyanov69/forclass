#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream> 
#include <sstream> 
#include <cstdlib> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <signal.h> 
#include <errno.h> 
using namespace std; 
  
void sigupHandler(int sig) { 
    cout << "<<CONFIG RELOADED>>" << endl; 
} 
  
bool isCommandValid(const string& command) { 
    return (command == "echo" || command == "exit" || command == "\\q" || command == "\\e" || command == "\\l" || command == "\\cron"); 
} 
  
void executeEcho(stringstream& ss) { 
    string arg; 
    while (ss >> arg) { 
        cout << arg << " "; 
    } 
    cout << endl; 
} 
  
void printEnvVariable(stringstream& ss) { 
    string varName; 
    ss >> varName; 
    if (varName.empty()) { 
        cout << "<<Где имя?>>" << endl; 
    } else { 
        const char* varValue = getenv(varName.c_str()); 
        if (varValue != nullptr) { 
            cout << varValue << endl; 
        } else { 
            cout << "Я ничего не нашёл :(" << endl; 
        } 
    } 
} 

void listPartitions() { 
    system("lsblk"); 
} 
  
void executeBinary(const string& command) { 
    if (fork() == 0) { 
        char* argv[2] = {const_cast<char*>(command.c_str()), nullptr}; 
        execvp(argv[0], argv); 
        perror("execvp не удался"); 
        exit(1); 
    } else { 
        wait(nullptr); 
    } 
} 

void connectVFS() { 
    string mountPoint = "/tmp/vfs"; 
    if (access(mountPoint.c_str(), F_OK) != 0) { 
        cout << "создайте с помощью mkdir /tmp/vfs." << endl; 
        return; 
    } 
    system("fusermount -uz /tmp/vfs"); 
    int result = system(("mount -t vfs vfs " + mountPoint).c_str()); 
    if (result != 0) { 
        cout << "ошибка vfs. vfs правильный?" << endl; 
        return; 
    } 
    cout << "vfs здесь " << mountPoint << endl; 
    string crontabEntry = " * * * * * /usr/bin/touch " + mountPoint + "/test.txt"; 
    result = system(("crontab -l; echo \"" + crontabEntry + "\"").c_str()); 
    if (result != 0) { 
        cout << "ошибка" << endl; 
    } 
} 

int main() { 
    string inputString; 
    vector<string> commandHistory; 
    ifstream historyFile("history.txt"); 
    string line; 
  
    while (getline(historyFile, line)) { 
        commandHistory.push_back(line); 
    } 
    historyFile.close(); 
  
    signal(SIGHUP, sigupHandler);  
  
    while (true) { 
        cout << "-> "; 
        if (!getline(cin, inputString)) { 
            break; 
        } 
        commandHistory.push_back(inputString); 
        if (inputString == "exit" || inputString == "\\q") { 
            break; 
        } 
        stringstream ss(inputString); 
        string command; 
        ss >> command; 
        if (!isCommandValid(command)) {
            cout << "Неверная команда!" << endl;
            continue;
        }
        if (command == "echo") { 
            executeEcho(ss); 
        } else if (command == "\\e") { 
            printEnvVariable(ss); 
        } else if (command == "\\l") { 
            listPartitions(); 
        } else if (command == "\\cron") { 
            connectVFS(); 
        } else { 
            executeBinary(command); 
        } 
    } 
  
    ofstream outFile("history.txt"); 
    for (const auto& command : commandHistory) { 
        outFile << command << endl; 
    } 
    outFile.close(); 
    return 0; 
}
