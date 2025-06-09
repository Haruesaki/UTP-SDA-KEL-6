#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

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

int main(){

    return 0;
}