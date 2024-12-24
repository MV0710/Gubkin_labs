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
    cout << "Введите имя трубы: ";
    name = get_str();
    std::cout << "Введите длину трубы ";
    length = get_correct_value<int>(1, INT_MAX);
    std::cout << "Введите диаметр трубы: ";
    diameter = get_correct_value<int>(1, INT_MAX);
    under_repair = false;
}

std::ostream& operator << (std::ostream& out, const Pipe& p) {
    out << "ID: " << p.id << "\n";
    out << "Имя: " << p.name << "\n";
    out << "Длина: " << p.length << "\n";
    out << "Диаметр: " << p.diameter << "\n";
    out << "Статус в ремонте " << (p.under_repair ? "Да" : "Нет") << "\n";
    return out;
}

void Pipe::toggle_repair() {
    under_repair = !under_repair;
}

void Pipe::save_data(ofstream& out) {
    if (out.is_open()) {
        out << "Труба\n";
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
        cerr << "Ошибка в трубе!";
    }
}