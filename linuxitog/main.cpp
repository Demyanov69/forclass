#define FUSE_USE_VERSION 31
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <fcntl.h>
#include <dirent.h>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <csignal>
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <cstdlib>
#include <array>
#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <map>


using namespace std;

bool command_exists(const string& command) {
    if (command == "ls" || command == "pwd" || command == "cd" || command == "echo" || command == "export" || command == "unset") {
        return true;    }
    return access(command.c_str(), X_OK) == 0;
}

/*void execute_command(const string& command) { 
    if (!command_exists(command)) { 
        // Check if the command is a binary file 
        struct stat st; 
        if (stat(command.c_str(), &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) { 
            pid_t pid = fork(); 
            if (pid == 0) { 
                execl(command.c_str(), command.c_str(), nullptr); 
                perror("execl failed"); 
                exit(1); 
            } else if (pid > 0) { 
                int status; 
                waitpid(pid, &status, 0); 
                if (WIFEXITED(status)) { 
                    int exitStatus = WEXITSTATUS(status); 
                    if (exitStatus != 0) { 
                        cerr << "Command '" << command << "' exited with status " << exitStatus << endl; 
                    } 
                } else { 
                    cerr << "Command '" << command << "' terminated abnormally" << endl; 
                } 
            } else { 
                perror("fork failed"); 
            } 
        } else { 
            cerr << "Command not found: " << command << endl; 
        } 
    } else { 
        pid_t pid = fork(); 
        if (pid == 0) { 
            char *args[] = {const_cast<char*>(command.c_str()), nullptr}; 
            execvp(args[0], args); 
            perror("execvp failed"); 
            exit(1); 
        } else if (pid > 0) { 
            int status; 
            waitpid(pid, &status, 0); 
            if (WIFEXITED(status)) { 
                int exitStatus = WEXITSTATUS(status); 
                if (exitStatus != 0) { 
                    cerr << "Command '" << command << "' exited with status " << exitStatus << endl; 
                } 
            } else { 
                cerr << "Command '" << command << "' terminated abnormally" << endl; 
            } 
        } else { 
            perror("fork failed"); 
        } 
    } 
}*/ 

vector<string> split(const string &str, char delimiter);

void execute_command(const string& command) { 
    vector<string> args = split(command, ' '); 
    vector<char*> c_args; 
    for (const auto& arg : args) { 
        c_args.push_back(const_cast<char*>(arg.c_str())); 
    } 
    c_args.push_back(nullptr); // execvp ожидает массив, заканчивающийся nullptr 
 
    pid_t pid = fork(); 
    if (pid == -1) { 
        perror("Ошибка при создании процесса"); 
        return; 
    } else if (pid == 0) { 
        // Дочерний процесс 
        if (execvp(c_args[0], c_args.data()) == -1) { 
            perror("команда не существует"); 
            exit(EXIT_FAILURE); 
        } 
    } else { 
        // Родительский процесс 
        int status; 
        waitpid(pid, &status, 0); 
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
  int fd;
  unsigned char buffer[512]; // Sector size - 512 bytes
  bool bootable = false;

  // Open the disk in read-only mode
  fd = open("/dev/sda", O_RDONLY);
  if (fd == -1) {
    perror("Error opening disk");
    return;
  }

  // Read the first sector (512 bytes)
  ssize_t bytesRead = read(fd, buffer, 512);
  if (bytesRead == -1) {
    perror("Error reading from disk");
    close(fd);
    return;
  } else if (bytesRead != 512) {
    cerr << "Failed to read the entire sector" << endl;
    close(fd);
    return;
  }

  // Check for the boot signature (55AA) in the last two bytes of the sector
  if (buffer[510] == 0x55 && buffer[511] == 0xAA) {
    bootable = true;
  }

  close(fd);

  if (bootable) {
    cout << "/dev/sda: Bootable sector" << endl;
  } else {
    cout << "/dev/sda: Non-bootable sector" << endl;
  }
}



string exec(const string cmd) {
    array<char, 128> buffer{};
    string result;            
    unique_ptr<FILE, int (*)(FILE *)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw runtime_error("Не удалось открыть процесс!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result; 
}

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(str);
    string token;

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void create_cron_vfs() {
    string crontab_info = exec("crontab -l");
    vector<string> cron_commands = split(crontab_info, '\n');
    cout << "Starting mount" << endl;
    exec("mkdir -p .cronfs");
    exec("sudo mount -t tmpfs tmpfs .cronfs");
    for (string i : cron_commands) {
        if (i.length() != 0) {
            string file_name = i.substr(10, i.length() - 1);
            ofstream outfile(".cronfs/" + file_name);
            outfile << i.substr(0, 10) << std::endl;
            outfile.close();
            cout << "Create file " + file_name << endl;
        }
    }
    cout << "Mounting is done!" << endl;
}

void umount_cron_vfs() {
    cout << "Starting umount" << endl;
    exec("sudo umount /tmp/vfs");
    exec("rm -rf .cronfs");
    cout << ".cronfs was deleted!" << endl;
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
            create_cron_vfs();
        } else if (command.empty()) {
            cout << "<<Please enter a command>>" << endl;
        } else {
            execute_command(command);
        }
    }

    ofstream outFile("history.txt");
    for (const auto& command : commandHistory) {
        outFile << command << endl;
    }
    outFile.close();
    return 0;
}
