#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Special { KN, SA, IS, KB };
string specialStr[] = { "Комп'ютерні науки", "Системний аналіз", "Інформаційні ссистеми", "Кібербезпека" };
struct Student
{
	string prizv;
	int kurs;
	Special special;
	union
	{
		int physic;
		int math;
		int inform;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Special special);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість працівників N: "; cin >> N;

	Student* p = new Student[N];
	double proc;
	int ispecial;
	Special special;
	string prizv;
	int found;
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - бінарний пошук працівника за посадою та прізвищем" << endl;
		cout << " [6] - індексне впорядкування та вивід даних" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:

		case 4:
			Sort(p, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність (0 -Комп'ютерні науки, 1-Системний аналіз, 2-Інформаційні ссистеми, 3-Кібербезпека ): ";
			cin >> ispecial;
			special = (Special)ispecial;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, special)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 6:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int special, kurs ;
	for (int i = 0; i < N; i++)
	{
		cout << " Студент № " << i + 1 << ":" << endl;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " спеціальність (0 -Комп'ютерні науки, 1-Системний аналіз, 2-Інформаційні ссистеми, 3-Кібербезпека ): ";
		cin >> special;
		p[i].special = (Special)special;
		switch (p[i].special)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << " фізика : "; cin >> p[i].physic;
			cout << " математика : "; cin >> p[i].math;
			cout << " інформатика : "; cin >> p[i].inform;
			break;
		}
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Інформатика |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(11) << left << specialStr[p[i].special];
		switch (p[i].special)
		{
		case 0:
		case 1: 
		case 2:
		case 3:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].physic << " |" << setw(13) << right << "|" << endl;
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right
				<< p[i].math << " |" << endl;
			cout << "| " << setw(15) << right << "|" << " " << setw(5) << right
				<< p[i].inform << " |" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].special > p[i1 + 1].special)
				||
				(p[i1].special == p[i1 + 1].special &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Special special)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].special == special)
			return m;
		if ((p[m].special < special)
			||
			(p[m].special == special &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{ 
		int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value; 
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].special > p[value].special) ||
				(p[I[j]].special == p[value].special &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ 
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Рік.нар. | Посада | Тариф | Ставка |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(11) << left << specialStr[p[I[i]].special];
		switch (p[I[i]].special)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[I[i]].physic << " |"
				<< setw(13) << right << "|"
				<< endl;
			cout << "| " << setw(11) << right << "|" << " " << setw(8) << right
				<< p[I[i]].math << " |"
				<< endl;
			cout << "| " << setw(15) << right << "|" << " " << setw(5) << right
				<< p[i].inform << " |" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
