#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <crypt.h>

using namespace std;

int main(int argc, char *argv[]) {
    string userInput = argv[1];
    if (userInput.length() < 3 || userInput.length() > 32){
        cout << "User must be between 3 and 32 characters!\n";
        exit(EXIT_FAILURE);
    }
    string user;
    string pass;
    string encPass;
    string userPass;
    int attempts = strtol(argv[2],NULL,10);
    if (attempts < 1) {
        cout << "Number of attempts given must be 1 or more!\n";
        exit(EXIT_FAILURE);
    }
    ifstream readFile;
    readFile.open("passwd");
    cout << "Entered user: " + userInput + "\n";
    std::string line;
    while (std::getline(readFile, line)) {
        std::istringstream tokenizer(line);
        std::getline(tokenizer, user, ':');
        std::getline(tokenizer, pass, ':');
        if (user == userInput) {
            int n = 0;
            while (n < attempts) {
            string str;
            cout << "Enter your password: \n";
            getline(cin, userPass);
            encPass = crypt(userPass.c_str(), "xx");
                if (encPass == pass) {
                    cout << "Success, you have been authenticated!\n";
                    exit(0);
                } else {
                    n = n + 1;
                }
            }
            cout << "Too many attempts! Unsuccessful!\n";
            exit(EXIT_FAILURE);
        }
    }
    readFile.close();
    string st;
    bool valid = true;
    string newPass;
    string tempNewPass;
    string encNewPass;
    int count = 1;
    do {
        valid = true;
        cout << "Enter a new password: \n";
        getline(cin, newPass);
        if(newPass.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
            cout << "No special characters allowed!\n";
            valid = false;
        }
        if (newPass.length() > 12) {
            cout << "Password cannot exceed 12 characters!\n";
            valid = false;
        }
        if (count == attempts) {
            cout << "Too many attempts! Unsuccessful!\n";
            exit(EXIT_FAILURE);
        }
        count = count + 1;
    } while (!valid);
    encNewPass = crypt(newPass.c_str(), "xx");
    ofstream writeFile;
    writeFile.open("passwd", std::ios_base::app);
    writeFile << userInput + ":" + encNewPass + ":x:x:" + userInput + ":/home/" + userInput + "\n";
    cout << "A new login has been created! Login successful!\n";
    return 0;
}