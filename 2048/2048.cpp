// 2048.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

int board[4][4];
//напрвления
int dirLine[] = { 1,0,-1,0 };
int dirColumn[] = { 0,1,0,-1 };

//Случайные чисел
pair<int, int>generateUnoccupiedPosition() {
	int occupied = 1, line, column;
	while (occupied) {
		int line = rand() % 4;
		int column = rand() % 4;
		if (board[line][column] == 0)
			occupied = 0;
	}
	return make_pair(line, column);
}

void addPiece() {
	pair<int, int>pos = generateUnoccupiedPosition();
	board[pos.first][pos.second] = 2;
}

void newGame2048() {
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			board[i][j] = 0;
			addPiece();
			
		}
	}

}

//ползовательский интерфейс
void printUi() {
	system("cls");

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			if (board[i][j] == 0)
				cout <<setw(4)<<".";
			else
				cout <<  setw(4) << board[i][j];
		cout << endl;
		
	}
	cout << "n: new game(новая игра), w:up (вверх), s:down,(вниз), d:right(вправо), a:left(влево), q:quit(выход)\n";

	//28:03
}

bool canDoMove(int line, int column, int nextline, int nextColumn) {
	if (nextline < 0 || nextColumn < 0 || nextline >= 4 || nextColumn >= 0 
		|| (board[line][column] != board[nextline][nextColumn] && board[nextline][nextColumn] !=0))
		return false;
}


 //движения  
void applyMove(int direction) {
	int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
	if (direction == 0) {
		startLine = 3;
		lineStep = -1;
	}
	if (direction == 1) {
		startColumn = 3;
		columnStep = -1;
	}
	int movePossible,canAddPiece = 0;
	do {
		movePossible = 0;
		for (int i = startLine; i >= 0 && i < 4; i += lineStep)
		{
			for (int j = startColumn; j >= 0 && j < 4; j += columnStep) {
				int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
				//cout << i << " " << j << " " << nextI << " " << nextJ << "\n";
				if (canDoMove(i, j, nextI, nextJ))
				{
					board[nextI][nextJ] += board[i][j];
					board[i][j] = 0;
					movePossible =canAddPiece = 1;
				}
			}

		}
		printUi();
		char c;
		cin >> c;

	}
	while (movePossible);
	if (canAddPiece)
		addPiece();
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	char commandToDir[128];
	commandToDir['s'] = 0;
	commandToDir['d'] = 1;
	commandToDir['w'] = 2;
	commandToDir['a'] = 3;

	while (true) {
		printUi();
		char command;
		cin >> command; 
		if (command == 'n')
			newGame2048();
		else if (command == 'q')
			break;
		else {
			int currentDirection = commandToDir[command];
			//cout << currentDirection << "\n";
			applyMove(currentDirection);
		}

	}
	return 0;












}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
