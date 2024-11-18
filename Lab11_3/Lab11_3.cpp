#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

struct Enterprise {
    string mobilePhone;
    int numBuilding;
    string employees[4];
    int employeeCount = 0;
};

void Create(Enterprise* p, const int N);
void Print(Enterprise* p, const int N);
void AddRecord(Enterprise*& p, int& N);
void EditRecord(Enterprise* p, const int N);
void DeleteRecord(Enterprise* p, int& N);
void FindByPhone(Enterprise* p, const int N);
void FindByBuilding(Enterprise* p, const int N);
void FindBySurname(Enterprise* p, const int N);
void SaveToFile(Enterprise* p, const int N, const char* filename);
void LoadFromFile(Enterprise*& p, int& N, const char* filename);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість записів N: "; cin >> N;

    Enterprise* p = new Enterprise[N];
    int menuItem;
    do {
        cout << endl << "Виберіть дію:" << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - додати запис" << endl;
        cout << " [4] - редагувати запис" << endl;
        cout << " [5] - видалити запис" << endl;
        cout << " [6] - пошук за номером телефону" << endl;
        cout << " [7] - пошук за номером приміщення" << endl;
        cout << " [8] - пошук за прізвищем службовця" << endl;
        cout << " [9] - зберегти дані у файл" << endl;
        cout << " [10] - завантажити дані з файлу" << endl << endl;
        cout << " [0] - вихід" << endl;
        cout << "Введіть значення: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            AddRecord(p, N);
            break;
        case 4:
            EditRecord(p, N);
            break;
        case 5:
            DeleteRecord(p, N);
            break;
        case 6:
            FindByPhone(p, N);
            break;
        case 7:
            FindByBuilding(p, N);
            break;
        case 8:
            FindBySurname(p, N);
            break;
        case 9:
            SaveToFile(p, N, "enterprise_data.dat");
            cout << "Дані збережено у файл 'enterprise_data.dat'" << endl;
            break;
        case 10:
            LoadFromFile(p, N, "enterprise_data.dat");
            cout << "Дані завантажено з файлу 'enterprise_data.dat'" << endl;
            break;
        case 0:
            break;
        default: cout << "Невірний вибір!" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Enterprise* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Приміщення № " << i + 1 << ":" << endl;
        cout << " Номер телефону: "; cin >> p[i].mobilePhone;
        cout << " Номер приміщення: "; cin >> p[i].numBuilding;
        cout << " Введіть кількість службовців (до 4): "; cin >> p[i].employeeCount;

        for (int j = 0; j < p[i].employeeCount; j++) {
            cout << "  Службовець № " << j + 1 << ": ";
            cin >> ws; // очистити буфер
            getline(cin, p[i].employees[j]);
        }
    }
}

void Print(Enterprise* p, const int N) {
    cout << "=========================================================================" << endl;
    cout << "| №  | Телефон | Номер приміщення | Службовці                           |" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1
            << " | " << setw(8) << p[i].mobilePhone
            << " | " << setw(16) << p[i].numBuilding
            << setw(37) << " | ";
        for (int j = 0; j < p[i].employeeCount; j++) {
            cout << p[i].employees[j];
            if (j < p[i].employeeCount - 1) cout << ", ";
        }
        cout << " | " << endl;
    }
    cout << "=========================================================================" << endl;
}

void AddRecord(Enterprise*& p, int& N) {
    Enterprise* temp = new Enterprise[N + 1]; // створюємо новий масив більшого розміру
    for (int i = 0; i < N; i++) {
        temp[i] = p[i]; // копіюємо старі записи
    }
    delete[] p; // видаляємо старий масив
    p = temp; // переназначаємо вказівник

    // Заповнення нового запису
    cout << "Додавання нового запису:" << endl;

    cout << " Номер телефону: ";
    cin >> ws; // очищаємо буфер
    getline(cin, p[N].mobilePhone);

    cout << " Номер приміщення: ";
    cin >> p[N].numBuilding;

    cout << " Введіть кількість службовців (до 4): ";
    cin >> p[N].employeeCount;
    while (p[N].employeeCount < 1 || p[N].employeeCount > 4) {
        cout << " Кількість службовців має бути від 1 до 4. Повторіть введення: ";
        cin >> p[N].employeeCount;
    }

    for (int j = 0; j < p[N].employeeCount; j++) {
        cout << "  Службовець № " << j + 1 << ": ";
        cin >> ws; // очищаємо буфер
        getline(cin, p[N].employees[j]);
    }

    N++; // збільшуємо розмір масиву
}


void EditRecord(Enterprise* p, const int N) {
    int index;
    cout << "Введіть номер запису для редагування (1 - " << N << "): ";
    cin >> index;

    if (index < 1 || index > N) { // Перевірка коректності індексу
        cout << "Невірний індекс!" << endl;
        return;
    }

    index--; // Перетворення на 0-індексацію

    cout << "Редагування запису № " << index + 1 << ":" << endl;

    cout << "Новий номер телефону: ";
    cin >> ws;
    getline(cin, p[index].mobilePhone);

    cout << "Новий номер приміщення: ";
    cin >> p[index].numBuilding;

    cout << "Введіть кількість службовців (до 4): ";
    cin >> p[index].employeeCount;
    while (p[index].employeeCount < 1 || p[index].employeeCount > 4) {
        cout << " Кількість службовців має бути від 1 до 4. Повторіть введення: ";
        cin >> p[index].employeeCount;
    }

    for (int j = 0; j < p[index].employeeCount; j++) {
        cout << "  Службовець № " << j + 1 << ": ";
        cin >> ws;
        getline(cin, p[index].employees[j]);
    }

    cout << "Запис успішно оновлено!" << endl;
}



void DeleteRecord(Enterprise* p, int& N) {
    int index;
    cout << "Введіть номер запису для видалення (1 - " << N << "): ";
    cin >> index;
    index--;
    if (index < 0 || index >= N) {
        cout << "Невірний індекс!" << endl;
        return;
    }

    for (int i = index; i < N - 1; i++) {
        p[i] = p[i + 1];
    }
    N--;
    cout << "Запис видалено." << endl;
}

void FindByPhone(Enterprise* p, const int N) {
    string phone;
    cout << "Введіть номер телефону: ";
    cin >> phone;
    for (int i = 0; i < N; i++) {
        if (p[i].mobilePhone == phone) {
            cout << "Номер приміщення: " << p[i].numBuilding << endl;
            cout << "Список службовців: ";
            for (int j = 0; j < p[i].employeeCount; j++) {
                cout << p[i].employees[j] << (j < p[i].employeeCount - 1 ? ", " : "");
            }
            cout << endl;
            return;
        }
    }
    cout << "Номер телефону не знайдено!" << endl;
}

void FindByBuilding(Enterprise* p, const int N) {
    int building;
    cout << "Введіть номер приміщення: ";
    cin >> building;
    for (int i = 0; i < N; i++) {
        if (p[i].numBuilding == building) {
            cout << "Номер телефону: " << p[i].mobilePhone << endl;
            return;
        }
    }
    cout << "Номер приміщення не знайдено!" << endl;
}

void FindBySurname(Enterprise* p, const int N) {
    string surname;
    cout << "Введіть прізвище службовця: ";
    cin >> ws;
    getline(cin, surname);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < p[i].employeeCount; j++) {
            if (p[i].employees[j] == surname) {
                cout << "Номер телефону: " << p[i].mobilePhone << ", Номер приміщення: " << p[i].numBuilding << endl;
                return;
            }
        }
    }
    cout << "Службовця не знайдено!" << endl;
}
void SaveToFile(Enterprise* p, const int N, const char* filename) {
    ofstream fout(filename); // відкриваємо файл у текстовому режимі
    if (!fout.is_open()) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    fout << N << endl; // записуємо кількість записів

    for (int i = 0; i < N; i++) {
        fout << p[i].mobilePhone << endl;       // номер телефону
        fout << p[i].numBuilding << endl;       // номер приміщення
        fout << p[i].employeeCount << endl;     // кількість службовців

        for (int j = 0; j < p[i].employeeCount; j++) {
            fout << p[i].employees[j] << endl; // список службовців
        }
    }

    fout.close(); // закриваємо файл
    cout << "Дані успішно збережено у файл '" << filename << "'" << endl;
}

void LoadFromFile(Enterprise*& p, int& N, const char* filename) {
    ifstream fin(filename); // відкриваємо файл у текстовому режимі
    if (!fin.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    fin >> N; // читаємо кількість записів
    fin.ignore(); // очищаємо залишки символів у потоці

    delete[] p; // очищаємо старі дані
    p = new Enterprise[N]; // виділяємо новий масив

    for (int i = 0; i < N; i++) {
        getline(fin, p[i].mobilePhone);     // читаємо номер телефону
        fin >> p[i].numBuilding;            // читаємо номер приміщення
        fin >> p[i].employeeCount;          // читаємо кількість службовців
        fin.ignore(); // очищаємо залишки символів у потоці

        for (int j = 0; j < p[i].employeeCount; j++) {
            getline(fin, p[i].employees[j]); // читаємо імена службовців
        }
    }

    fin.close(); // закриваємо файл
    cout << "Дані успішно завантажено з файлу '" << filename << "'" << endl;
}

