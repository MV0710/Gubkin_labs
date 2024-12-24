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
    cout << "������� ��� ��: ";
    name = get_str();
    std::cout << "������� ���-�� �����: ";
    num_workshops = get_correct_value<int>(0, INT_MAX);
    std::cout << "������� ���-�� ����� � ������: ";
    num_workshops_in_operation = get_correct_value<int>(0, num_workshops);
    std::cout << "������� �������������: ";
    efficiency = get_correct_value<double>(0.0, 100.0);
}

std::ostream& operator << (std::ostream& out, const CompressorStation& cs) {
    out << "Id: " << cs.id << "\n";
    out << "���: " << cs.name << "\n";
    out << "���-�� �����: " << cs.num_workshops << "\n";
    out << "���-�� ����� � ������: " << cs.num_workshops_in_operation << "\n";
    out << "�������������: " << cs.efficiency << "\n";
    return out;
}

void CompressorStation::edit() {
    std::cout << "������� ����� ���-�� ����� � ������: ";
    num_workshops_in_operation = get_correct_value<int>(0, num_workshops);
}

void CompressorStation::save_data(ofstream& out) {
    if (out.is_open()) {
        out << "��\n";
        out << id << "\n";
        out << name << "\n";
        out << num_workshops << "\n";
        out << num_workshops_in_operation << "\n";
        out << efficiency << "\n";
    }
}

void CompressorStation::load_data(ifstream& read) {
    if (read.is_open()) {
        read >> id;
        read >> name;
        read >> num_workshops;
        read >> num_workshops_in_operation;
        read >> efficiency;
    }
    else {
        cout << "������ � ��!";
    }
}