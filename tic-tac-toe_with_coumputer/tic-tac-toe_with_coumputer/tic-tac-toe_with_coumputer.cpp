
#include <iostream> 
#include <ctime> 
#include <string> 
#include <vector> 
#include <algorithm>
#include <list>

using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';



void intructions()
{
	setlocale(LC_ALL, "ru");

	cout << "В игре вам требуется собрать 3 подряд символа.\n";
	cout << "Либо крестики, либо нолики.\n";
	cout << "Побеждает тот, кто соберет подряд те самые 3 символа подряд.\n";
	cout << " 0 | 1 | 2\n";
	cout << "----------\n";
	cout << " 3 | 4 | 5\n";
	cout << "----------\n";
	cout << " 6 | 7 | 8\n";

}
char YesNo(string question)
{
	setlocale(LC_ALL, "ru");
	char ans;

	do
	{
		cout << question << " (y/n): ";
		cin >> ans;

	} while (ans != 'y' && ans != 'n');

	return ans;
}

int askNumberField(string question, int high, int low = 0)
{
	setlocale(LC_ALL, "ru");
	int number;

	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;

	} while (number > high || number < low);

	return number;
}

char humanPiece()
{
	setlocale(LC_ALL, "ru");
	char go_first = YesNo("Хотите сделать первый ход? ");

	if (go_first == 'y')
	{
		cout << "Вы выбрали быть первым. ";
		return X;
	}
	if (go_first == 'n')
	{
		cout << "Вы выбрали быть вторым. ";
		return O;
	}
}

char opponent(char piece)
{
	if (piece == X)
	{
		return O;
	}
	else
	{
		return X;
	}
}

void displayBoard(const vector<char>& board)
{
	cout << "\n" << board[0] << " | " << board[1] << " | " << board[2];
	//cout << "----------\n";
	cout << "\n" << board[3] << " | " << board[4] << " | " << board[5];
	//cout << "----------\n";
	cout << "\n" << board[6] << " | " << board[7] << " | " << board[8];

	cout << "\n\n";
}

char winner(const vector<char>& board)
{
	const int WinRowsCols[8][3] = { {0,1,2},
	{3,4,5},
	{6,7,8},
	{0,3,6},
	{1,4,7},
	{2,5,8},
	{0,4,8},
	{2,4,6} };


	const int TOTAL_ROWS = 8;

	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WinRowsCols[row][0]] != EMPTY) && (board[WinRowsCols[row][0]] == board[WinRowsCols[row][1]]) && (board[WinRowsCols[row][1]] == board[WinRowsCols[row][2]]))
		{
			return board[WinRowsCols[row][0]];
		}
	}

	if (count(board.begin(), board.end(), EMPTY) == 0)
	{
		return TIE;
	}
	else
	{
		return NO_ONE;
	}
}

inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == EMPTY);
}

int humanMove(const vector <char>& board, char human)
{
	setlocale(LC_ALL, "ru");
	int move = askNumberField("В какую клетку вписать ваш символ?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "Эта клетка уже занята.";
		move = askNumberField("В какую клетку вписать ваш символ?", (board.size() - 1));
	}
	return move;

}

int computerMove(vector<char>& board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			move++;
		}
	}


	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				move++;
			}

		}
	}
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}
			i++;
		}
	}
	return move;



}
int II = 0;
int HUM = 0;
int T = 0;
void TrueWinner(char winner, char computer, char human)
{
	setlocale(LC_ALL, "ru");
	if (winner == computer)
	{
		cout << "Победителем стал искуственный ителлект!\n";
		II++;
		cout << "\nЧеловек: " << HUM;
		cout << "\nИскуственный ителлект: " << II;
		cout << "\nНичьи: " << T;
	}
	else if (winner == human)
	{
		HUM++;
		cout << "Вы победили! Поздравляю!\n";
		cout << "\nЧеловек: " << HUM;
		cout << "\nИскуственный ителлект: " << II;
	}
	else
	{
		T++;
		cout << "Ничья!";
		cout << "\nЧеловек: " << HUM;
		cout << "\nИскуственный ителлект: " << II;
		cout << "\nНичьи: " << T;
	}
}
int main()
{
	string answer;
	while (answer != "n")
	{
		setlocale(LC_ALL, "ru");
		cout << "Добро пожаловать в игру <<Крестики - нолики>>";
		int move;
		const int NUM_SQ = 9;
		vector <char>board(NUM_SQ, EMPTY);
		intructions();
		char human = humanPiece();
		char computer = opponent(human);
		char turn = X;
		displayBoard(board);


		while (winner(board) == NO_ONE)
		{
			if (turn == human)
			{
				move = humanMove(board, human);
				board[move] = human;
			}
			else
			{
				move = computerMove(board, human);
				board[move] = computer;
			}
			displayBoard(board);
			turn = opponent(turn);
		}


		TrueWinner(winner(board), computer, human);

		cout << "\nХотите сыграть снова? (y/n): ";
		cin >> answer;

	}
	cout << "До свидания! ";

	return 0;
}