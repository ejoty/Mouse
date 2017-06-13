#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

void testQuit(int a);

bool quit, reachedErised;
int xCheese, yCheese;

int getKey(int input){
	if (_kbhit()){
		input = _getch();
		if (input != 0);
			return input;
	}
}
// a change
int speedBoost(bool boosting, int *speed){
	int hungerTickSpeed;
	if (boosting){
		hungerTickSpeed += 10;
		*speed = 2;
	}
	else {
		hungerTickSpeed -= 10;
		*speed = 1;
	}
	return hungerTickSpeed;
}

int xRNG(int randx, int difficulty){
	int tempx = randx - (rand() % (difficulty * 2 + 1) - difficulty);
	if (tempx < 0)
		tempx = 0;
	if (tempx > 24)
		tempx = 24;
	return tempx;
}

int yRNG(int randy, int difficulty){
	int tempy = randy - (rand() % (difficulty * 2 + 1) - difficulty);
	if (tempy < 0)
		tempy = 0;
	if (tempy > 24)
		tempy = 24;
	return tempy;
}

int disp(int input, char selectedChar, char selectedErised, int score, int xCoord, int yCoord, bool boosting, int hunger, int xCheese, int yCheese, int numCheeseEaten, int timeFrame, bool quit){
	cout << "Score: " << score /*<< " Boosting: "*/;
	/*
	if (boosting)
		cout << "true";
	else
		cout << "false";
	*/
	cout << " Number of Cheese Eaten: " << numCheeseEaten << endl;
	int tempInt = hunger / 20;
	for (int b = tempInt; b >= 0; b--)
		cout << " +";
	cout << endl;
	int a = getKey(input);
	testQuit(a);
	if (yCoord < 0)
		yCoord = 0;
	if (yCoord > 24)
		yCoord = 24;
	if (xCoord < 0)
		xCoord = 0;
	if (xCoord > 24)
		xCoord = 24;
	if (yCoord < yCheese){
		yCheese -= yCoord;
		for (int b = yCoord; b >= 0; b--)
			cout << endl;
		for (int b = xCoord; b >= 0; b--)
			cout << "  ";
		cout << selectedChar;
		for (int b = yCheese; b >= 0; b--)
			cout << endl;
		for (int b = xCheese; b >= 0; b--)
			cout << "  ";
		cout << selectedErised;
	}
	else if (yCoord == yCheese){
		for (int b = yCoord; b >= 0; b--)
			cout << endl;
		if (xCoord < xCheese){
			xCheese -= (xCoord + 1);
			for (int b = xCoord; b >= 0; b--)
				cout << "  ";
			cout << selectedChar;
			for (int b = xCheese; b >= 0; b--)
				cout << "  ";
			cout << selectedErised;
		}
		else if (xCoord == xCheese){
			reachedErised = true;
			for (int b = xCoord; b >= 0; b--)
				cout << "  ";
			cout << selectedChar;
		}
		else {
			xCoord -= (xCheese + 2);
			for (int b = xCheese; b >= 0; b--)
				cout << "  ";
			cout << selectedErised;
			for (int b = xCoord; b >= 0; b--)
				cout << "  ";
			cout << ' ' << selectedChar;
		}
	}
	else {
		yCoord -= (yCheese + 1);
		for (int b = yCheese; b >= 0; b--)
			cout << endl;
		for (int b = xCheese; b >= 0; b--)
			cout << "  ";
		cout << selectedErised;
		for (int b = yCoord; b >= 0; b--)
			cout << endl;
		for (int b = xCoord; b >= 0; b--)
			cout << "  ";
		cout << selectedChar;
	}
	a = getKey(input);
	testQuit(a);
	Sleep(timeFrame * 10);
	system("cls");
	a = getKey(input);
	testQuit(a);
	return a;
}

bool ateCheese(int *numCheeseEaten, int *hunger, int *hungerTickSpeed, int *score){
	*numCheeseEaten += 1;
	*hunger = 500;
	*hungerTickSpeed += 1;
	*score += 500;
	xCheese = rand() % 24;
	yCheese = rand() % 24;
	return false;
}

void testQuit(int a){
	if (a == 113)
		quit = true;
}

int main(){
	srand(time(NULL));
	cout << "Follow your dreams until they kill you with starvation.\n";
	//highscore: 8323 at speed 1, timeframe 10
	char selectedChar;
	char selectedErised;
	int difficulty;
	int timeFrame;
	cout << "Pick your character: ";
	cin >> selectedChar;
	cout << "Type what you see in the Mirror of Erised: ";
	cin >> selectedErised;
	cout << "Evasiveness of your dream: ";
	cin >> difficulty;
	cout << "Time frame of your dream: ";
	cin >> timeFrame;
	int input = 0;
	int xCoord = 12;
	int yCoord = 12;
	int speed = 1;
	bool boosting = false; //5 boosts, increases hunger tick, hitting 5 again goes back down
	int hunger = 500;
	int hungerTickSpeed = 1;
	int score = 0;
	int numCheeseEaten = 0;
	quit = false;
	reachedErised = false;
	xCheese = rand() % 24;
	yCheese = rand() % 24;

	while (!quit && hunger > 0){
		int a = disp(input, selectedChar, selectedErised, score, xCoord, yCoord, boosting, hunger, xCheese, yCheese, numCheeseEaten, timeFrame, quit);
		testQuit(a);
		if (quit)
			break;
		if (reachedErised)
			reachedErised = ateCheese(&numCheeseEaten, &hunger, &hungerTickSpeed, &score);
		score++;
		switch (a){
		case 49:
			xCoord -= speed;
			yCoord += speed;
			break;
		case 50:
			yCoord += speed;
			break;
		case 51:
			xCoord += speed;
			yCoord += speed;
			break;
		case 52:
			xCoord -= speed;
			break;
		/*case 53:
			hungerTickSpeed = speedBoost(boosting, &speed);
			break;*/
		case 54:
			xCoord += speed;
			break;
		case 55:
			xCoord -= speed;
			yCoord -= speed;
			break;
		case 56:
			yCoord -= speed;
			break;
		case 57:
			xCoord += speed;
			yCoord -= speed;
			break;
		default:
			break;
		}
		xCheese = xRNG(xCheese, difficulty);
		yCheese = yRNG(yCheese, difficulty);
		hunger -= hungerTickSpeed;
		a = getKey(input);
		testQuit(a);
	}
	if (hunger <= 0)
		cout << "You died curled up alone in a dank corner. Your cause of death was loneliness, hunger, or a sudden apathy for life.\n" << endl;
	cout << "Your final score: " << score << endl << endl;
	Sleep(1000);
}
