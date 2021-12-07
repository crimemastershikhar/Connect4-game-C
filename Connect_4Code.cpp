#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <string>
#include <stdlib.h>
#define CLRSCR "\e[2J\e[H";
#define RED "\x1b[31m";
#define GREEN "\x1b[32m";
#define BLUE "\x1b[34m";
#define MAGENTA "\x1b[35m";
#define WHITE "\x1b[37m";
using namespace std;

struct Player
{
	char name[100];
	char id;
};
int PlayerInput(char board[][10], Player active)
{
	int choice;
	do
	{
		if(active.id == 'R')	cout<<RED;
		if(active.id == 'B')	cout<<BLUE;
		
		cout<<active.id << " Turn "<<endl;
		cout<<"Enter column number between 1 and 7: ";
		cin>>choice;
		cout<<WHITE;

		while(board[1][choice] == 'R' || board[1][choice] == 'B')
		{
			cout<<"Row is full, please enter a new row: ";
			cin>>choice;
		}
		cout<<CLRSCR;
	}while(choice < 1 || choice > 7);

	return choice;
}
void CheckTurn(char board[][10], Player active, int choice)
{
	int length = 6, turn = 0;

	while(turn != 1)
	{
		if(board[length][choice] != 'R' && board[length][choice] != 'B')
		{
			board[length][choice] = active.id;
			turn = 1;
		}
		else
		{
			length--;
		}
	}
}
void PrintBoard(char board[][10])
{
	int rows = 6, cols = 7;
	for(int i = 1; i <= rows; i++)
	{
		for(int j = 1; j <= cols; j++)
		{
			if(board[i][j] != 'R' && board[i][j] != 'B')
			{
				board[i][j] = '_';
			}
			cout<<GREEN;
			cout<<"|";
			cout<<WHITE;
			cout<<board[i][j];		
		}
		cout<<MAGENTA;
		cout<<"|"<<endl;
		cout<<WHITE;
	}
	cout<<endl;
}
int CheckFour(char board[][10], Player active)
{
	char activeID = active.id;
	int win = 0;

	for(int i = 8; i >= 1; i--)
	{
		for(int j = 9; j >= 1; j--)
		{
			if(board[i][j] == activeID && board[i-1][j-1] == activeID && 
				board[i-2][j-2] == activeID && board[i-3][j-3] == activeID)
			{
				win = 1;
			}

			if(board[i][j] == activeID && board[i][j-1] == activeID &&
				board[i][j-2] == activeID && board[i][j-3] == activeID)
			{
				win = 1;
			}
					
			if(board[i][j] == activeID && board[i-1][j] == activeID &&
				board[i-2][j] == activeID && board[i-3][j] == activeID)
			{	
				win = 1;
			}
					
			if(board[i][j] == activeID && board[i-1][j+1] == activeID &&
				board[i-2][j+2] == activeID && board[i-3][j+3] == activeID)
			{
				win = 1;
			}
						
			if(board[i][j] == activeID && board[i][j+1] == activeID &&
				 board[i][j+2] == activeID && board[i][j+3] == activeID)
			{
				win = 1;
			}
		}
	}
	return win;
}
int FullBoard(char board[][10])
{
	int full = 0;
	for(int i = 1; i <= 7; i++)
	{
		if(board[1][i] != '_')
		{
			full++;
		}
	}
	return full;
}
void Winner(Player active)
{
	if(active.id == 'R')	cout<<RED;
	if(active.id == 'B')	cout<<BLUE;

	cout<<active.name<<" Connected Four!"<<endl;
	cout<<active.name<<" is the WINNER!"<<endl;
	cout<<WHITE;
}
void Rules()
{
	cout<<MAGENTA;
	cout<<"                      RULES OF THE BELOVED GAME ARE BELOW:"<<endl<<endl;
  cout<<"This game will be played between 2 players"<<endl;
	cout<<"1) Player 1 will be RED & Player 2 will be BLUE."<<endl;
	cout<<"2) By default the board is 6X7."<<endl;
	cout<<"3) WIN CONDITIONS ARE BELOW,"<<endl;
  cout<<"    a) If any 1 of the player matches the fills the 4 boxes horizontally "<<endl;
  cout<<"    b) If any 1 of the player matches the fills the 4 boxes vertically "<<endl;
  cout<<"    c) If any 1 of the player matches the fills the 4 boxes diagnolly "<<endl;  
	cout<<"4)GAME DRAW: If no one wins + board is full."<<endl<<endl<<endl;
	cout<<WHITE;
}
int main()
{
	Player playerOne, playerTwo;
	char board[9][10]; 
	int trueWidth = 7; 
	int trueLength = 6; 
	int choice, win, full, again;
	cout<<CLRSCR;
  cout<<RED;
  cout<<"***********************************************************************************************************************************"<<endl;
  cout<<"***********************************************************************************************************************************"<<endl;
  cout<<"***********************************************************************************************************************************"<<endl;
  cout<<"*********************                  WELCOME TO THE RETRO GAME: CONNECT4          *******************************************"<<endl<<endl;
  cout<<"***********************************************************************************************************************************"<<endl;
  cout<<"***********************************************************************************************************************************"<<endl;
  cout<<"***********************************************************************************************************************************"<<endl;
	srand(time(NULL));
	sleep(3);

	Rules();
	sleep(5);
	cout<<CLRSCR;
	playerOne.id = 'R';
	playerTwo.id = 'B';
	full = 0;
	win = 0;
	PrintBoard(board);
	do
	{
		choice = PlayerInput(board, playerOne);
		CheckTurn(board, playerOne, choice);
		cout<<endl;
		PrintBoard(board);
		win = CheckFour(board, playerOne);
		if(win == 1)
		{
			Winner(playerOne);
			break;
		}

		choice = PlayerInput(board, playerTwo);
		CheckTurn(board, playerTwo, choice);
		cout<<endl;
		PrintBoard(board);
		win = CheckFour(board, playerTwo);
		if(win == 1)
		{
			Winner(playerTwo);
			break;
		}
		full = FullBoard(board);
		if(full == 7)
		{
			cout<<"The board is full, GAME DRAW!" << endl;
			break;
		}
	}while(win != 1 || full != 7);
return 0;
}