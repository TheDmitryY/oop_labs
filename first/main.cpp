#include <iostream>
#include <fstream>

using namespace std;

class Student {
    public:
        char name[40];
        int course;
        char group[10];
        int grades[4];
};
// write to info.dat
void RW(const char* filename, Student arr[], int n) {
    ofstream f(filename, ios::binary);
    f.write((char*)&n, sizeof(n));
    f.write((char*)arr, sizeof(Student) * n);
    f.close();
}

// write to info.txt
void RW(const char* filename, Student arr[], int n, double avg[]) {
    ofstream f(filename);

    f << "Список студентів:\n";
    for (int i = 0; i < n; i++) {
        f << arr[i].name << "   Курс: " << arr[i].course 
          << "   Група: " << arr[i].group << "   Оцінки: ";
        for (int j = 0; j < 4; j++) {
            f << arr[i].grades[j] << " ";
        }
        f << "\n";
    }

    f << "\nСередній бал за іспитами:\n";
    for (int j = 0; j < 4; j++) {
        f << "Іспит " << (j + 1) << ": " << avg[j] << "\n";
    }
    f.close();
}

// output info.dat
void RD(const char* filename, Student arr[], int &n) {
    ifstream f(filename, ios::binary);
    
    f.read((char*)&n, sizeof(n));
    f.read((char*)arr, sizeof(Student) * n);
    f.close();

    cout << "Дані з бінарного файлу (" << filename << ")   \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].name << ", Курс: " << arr[i].course 
             << ", Група: " << arr[i].group << ", Оцінки: ";
        for (int j = 0; j < 4; j++) {
            cout << arr[i].grades[j] << " ";
        }
        cout << "\n";
    }
}

// output info.txt
void RD(const char* filename) {
    ifstream f(filename);
    

    cout << "\n   Вміст текстового файлу (" << filename << ")   \n";
    char line[256];
    while (f.getline(line, sizeof(line))) {
        cout << line << "\n";
    }
    f.close();
}

int main() {
    const int N = 3;
    Student group[N] = {
        {"Коваль О.", 2, "КІ-23", {85, 90, 75, 88}},
        {"Мельник С.", 2, "КІ-23", {95, 92, 89, 98}},
        {"Шевченко Т.", 2, "КІ-23", {60, 74, 68, 70}}
    };

    RW("info.dat", group, N);

    Student loaded[10];
    int count = 0;
    RD("info.dat", loaded, count);

    double avg[4] = {0};
    for (int j = 0; j < 4; j++) {
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += loaded[i].grades[j];
        }
        avg[j] = sum / count;
    }

    cout << "\nСередній бал за кожним іспитом:\n";
    for (int j = 0; j < 4; j++) {
        cout << "Предмет " << (j + 1) << ": " << avg[j] << "\n";
    }

    // write info.txt
    RW("info.txt", loaded, count, avg);

    //read info.txt
    RD("info.txt");

    return 0;
}