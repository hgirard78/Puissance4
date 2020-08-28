#include<iostream>
#include<string>
#include<chrono>
#include<sstream>
#include<thread>
using namespace std;

enum class ansi_color_code: int{
	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,
	magenta = 35,
	cyan = 36,
	white = 37,
	bright_black = 90,
    bright_red=91,
    bright_green=92,
    bright_yellow=93,
    bright_blue=94,
    bright_magenta=95,
    bright_cyan=96,
    bright_white=97,
};

template<typename printable>
string print_as_color(printable const& value, ansi_color_code color){
	stringstream sstr;
	sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
	return sstr.str();
}

template<ansi_color_code color, typename printable>
string print_as_color(printable const& value){
	stringstream sstr;
	sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
	return sstr.str();
}

void printGrid(int **tab){
	cout << "    ";
	for (int j = 0; j < 7; j++)
		cout << j << "   ";
	cout << endl;
	cout << "  ";
	for (int k = 0; k < 29; k++)
			cout << "-";
		cout << endl;
	for (int i = 0; i < 6; i++){
		cout << i << " ";
		for (int j = 0; j < 7; j++){
			cout << "| ";
			if (tab[i][j] == 1)
				cout << print_as_color<ansi_color_code::red>(tab[i][j]) << " ";
			else if (tab[i][j] == 2)
				cout << print_as_color<ansi_color_code::blue>(tab[i][j]) << " ";
			else
				cout << tab[i][j] << " ";
		}
		cout << "|" << endl;
		cout << "  ";
		for (int k = 0; k < 29; k++)
			cout << "-";
		cout << endl;
	}
}

bool isFinish(int** tab){
	for (int i = 5; i >= 3; i--){
		for (int j = 0; j < 7; j++){
			int val = tab[i][j];
			if ((val == 1 || val == 2) && tab[i - 1][j] == val && tab[i - 2][j] == val && tab[i - 3][j] == val)
				return true;
			if (j < 4 && (val == 1 || val == 2) && tab[i - 1][j + 1] == val && tab[i - 2][j + 2] == val && tab[i - 3][j + 3] == val)
				return true;
			if (j > 2 && (val == 1 || val == 2) && tab[i - 1][j - 1] == val && tab[i - 2][j - 2] == val && tab[i - 3][j - 3] == val)
				return true;
		}
	}

	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 4; j++){
			int val = tab[i][j];
			if ((val == 1 || val == 2) && tab[i][j + 1] == val && tab[i][j + 2] == val && tab[i][j + 3] == val)
				return true;
		}
	}

	return false;
}

bool placerPion(int** tab, int player){
	int col;
	cout << "Entrez la colonne où placer le pion : " << endl;
	cout << "x: ";
	cin >> col;
	cout << endl;
	if (tab[0][col] != 0){
		cout << "Erreur, vous ne pouvez pas placer de pion dans cette colonne, veuillez choisir une autre colonne non pleine." << endl;
		return false;
	}
	else
	{
		for (int i = 5; i >= 0; i--){
			if (tab[i][col] == 0){
				tab[i][col] = player;
				return true;
			}
		}
	}
	
}

void play(int **tab){
	int player = 1;
	bool finished = isFinish(tab);
	while(!finished){
		printGrid(tab);
		cout << "Player: " << player << endl;
		bool played = placerPion(tab, player);
		if(played && player == 1){
			player = 2;
			played = false;
		}
		if(played && player == 2){
			player = 1;
			played = false;
		}
		
		finished = isFinish(tab);
	}
	printGrid(tab);
	if(player == 2)
		player = 1;
	else
		player = 2;
	cout << "Bravo au joueur " << player << " !";
}
int main(int argc, char *argv[])
{
	cout << print_as_color<ansi_color_code::bright_green>("           PUISSANCE 4") << endl;
	//Créer le tableau dynamiquement
	int nbRow = 6, nbCol = 7;
	int **tab = new int* [nbRow];
	for (int i = 0; i < nbRow; i++){
		tab[i] = new int [nbCol];
		for (int j = 0; j < nbCol; j++)
			tab[i][j] = 0;
	}
	//Utiliser le tableau
	play(tab);
	//Détruire le tableau
	for (int i = 0; i < nbRow; i++)
		delete[] tab[i];
	delete[] tab;
}