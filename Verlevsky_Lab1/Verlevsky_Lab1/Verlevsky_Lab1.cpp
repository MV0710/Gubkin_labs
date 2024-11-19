#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Pipe {
	string name;
	int lenght;
	int diametr;
	bool repair_status;
	Pipe() :
		name("0"), lenght(0), diametr(0), repair_status(0) {}
};

struct CS {
	string name;
	int quantity_workshop;
	int workshops_in_work;
	double efficiency;
	CS() :
		name("0"), quantity_workshop(0), workshops_in_work(0), efficiency(0.0) {}
};

int check_type_variable(string temp) {
	int check = 0;
	for (int i = 0; i < temp.size(); i++) {
		if (int(temp[i]) > 31 && int(temp[i] < 48)) {
			return 2;
		}
		if (int(temp[i]) > 47 && int(temp[i]) < 58) {
			check++;
		}
	}
	if (temp.size() == check && check!=0) {
		if (stoi(temp) == 0){
			return 3;//это ноль
		}
		return 0; //это число
	}
	else {
		if (check == 0) {
			return 1;//это строка
		}
		else {
			return 2;//некоретный ввод
		}
	}

}

Pipe PIPE_add() {
	Pipe new_pipe;
	string temp_s;
	cout << "Введите название трубы" << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s)!=1) {
		cout << "Введите одну строку" << endl;
		getline(cin, temp_s);
	}
	new_pipe.name = temp_s;
	cout << "Введите длину трубы" << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, temp_s);
	}
	new_pipe.lenght = stoi(temp_s);
	cout << "Введите диаметр трубы" << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, temp_s);
	}
	new_pipe.diametr = stoi(temp_s);
	cout << "Введите статус трубы (0-исправна,1-в ремонте) " << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) == 0 && check_type_variable(temp_s) != 3) {
		cout << "Введите 0 или 1" << endl;
		if (stoi(temp_s) < 2) {
			break;
		}
		else {
			getline(cin, temp_s);
		}
	}
	while (check_type_variable(temp_s) != 0 && check_type_variable(temp_s) != 3) {
		cout << "Введите 0 или 1" << endl;
		getline(cin, temp_s);
		if (check_type_variable(temp_s) == 0 && stoi(temp_s) > 1){
			temp_s = "-1";
		}
	}
	new_pipe.repair_status = stoi(temp_s);
	return new_pipe;
}

CS CS_add() {
	CS new_CS;
	string temp_s;
	cout << "Введите название КС" << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) != 1) {
		cout << "Введите одну строку" << endl;
		getline(cin, temp_s);
	}
	new_CS.name = temp_s;
	cout << "Введите количество цехов" << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, temp_s);
	}
	new_CS.quantity_workshop = stoi(temp_s);
	cout << "Введите количество цехов в работе" << endl;
	getline(cin, temp_s);
	while(check_type_variable(temp_s) == 0) {
		if (new_CS.quantity_workshop < stoi(temp_s)) {
			temp_s = "-1";
			cout << "Число цехов в работе должно быть не больше общего кол-ва цехов" << endl;
			getline(cin, temp_s);
		}
		else {
			break;
		}
	}
	while (check_type_variable(temp_s) != 0 && check_type_variable(temp_s) != 3){
		cout << "Введите одно неотрицательное число" << endl;
		getline(cin, temp_s);
		if (check_type_variable(temp_s) == 0 || check_type_variable(temp_s) == 3) {
			if (new_CS.quantity_workshop < stoi(temp_s)) {
				temp_s = "-1";
				cout << "Число цехов в работе должно быть не больше общего кол-ва цехов" << endl;
			}
		}
	}
	new_CS.workshops_in_work = stoi(temp_s);
	/*cout << "Введите эффектиновсть " << endl;
	getline(cin, temp_s);
	while (check_type_variable(temp_s) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, temp_s);
	}*/
	new_CS.efficiency = new_CS.workshops_in_work/new_CS.quantity_workshop;
	return new_CS;
}

void Show_subjets(vector <Pipe> P, vector <CS> C) {
	int count = 0;
	cout << "Трубы:" << endl;
	for (int i = 0; i < P.size(); i++) {
		count++;
		cout << P[i].name << " " << P[i].lenght << " " << P[i].diametr << " " << P[i].repair_status << endl;
	}
	if (count == 0) {
		cout << "Нет записаннах труб!" << endl;
	}
	count = 0;
	cout << "KC:" << endl;
	for (int i = 0; i < C.size(); i++) {
		count++;
		cout << C[i].name << " " << C[i].quantity_workshop << " " << C[i].workshops_in_work << " " << C[i].efficiency << endl;
	}
	if (count == 0) {
		cout << "Нет записанных КС!" << endl;
	}
}

void Main_menu() {
	cout << "Выберете Действие из предложенных: \n1.Добавить трубу \n2.Добавить КС \n3.Просмотр всех объектов \n4.Редактировать трубу \n5.Редактировать КС \n6.Сохранить \n7.Загрузить \n0.Выход" << endl;
}

int main() {
	setlocale(LC_ALL, "ru");
	string n="-1";
	vector <Pipe> PIPE_list;//считывание труб из файла
	vector <CS> CS_list;//считывание КС из файла
	while (stoi(n) != 0) {
		if (stoi(n) == 1) {
			PIPE_list.push_back(PIPE_add());
		}
		if (stoi(n) == 2) {
			CS_list.push_back(CS_add());
		}
		if (stoi(n) == 3) {
			Show_subjets(PIPE_list, CS_list);
		}
		Main_menu();
		getline(cin, n);
		while (check_type_variable(n) != 0 && check_type_variable(n) != 3) {
			cout << "Некоретный ввод введите цифру из предложенных" << endl;
			getline(cin, n);
		}
	}
	cout << "Работа окончена" << endl;
	return 0;
}