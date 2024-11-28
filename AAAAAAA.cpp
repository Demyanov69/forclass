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
#include <sys/types.h> // для pid_t
#include <stdexcept> // для runtime_error


using namespace std;

void sigupHandler(int sig) {
    cout << "<<CONFIG RELOADED>>" << endl;
}

bool isCommandValid(const string& command) {
    return (command == "echo" || command == "exit" || command == "\q" || command == "\e" || command == "\l" || command == "\cron" || command == "./test");
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
        cout << "<<Where is the name?>>" << endl;
    } else {
        const char* varValue = getenv(varName.c_str());
        if (varValue != nullptr) {
            cout << varValue << endl;
        } else {
            cout << "I dont found anything :(" << endl;
        }
    }
}

void listPartitions() {
    system("lsblk");
}

void executeBinary(const string& command) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        char* argv[] = {const_cast<char*>(command.c_str()), nullptr};
        if (execvp(argv[0], argv) == -1) {
            perror("execvp failed");
            exit(1);
        }
    } else if (pid > 0) { // Parent process
        int status;
        if (wait(&status) == -1) {
            perror("wait failed");
        }
        if (WIFEXITED(status)) {
            cout << "Binary exited with status: " << WEXITSTATUS(status) << endl;
        } else if (WIFSIGNALED(status)) {
            cout << "Binary terminated by signal: " << WTERMSIG(status) << endl;
        }
    } else {
        perror("fork failed");
        throw runtime_error("fork failed"); // Выбрасываем исключение при ошибке fork
    }
}

void connectVFS() {
    string mountPoint = "/tmp/vfs";
    if (access(mountPoint.c_str(), F_OK) != 0) {
        cout << "create with mkdir /tmp/vfs." << endl;
        return;
    }
    system("fusermount -uz /tmp/vfs");
    int result = system(("mount -t vfs vfs " + mountPoint).c_str());
    if (result != 0) {
        cout << "vfs error. is vfs right?" << endl;
        return;
    }
    cout << "vfs is here " << mountPoint << endl;
    string crontabEntry = " * * * * * /usr/bin/touch " + mountPoint + "/test.txt";
    result = system(("crontab -l; echo "" + crontabEntry + """).c_str());
    if (result != 0) {
        cout << "error" << endl;
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
        stringstream ss(inputString);
        string command;
        ss >> command;

        if (command == "echo") {
            executeEcho(ss);
        } else if (command == "\q" || command == "exit") {
            break;
        } else if (command == "\e") {
            printEnvVariable(ss);
        } else if (command == "\l") {
            listPartitions();
        } else if (command == "\cron") {
            connectVFS();
        } else if (command == "./test" || isCommandValid(command)) {
            executeBinary(command);
        } else {
            cerr << "Unknown command: " << command << endl;
        }
    }

    ofstream historyFileOut("history.txt");
    for (const string& cmd : commandHistory) {
        historyFileOut << cmd << endl;
    }
    historyFileOut.close();
    return 0;
}
