#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

string getTodayDate(){
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

bool isUsernameExist (const string& username){
    ifstream file ("userdata.txt");
    string fileUsername, filePassword;
    while (file >> fileUsername >> filePassword){
        if (fileUsername == username){
            return true;
        }
    }

}
void registerUser (){
    string username, password ;
    cout << "Masukkan username: ";
    cin >> username;

    if (isUsernameExist(username)){
        cout << "Username sudah ada. Silahkan coba username lain." << endl;
        return;
    }

    cout << "Masukkan password: ";
    cin >> password;
    ofstream file ("userdata.txt", ios::app);
    file << username << " " << password << endl ;
    cout << "Registrasi berhasil!" << endl;

}

bool loginUser(string& loggedInUser) { //menambahkan fungsi loginUser
    string username, password ;
    cout << "Masukan username: ";
    cin >> username;
    cout << "Masukan password: ";
    cin >> password;

    ifstream file("userdata.txt");
    string fileUsername, filePassword;
    while (file >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password) {
            loggedInUser = username;
            return true;
        }
    }
    cout << "Username atau password salah." << endl;
    return false;
}

int main(){

    return 0;
}
