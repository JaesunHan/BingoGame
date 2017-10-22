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

	init(computerBingoPan);				//��ǻ�� �������� �����ϱ� ���� ���� 1~25������ ������ �������迭�� ���������� �����Ѵ�.
	shuffleBingoPan(computerBingoPan);	// �״��� ���´�.
	init(playerBingoPan);				//�÷��̾ ���� ������� �Ѵ�.
	shuffleBingoPan(playerBingoPan);
	
	/*
	//�Ʒ� �ڵ�� ����ڰ� ���� �������� �����ϴ� �κ��ε�, �׳� ����� �����ǵ� �������� �����ϴ� �ɷ� �ٲ�
	cout << "����� ��������??( 1~ 25 ������ ���ڸ� �Է��ϼ���)" << endl;

	//���ڸ� �Է¹ް�
	for (int i = 0; i < totalNum; i++) {
		cin >> playerSetN[i];
		if (playerSetN[i] > 25 || playerSetN[i]<=0) {	// �������� ���ڸ� �Է��ϸ� �ٽ� �Է¹ޱ�
			cout << "1~ 25 ������ ���ڸ� �Է��ϼ���" << endl;
			i--;
		}
		for (int j = 0; j < i; j++) {
			if (playerSetN[i] == playerSetN[j]) {		// �ߺ��� ���ڸ� �Է��ϸ� �ٽ� �Է¹ޱ�
				cout << "�ߺ��� ���ڸ� �Է��߾�. �ٽ� �Է��ض�" << endl;
				i--;
			}
		}
	}
	//�Է¹��� ���ڸ� ���߹迭�� �����Ұ���
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

//���� �������迭�� 1~25���� ���ڸ� ���������� �����Ѵ�.
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
	cout << endl << "�� �� �� �����Ƽ� ���ڸ� �����Ѵ�. ���� 5���� ���߸� �̱�. �׷� ���!" << endl;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	cout << "���� ���� : ";
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
					cout << "	��";
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
	for (int i = 0; i < MAX; i++) {			//���� ����
		if (doubleArray[i][0] == 35 && doubleArray[i][1] == 35&& doubleArray[i][2] == 35&& doubleArray[i][3] == 35&& doubleArray[i][4] == 35) {
			++Bingo;
		}
	}
	for (int i = 0; i < MAX; i++) {			//���� ����
		if (doubleArray[0][i] == 35 && doubleArray[1][i] == 35 && doubleArray[2][i] == 35 && doubleArray[3][i] == 35 && doubleArray[4][i] == 35) {
			++Bingo;
		}
	}
	//�밢�� ����
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
	cout << "���� ���� : ";
	cin >> pSelectNum;
	selectNum[selectIDX] = pSelectNum;
	//���� �ߺ� ���� ����ó��
	for (int i = 0; i < selectIDX;) {
		if (selectNum[i] == selectNum[selectIDX]) {	//�̹� �Է��ߴ� ���ڶ�� �ٽ� �Է� �޾Ƽ� �迭�� �����ض�.
			cout << "�̹� �ߴ� ������. �ٽ� �Է��ϼ�" << endl << "���� ���� : ";
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

	changeIntToSharp(computerBingoPan, pSelectNum);	//��ǻ�� �����ǿ��� �÷��̾ �� ���ڶ� ��ġ�ϴ� ���ڸ� #���� ġȯ
	changeIntToSharp(playerBingoPan, pSelectNum);	//����� �����ǿ��� �÷��̾ �� ���ڶ� ��ġ�ϴ� ���ڸ� #���� ġȯ
	
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

	changeIntToSharp(computerBingoPan, cSelectN);	//��ǻ�� �����ǿ��� ��ǻ�Ͱ� �� ���ڶ� ��ġ�ϴ� ���ڸ� #���� ġȯ
	changeIntToSharp(playerBingoPan, cSelectN);	//����� �����ǿ��� ��ǻ�Ͱ� �� ���ڶ� ��ġ�ϴ� ���ڸ� #���� ġȯ
	
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

