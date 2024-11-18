#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;
struct Pipe {

};
int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wcout << L"Добрый День! Выберете Действие из предложенных: \n1.Добавить трубу \n2.Добавить КС \n3.Просмотр всех объектов \n4.Редактировать трубу \n5.Редактировать КС \n6.Сохранить \n7.Загрузить \n0.Выход" << endl;
	int n=-1;
	while (n != 0) {
		wcin >> n;
	}
	wcout << L"Работа окончена" << endl;
	return 0;
}