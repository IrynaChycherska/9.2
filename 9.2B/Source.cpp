#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Special { KN, SA, IS, KB };
string specialStr[] = { "����'����� �����", "��������� �����", "����������� ��������", "ʳ����������" };
struct Student
{
	string prizv;
	int kurs;
	Special special;
	int physic;
	int math;
	union
	{
		int prigraming;
		int mathod;
		int pedagogy;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Special special);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double proc;
	int ispecial;
	Special special;
	string prizv;
	int found;
	char filename[100];
	int N;
	cout << "������ ������� ���������� N: "; cin >> N;
	cout << endl;
	Student* p = new Student[N];
	Create(p, N);
	cout << endl;
	Print(p, N);
	cout << endl;
	Sort(p, N);
	cout << endl;
	cout << " ������������ (0 -����'����� �����, 1-��������� �����, 2-����������� ��������, 3-ʳ���������� ): ";
	cin >> ispecial;
	special = (Special)ispecial;
	cin.get();
	cin.sync();
	cout << " �������: "; getline(cin, prizv);
	cout << endl;
	if ((found = BinSearch(p, N, prizv, special)) != -1)
		cout << "�������� �������� � ������� " << found + 1 << endl;
	else
		cout << "�������� �������� �� ��������" << endl;
	PrintIndexSorted(p, IndexSort(p, N), N);
	cout << endl;
	delete[] p;

}

