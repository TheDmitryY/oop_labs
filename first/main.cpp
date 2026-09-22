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

void writeBest(const char* filename, Student best[], int ccount) {
    ofstream f(filename);

    f << "5 найкращих студентів:\n";

    int limit;
    if (ccount < 5) {
        limit = ccount;
    } else {
        limit = 5;
    }

    for (int i = 0; i < limit; i++) {
        f << (i + 1) << ". " << best[i].name 
          << "   Курс: " << best[i].course 
          << "   Група: " << best[i].group << "   Оцінки: ";
        
        for (int j = 0; j < 4; j++) {
            f << best[i].grades[j] << " ";
        }
        f << "\n";
    }

    f.close();
    cout << "\nТОП-5 студентів успішно записано у файл " << filename << "!\n";
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
    const int N = 15;
    Student group[N] = {
        {"Коваль О.", 2, "КІ-25-1", {85, 90, 75, 88}},
        {"Мельник С.", 2, "КІ-25-1", {95, 92, 89, 98}},
        {"Ловчук Д.", 2, "KI-25-2", {99, 100, 100,100}},
        {"Мельник Н.", 2, "KI-25-2", {100, 100, 100, 100}},
        {"Шевченко Т.", 2, "КІ-25-1", {60, 74, 68, 70}},
        {"Шевченко А.", 2, "КІ-25-1", {60, 74, 68, 70}},
        {"Шевченко Н.", 2, "КІ-25-1", {91, 90, 75, 87}},

    };

    RW("info.dat", group, N);

    Student loaded[10];
    int count = 0;
    RD("info.dat", loaded, count);
    int ccount = 5;
    double avg[4] = {0};
    for (int j = 0; j < 4; j++) {
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += loaded[i].grades[j];
        }
        avg[j] = sum / count;
    }

    Student best[100];
    for (int i = 0; i < ccount; i++) {
        best[i] = loaded[i];
    }

    for (int i = 0; i < ccount - 1; i++) {
        for (int j = 0; j < ccount - i - 1; j++) {
            
            double sumA = 0;
            for (int k = 0; k < 4; k++) sumA += best[j].grades[k];
            
            double sumB = 0;
            for (int k = 0; k < 4; k++) sumB += best[j + 1].grades[k];
            
            if (sumB > sumA) {
                Student temp = best[j];
                best[j] = best[j + 1];
                best[j + 1] = temp;
            }
        }
    }

    cout << "\n5 найкращих студентів:\n";

    int limit;
    if (ccount < 5) {
        limit = ccount;
    } else {
        limit = 5;
    }

    for (int j = 0; j < limit; j++) {
        cout << j + 1 << ". " << best[j].name << " | Оцінки: ";
        
        for (int k = 0; k < 4; k++) {
            cout << best[j].grades[k] << " ";
        }
        cout << "\n";
    }

    cout << "\nСередній бал за кожним іспитом:\n";
    for (int j = 0; j < 4; j++) {
        cout << "Предмет " << (j + 1) << ": " << avg[j] << "\n";
    }
    // write info.txt
    RW("info.txt", loaded, count, avg);
    writeBest("best.txt", best, ccount);
    //read info.txt
    RD("info.txt");

    return 0;
}