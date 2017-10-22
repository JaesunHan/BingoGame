#include <iostream>
#include <time.h>
//#include <stdlib.h> 

#define MAX 5
#define totalNum 25
using namespace std;

int playerBingoPan[MAX][MAX], computerBingoPan[MAX][MAX];
int selectNum[totalNum];
int selectIDX = 0;
int pBingo = 0, cBingo = 0;

void init(int doubleArray[MAX][MAX]);
void shuffleBingoPan(int doubleArray[MAX][MAX]);
void printAllBingoPan();
int isItBingo(int doubleArray[MAX][MAX], int Bingo);
void playerTurn();
void computerTurn();
void changeIntToSharp(int doubleArray[MAX][MAX], int n);

int main() {
	srand(time(NULL));

	init(computerBingoPan);				//컴퓨터 빙고판을 세팅하기 위해 먼저 1~25까지의 숫차를 이차원배열에 순차적으로 저장한다.
	shuffleBingoPan(computerBingoPan);	// 그다음 섞는다.
	init(playerBingoPan);				//플레이어도 같은 방식으로 한다.
	shuffleBingoPan(playerBingoPan);
	
	/*
	//아래 코드는 사용자가 직접 빙고판을 세팅하는 부분인데, 그냥 사용자 빙고판도 랜덤으로 세팅하는 걸로 바꿈
	cout << "당신의 빙고판은??( 1~ 25 사이의 숫자만 입력하세요)" << endl;

	//숫자를 입력받고
	for (int i = 0; i < totalNum; i++) {
		cin >> playerSetN[i];
		if (playerSetN[i] > 25 || playerSetN[i]<=0) {	// 범위밖의 숫자를 입력하면 다시 입력받기
			cout << "1~ 25 사이의 숫자만 입력하세요" << endl;
			i--;
		}
		for (int j = 0; j < i; j++) {
			if (playerSetN[i] == playerSetN[j]) {		// 중복된 숫자를 입력하면 다시 입력받기
				cout << "중복된 숫자를 입력했어. 다시 입력해라" << endl;
				i--;
			}
		}
	}
	//입력받은 숫자를 이중배열에 저장할거임
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			playerBingoPan[i][j] = playerSetN[cnt++];
		}
	}
	cnt = 0;
	*/
	
	while (true) {
		printAllBingoPan();
		playerTurn();
		computerTurn();
		if (cBingo == pBingo && pBingo >5) {
			cout << "???	DRAWN		???" << endl;
			break;
		}

		if (pBingo >= 5) {
			printAllBingoPan();
			cout << "!!!	YOU WIN		!!!" << endl;
			break;
		} 
		if (cBingo >= 5) {
			printAllBingoPan();
			cout << "T-T	YOU LOSE	T-T" << endl;
			break;
		}
	}
	return 0;
}

//먼저 이차원배열에 1~25까지 숫자를 순차적으로 저장한다.
void init(int doubleArray[MAX][MAX]) {
	int cnt = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			doubleArray[i][j] = ++cnt;
		}
	}
}

void shuffleBingoPan(int doubleArray[MAX][MAX]) {
	int shuffle1, shuffle2, shuffle3, shuffle4, tmp;
	int cnt = 0;
	for (int i = 0; i < 30; i++) {
		shuffle1 = rand() % 5;
		shuffle2 = rand() % 5;
		shuffle3 = rand() % 5;
		shuffle4 = rand() % 5;
		tmp = doubleArray[shuffle1][shuffle2];
		doubleArray[shuffle1][shuffle2] = doubleArray[shuffle3][shuffle4];
		doubleArray[shuffle3][shuffle4] = tmp;
	}
}

void printAllBingoPan() {
	system("cls");
	cout << "-----------------------------------------------BINGO GAME-----------------------------------------------" << endl;
	cout << endl << "한 턴 씩 번갈아서 숫자를 선택한다. 먼저 5빙고를 맞추면 이김. 그럼 즐겜!" << endl;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	cout << "숫자 스택 : ";
	for (int i = 0; i < selectIDX; i++) {
		cout << "\t" << selectNum[i];
	}
	cout << endl << endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX * 2; j++) {
			if (j < 5) {
				if (computerBingoPan[i][j] == 35) { 
					cout << "	#"; 
				}
				else
				{
					cout << "	□";
				}
				if (j == 4)	cout << "\t || \t";
			}
			else if (j >= 5) {
				if (playerBingoPan[i][j - MAX] == 35) {
					cout << "	#";
				}
				else {
					cout << "	" << playerBingoPan[i][j - MAX];
				}
			}
		}
		cout << endl << endl;
	}
	cout << "		-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+score-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+		" << endl;
	cout << "Computer : "<<cBingo <<" Bingo!\t\t\t\tvs\t\t\t\tPlayer : " << pBingo << "Bingo!"  <<endl;
}

int isItBingo(int doubleArray[MAX][MAX], int Bingo) {
	Bingo = 0;
	for (int i = 0; i < MAX; i++) {			//가로 빙고
		if (doubleArray[i][0] == 35 && doubleArray[i][1] == 35&& doubleArray[i][2] == 35&& doubleArray[i][3] == 35&& doubleArray[i][4] == 35) {
			++Bingo;
		}
	}
	for (int i = 0; i < MAX; i++) {			//세로 빙고
		if (doubleArray[0][i] == 35 && doubleArray[1][i] == 35 && doubleArray[2][i] == 35 && doubleArray[3][i] == 35 && doubleArray[4][i] == 35) {
			++Bingo;
		}
	}
	//대각선 빙고
	if (doubleArray[0][0] == 35 && doubleArray[1][1] == 35 && doubleArray[2][2] == 35 && doubleArray[3][3] == 35 && doubleArray[4][4] == 35) {
		++Bingo;
	}
	if (doubleArray[0][4] == 35 && doubleArray[1][3] == 35 && doubleArray[2][2] == 35 && doubleArray[3][1] == 35 && doubleArray[4][0] == 35) {
		++Bingo;
	}
	return Bingo;
}

void playerTurn() {
	int pSelectNum = 0;
	int checkIDX = 0;
	cout << "숫자 선택 : ";
	cin >> pSelectNum;
	selectNum[selectIDX] = pSelectNum;
	//숫자 중복 선택 예외처리
	for (int i = 0; i < selectIDX;) {
		if (selectNum[i] == selectNum[selectIDX]) {	//이미 입력했던 숫자라면 다시 입력 받아서 배열에 저장해라.
			cout << "이미 했던 숫자임. 다시 입력하셈" << endl << "숫자 선택 : ";
			cin >> pSelectNum;
			selectNum[selectIDX] = pSelectNum;
			i = 0;
		}
		else {
			i++;
		}
	}
	cout << endl << endl;
	selectIDX++;

	changeIntToSharp(computerBingoPan, pSelectNum);	//컴퓨터 빙고판에서 플레이어가 고른 숫자랑 일치하는 숫자를 #으로 치환
	changeIntToSharp(playerBingoPan, pSelectNum);	//사용자 빙고판에서 플레이어가 고른 숫자랑 일치하는 숫자를 #으로 치환
	
	pBingo = isItBingo(playerBingoPan, pBingo);
	cBingo = isItBingo(computerBingoPan, pBingo);
}
void computerTurn() {
	srand(time(NULL));
	int cSelectN = rand() % 25 + 1;
	selectNum[selectIDX] = cSelectN;

	for (int i = 0; i < selectIDX;) {
		if (selectNum[i] == cSelectN) {
			cSelectN = rand() % 25 + 1;
			selectNum[selectIDX] = cSelectN;
			i = 0;
		}
		else
		{
			i++;
		}
	}
	selectIDX++;

	changeIntToSharp(computerBingoPan, cSelectN);	//컴퓨터 빙고판에서 컴퓨터가 고른 숫자랑 일치하는 숫자를 #으로 치환
	changeIntToSharp(playerBingoPan, cSelectN);	//사용자 빙고판에서 컴퓨터가 고른 숫자랑 일치하는 숫자를 #으로 치환
	
	cBingo = isItBingo(computerBingoPan, cBingo);
	pBingo = isItBingo(playerBingoPan, cBingo);
}

void changeIntToSharp(int doubleArray[MAX][MAX], int num) {
	for (int i = 0;i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (doubleArray[i][j] == num) {
				doubleArray[i][j] = 35;
			}
		}
	}
}

