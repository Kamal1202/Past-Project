#include <iostream>
#include <string>

using namespace std;

// Struktur untuk menyimpan informasi buku
struct Book {
    int bookNumber; // Nomor buku
    string title;
    string author;
    int year;
    bool isAvailable;
    Book* next; // Pointer untuk membuat linked list
};

// Kelas untuk mengelola perpustakaan
class Library {
private:
    Book* head; // Pointer ke kepala linked list buku
    int nextBookNumber; // Nomor untuk buku selanjutnya
    int bookNumbers[100]; // Array untuk menyimpan nomor buku

public:
    Library() {
        head = nullptr;
        nextBookNumber = 1; // Dimulai dari nomor 1
        for (int i = 0; i < 100; ++i) {
            bookNumbers[i] = 0; // Inisialisasi array nomor buku
        }
    }

    // Fungsi untuk mencari indeks pertama yang tersedia dalam array nomor buku
    int findEmptyIndex() {
        for (int i = 0; i < 100; ++i) {
            if (bookNumbers[i] == 0) {
                return i;
            }
        }
        return -1; // Jika tidak ada indeks kosong yang tersedia
    }

    // Fungsi untuk menambahkan buku ke dalam perpustakaan
    void addBook(string title, string author, int year) {
        int choiceFunct;
        int index = findEmptyIndex();
        if (index != -1) {
            Book* newBook = new Book;
            newBook->bookNumber = nextBookNumber++;
            newBook->title = title;
            newBook->author = author;
            newBook->year = year;
            newBook->isAvailable = true;
            newBook->next = nullptr;

            if (head == nullptr) {
                head = newBook;
            } else {
                Book* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newBook;
            }
            bookNumbers[index] = newBook->bookNumber;
            cout << "Buku berhasil ditambahkan. Nomor buku: " << newBook->bookNumber << "\n\n";            
        } else {
            cout << "Perpustakaan penuh, tidak bisa menambahkan buku baru.\n";
        }
    }

    // Fungsi untuk menampilkan daftar buku dalam perpustakaan
    void displayBooks() {
        Book* temp = head;

        system("cls");
        cout << "Daftar Buku:\n\n";
        while (temp != nullptr) {
            cout << "Nomor Buku: " << temp->bookNumber << endl;
            cout << "Judul: " << temp->title << endl;
            cout << "Penulis: " << temp->author << endl;
            cout << "Tahun Terbit: " << temp->year << endl;
            cout << "Status: " << (temp->isAvailable ? "Tersedia" : "Tidak Tersedia") << endl;
            cout << "--------------------------\n";
            temp = temp->next;
        }
    }

    // Fungsi untuk mengedit informasi buku berdasarkan nomor buku
    void editBook(int bookNumber, string title, string author, int year) {
        Book* temp = head;
        while (temp != nullptr) {
            if (temp->bookNumber == bookNumber) {
                temp->title = title;
                temp->author = author;
                temp->year = year;
                cout << "Informasi buku berhasil diperbarui.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Buku dengan nomor " << bookNumber << " tidak ditemukan.\n";
    }

    // Fungsi untuk menghapus buku berdasarkan nomor buku
    void deleteBook(int bookNumber) {
        if (head == nullptr) {
            cout << "Perpustakaan kosong.\n";
            return;
        }

        Book* temp = head;
        Book* prev = nullptr;

        // Temukan buku yang akan dihapus
        while (temp != nullptr && temp->bookNumber != bookNumber) {
            prev = temp;
            temp = temp->next;
        }

        // Jika buku ditemukan, hapus buku
        if (temp != nullptr) {
            if (prev != nullptr) {
                prev->next = temp->next;
            } else {
                head = temp->next;
            }
            delete temp;
            cout << "Buku berhasil dihapus.\n";

            // Kosongkan nomor buku dari array
            for (int i = 0; i < 100; ++i) {
                if (bookNumbers[i] == bookNumber) {
                    bookNumbers[i] = 0;
                    break;
                }
            }
        } else {
            cout << "Buku dengan nomor " << bookNumber << " tidak ditemukan.\n";
        }
    }

    // Fungsi untuk meminjam buku berdasarkan nomor buku
    void borrowBook(int bookNumber) {
        Book* temp = head;
        while (temp != nullptr) {
            if (temp->bookNumber == bookNumber) {
                            if (temp->isAvailable) {
                    temp->isAvailable = false;
                    cout << "Buku berhasil dipinjam.\n";
                } else {
                    cout << "Buku sudah dipinjam, silahkan cari buku lain.\n";
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Buku dengan nomor " << bookNumber << " tidak ditemukan.\n";
    }

    // Fungsi untuk mengembalikan buku berdasarkan nomor buku
    void returnBook(int bookNumber) {
        Book* temp = head;
        while (temp != nullptr) {
            if (temp->bookNumber == bookNumber) {
                if (!temp->isAvailable) {
                    temp->isAvailable = true;
                    cout << "Buku berhasil dikembalikan.\n";
                } else {
                    cout << "Buku sudah tersedia.\n";
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Buku dengan nomor " << bookNumber << " tidak ditemukan.\n";
    }

    // Destruktor untuk menghapus semua buku saat objek Library dihapus
    ~Library() {
        Book* temp = head;
        while (temp != nullptr) {
            Book* nextBook = temp->next;
            delete temp;
            temp = nextBook;
        }
    }
};

int main() {
    Library library;

    system ("cls");

    // Menu utama
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Daftar Buku\n";
        cout << "3. Edit Informasi Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Pinjam Buku\n";
        cout << "6. Kembalikan Buku\n";
        cout << "7. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system("cls");
                string title, author;
                int year;

                cout << "Input data Buku \n\n";
                cout << "Judul: ";
                cin.ignore();
                getline(cin, title);
                cout << "Penulis: ";
                getline(cin, author);
                cout << "Tahun Terbit: ";
                cin >> year;

                library.addBook(title, author, year);
                break;
            }
            case 2:
                library.displayBooks();
                break;
            case 3: {
                int bookNumber;
                string title, author;
                int year;
                system("cls");

                cout << "Edit Buku \n\n";

                cout << "Masukkan nomor buku yang ingin diedit: ";
                cin >> bookNumber;
                cout << "Judul: ";
                cin.ignore();
                getline(cin, title);
                cout << "Penulis: ";
                getline(cin, author);
                cout << "Tahun Terbit: ";
                cin >> year;

                library.editBook(bookNumber, title, author, year);
                break;
            }
            case 4: {
                int bookNumber;

                system("cls");

                cout << "Masukkan nomor buku yang ingin dihapus: ";
                cin >> bookNumber;
                library.deleteBook(bookNumber);
                break;
            }
            case 5: {
                int bookNumber;

                system("cls");

                cout << "Pinjam Buku \n\n";
                cout << "Masukkan nomor buku yang ingin dipinjam: ";
                cin >> bookNumber;
                library.borrowBook(bookNumber);
                break;
            }
            case 6: {
                int bookNumber;
                
                system("cls");

                cout << "Kembalikan Buku \n\n";
                cout << "Masukkan nomor buku yang ingin dikembalikan: ";
                cin >> bookNumber;
                library.returnBook(bookNumber);
                break;
            }
            case 7:
                cout << "Program berakhir.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 7);

    return 0;
}
   
