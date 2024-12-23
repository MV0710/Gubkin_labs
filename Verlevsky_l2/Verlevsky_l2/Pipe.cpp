#include <iostream>
#include <fstream>

#include "Pipe.h"
#include "Get_Correct.cpp"

int Pipe::Nextid = 1;

Pipe::Pipe()
{
    id = Nextid++;
}

void Pipe::read() {
    cout << "Enter the pipe name: ";
    name = get_str();
    std::cout << "Enter the length of the pipe (in km): ";
    length = get_correct_value<int>(1, INT_MAX);
    std::cout << "Enter the diameter of the pipe: ";
    diameter = get_correct_value<int>(1, INT_MAX);
    under_repair = false;
}

std::ostream& operator << (std::ostream& out, const Pipe& p) {
    out << "ID: " << p.id << "\n";
    out << "Name: " << p.name << "\n";
    out << "Length (km): " << p.length << "\n";
    out << "Diameter: " << p.diameter << "\n";
    out << "Under repair: " << (p.under_repair ? "Yes" : "No") << "\n";
    return out;
}

void Pipe::toggle_repair() {
    under_repair = !under_repair;
}

void Pipe::save_data(ofstream& out) {
    if (out.is_open()) {
        out << "Pipe\n";
        out << id << "\n";
        out << name << "\n";
        out << length << "\n";
        out << diameter << "\n";
        out << under_repair << "\n";
    }
}

void Pipe::load_data(ifstream& read) {
    if (read.is_open()) {
        read >> id;
        read >> name;
        read >> length;
        read >> diameter;
        read >> under_repair;

    }
    else {
        cerr << "Error!";
    }
}