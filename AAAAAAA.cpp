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
#include <fcntl.h>
#include <cstring>
#include <sys/types.h> // for pid_t


using namespace std;

bool command_exists(const string& command) {
    char *path = (char *)getenv("PATH");
    if(path == nullptr) return false;

    char *dir = strtok(strdup(path), ":");
    while(dir != nullptr){
        string cmd_path = dir + "/" + command;
        if(access(cmd_path.c_str(), X_OK) == 0) return true;
        dir = strtok(nullptr, ":");
    }
    return false;
}

void execute_command(const string& command) {
    if (!command_exists(command)) {
        cerr << "Command not found: " << command << endl;
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {const_cast<char*>(command.c_str()), nullptr};
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        wait(nullptr);
    } else {
        perror("fork failed");
    }
}


void sigupHandler(int sig) {
    cout << "<<CONFIG RELOADED>>" << endl;
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
        cout << "<<Where is the variable name?>>" << endl;
    } else {
        const char* varValue = getenv(varName.c_str());
        if (varValue != nullptr) {
            cout << varValue << endl;
        } else {
            cout << "I found nothing :(" << endl;
        }
    }
}

void listPartitions() {
    int fd = open("/dev/sda", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /dev/sda");
        return;
    }

    unsigned char buffer[512];
    if (read(fd, buffer, sizeof(buffer)) != sizeof(buffer)) {
        perror("Failed to read the first sector");
        close(fd);
        return;
    }

    close(fd);

    // Check for the boot signature at the end of the first sector
    if (buffer[510] == 0x55 && buffer[511] == 0xAA) {
        cout << "The first sector is bootable." << endl;
    } else {
        cout << "The first sector is not bootable." << endl;
    }
}


void connectVFS() {
    string mountPoint = "/tmp/vfs";
    if (access(mountPoint.c_str(), F_OK) != 0) {
        cout << "Please create using mkdir /tmp/vfs." << endl;
        return;
    }
    system("fusermount -uz /tmp/vfs");
    int result = system(("mount -t vfs vfs " + mountPoint).c_str());
    if (result != 0) {
        cout << "VFS error. Is the vfs correct?" << endl;
        return;
    }
    cout << "VFS is mounted at " << mountPoint << endl;
    string crontabEntry = " * * * * * /usr/bin/touch " + mountPoint + "/test.txt";
    result = system(("crontab -l; echo \"" + crontabEntry + "\"").c_str());
    if (result != 0) {
        cout << "Error" << endl;
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
        if (command == "echo") {
            executeEcho(ss);
        } else if (command == "\\e") {
            printEnvVariable(ss);
        } else if (command == "\\l") {
            listPartitions();
        } else if (command == "\\cron") {
            connectVFS();
        } else if (command.empty()) {
            cout << "<<Please enter a command>>" << endl;
        } else {
            execute_command(command); // Use the improved execute_command function
        }
    }

    ofstream outFile("history.txt");
    for (const auto& command : commandHistory) {
        outFile << command << endl;
    }
    outFile.close();
    return 0;
}

-----------------------



ДАЛЬШЕ
НЕ
КОПИРОВАТЬ


-----------------------
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
