// Kelompok 6, SDA
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

void simpanTransaksiKeFile(const string& username, const string& tanggal, const queue<string>& queueData,
    const stack<string>& stackData) {
    string filename = username + ".txt";

    ifstream cekFile(filename);
    bool fileBaru = !cekFile.good();
    cekFile.close();

    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan transaksi.\n";
        return;
    }

    file << "=== Tanggal: " << tanggal << " ===\n";
    file << "[FIFO]\n";
    queue<string> tempQueue = queueData;
    while (!tempQueue.empty()) {
        file << "- " << tempQueue.front() << "\n";
        tempQueue.pop();
    }

    file << "[LIFO]\n";
    stack<string> tempStack = stackData;
    while (!tempStack.empty()) {
        file << "- " << tempStack.top() << "\n";
        tempStack.pop();
    }
    
    file << "\n";
    file.close();

    if (fileBaru) {
        cout << "File baru \"" << filename << "\" dibuat dan transaksi disimpan.\n";
    } else {
        cout << "Transaksi ditambahkan ke file \"" << filename << "\".\n";
    }
}

class Barang {
    string makanan[10] = {
        "Oreo Neapolitan",
        "Hello Panda Strawberry",
        "Samyang Buldak",
        "Taro Barbeque",
        "Lays",
        "Sari Roti Tawar"
    };
    double hargaMakanan[10] = {13500, 9300, 19500, 9000, 13900, 18000};
    
    string minuman[10] = {
        "Sprite Botol Sedang",
        "Coca-Cola Kaleng",
        "AW Kaleng",
        "Air Mineral"
    };
    double hargaMinuman[10] = {5400, 6600, 6000, 3900};

    int jumlahMakanan = 6;
    int jumlahMinuman = 4;

public:
    void tampilkanDaftarBarang() {
        cout << "\n=== Daftar Makanan ===\n";
        for (int i = 0; i < jumlahMakanan; i++) {
            cout << i + 1 << ". " << makanan[i] << " - Rp" << hargaMakanan[i] << endl;
        }
        cout << "\n=== Daftar Minuman ===\n";
        for (int i = 0; i < jumlahMinuman; i++) {
            cout << i + 1 + jumlahMakanan << ". " << minuman[i] << " - Rp" << hargaMinuman[i] << endl;
        }
    }

    void tampilkanDetailBarang(int nomor) {
        if (nomor >= 1 && nomor <= jumlahMakanan) {
            int index = nomor - 1;
            cout << "\nDetail Barang:\n";
            cout << "Nama     : " << makanan[index] << endl;
            cout << "Kategori : Makanan\n";
            cout << "Harga    : Rp" << hargaMakanan[index] << endl;
        } else if (nomor > jumlahMakanan && nomor <= jumlahMakanan + jumlahMinuman) {
            int index = nomor - jumlahMakanan - 1;
            cout << "\nDetail Barang:\n";
            cout << "Nama     : " << minuman[index] << endl;
            cout << "Kategori : Minuman\n";
            cout << "Harga    : Rp" << hargaMinuman[index] << endl;
        } else {
            cout << "Nomor tidak valid.\n";
        }
    }


    int getTotalBarang() {
        return jumlahMakanan + jumlahMinuman;
    }
};

class HistoryManager {
public:
    queue<string> historyHariIni[1000];
    stack<string> historyKeseluruhan[1000];
    int index = 0;

    void tambahRiwayat(const string& data) {
        if (index < 1000) {
            historyHariIni[index].push(data);
            historyKeseluruhan[index].push(data);
        }
    }

    void tampilkanRiwayatHariIni() {
        cout << "\n=== HISTORY PEMBELIAN HARI INI (QUEUE) ===\n";
        for (int i = 0; i <= index; i++) {
            queue<string> temp = historyHariIni[i];
            while (!temp.empty()) {
                cout << "- " << temp.front() << endl;
                temp.pop();
            }
        }
    }

    void tampilkanRiwayatKeseluruhan() {
        cout << "\n=== HISTORY KESELURUHAN (STACK) ===\n";
        for (int i = index; i >= 0; i--) {
            stack<string> temp = historyKeseluruhan[i];
            while (!temp.empty()) {
                cout << "- " << temp.top() << endl;
                temp.pop();
            }
        }
    }

    void simpanTransaksi(queue<string> transaksiQueue, stack<string> transaksiStack) {
        if (index < 1000) {
            while (!transaksiQueue.empty()) {
                historyHariIni[index].push(transaksiQueue.front());
                transaksiQueue.pop();
            }
            while (!transaksiStack.empty()) {
                historyKeseluruhan[index].push(transaksiStack.top());
                transaksiStack.pop();
            }
            index++;
        }
    }
};

bool isUsernameExist (const string& username){
    ifstream file ("userdata.txt");
    string fileUsername, filePassword;
    while (file >> fileUsername >> filePassword){
        if (fileUsername == username){
            return true;
        }
    }
        return false;
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
    cout << "Registrasi Berhasil!" << endl;

}

bool loginUser(string& loggedInUser) { //menambahkan fungsi loginUser
    string username, password ;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
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

void tampilkanHistoryFIFO(const string& username) { 
    string filename = username + ".txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Tidak ada file transaksi untuk user ini.\n";
        return;
    }

    string tanggal = getTodayDate();
    char lihatLain;

    do {
        file.clear();
        file.seekg(0, ios::beg);

        string line;
        bool tanggalDitemukan = false;
        bool bacaFIFO = false;

        while (getline(file, line)) {
            if (line == "=== Tanggal: " + tanggal + " ===") {
                tanggalDitemukan = true;
            } else if (tanggalDitemukan && line == "[FIFO]") {
                bacaFIFO = true;
                cout << "\n=== HISTORY PEMBELIAN FIFO: " << tanggal << " ===\n";
            } else if (bacaFIFO && line == "[LIFO]") {
                break;
            } else if (bacaFIFO) {
                cout << line << endl;
            }
        }

        if (!tanggalDitemukan) {
            cout << "\nTidak ada transaksi untuk tanggal " << tanggal << ".\n";
        }

        cout << "\nLihat tanggal lain? (y/n): ";
        cin >> lihatLain;
        if (lihatLain == 'y' || lihatLain == 'Y') {
            cout << "Masukkan tanggal (YYYY-MM-DD): ";
            cin >> tanggal;
        }
    } while (lihatLain == 'y' || lihatLain == 'Y');

    file.close();
}

void tampilkanHistoryLIFO(const string& username) {
    string filename = username + ".txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Tidak ada file transaksi untuk user ini.\n";
        return;
    }

    cout << "\n=== HISTORY KESELURUHAN (LIFO) DARI FILE ===\n";
    string line;
    string currentTanggal;
    bool bacaLIFO = false;
    vector<string> buffer;

    while (getline(file, line)) {
        if (line.find("=== Tanggal: ") != string::npos) {
            if (!currentTanggal.empty() && !buffer.empty()) {
                cout << "Tanggal: " << currentTanggal << endl;
                for (const auto& item : buffer) {
                    cout << item << endl;
                }
                cout << endl;
                buffer.clear();
            }
            currentTanggal = line.substr(13, 10);
        } else if (line == "[LIFO]") {
            bacaLIFO = true;
        } else if (line.empty() || line == "[LIFO]") {
            bacaLIFO = false;
        } else if (bacaLIFO) {
            buffer.push_back(line);
        }
    }

    if (!currentTanggal.empty() && !buffer.empty()) {
        cout << "Tanggal: " << currentTanggal << endl;
        for (const auto& item : buffer) {
            cout << item << endl;
        }
        cout << endl;
    }

    file.close();
}

void afterLoginMenu(const string& username) {
    int pilihan;
    bool stayLoggedIn = true;
    Barang daftarBarang;

    static map<string, queue<string>> historyHariIniMap;
    static map<string, stack<string>> historyKeseluruhanMap;


    while (stayLoggedIn) {
        cout << "\n=== MENU PENGGUNA (" << username << ") ===\n";
        cout << "1. Input barang\n";
        cout << "2. Kembali ke menu utama\n";
        cout << "3. Tampilkan history hari ini\n";
        cout << "4. Tampilkan history keseluruhan\n";
        cout << "Pilih opsi (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                stack<string> stackBarang;
                queue<string> queueBarang;
                int nomor;
                do {
                    daftarBarang.tampilkanDaftarBarang();
                    cout << "\nMasukkan nomor barang (0 untuk selesai): ";
                    cin >> nomor;

                    if (nomor == 0) break;

                    string nama, kategori;
                    double harga;

                    if (nomor >= 1 && nomor <= 6) {
                        string makananList[6] = {
                            "Oreo Neapolitan", "Hello Panda Strawberry",
                            "Samyang Buldak", "Taro Barbeque",
                            "Lays", "Sari Roti Tawar"
                        };
                        double hargaMakanan[6] = {13500, 9300, 19500, 9000, 13900, 18000};
                        nama = makananList[nomor - 1];
                        harga = hargaMakanan[nomor - 1];
                        kategori = "Makanan";
                    } else if (nomor >= 7 && nomor <= 10) {
                        string minumanList[4] = {
                            "Sprite Botol Sedang", "Coca-Cola Kaleng",
                            "AW Kaleng", "Air Mineral"
                        };
                        double hargaMinuman[4] = {5400, 6600, 6000, 3900};
                        nama = minumanList[nomor - 7];
                        harga = hargaMinuman[nomor - 7];
                        kategori = "Minuman";
                    } else {
                        cout << "Nomor tidak valid.\n";
                        continue;
                    }

                    string data = nama + " (" + kategori + ") - Rp" + to_string((int)harga);
                    stackBarang.push(data);
                    queueBarang.push(data);
                    cout << "Berhasil ditambahkan: " << data << "\n";

                } while (true);

                string today = getTodayDate();

                stack<string> stackCopy = stackBarang;
                queue<string> queueCopy = queueBarang;

                while (!stackBarang.empty()) {
                    string data = stackBarang.top(); stackBarang.pop();
                    historyKeseluruhanMap[today].push(data);
                }
                while (!queueBarang.empty()) {
                    string data = queueBarang.front(); queueBarang.pop();
                    historyHariIniMap[today].push(data);
                }

                simpanTransaksiKeFile(username, today, queueCopy, stackCopy);

                cout << "\nTransaksi hari ini telah disimpan.\n";

                break;
            }

            case 2:
                stayLoggedIn = false;
                cout << "Kembali ke menu utama." << endl;
                break;

            case 3: {
                tampilkanHistoryFIFO(username);
                break;
            }

            case 4: {
                tampilkanHistoryLIFO(username);
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

int main(){
    int pilihan;
    bool isRunning = true;

    while(isRunning){
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Daftar\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih opsi (1-3): ";
        cin >> pilihan;

        switch (pilihan){
        case 1: 
            registerUser();
            break;
        case 2: {
            string currentUser;
            if (loginUser(currentUser)) {
                afterLoginMenu(currentUser);
            } break;
        }
        case 3:
            cout << "Program selesai. Terima kasih.\n";
                isRunning = false;
                break;
    
        default:
        cout<< "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
