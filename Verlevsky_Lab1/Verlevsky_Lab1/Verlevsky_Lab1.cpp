#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
    string name;
    int length;
    int diameter;
    bool repair_status;
    Pipe() : name(""), length(0), diameter(0), repair_status(false) {}
};

struct CS {
    string name;
    int quantity_workshop;
    int workshops_in_work;
    double efficiency;

    CS() : name(""), quantity_workshop(0), workshops_in_work(0), efficiency(0.0) {}
};

bool ValidString(const string& input) {
    for (char el : input) {
        if (!isalpha(el) && !isspace(el)) {
            return false;
        }
        if (input.size() == 1) {
            if (isspace(el)) {
                return false;
            }

        }
    }
    return true;
}

Pipe PIPE_add() {
    Pipe new_pipe;
    cout << "Введите название трубы:" << endl;
    getline(cin, new_pipe.name);
    while (!ValidString(new_pipe.name)){
        cout << "Введите одну строку" << endl;
        getline(cin, new_pipe.name);
    }
    cout << "Введите длину трубы:" << endl;
    while (true) {
        cin >> new_pipe.length;
        if (cin.fail() || new_pipe.length <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите положительное число:" << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    cout << "Введите диаметр трубы:" << endl;
    while (true) {
        cin >> new_pipe.diameter;
        if (cin.fail() || new_pipe.diameter <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите положительное число:" << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    cout << "Введите статус трубы (0-исправна, 1-в ремонте)" << endl;
    while (true) {
        cin >> new_pipe.repair_status;
        if (cin.fail() || (new_pipe.repair_status != 0 && new_pipe.repair_status != 1)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите 0 или 1:" << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    return new_pipe;
}

CS CS_add() {
    CS new_cs;
    cout << "Введите название КС:" << endl;
    getline(cin, new_cs.name);
    while (!ValidString(new_cs.name)) {
        cout << "Введите одну строку" << endl;
        getline(cin, new_cs.name);
    }
    cout << "Введите количество цехов:" << endl;
    while (true) {
        cin >> new_cs.quantity_workshop;
        if (cin.fail() || new_cs.quantity_workshop <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите положительное число:" << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    cout << "Введите количество цехов в работе:" << endl;
    while (true) {
        cin >> new_cs.workshops_in_work;
        if (cin.fail() || new_cs.workshops_in_work < 0 || new_cs.workshops_in_work > new_cs.quantity_workshop) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите число от 0 до " << new_cs.quantity_workshop << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    };
    cout << "Введите эффективность" << endl;
    while (true) {
        cin >> new_cs.efficiency;
        if (cin.fail() || new_cs.efficiency <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите положительное число:" << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }
    return new_cs;
}

void Show_subjects(const Pipe& pipe, const CS& cs) {
    cout << "Труба:" << endl;
    if (pipe.name != "") {
        cout << "Название: " << pipe.name << ", Длина: " << pipe.length
            << ", Диаметр: " << pipe.diameter << ", Статус: "
            << (pipe.repair_status ? "В ремонте" : "Исправна") << endl;
    }
    else {
        cout << "Данных о трубе нет." << endl;
    }
    cout << "КС:" << endl;
    if (cs.name != "") {
        cout << "Название: " << cs.name << ", Цехов: " << cs.quantity_workshop << ", Цехов в работе: " << cs.workshops_in_work
            << ", Эффективность: " << cs.efficiency << endl;
    }
    else {
        cout << "Данных о КС нет." << endl;
    }
}

void Main_menu() {
    cout << "Выберите действие:\n"
        << "1. Добавить трубу\n"
        << "2. Добавить КС\n"
        << "3. Просмотреть объекты\n"
        << "4. Изменить статус трубы\n"
        << "5. Изменить цехи КС\n"
        << "6. Сохранить\n"
        << "7. Загрузить\n"
        << "0. Выход" << endl;
}

void Change_status_Pipe(Pipe& pipe) {
    if (pipe.name == "") {
        cout << "Труба не добавлена." << endl;
        return;
    }
    pipe.repair_status = !pipe.repair_status;
    cout << "Статус трубы изменен на " << (pipe.repair_status ? "в ремонте" : "исправна") << endl;
}

void Change_status_CS(CS& cs) {
    if (cs.name == "") {
        cout << "КС не добавлена." << endl;
        return;
    }
    int new_workshops_in_work;
    cout << "Введите новое число цехов в работе:" << endl;
    while (true) {
        cin >> new_workshops_in_work;
        if (cin.fail() || new_workshops_in_work < 0 || new_workshops_in_work > cs.quantity_workshop) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите число от 0 до " << cs.quantity_workshop << endl;
        }
        else if (cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введите корректное число:" << endl;
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }
    cs.workshops_in_work = new_workshops_in_work;
    cout << "Изменения успешно внесены." << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    Pipe pipe;
    CS cs;
    int choice;
    choice = -1;
    while (choice != 0) {
        Main_menu();
        cout << "Ваш выбор:" << endl;
        while (true) {
            cin >> choice;
            if (cin.fail()) { 
                cin.clear();  
                cin.ignore(10000, '\n'); 
                cout << "Введите корректное число:" << endl;
            }
            else if (cin.peek() != '\n') { 
                cin.clear(); 
                cin.ignore(10000, '\n'); 
                cout << "Введите корректное число:" << endl;
            }
            else {
                cin.ignore(10000, '\n'); 
                break; 
            }
        }
        switch (choice) {
        case 1:
            pipe = PIPE_add();
            break;
        case 2:
            cs = CS_add();
            break;
        case 3:
            Show_subjects(pipe, cs);
            break;
        case 4:
            Change_status_Pipe(pipe);
            break;
        case 5:
            Change_status_CS(cs);
            break;
        case 6: {
            ofstream out("FILE_L1.txt");
            out << pipe.name << " " << pipe.length << " " << pipe.diameter << " " << pipe.repair_status << endl;
            out << cs.name << " " << cs.quantity_workshop << " " << cs.workshops_in_work << " " << cs.efficiency << endl;
            out.close();
            cout << "Данные сохранены." << endl;
            break;
        }
        case 7: {
            ifstream in("FILE_L1.txt");
            if (in) {
                in >> pipe.name >> pipe.length >> pipe.diameter >> pipe.repair_status;
                in >> cs.name >> cs.quantity_workshop >> cs.workshops_in_work >> cs.efficiency;
                cout << "Данные загружены." << endl;
            }
            else {
                cout << "Ошибка загрузки файла." << endl;
            }
            in.close();
            break;
        }
        case 0:
            cout << "Работа завершена." << endl;
            break;
        default:
            cout << "Выберите корректный пункт меню." << endl;
        }
    };

    return 0;
}
