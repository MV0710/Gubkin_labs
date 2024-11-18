#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Pipe{
	string name;
	int lenght;
	int diametr;
	bool repair_status;
};
int check_type_variable(string temp) {
	int check = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (int(temp[i]) > 47 && int(temp[i]) < 58) {
			check++;
		}
	}
	if (temp.size() == check && check!=0) {
		return 0; //это число
	}
	else {
		if (check == 0) {
			return 1;//это число
		}
		else {
			return 2;//некоретный ввод
		}
	}

}
Pipe PIPE_add() {
	Pipe new_pipe;
	string temp_s;
	int temp;
	cout << "Введите название трубы" << endl;
	cin >> temp_s;
	new_pipe.name = temp_s;
	cout << "Введите длину трубы" << endl;
	cin >> new_pipe.lenght;
	cout << "Введите диаметр трубы" << endl;
	cin >> new_pipe.diametr;
	cout << "Введите статус трубы (0-исправна,1-в ремонте) " << endl;
	cin >> new_pipe.repair_status;
	return new_pipe;
}

void Main_menu() {
	cout << "Выберете Действие из предложенных: \n1.Добавить трубу \n2.Добавить КС \n3.Просмотр всех объектов \n4.Редактировать трубу \n5.Редактировать КС \n6.Сохранить \n7.Загрузить \n0.Выход" << endl;
}

int main() {
	setlocale(LC_ALL, "ru");
	string n="-1";
	vector <Pipe> PIPE_list;//считавание труб из файла
	while (stoi(n) != 0) {
		if (stoi(n) == 1) {
			PIPE_list.push_back(PIPE_add());
		}
		Main_menu();
		cin >> n;
		while (check_type_variable(n) != 0) {
			cout << "Некоретный ввод введите цифру из предложенных" << endl;
			cin >> n;
		}
	}
	cout << "Работа окончена" << endl;
	return 0;
}