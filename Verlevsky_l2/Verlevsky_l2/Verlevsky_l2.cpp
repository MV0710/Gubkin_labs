#include <iostream>
#include <fstream>
#include <format>
#include <chrono>
#include <unordered_map>
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
        cerr << "Ошибка: Введите существующий ID: ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << message;
    }
    return id;
}
int main() {
    /*redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d-%m-%Y %H_%M_%S}", system_clock::now());
    ofstream logfile("log" + time + ".txt");
    if (logfile) {
        cerr_out.redirect(logfile);
    }*/

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
        cout << "0. Exit\n";
        int choice;
        cout << "\nEnter a number from 0 to 9 to perform the corresponding action: ";
        choice = get_correct_value<int>(0, 9);
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
            cout << "Pipes:\n";
            for (const auto& pipeEntry : pipes) {
                const Pipe& pipe = pipeEntry.second;
                pipe.display();
                cout << endl;
            }
            cout << "Compressor Stations:\n";
            for (const auto& stationEntry : stations) {
                const CompressorStation& station = stationEntry.second;
                station.display();
                cout << endl;
            }
            break;
        }
        case 4: {
            int pipe_id = get_valid_id("Enter the pipe ID for editing: ", pipes);
            Pipe& pipe = pipes[pipe_id];
            pipe.toggle_repair();
            cout << "The state of the pipe with ID " << pipe_id << " has been changed to 'Under repair: " << (pipe.under_repair ? "Yes" : "No") << "'\n";
            break;
        }
        case 5: {
            int station_id = get_valid_id("Enter the compressor station ID for editing: ", stations);
            CompressorStation& station = stations[station_id];
            station.edit();
            break;
        }
        case 6: {
            string file_name;
            cout << "Enter the file name to save ('file name.txt'): ";
            cin >> file_name;
            Pipe pipe;
            pipe.save_data(pipes, file_name);
            CompressorStation station;
            station.save_data(stations, file_name);
            cout << "Data saved to file: " << file_name << endl;
            break;
        }
        case 7: {
            string file_name;
            cout << "Enter the file name for loading ('file name.txt'): ";
            cin >> file_name;
            Pipe pipe;
            pipe.load_data(pipes, file_name);
            CompressorStation station;
            station.load_data(stations, file_name);
            cout << "Data loaded from the file: " << file_name << endl;
            break;
        }
        case 8: {
            int pipe_id = get_valid_id("Введите ID трубы для удаления: ", pipes);
            pipes.erase(pipe_id);
            cout << "Pipe with ID " << pipe_id << " has been deleted.\n";
            break;
        }
        case 9: {
            int station_id = get_valid_id("Enter the ID of the compressor station to delete: ", stations);
            stations.erase(station_id);
            cout << "Compressor station with ID " << station_id << " has been deleted.\n";
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