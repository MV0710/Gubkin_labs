#include <iostream>
#include <fstream>
#include <format>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "CompressorStation.h"
#include "Logging.h"
#include "Get_Correct.cpp"

using namespace std;
using namespace chrono;

template<typename K>
int get_valid_id(const string& message, const std::unordered_map<int, K>& items) {
    int id;
    cout << message;
    while (!(cin >> id) || items.find(id) == items.end()) {
        cerr << "Ошибка, введите корректный id ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << message;
    }
    return id;
}

template<typename T1, typename T2>
using filter = bool(*)(const T1& dict, T2 param);

template<typename T>
bool filter_by_name(const T& dict, string name) {
    return dict.name.find(name) != string::npos;
}

bool filter_by_status(const Pipe& dict, bool status) {
    return dict.under_repair == status;
}

bool filter_by_non_working(const CompressorStation& dict, int non_working) {
    return dict.num_workshops - dict.num_workshops_in_operation >= dict.num_workshops * non_working / 100;
}

template <typename T1, typename T2>
unordered_set<int> find_by_filter(const unordered_map<int, T1>& dict, filter<T1, T2> f, T2 par) {
    unordered_set<int> ids;
    for (auto& pair : dict) {
        if (f(pair.second, par)) {
            ids.insert(pair.first);
        }
    }
    return ids;
}

template <typename F>
void display_id(unordered_map<int, F>& dict, int id) {
    for (auto const& pair : dict) {
        if (id == pair.first) {
            cout << pair.second << endl;
        }
    }
}

template <typename T>
void edit_multiple_items(unordered_map<int, T>& dict, const unordered_set<int>& ids) {
    for (int id : ids) {
        cout << "Вы уверены что:\n";
        display_id(dict, id);
        cout << "0-Нет 1-Да\n";
        if (get_correct_value(0, 1)) {
            T& item = dict[id];
            item.toggle_repair();
        }
    }
    cout << "Изменения выполнены." << endl;
}

template <typename T>
void delete_multiple_items(unordered_map<int, T>& dict, const unordered_set<int>& ids) {
    for (int id : ids) {
        cout << "Вы уверены что хотите удалить трубу?:\n";
        display_id(dict, id);
        cout << "0-Нет 1-Да\n";
        if (get_correct_value(0, 1)) {
            dict.erase(id);
        }
    }
    cout << "Удаление успешно." << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");

    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("log.txt");
    if (logfile) {
        cerr_out.redirect(logfile);
    }

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;

    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Посмотреть все обьекты\n";
        cout << "4. Изменить трубу\n";
        cout << "5. Изменить \n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "8. Удалить трубу\n";
        cout << "9. Удалить КС\n";
        cout << "10. Поиск трубы по фильтру\n";
        cout << "11. Поиск КС по фильтру\n";
        cout << "12. Изменение труб пакетом\n";
        cout << "13. Удаление труб пакетом\n";
        cout << "0. Выход\n";

        int choice;
        cout << "\nВведите число от 0 до 13: ";
        choice = get_correct_value<int>(0, 13);
        switch (choice) {
        case 0:
            exit(0);
            break;
        case 1: {
            Pipe pipe;
            pipe.read();
            pipes.insert(make_pair(pipe.getid(), pipe));
            break;
        }
        case 2: {
            CompressorStation station;
            station.read();
            stations.insert(make_pair(station.getid(), station));
            break;
        }
        case 3: {
            if (pipes.size() != 0) {
                cout << "Трубы:\n";
                for (auto& [id, pipe] : pipes) {
                    cout << pipe << endl;
                }
            }
            else {
                cout << "Трубы отсутствуют\n";
            }
            if (stations.size() != 0) {
                cout << "Компрессорные станции:\n";
                for (auto& [id, station] : stations) {
                    cout << station << endl;
                }
            }
            else {
                cout << "КС отсутсвуют\n";
            }
            break;
        }
        case 4: {
            if (pipes.size() != 0) {
                int pipe_id = get_valid_id("Введите id трубы для измененя", pipes);
                Pipe& pipe = pipes[pipe_id];
                pipe.toggle_repair();
                cout << "Статус трубы с id " << pipe_id << "был изменен на" << (pipe.under_repair ? "Да" : "Нет") << "'\n";
            }
            else {
                cout << "Нет данных\n";
            }
            break;
        }
        case 5: {
            if (stations.size() != 0) {
                int station_id = get_valid_id("Введите id КС для изменения", stations);
                CompressorStation& station = stations[station_id];
                station.edit();
            }
            else {
                cout << "Нет данных\n";
            }
            break;
        }
        case 6: {
            cout << "Введите имя файла ";
            string file_name = get_str();
            ofstream out(file_name);
            for (auto const& p : pipes) {
                if (!p.second.name.empty()) {
                    pipes[p.first].save_data(out);
                }
            }
            for (auto const& cs : stations) {
                if (!cs.second.name.empty()) {
                    stations[cs.first].save_data(out);
                }
            }
            cout << "Сохранено в файл: " << file_name << endl;
            break;
        }
        case 7: {
            cout << "Введите имя файл: ";
            string file_name;
            string read_file = get_str();
            ifstream read(read_file);
            if (read.peek() == ifstream::traits_type::eof()) {
                cout << "Ошибка нет данных в файл.\n";
            }
            else {
                string Name;
                while (getline(read, Name)) {
                    if (Name == "Труба") {
                        Pipe read_pipe;
                        read_pipe.load_data(read);
                        pipes.insert({ read_pipe.getid(), read_pipe });
                        cout << "Данные труб " << read_pipe.getid() << " скачаны из файла." << '\n';
                    }
                    if (Name == "КС") {
                        CompressorStation read_ks;
                        read_ks.load_data(read);
                        stations.insert({ read_ks.getid(), read_ks });
                        cout << "Данные КС " << read_ks.getid() << " скачаны из файла." << '\n';
                    }
                }
            }
            break;
        }
        case 8: {
            if (pipes.size() != 0) {
                int pipe_id = get_valid_id("Введите id трубы для удаления: ", pipes);
                pipes.erase(pipe_id);
                cout << "Труба с  ID " << pipe_id << " была удалена.\n";
            }
            else {
                cout << "Нет данных\n";
            }
            break;
        }
        case 9: {
            if (stations.size() != 0) {
                int station_id = get_valid_id("Введите id КС для удаления: ", stations);
                stations.erase(station_id);
                cout << "Станция КС с ID " << station_id << " была удалена.\n";
            }
            else {
                cout << "Данных нет\n";
            }
            break;
        }
        case 10: {
            if (pipes.size() != 0) {
                cout << "0 - По статусу в работе \n1 - По имени трубы\nВыберите фильтр: ";
                if (get_correct_value(0, 1)) {
                    cout << "Введите имя трубы которую нужно найти: ";
                    string name = get_str();
                    for (int i : find_by_filter(pipes, filter_by_name, name)) {
                        display_id(pipes, i);
                    }
                }
                else {
                    cout << "0 - труба не в ремонте\n1 - труба в ремонте\nВведите номер: ";
                    bool under_repair = get_correct_value(0, 1);
                    for (int i : find_by_filter(pipes, filter_by_status, under_repair)) {
                        display_id(pipes, i);
                    }
                }
            }
            else {
                cout << "Данных нет\n";
            }
            break;
        }
        case 11: {
            if (stations.size() != 0) {
                cout << "0 - По эффективности\n1- По имени КС\nВыберите фильтр: ";
                if (get_correct_value(0, 1)) {
                    cout << "Введите имя КС: ";
                    string name = get_str();
                    for (int i : find_by_filter(stations, filter_by_name, name)) {
                        display_id(stations, i);
                    }
                }
                else {
                    cout << "Введите эффективность: ";
                    int non_working = get_correct_value(0, 100);
                    for (int i : find_by_filter(stations, filter_by_non_working, non_working)) {
                        display_id(stations, i);
                    }
                }
            }
            else {
                cout << "Данных нет\n";
            }
            break;
        }
        case 12: {
            if (pipes.size() != 0) {
                cout << "0 - По статусу в работе\n1 - По имени трубы\nВыберите какой фильтр использовать для пакетов: ";
                int filter_choice = get_correct_value<int>(0, 1);

                if (filter_choice == 0) {
                    cout << "0 - Не в работе\n1 - В работе\nВыберите статус: ";
                    bool under_repair = get_correct_value(0, 1);
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_status, under_repair);
                    edit_multiple_items(pipes, selected_pipes);
                }
                else if (filter_choice == 1) {
                    cout << "Введите имя для поиска: ";
                    string name = get_str();
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_name, name);
                    edit_multiple_items(pipes, selected_pipes);
                }
            }
            else {
                cout << "Данных нет\n";
            }
            break;
        }
        case 13: {
            if (pipes.size() != 0) {
                cout << "0 - По статусу в работе\n1 - По имени труб\nВыберите критерий для удаления: ";
                int filter_choice = get_correct_value<int>(0, 1);

                if (filter_choice == 0) {
                    cout << "0 - Не в ремонте\n1 - в ремонте\nВыберите статус: ";
                    bool under_repair = get_correct_value(0, 1);
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_status, under_repair);
                    delete_multiple_items(pipes, selected_pipes);
                }
                else if (filter_choice == 1) {
                    cout << "Введите имя трубы для поиска: ";
                    string name = get_str();
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_name, name);
                    delete_multiple_items(pipes, selected_pipes);
                }
            }
            else {
                cout << "Нет данных\n";
            }
            break;
        }
        default: {
            cerr << "Неверный выбор повторите.\n";
            break;
        }
        }
    }
    return 0;
}