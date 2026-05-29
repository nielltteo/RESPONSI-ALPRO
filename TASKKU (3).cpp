#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Tugas {
public:
    string namaTugas;
    string mataKuliah;
    string deadline;
    bool selesai;

    Tugas() {
        selesai = false;
    }
};

class Taskku {
private:
    static const int MAX_TUGAS = 100;
    Tugas daftarTugas[MAX_TUGAS];
    int jumlahTugas;

public:
    Taskku() {
        jumlahTugas = 0;
    }

 
    bool login() {
        string nama, nim;

        cout << "=================================\n";
        cout << "         LOGIN TASKKU\n";
        cout << "=================================\n";

        cout << "Masukkan Nama : ";
        getline(cin, nama);

        cout << "Masukkan NIM  : ";
        getline(cin, nim);

        if (nama.empty() || nim.empty()) {
            cout << "\nLogin gagal!\n";
            return false;
        }

        cout << "\nLogin berhasil. Selamat datang, "
             << nama << "!\n";

        return true;
    }


    void tambahTugas() {

        if (jumlahTugas >= MAX_TUGAS) {
            cout << "Kapasitas tugas penuh!\n";
            return;
        }

        cout << "\n===== TAMBAH TUGAS =====\n";

        cin.ignore();

        cout << "Nama Tugas   : ";
        getline(cin, daftarTugas[jumlahTugas].namaTugas);

        cout << "Mata Kuliah  : ";
        getline(cin, daftarTugas[jumlahTugas].mataKuliah);

        cout << "Deadline     : ";
        getline(cin, daftarTugas[jumlahTugas].deadline);

        daftarTugas[jumlahTugas].selesai = false;

        jumlahTugas++;

        cout << "\nTugas berhasil ditambahkan!\n";
    }


    void lihatTugasAktif() {

        cout << "\n===== DAFTAR TUGAS AKTIF =====\n";

        bool ada = false;

        for (int i = 0; i < jumlahTugas; i++) {

            if (!daftarTugas[i].selesai) {

                ada = true;

                cout << "\nNomor        : " << i + 1;
                cout << "\nNama Tugas   : " << daftarTugas[i].namaTugas;
                cout << "\nMata Kuliah  : " << daftarTugas[i].mataKuliah;
                cout << "\nDeadline     : " << daftarTugas[i].deadline;
                cout << "\n----------------------------\n";
            }
        }

        if (!ada) {
            cout << "Tidak ada tugas aktif.\n";
        }
    }


    void tandaiSelesai() {

        lihatTugasAktif();

        int nomor;

        cout << "\nMasukkan nomor tugas yang selesai : ";
        cin >> nomor;

        if (nomor >= 1 && nomor <= jumlahTugas) {

            daftarTugas[nomor - 1].selesai = true;

            cout << "Tugas berhasil ditandai selesai.\n";
        }
        else {

            cout << "Nomor tidak valid!\n";
        }
    }


    void lihatRiwayat() {

        cout << "\n===== RIWAYAT TUGAS SELESAI =====\n";

        bool ada = false;

        for (int i = 0; i < jumlahTugas; i++) {

            if (daftarTugas[i].selesai) {

                ada = true;

                cout << "\nNomor        : " << i + 1;
                cout << "\nNama Tugas   : " << daftarTugas[i].namaTugas;
                cout << "\nMata Kuliah  : " << daftarTugas[i].mataKuliah;
                cout << "\nDeadline     : " << daftarTugas[i].deadline;
                cout << "\nStatus       : SELESAI";
                cout << "\n----------------------------\n";
            }
        }

        if (!ada) {
            cout << "Belum ada tugas selesai.\n";
        }
    }


    void hapusTugas() {

        if (jumlahTugas == 0) {
            cout << "Belum ada tugas.\n";
            return;
        }

        cout << "\n===== HAPUS TUGAS =====\n";

        for (int i = 0; i < jumlahTugas; i++) {
            cout << i + 1 << ". "
                 << daftarTugas[i].namaTugas
                 << endl;
        }

        int nomor;

        cout << "\nMasukkan nomor tugas yang ingin dihapus : ";
        cin >> nomor;

        if (nomor >= 1 && nomor <= jumlahTugas) {

            for (int i = nomor - 1; i < jumlahTugas - 1; i++) {
                daftarTugas[i] = daftarTugas[i + 1];
            }

            jumlahTugas--;

            cout << "Tugas berhasil dihapus.\n";
        }
        else {

            cout << "Nomor tidak valid!\n";
        }
    }

    
    int hitungTugasAktifRekursif(int index) {

        if (index >= jumlahTugas) {
            return 0;
        }

        if (!daftarTugas[index].selesai) {
            return 1 + hitungTugasAktifRekursif(index + 1);
        }

        return hitungTugasAktifRekursif(index + 1);
    }

 
    void tampilTugasRekursif(int index) {

        if (index >= jumlahTugas) {
            return;
        }

        cout << "\nTugas Ke-" << index + 1 << endl;
        cout << "Nama Tugas  : "
             << daftarTugas[index].namaTugas << endl;

        cout << "Mata Kuliah : "
             << daftarTugas[index].mataKuliah << endl;

        cout << "Deadline    : "
             << daftarTugas[index].deadline << endl;

        cout << "Status      : "
             << (daftarTugas[index].selesai ?
                "SELESAI" : "AKTIF")
             << endl;

        cout << "----------------------------\n";

        tampilTugasRekursif(index + 1);
    }


    void simpanFile() {

        ofstream file("arsip_taskku.txt");

        if (!file.is_open()) {

            cout << "Gagal membuka file!\n";
            return;
        }

        file << "========== ARSIP TASKKU ==========\n\n";

        for (int i = 0; i < jumlahTugas; i++) {

            file << "Tugas Ke     : "
                 << i + 1 << endl;

            file << "Nama Tugas   : "
                 << daftarTugas[i].namaTugas << endl;

            file << "Mata Kuliah  : "
                 << daftarTugas[i].mataKuliah << endl;

            file << "Deadline     : "
                 << daftarTugas[i].deadline << endl;

            file << "Status       : "
                 << (daftarTugas[i].selesai ?
                     "SELESAI" : "AKTIF")
                 << endl;

            file << "--------------------------------\n";
        }

        file.close();

        cout << "\nData berhasil disimpan ke file "
             << "arsip_taskku.txt\n";
    }

    void menu() {

        int pilihan;

        do {

            cout << "\n=================================\n";
            cout << "             TASKKU\n";
            cout << "=================================\n";
            cout << "1. Tambah Tugas\n";
            cout << "2. Lihat Tugas Aktif\n";
            cout << "3. Tandai Tugas Selesai\n";
            cout << "4. Riwayat Tugas Selesai\n";
            cout << "5. Hapus Tugas\n";
            cout << "6. Simpan File TXT\n";
            cout << "7. Hitung Tugas Aktif (Rekursif)\n";
            cout << "8. Tampilkan Semua Tugas (Rekursif)\n";
            cout << "0. Keluar\n";
            cout << "Pilih Menu : ";
            cin >> pilihan;

            switch (pilihan) {

                case 1:
                    tambahTugas();
                    break;

                case 2:
                    lihatTugasAktif();
                    break;

                case 3:
                    tandaiSelesai();
                    break;

                case 4:
                    lihatRiwayat();
                    break;

                case 5:
                    hapusTugas();
                    break;

                case 6:
                    simpanFile();
                    break;

                case 7:
                    cout << "\nJumlah tugas aktif : "
                         << hitungTugasAktifRekursif(0)
                         << endl;
                    break;

                case 8:
                    cout << "\n===== DAFTAR SEMUA TUGAS =====\n";
                    tampilTugasRekursif(0);
                    break;

                case 0:
                    cout << "\nTerima kasih telah menggunakan TASKKU.\n";
                    break;

                default:
                    cout << "\nMenu tidak tersedia!\n";
            }

        } while (pilihan != 0);
    }
};

int main() {

    Taskku app;

    if (app.login()) {
        app.menu();
    }

    return 0;
}
