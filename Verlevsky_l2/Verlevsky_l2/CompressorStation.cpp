#include <iostream>
#include <fstream>
#include "CompressorStation.h"
#include "Get_Correct.cpp"

int CompressorStation::Nextid = 1;

CompressorStation::CompressorStation()
{
    id = Nextid++;
}

void CompressorStation::read() {
    cout << "Enter the compressor station name: ";
    name = get_str();
    std::cout << "Enter the number of workshops: ";
    num_workshops = get_correct_value<int>(0, INT_MAX);
    std::cout << "Enter the number of workshops in operation: ";
    num_workshops_in_operation = get_correct_value<int>(0, num_workshops);
    std::cout << "Enter the efficiency (0 to 100): ";
    efficiency = get_correct_value<double>(0.0, 100.0);
}

void CompressorStation::display() const {
    std::cout << "Id: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Number of workshops: " << num_workshops << std::endl;
    std::cout << "Number of workshops in operation: " << num_workshops_in_operation << std::endl;
    std::cout << "Efficiency: " << efficiency << std::endl;
}

void CompressorStation::edit() {
    std::cout << "Enter the new number of workshops in operation: ";
    num_workshops_in_operation = get_correct_value<int>(0, num_workshops);
}

void CompressorStation::save_data(const std::unordered_map<int, CompressorStation>& stations, const std::string& file_name) {
    ofstream file(file_name, ios::app);
    if (!file) {
        cerr << "Error opening file for writing: " << file_name << endl;
        return;
    }
    for (const auto& stationEntry : stations) {
        const CompressorStation& station = stationEntry.second;
        file << "Compressor Station\n";
        file << station.id << "\n";
        file << station.name << "\n";
        file << station.num_workshops << "\n";
        file << station.num_workshops_in_operation << "\n";
        file << station.efficiency << "\n";
    }
    file.close();
}

void CompressorStation::load_data(std::unordered_map<int, CompressorStation>& stations, const std::string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file for reading:: " << file_name << endl;
        return;
    }
    stations.clear();
    string line;
    while (getline(file, line)) {
        if (line == "Compressor Station") {
            CompressorStation station;
            int station_id;
            file >> station_id >> ws;
            file >> ws;
            file >> station.name >> station.num_workshops >> station.num_workshops_in_operation >> station.efficiency;
            stations[station_id] = station;
            file.ignore(10000, '\n');
        }
    }
    file.close();
}