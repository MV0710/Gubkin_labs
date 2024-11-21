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
	while (check_type_variable(temp_s) == 0) {
		if (new_CS.quantity_workshop < stoi(temp_s)) {
			temp_s = "-1";
			cout << "Число цехов в работе должно быть не больше общего кол-ва цехов" << endl;
			getline(cin, temp_s);
		}
		else {
			break;
		}
	}
	while (check_type_variable(temp_s) != 0 && check_type_variable(temp_s) != 3) {
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
	new_CS.efficiency = double(new_CS.workshops_in_work) / double(new_CS.quantity_workshop);
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

vector <Pipe> Change_status_Pipe(vector <Pipe> Pipes) {
	if (Pipes.size() == 0) {
		cout << "Список труб пустой!" << endl;
		return Pipes;
	}
	string choosen;
	for (int i = 0; i < Pipes.size(); i++) {
		cout << i + 1 << " " << Pipes[i].name << " " << Pipes[i].repair_status;
	}
	cout << "Выберете номер из списка" << endl;
	getline(cin, choosen);
	while (check_type_variable(choosen) == 0) {
		if (stoi(choosen) > Pipes.size()) {
			cout << "Такого номера нет в списке" << endl;
			getline(cin, choosen);
		}
		else {
			break;
		}
	}
	while (check_type_variable(choosen) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, choosen);
	}
	Pipes[stoi(choosen) - 1].repair_status = !(Pipes[stoi(choosen) - 1].repair_status);
	cout << "Изменения успешно внесены" << endl;
	return Pipes;
}

vector <CS> Change_status_CS(vector <CS> CSions) {
	if (CSions.size() == 0) {
		cout << "Список КС пустой!" << endl;
		return CSions;
	}
	string choosen, number;
	for (int i = 0; i < CSions.size(); i++) {
		cout << "Номер" << i + 1 << "Название КС" << CSions[i].name << "Кол-во всех цехов" << CSions[i].quantity_workshop << "\nКоличество цехов в работе" << CSions[i].workshops_in_work << endl;
	}
	cout << "Выберете номер из списка" << endl;
	getline(cin, choosen);
	while (check_type_variable(choosen) == 0) {
		if (stoi(choosen) > CSions.size()) {
			cout << "Такого номера нет в списке" << endl;
			getline(cin, choosen);
		}
		else {
			break;
		}
	}
	while (check_type_variable(choosen) != 0) {
		cout << "Введите одно положительное число" << endl;
		getline(cin, choosen);
	}
	cout << "Введите новое число цехов в работе" << endl;
	getline(cin, number);
	while (check_type_variable(number) == 0) {
		if (CSions[stoi(choosen)-1].quantity_workshop < stoi(number)) {
			number = "-1";
			cout << "Число цехов в работе должно быть не больше общего кол-ва цехов" << endl;
			getline(cin, number);
		}
		else {
			break;
		}
	}
	while (check_type_variable(number) != 0) {
		cout << "Введите одно положительное число меньшее кол-ва общих цехов" << endl;
		getline(cin, number);
		if (check_type_variable(number) == 0 || check_type_variable(number) == 3) {
			if (CSions[stoi(choosen) - 1].quantity_workshop < stoi(number)) {
				cout << "Число цехов в работе должно быть не больше общего кол-ва цехов" << endl;
				getline(cin, number);
			}
			else {
				break;
			}
		}
	}
	CSions[stoi(choosen)-1].workshops_in_work = stoi(number);
	CSions[stoi(choosen) - 1].efficiency = double(CSions[stoi(choosen) - 1].workshops_in_work) / double(CSions[stoi(choosen) - 1].quantity_workshop);
	cout << "Изменения успешно внесены" << endl;
	return CSions;
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
		if (stoi(n) == 4) {
			PIPE_list=Change_status_Pipe(PIPE_list);
		}
		if (stoi(n) == 5) {
			CS_list = Change_status_CS(CS_list);
		}
		if (stoi(n) == 6) {
			ofstream PIPE_FILE("PIPE_FILE.txt");
			ofstream CS_FILE("CS_FILE.txt");
			for (int i = 0; i < PIPE_list.size(); i++) {
				PIPE_FILE << PIPE_list[i].name << " " << PIPE_list[i].lenght << " " << PIPE_list[i].diametr << " " << PIPE_list[i].repair_status << endl;
			}
			for (int i = 0; i < CS_list.size(); i++) {
				CS_FILE << CS_list[i].name << " " << CS_list[i].quantity_workshop << " " << CS_list[i].workshops_in_work << " " << CS_list[i].efficiency << endl;
			}
			PIPE_FILE.close();
			CS_FILE.close();
		}
		if (stoi(n) == 7) {
			ifstream PIPE_FILE("PIPE_FILE.txt");
			cout << PIPE_FILE << endl;
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