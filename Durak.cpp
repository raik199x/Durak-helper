//durak-helper (card game)
//made by AlexanderXD

#include <iostream>
#include <string.h>
#include <cstdio>
#include <Windows.h>

using namespace std;
int enter_card(char put[2]) {
	rewind(stdin);
	scanf_s("%c",&put[0]);
	if (put[0] == '\n')
		return 15;
	cin >> put[1];
	//exception
	if (put[0] == '~' && put[1] == '~')
		return 11;
	//case insensetive
	if (put[0] >= 'a' && put[0] <= 'z')
		put[0] -= 32;
	if (put[1] >= 'a' && put[1] <= 'z')
		put[1] -= 32;

	if (put[0] == 'E' && put[1] == 'T')
		return 12;
	else if (put[0] == 'I' && put[1] == 'T')
		return 13;
	else if (put[0] == 'G' && put[1] == 'G')
		return 14;

	if ((put[0] != '6' && put[0] != '7' && put[0] != '8' && put[0] != '9' && put[0] != '1' && put[0] != 'J' && put[0] != 'Q' && put[0] != 'K' && put[0] != 'T') || (put[1] != 'H' && put[1] != 'K' && put[1] != 'P' && put[1] != 'B')) {
		cout << "Error, wrong format, reset card" << endl;
		return 1;
	}
	else
		return 0;
}

int game_init(char cards[4][9], char my_cards[30][2], char enemy_cards[30][2], bool played[4][9]) {
	system("cls");
	cout << "Preparing program, write your cards (without space, case isensetive)\n6 - six\n7 - seven\n8 - eight\n9 - nine\n1 - ten\nJ - Jack\nQ - Queen\nK - King\nT - Ace\nH - hear, K - cross, P - pica, B - buba\n~~ - exit immidietly\n";
		//first of all i want to set all cards
	   // 0 - Heart
	  // 1 - Krest
	 // 2 - Pika
	// 3 - Buba
   // but this is our *silent* rule, because in the massiv that wount be mentioned
	for (int i = 0; i < 4; i++) {
		cards[i][0] = '6';
		cards[i][1] = '7';
		cards[i][2] = '8';
		cards[i][3] = '9';
		cards[i][4] = '1';
		cards[i][5] = 'J';
		cards[i][6] = 'Q';
		cards[i][7] = 'K';
		cards[i][8] = 'T';
	}
	//Now, set up played cards, it's simple, because on the start we've got all cards
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 9; j++)
			played[i][j] = 0;
	//enemy cards, that a bit easy, because on the start of game we dont know them, so, we just put "*"
	//on the start we have only 6 cards, so
	int i = 0;
	while (i < 6) {
		enemy_cards[i][0] = '*';
		enemy_cards[i][1] = '*';
		i++;
	}
	enemy_cards[6][0] = '\0'; //to set up end
	 //now, set up our cards
	//first of all, we need to take 2 parts (KH - where K, means name of card "king". H means type of card "heart")
	char put[2]; int success = 0, j = 0;
	for (i = 0; i < 6; i++) {
		success = enter_card(put); // i decided to make function, because we will use it in future
		if (success == 1) {
			i--;
			continue;
		}
		else if (success == 11)
			return 11;
		my_cards[i][0] = put[0];
		my_cards[i][1] = put[1];
	}
	my_cards[6][0] = '\0';
}

int check_card(char cards[4][9], char my_cards[30][2], char enemy_cards[30][2], bool played[4][9],int j, int i, char on_board[12][2]) {

	//first, check if card is already played
	if (played[j][i] == 1)
		return 1;

	//the thing before 2 coming checks, we need to know which type of card we are looking for
	char type;
	if (j == 0)
		type = 'H';
	else if (j == 1)
		type = 'K';
	else if (j == 2)
		type = 'P';
	else
		type = 'B';
	//Now, check if I had this card
	int num = 0;
	while (my_cards[num][0] != '\0') {
		if (my_cards[num][0] == cards[j][i] && my_cards[num][1] == type)
			return 2;
		num++;
	}
	// check if enemy has this card
	num = 0;
	while (enemy_cards[num][0] != '\0') {
		if (enemy_cards[num][0] == cards[j][i] && enemy_cards[num][1] == type)
			return 3;
		num++;
	}
	//if this card on board
	num = 0;
	while (on_board[num][0] != '\0') {
		if (on_board[num][0] == cards[j][i] && on_board[num][1] == type)
			return 4;
		num++;
	}
	//if this card somewhere in a deck
	return 5;
}

void output(char cards[4][9], char my_cards[30][2], char enemy_cards[30][2], bool played[4][9], char on_board[12][2]) {
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE); // this i need for colored text

	 //i want to put cards in table, so replace number of I and J
	//first of all, we need to put types of cards, to make in comfertable, i make all types of cards consist of 3 books
	cout << "Hea" << " " << "Kre" << " " << "Pik" << " " << "Bub" << endl << " ";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 4; j++) {
			int success = 0;
			success = check_card(cards, my_cards, enemy_cards, played, j, i, on_board); //i want to see, how i should represent the card to user

			if (success == 1) {  //if card already played
				cout << "    ";
				continue;
			}
			else if (success == 2) {
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << cards[j][i] << "   ";
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (success == 3) {
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << cards[j][i] << "   ";
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (success == 4) {
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << cards[j][i] << "   ";
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else {
				cout << cards[j][i] << "   ";
			}
		}
		cout << endl << " ";
	}
	cout << endl;
	//output of our *hands*
	SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("enemy cards: ");
	for (int i = 0; enemy_cards[i][0] != '\0'; i++)
		cout << enemy_cards[i][0] << enemy_cards[i][1] << " ";
	cout << endl << endl;

	SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("on board:    ");
	for (int i = 0; on_board[i][0] != '\0'; i++)
		cout << on_board[i][0] << on_board[i][1] << " ";

	cout << endl << endl;
	SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("my cards:    ");
	for (int i = 0; my_cards[i][0] != '\0'; i++)
		cout << my_cards[i][0] << my_cards[i][1] << " ";
	cout << endl << endl;
	SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void move_card(char someone_hand[30][2],char on_board[12][2],char put[2]) {
	for(int i=0; someone_hand[i][0] != '\0'; i++)
	{ 
		if ((someone_hand[i][0]==put[0])&&(someone_hand[i][1]==put[1]))
		{
			for(int j=0; ;j++)
			{ 
				if (on_board[j][0]=='\0')
				{ 
					on_board[j][0]=put[0];
					on_board[j][1]=put[1];
					on_board[j+1][0]='\0';
					break;
				}
			}
			do
			{
				someone_hand[i][0]=someone_hand[i+1][0];
				someone_hand[i][1]=someone_hand[i+1][1];
				i++;
			}while (someone_hand[i][0] != '\0');
			return;
		}
	}
	for(int i=0; someone_hand[i][0] != '\0'; i++)
	{ 
		if (someone_hand[i][0] == '*')
		{
			for(int j=0; ;j++)
			{ 
				if (on_board[j][0]=='\0')
				{ 
					on_board[j][0]=put[0];
					on_board[j][1]=put[1];
					on_board[j+1][0]='\0';
					break;
				}
			}			
			do
			{
				someone_hand[i][0]=someone_hand[i+1][0];
				someone_hand[i][1]=someone_hand[i+1][1];
				i++;
			}while (someone_hand[i][0] != '\0');
			return;
		}
	}
	puts("There is no card like that!\n");
	return;
}

void take_someone(char someone_cards[30][2],char on_board[12][2]) {
	int i = 0;
	for (i; someone_cards[i][0] != '\0'; i++)
		continue;
	int j = 0;
	while (on_board[j][0] != '\0') {
		someone_cards[i][0] = on_board[j][0];
		someone_cards[i][1] = on_board[j][1];
		i++; j++;
	}
	someone_cards[i][0] = '\0';
	on_board[0][0] = '\0';
	return;
}

void set_played(char on_board[12][2],bool played[4][9]) {
	int i, j, probeg = 0;
	while (on_board[probeg][0] != '\0') {
		switch (on_board[probeg][0]) {
		case '6': i = 0; break;
		case '7': i = 1; break;
		case '8': i = 2; break;
		case '9': i = 3; break;
		case '1': i = 4; break;
		case 'J': i = 5; break;
		case 'Q': i = 6; break;
		case 'K': i = 7; break;
		case 'T': i = 8; break;
		default: return;
		}
		switch (on_board[probeg][1]){
		case 'H': j = 0; break;
		case 'K': j = 1; break;
		case 'P': j = 2; break;
		case 'B': j = 3; break;
		default: return;
		}
		played[j][i] = 1;
		probeg++;
	}
	return;
}

void deck(int& in_deck, char my_cards[30][2], char enemy_cards[30][2], bool played[4][9]) {
	int new_deck = 0, i = 0;
	//amount cards in our hand
	for (i; my_cards[i][0] != '\0'; i++)
		continue;
	new_deck += i;
	i = 0;
	//amount cards in enemy hand
	for (i; enemy_cards[i][0] != '\0'; i++)
		continue;
	new_deck += i;
	i = 0;
	//already played cads
	for(int z = 0; z < 4;z++)
		for (int x = 0; x < 9; x++) {
			if (played[z][x] == 1)
				i++;
			else
				continue;
		}
	new_deck += i;
	in_deck = 36 - new_deck;  //our amount of cards
}

void refresh_hand(char someone_hand[30][2], int send) {
	int i = 0;
	if (send == 2) {
		for (i = 0; someone_hand[i][0] != '\0'; i++)
			continue;
		if (i >= 6)
			return;
		for (i; i < 6; i++) {
			someone_hand[i][0] = '*';
			someone_hand[i][1] = '*';
		}
		someone_hand[i + 1][0] = '\0';
		return;
	}
	else {
		printf("enter your new cards\n>");
		for (i = 0; someone_hand[i][0] != '\0'; i++)
			continue;
		if (i >= 6)
			return;
		char put[2];
		for (i; i < 6; i++) {
			int calc = enter_card(put);
			if (calc == 1) {
				i--;
				continue;
			}
			someone_hand[i][0] = put[0];
			someone_hand[i][1] = put[1];
		}
		someone_hand[i + 1][0] = '\0';
		return;
	}

}

void show_enemy(char cards[4][9],char my_cards[30][2],char enemy_cards[30][2],bool played[4][9]) {
	static int reveal = 0;
	if (reveal == 1) {
		printf("enemy cards are shown!\n");
		return;
	}
	reveal++;
	int set = 0;
	for (int i = 0; i < 4; i++) {
		char type;
		if (i == 0)
			type = 'H';
		else if (i == 1)
			type = 'K';
		else if (i == 2)
			type = 'P';
		else
			type = 'B';
		for (int j = 0; j < 9; j++) {
			if (played[i][j] == 1)
				continue;
			int probeg = 0;
			while (my_cards[probeg][0] != '\0') {
				if (my_cards[probeg][0] == cards[i][j] && my_cards[probeg][1] == type) {
					probeg = 99;
					break;
				}
				probeg++;
			}
			if (probeg != 99) {
				enemy_cards[set][0] = cards[i][j];
				enemy_cards[set][1] = type;
				set++;
			}
		}
	}
	enemy_cards[set + 1][0] = '\0';
	return;
}

int check_end(int &in_deck,char my_cards[30][2], char enemy_cards[30][2],bool played[4][9],char cards[4][9],int &win) {
	system("cls");
	if (in_deck != 0)
		deck(in_deck, my_cards, enemy_cards, played);          // check, how many cards left
	else if (my_cards[0][0] == '\0' && enemy_cards[0][0] == '\0') {
		win = 3;
		return 1;
	}
	else if (my_cards[0][0] == '\0') {
		win = 0;
		return 1;
	}
	else if (enemy_cards[0][0] == '\0') {
		win = 1;
		return 1;
	}
	return 0;
}

int main() {

	char cards[4][9],my_cards[30][2],enemy_cards[30][2],on_board[12][2];
	bool played[4][9], game = 1;

	if (game_init(cards, my_cards, enemy_cards, played) == 11)
		return 0;

	system("cls");
	int move; // 0 - you 1 - enemy
	cout << "0 - your move" << " " << "1 - opponent move" << endl << ">";
	cin >> move;
	if (move < 0 || move > 1)
		return 0;
	int in_deck = 36, win = 20, round_move; //about win if 0 - you win if 1 - you loose if 3 - draw
	while (game) {
		round_move = move;
		on_board[0][0] = '\0';
		if (check_end(in_deck, my_cards, enemy_cards, played, cards, win) == 1)
			break;
		if (in_deck != 0) {
			output(cards, my_cards, enemy_cards, played, on_board);
			if (game == 1)
				refresh_hand(my_cards, 1);
			else
				refresh_hand(enemy_cards, 2);
			check_end(in_deck, my_cards, enemy_cards, played, cards, win);
			if (in_deck != 0) {
				if (game == 1)
					refresh_hand(enemy_cards, 2);
				else
					refresh_hand(my_cards, 2);
			}
		}
		system("cls");
		if (in_deck == 0)
			show_enemy(cards, my_cards, enemy_cards, played);
		//enter cards
		char put[2]; put[0] = '\0';
		while (put[0] != '\n') {
			system("cls");
			output(cards, my_cards, enemy_cards, played, on_board);
			printf("\n\tWrite cards on board (double enter to stop writting)\n");
			if (move % 2 == 0)
				printf("et - enemy take\ngg -cards played\n>");
			else
				printf("it - i take\ngg - cards played\n");
			if (round_move % 2 == 0)
				printf("now is your turn to put card\n>");
			else
				printf("now is enemy turn to put cards\n>");
			int side = enter_card(put);
			if (side == 15) {
				round_move++;
				put[0] = '\0';
				continue;
			}
			switch (side){
			case 0: if(round_move % 2 == 0) move_card(my_cards,on_board,put); else move_card(enemy_cards, on_board, put); break;
			case 1: continue; break;
			case 11: return 0;
			case 12: take_someone(enemy_cards, on_board); put[0] = '\n'; break;
			case 13: take_someone(my_cards, on_board); put[0] = '\n'; break;
			case 14: set_played(on_board, played); if (move == 0) move = 1; else move = 0; break;
			}
			if (side == 12 || side == 13 || side == 14)
				break;
		}

		rewind(stdin);
	}
	switch (win){
	case 0: printf("nice win bro, thanks for playing!\n;"); return 0;
	case 1: printf("mission failed, better luck next time\n"); return 0;
	case 3: printf("draw, nobody wins...\n"); return 0;
	default: return 0;
	}
}