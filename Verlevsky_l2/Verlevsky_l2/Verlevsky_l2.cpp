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
        cerr << "Error! Enter an exiting ID: ";
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
        cout << "Are you sure you want to edit the pipe:\n";
        display_id(dict, id);
        cout << "0-No 1-Yes\n";
        if (get_correct_value(0, 1)) {
            T& item = dict[id];
            item.toggle_repair();
        }
    }
    cout << "Editing completed for the selected items." << endl;
}

template <typename T>
void delete_multiple_items(unordered_map<int, T>& dict, const unordered_set<int>& ids) {
    for (int id : ids) {
        cout << "Are you sure you want to delete the pipe:\n";
        display_id(dict, id);
        cout << "0-No 1-Yes\n";
        if (get_correct_value(0, 1)) {
            dict.erase(id);
        }
    }
    cout << "Deletion completed for the selected items." << endl;
}

int main() {
    redirect_output_wrapper cerr_out(cerr);
    //string time = format("{:%d-%m-%Y %H_%M_%S}", system_clock::now());
    ofstream logfile("log.txt");
    if (logfile) {
        cerr_out.redirect(logfile);
    }

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a pipe\n";
        cout << "2. Add a compressor station\n";
        cout << "3. View all objects\n";
        cout << "4. Edit a pipe\n";
        cout << "5. Edit a compressor station\n";
        cout << "6. Save\n";
        cout << "7. Load\n";
        cout << "8. Delete a pipe\n";
        cout << "9. Delete a compressor station\n";
        cout << "10. Searching pipes by filter\n";
        cout << "11. Searching compressor station by filter\n";
        cout << "12. Batch editing of pipes\n";
        cout << "13. Batch deletion of pipes\n";
        cout << "0. Exit\n";

        int choice;
        cout << "\nEnter a number from 0 to 13 to perform the corresponding action: ";
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
                cout << "Pipes:\n";
                for (auto& [id, pipe] : pipes) {
                    cout << pipe << endl;
                }
            }
            else {
                cout << "No pipes\n";
            }
            if (stations.size() != 0) {
                cout << "Compressor Stations:\n";
                for (auto& [id, station] : stations) {
                    cout << station << endl;
                }
            }
            else {
                cout << "No compressor stations\n";
            }
            break;
        }
        case 4: {
            if (pipes.size() != 0) {
                int pipe_id = get_valid_id("Enter the pipe ID for editing: ", pipes);
                Pipe& pipe = pipes[pipe_id];
                pipe.toggle_repair();
                cout << "The state of the pipe with ID " << pipe_id << " has been changed to 'Under repair: " << (pipe.under_repair ? "Yes" : "No") << "'\n";
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 5: {
            if (stations.size() != 0) {
                int station_id = get_valid_id("Enter the compressor station ID for editing: ", stations);
                CompressorStation& station = stations[station_id];
                station.edit();
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 6: {
            cout << "Enter the file name to save ('file name.txt'): ";
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
            cout << "Data saved to file: " << file_name << endl;
            break;
        }
        case 7: {
            cout << "Enter the file name: ";
            string file_name;
            string read_file = get_str();
            ifstream read(read_file);
            if (read.peek() == ifstream::traits_type::eof()) {
                cout << "Error! There is no data in the file.\n";
            }
            else {
                string Name;
                while (getline(read, Name)) {
                    if (Name == "Pipe") {
                        Pipe read_pipe;
                        read_pipe.load_data(read);
                        pipes.insert({ read_pipe.getid(), read_pipe });
                        cout << "Pipe data " << read_pipe.getid() << " downloaded from a file." << '\n';
                    }
                    if (Name == "Compressor Station") {
                        CompressorStation read_ks;
                        read_ks.load_data(read);
                        stations.insert({ read_ks.getid(), read_ks });
                        cout << "Compressor Station data " << read_ks.getid() << " downloaded from a file." << '\n';
                    }
                }
            }
            break;
        }
        case 8: {
            if (pipes.size() != 0) {
                int pipe_id = get_valid_id("Enter the pipe ID for delete: ", pipes);
                pipes.erase(pipe_id);
                cout << "Pipe with ID " << pipe_id << " has been deleted.\n";
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 9: {
            if (stations.size() != 0) {
                int station_id = get_valid_id("Enter the ID of the compressor station to delete: ", stations);
                stations.erase(station_id);
                cout << "Compressor station with ID " << station_id << " has been deleted.\n";
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 10: {
            if (pipes.size() != 0) {
                cout << "0 - By the 'under repair' status \n1 - By pipe name\nChoose by which filter you want to filter: ";
                if (get_correct_value(0, 1)) {
                    cout << "Enter the name of the pipes you want to find: ";
                    string name = get_str();
                    for (int i : find_by_filter(pipes, filter_by_name, name)) {
                        display_id(pipes, i);
                    }
                }
                else {
                    cout << "0 - pipe not under repair\n1 - pipe under repair\nEnter the number: ";
                    bool under_repair = get_correct_value(0, 1);
                    for (int i : find_by_filter(pipes, filter_by_status, under_repair)) {
                        display_id(pipes, i);
                    }
                }
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 11: {
            if (stations.size() != 0) {
                cout << "0 - By the percentage of unused workshops\n1- By the name of compressor stations\nChoose by which filter you want to filter: ";
                if (get_correct_value(0, 1)) {
                    cout << "Enter the name of the compressor station you want to find: ";
                    string name = get_str();
                    for (int i : find_by_filter(stations, filter_by_name, name)) {
                        display_id(stations, i);
                    }
                }
                else {
                    cout << "Enter the efficiency of the compressor stations you want to find: ";
                    int non_working = get_correct_value(0, 100);
                    for (int i : find_by_filter(stations, filter_by_non_working, non_working)) {
                        display_id(stations, i);
                    }
                }
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 12: {
            if (pipes.size() != 0) {
                cout << "0 - By 'under repair' status\n1 - By pipe name\nChoose the criterion for selecting pipes for batch editing: ";
                int filter_choice = get_correct_value<int>(0, 1);

                if (filter_choice == 0) {
                    cout << "0 - Not under repair\n1 - Under repair\nChoose the pipe status: ";
                    bool under_repair = get_correct_value(0, 1);
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_status, under_repair);
                    edit_multiple_items(pipes, selected_pipes);
                }
                else if (filter_choice == 1) {
                    cout << "Enter the pipe name for search: ";
                    string name = get_str();
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_name, name);
                    edit_multiple_items(pipes, selected_pipes);
                }
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        case 13: {
            if (pipes.size() != 0) {
                cout << "0 - By 'under repair' status\n1 - By pipe name\nChoose the criterion for selecting pipes for batch deletion: ";
                int filter_choice = get_correct_value<int>(0, 1);

                if (filter_choice == 0) {
                    cout << "0 - Not under repair\n1 - Under repair\nChoose the pipe status: ";
                    bool under_repair = get_correct_value(0, 1);
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_status, under_repair);
                    delete_multiple_items(pipes, selected_pipes);
                }
                else if (filter_choice == 1) {
                    cout << "Enter the pipe name for search: ";
                    string name = get_str();
                    unordered_set<int> selected_pipes = find_by_filter(pipes, filter_by_name, name);
                    delete_multiple_items(pipes, selected_pipes);
                }
            }
            else {
                cout << "No data\n";
            }
            break;
        }
        default: {
            cerr << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }
    return 0;
}