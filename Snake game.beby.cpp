#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

// --- Pengaturan Game ---
const int width = 20;
const int height = 20;
int x, y; // Posisi Kepala Ular
int fruitX, fruitY; // Posisi Makanan
int score;
int tailX[100], tailY[100]; // Koordinat Ekor
int nTail; // Panjang Ekor
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool gameOver;

// --- Fungsi Inisialisasi Game ---
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    // Menghasilkan posisi makanan secara acak
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

// --- Fungsi Menggambar Peta dan Ular ---
void Draw() {
    // Membersihkan layar
    system("cls");

    // Menggambar Batas Atas
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Menggambar Peta dan Isinya
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (j == 0 || j == width + 1) {
                // Menggambar Batas Samping
                cout << "#";
            } else if (i == y && j == x + 1) {
                // Menggambar Kepala Ular
                cout << "O";
            } else if (i == fruitY && j == fruitX + 1) {
                // Menggambar Makanan
                cout << "F";
            } else {
                bool printTail = false;
                // Menggambar Ekor
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j - 1 && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    // Menggambar Batas Bawah
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Menampilkan Skor
    cout << "Skor: " << score << endl;
}

// --- Fungsi Mengambil Input Pemain ---
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

// --- Fungsi Logika Game ---
void Logic() {
    // Pergerakan Ekor
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Pergerakan Kepala
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    // Logika Batas (Permainan Selesai jika menabrak batas)
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
    }
    
    // Logika Menabrak Diri Sendiri
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Logika Makan Buah
    if (x == fruitX && y == fruitY) {
        score += 10;
        // Menambah panjang ekor
        nTail++;
        // Menghasilkan posisi buah baru
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

// --- Fungsi Utama ---
int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        // Kecepatan game (dalam milidetik)
        Sleep(50); 
    }

    cout << endl << "GAME OVER!" << endl;
    cout << "Skor Akhir Anda: " << score << endl;

    return 0;
}