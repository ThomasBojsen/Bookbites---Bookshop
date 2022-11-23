#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<stdio.h>
#include<cstdlib>
#include<cstdio>
#include<stdbool.h>
#include<iomanip>
#include<errno.h>
#include<conio.h>
#define books_SIZE 1024
#define MAX_LINE 2048


using namespace std;



//APPLIBRARY
//MENU
//	-Book management system
//		-Admin login
//			-Add book
//			-Display Books
//			-(Delete Books)
//		-Staff login 
//		-Guest login
//	-Snake Game
//		-Login
//		-Guest login
//			-Play
//			-Highscores
//			-Difficulty
//				-Easy
//				-Medium
//				-Hard
//	-Change font size
//	-Change theme
//		- Back
//		-White
//  -Exit
//
//
//
//



// Definitioner til Snake game
bool gameOver;
int width = 40;
int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // Koordinaterne til slangens hale
int nTail;	// Længden af halen
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

// MENU til snake
void SnakeOptions()
{
	system("pause");
	system("cls");

	cout << "\n\n\tWELCOME TO SNAKE MENU" << endl;
	cout << "\t=========================" << endl;
	cout << "\n\t1 : PLAY" << endl;
	cout << "\n\t2 : HIGHSCORES" << endl;
	cout << "\n\t3 : DIFFICULTY" << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

void DifficultyOptions()
{
	system("pause");
	system("cls");

	cout << "\n\n\tDIFFICULTY" << endl;
	cout << "\t=========================" << endl;
	cout << "\n\t1 : EASY" << endl;
	cout << "\n\t2 : MEDIUM" << endl;
	cout << "\n\t3 : HARD" << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}


//Funktioner til snake game:
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2; // Beskriver slangens koordinater
	y = height / 2; // -||-
	fruitX = rand() % width; // beskriver frugtens koordinater
	fruitY = rand() % height; // -||-
	score = 0;

}

// Princip af spillebanen:
//  ######
//  #    #
//  ######
// Princip af slangen:
// Ooooo

void Draw()
{
	system("cls"); // clearer skærmen
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) // i = højde
	{
		for (int j = 0; j < width; j++) // j = bredde
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false; //Holder styr på om vi printer halen eller ej
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;

					}
					
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}


	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	cout << "\nScore:" << score << endl;

}

void Input() // Her bestemmer jeg hvilke knappe der skal styre controls
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}


}

void Logic() // Her beskriver jeg kontrols:
{
	int prevX = tailX[0]; //tidligere koordinater
	int prevY = tailY[0]; // -||-
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;


	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}


	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y>height || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width; 
		fruitY = rand() % height;

		nTail++;

	}

}




int error;
void Login(string& admin, string& password); // admin login funktion
void staff(string& user, string& pass1);     // staff login funktion


// Her angiver jeg en funktion for adminmenu
void adminMenu();

// options er her tilsvarende til selve menuerne
void AdminOptions();
void DeleteOptions();
void SearchOptions();
void AddBooksOptions();
void DisplayBooksOptions();


//funktion til at skifte skriftstørelse
void fontsize()
{
	short font, x, y;

	do
	{
		error = 0;
		cout << "\n\t Enter font size : ";
		cin >> font;
		if (font >= 25 || font <= 5)
		{
			cout << "\t Please enter font size, less than 25 & greater than 5:" << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
		if (cin.fail())
		{
			cout << "\t Please enter a valid input:" << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	x = font;  // her bliver fontsize defineret som x
	y = 2 * x;
	HANDLE Hout = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD fsize = { x, y };
	CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
	::GetCurrentConsoleFontEx(Hout, FALSE, &Font);

	Font.dwFontSize = fsize;
	SetCurrentConsoleFontEx(Hout, 0, &Font);
	cin.clear();
	system("cls");

}

// Password asterisk generator  -  funkton til at skjulle password (asterisk)
string getpass(const char* prompt, bool show_asterisk = true)
{
	const char BACKSPACE = 8; //maksimum antal karakterer for password
	const char RETURN = 13; // maksimum antal karakterer der kan indtastes
	string password;
	unsigned char ch = 0; // Den gør så hele passwordet bliver opfattet som en enkelt karakter
	cout << "\n\n\t" << prompt;
	DWORD con_mode; // aktiverer console mode
	DWORD dwRead;   // Read only funktion
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hIn, &con_mode);
	SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)); // den tager altså endten den ene parameter i denne linje eller den anden.

	while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
	{
		if (ch == BACKSPACE) // hvis brugern trykker på backspace så:
		{
			if (password.length() != 0) // hvis password længden ikke er 0, aktiveres en ny if funktion
			{
				if (show_asterisk) // denne nye if funktion sletter en karakter 
					cout << "\b\b";
				password.resize(password.length() - 1);
			}
		}
		else
		{
			password += ch; // hvis der ikke bliver trykket backspace så bliver der derimod tilføjet et nyt asterisk tegn *
			if (show_asterisk)
				cout << '*';
		}
	}
	cout << endl;
	return password;
}

// Funktion til at skifte baggrundstema/farve
void color()
{
	int col;
	cout << "\n\t 1. Black and White theme" << endl;
	cout << "\n\t 2. White and Black theme  \n\n\t 0. Return" << endl;

	do
	{
		do
		{
			error = 0;
			cout << "\n\t Enter your selection here:";
			cin >> col;
			if (cin.fail())
			{
				cout << "\n\t Please enter a valid input." << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		if (col == 1)
		{
			system("color 0F");
			system("cls");
			return;
		}
		else if (col == 2)
		{
			system("color F0");
			system("cls");
			return;
		}
	} while (col != 0);
	system("cls");
}




// Main funktion
int main()
{
	fstream Highscore;
	string firstName, lastName, score;
	int choice;
	// Jeg definere en variable choice

	string User, password;
	cout << "\n\n\t WELCOME TO THOMAS' APP LIBRARY" << endl;
	cout << "\n\t ************ MENU ***************" << endl;

	// Nu printer jeg først menuen
	// Derefter laver jeg et do-while loop
	// Nu beder jeg om at give choice en værdi
	// Hvis man ikke giver et tal (altså en integer) så skal den printe en fejlbesked
	// Hvis choice ikke er en integer så er error lig med 1 går den "tilbage" til menuen og jeg giver brugeren 80 forsøg
	// Til sidst siger jeg altså at den skal gøre alt det her hvis choice ikke er lig med 0. Og det er jo fordi jeg har sagt at 0 = exit.
	do
	{
	menu:
	
		cin.clear();
		cout << "\n\n\t Please select an option from the given menu below: \n\n";
		cout << "\t\t 1. Book Management System \n\n\t\t 2. Snake Game \n\n\t\t 3. Change Font Size \n\n\t\t 4. Change Theme \n\n\t\t 0. Exit \n";

		do
		{
			error = 0;
			cout << "\n\t Please enter your selection : ";
			cin >> choice;
			if (cin.fail())
			{
				cout << "\n\t Please enter a valid input. " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		int SelBookSys, SelSnake, SelSnakeMenu, SelDiffiMenu;

		switch (choice)
		{
		case 1:
		{
			system("cls");
			cin.clear();
			cout << "\n\n\t Please select an option from the given menu below: \n\n";
			cout << "\t\t 1. Admin Login \n\n\t\t 2. Staff login \n\n\t\t 3. Guest Login \n\n\t\t 0. Exit \n";
			do
			{
				error = 0;
				cout << "\n\t Please enter your selection : ";
				cin >> SelBookSys;
				if (cin.fail())
				{
					cout << "\n\t Please enter a valid input. " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

			switch (SelBookSys)
			{
				system("cls");
			case 1:SelBookSys = 1; break;
			case 2:SelBookSys = 2; break;
			case 3:SelBookSys = 3; break;
			case 0:
			{system("pause"); return 1; }break;
			default: cout << "\n\tInvalid selection... try agian.";

			}while (SelBookSys != 0)

				if (SelBookSys == 1)
				{
					cout << "\n\t Please enter the admin username : ";
					cin >> User;
					password = getpass("Please enter the password : ", true);
					Login(User, password);

					AdminOptions();
					adminMenu();

					system("cls");
					goto menu;

				}

			if (SelBookSys == 2)
			{
				cout << "\n\t Please enter the staff username : ";
				cin >> User;
				password = getpass("Please enter the password : ", true);
				staff(User, password);

				AdminOptions();
				adminMenu();

				system("cls");
				goto menu;
			}

			if (SelBookSys == 3)
			{
				User = "Guest";
				password = "guest2";
				staff(User, password);

				AdminOptions();
				adminMenu();
				system("cls");
				goto menu;
			}

		}
		case 2:
		{
			system("cls");
			cin.clear();
			cout << "\n\n\t Please select an option from the given menu below: \n\n";
			cout << "\t\t 1. User Login \n\n\t\t 0. Exit \n";

			do
			{
				error = 0;
				cout << "\n\t Please enter your selection : ";
				cin >> SelSnake;
				if (cin.fail())
				{
					cout << "\n\t Please enter a valid input. " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

			switch (SelSnake)
			{
			case 1:SelSnake = 1; break;
			case 0:
			{system("pause"); goto menu; }break;
			default: cout << "\n\tInvalid selection... try agian.";

			}while (SelSnake != 0)

				if (SelSnake == 1)
				{

					cout << "\n\t Please enter the staff username : ";
					cin >> User;
					password = getpass("Please enter the password : ", true);
					staff(User, password);


					SnakeOptions();
					do
					{
						error = 0;
						cout << "\n\t Please enter your selection : ";
						cin >> SelSnakeMenu;
						if (cin.fail())
						{
							cout << "\n\t Please enter a valid input. " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);

					switch (SelSnakeMenu)
					{
					case 1:
						Setup();
						while (!gameOver)
						{
							Draw();
							Input();
							Logic();
							Sleep(10);
						}
						system("cls");

						cout << "\n\n Enter your name : ";
						cin >> firstName;
						cout << "\n\n Enter your last name : ";
						cin >> lastName;
						cout << "\n\n Enter score : ";
						cin >> score;

						Highscore.open("Highscore.txt", ios::out | ios::app);
						Highscore << "  " << firstName << "  " << lastName << "  " << score << "\n";
						Highscore.close();
						goto menu;
						break;
					case 2:SelSnakeMenu = 2; break;
					case 3:SelSnakeMenu = 3; break;
					case 0:
					{system("pause"); goto menu;; }break;
					default: cout << "\n\tInvalid selection... try agian.";
					}while (SelSnakeMenu != 0)
						break;

					if (SelSnakeMenu == 2)
					{
						system("cls");
						cout << "\n\n\t\t ******HIGHSCORE******";

						Highscore.open("Highscore.txt", ios::in);

						if (!Highscore)
							cout << "\n\nFile opening error";
						else
						{
							cout << "\n\n\n  First name"
								<< "\t\tLast name\tScore "
								"\n";

							Highscore >> firstName;
							Highscore >> lastName >> score;

							while (!Highscore.eof())
							{
								cout << "  " << firstName
									<< "\t\t" << lastName
									<< "\t\t" << score
									<< "\n\n";
								Highscore >> firstName;
								Highscore >> lastName >> score;
							}
							system("pause");
							Highscore.close();

							goto menu;
							break;
						}
					}


					if (SelSnakeMenu == 3)
					{
						system("cls");

						DifficultyOptions();

						do
						{
							error = 0;
							cout << "\n\t Please enter your selection : ";
							cin >> SelDiffiMenu;
							if (cin.fail())
							{
								cout << "\n\t Please enter a valid input. " << endl;
								error = 1;
								cin.clear();
								cin.ignore(80, '\n');
							}
						} while (error == 1);



						switch (SelDiffiMenu)
						{
						case 1:SelDiffiMenu = 1; break;
						case 2:SelDiffiMenu = 2; break;
						case 3:SelDiffiMenu = 3; break;
						case 0: {system("pause"); goto menu; }break;
						default: cout << "\n\tInvalid selection... try agian.";
						}while (SelDiffiMenu != 0)

						if (SelDiffiMenu == 1)
						{
								width = 100;
								height = 20;

								Setup();
								while (!gameOver)
								{
									Draw();
									Input();
									Logic();
									Sleep(10);
								}
								system("cls");
								goto menu;
						}
						else if (SelDiffiMenu == 2)
						{
							width = 60;
							height = 20;

							Setup();
							while (!gameOver)
							{
								Draw();
								Input();
								Logic();
								Sleep(10);
							}

							system("cls");
							goto menu;
						}
						else if (SelDiffiMenu == 3)
						{
							width = 20;
							height = 20;

							Setup();
							while (!gameOver)
							{
								Draw();
								Input();
								Logic();
								Sleep(10);
							}

							system("cls");
							goto menu;
						}

					}


				}

			
		}
		case 3: {
			fontsize();
			goto menu;
		} break;
		case 4: 
			system("cls");
			color();
			goto menu;
			break;
		case 0: {system("pause");
			return 0; }

		default: {cout << "\n\n\t Invalid entry!!! Please try again (Enter 1, 2, 3, 4, 5 or 0)" << endl;
			system("pause"); }
			   break;
		} while (choice != 0);

	} while (choice != 0);
}




// Liste af alle Admin options ( Admin funktioner)
void AdminOptions()
{
	system("pause");
	system("cls");

	cout << "\n\n\tWELCOME TO ADMIN MENU" << endl;
	cout << "\t=========================" << endl;
	cout << "\n\t1 : ADD NEW BOOKS" << endl;
	cout << "\n\t2 : DISPLAY ALL BOOKS" << endl;
	cout << "\n\t3 : (DELETE BOOKS)" << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

//Menu med ADD NEW BOOKS, Sel = 1
void AddBooksOptions()
{
	system("cls");

	cout << "\n\n\tADD NEW BOOKS MENU" << endl;
	cout << "	===================" << endl;
	cout << "\n\t1 : ADD NEW BOOK" << endl;
	cout << "\n\t2 : DISPLAY ALL BOOKS" << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

//Menu med DISPLAY ALL BOOKS, Sel = 2
void DisplayBooksOptions()
{
	system("cls");

	cout << "\n\n\tDISPLAY ALL BOOKS MENU" << endl;
	cout << "	=======================" << endl;
	cout << "\n\t1 : DISPLAY ALL BOOKS" << endl;
	cout << "\n\t0 : RETURN TO MAIN MENU" << endl;
}

//Liste/Menu med Search options (search menu), Sel = 3
void SearchOptions()
{
	system("cls");

	cout << "\n\n\tSEARCH BOOKS" << endl;
	cout << "\t====== ======\n\n" << endl;
	cout << "\n\t1 : SEARCH BOOKS BY title " << endl;
	cout << "\n\t2 : SEARCH BY BOOK AUTHOR " << endl;
	cout << "\n\t0 : BACK TO ADMIN MENU " << endl;

}

//Liste/Menu med Delete options (delete menu), Sel = 4
void DeleteOptions()
{
	system("cls");

	cout << "\n\tDELETE BOOKS" << endl;
	cout << "\t====== ======\n\n" << endl;
	cout << "\n\t1 : SEARCH & DELETE BY BOOK TITLE" << endl;
	cout << "\n\t2 : SEARCH & DELETE BY BOOK AUTHOR " << endl;
	cout << "\n\t3 : DISPLAY BOOKS " << endl;
	cout << "\n\t0 : BACK TO ADMIN MENU " << endl;
}

// Login funktion for admin
void Login(string& admin, string& password)
{
	string Users[200]; //grænseværdier
	string Pass[200];  //grænseværdier
	bool valid = false;

	int x = 0;
	ifstream UsFile;
	UsFile.open("Admin.txt");

	UsFile >> Users[x] >> Pass[x];

	while (UsFile) // Læser usernames og passwords fra filen og gemmer
	{
		x++;
		if (x >= 200) // x kan altså ikke overskride 200 som er de grænseværdier vi har givet
			break;
		UsFile >> Users[x] >> Pass[x];
	}

	for (int a = 0; a < x; a++)
	{
		if (admin == Users[a] && password == Pass[a]) // if(indtastet matcher eksisterende username og password)
		{
			cout << "\n\t Successfully logged into admin account" << endl;
			valid = true;
			break;
		}
	}
	if (!valid)
	{
		cout << "\n\t Username & password is invalid try again";


		system("pause");
		
	}

}

// Login funktion for staff
void staff(string& user, string& pass1)
{
	string Users[200];
	string Pass[200];
	bool valid = false;

	int x = 0;
	ifstream UsFile;
	UsFile.open("User.txt");


	UsFile >> Users[x] >> Pass[x];
	while (UsFile) // Læser alle usernames og passwords fra user.txt alrså alle eksisterende usernames og passwords
	{
		x++;
		if (x <= 200) // skal ikke overskride grænseværdier ved linje 162 og 163
			break;
		UsFile >> Users[x] >> Pass[x];
	}

	for (int a = 0; a < x; a++)
	{
		if (user == Users[a] && pass1 == Pass[a])
		{
			cout << "\n\t Successfully logged into staff account" << endl;
			valid = true;
			break;
		}
		if (user == "Guest" && pass1 == "guest2")
		{
			cout << "\n\t Succesfully logged into guest account" << endl;
			valid = true;
			break;
		}

	}
	if (!valid)
	{
		cout << "\n\tUsername or password is invalid \n\n";
		system("pause");
	}
}


//Admin Menu som indeholder/kalder alle funktioner fra Admin options
void adminMenu()
{
	int Sel, dltops, searchops, addops, dispops, no_copy = 0, count = 0, error = 0; //Her definerer jeg nogle ny variabler som skal bruges i menuen
	string booktitle, bookauthor, bookauthor1, booktitle1;  //Her definere jeg nogle variabler som skal bruges til at indlæse bøger
	fstream file, file2;

	cout << "\n\n\tPlease enter your selection : ";
	cin >> Sel;

	if (cin.fail())
	{
		cout << "\tPlease enter a valid input : " << endl;
		error = 1;
		cin.clear();
		cin.ignore(80, '\n');
	}


	switch (Sel)
	{
	case 1: Sel = 1; break;
	case 2: Sel = 2; break;
	case 3: Sel = 3; break;
	//case 4: Sel = 4; break;
	case 0: {system("pause");
		return; }
		break;
	default: cout << "\n\tInvalid selection... try agian.";
	} 

	// AddBooksOptions : Her kalder jeg funktionen "Add books" ( dette sker alstå hvis man indtaster 1)
	if (Sel == 1)
	{
		do
		{
			AddBooksOptions();


			do
			{
				error = 0;
				cout << "\n\n\tPlease enter your selection : ";
				cin >> addops;

				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			switch (addops)
			{
			case 1: addops = 1; break;
			case 2: addops = 2; break;
			case 0: {system("pause"); return; } break;
			default: cout << "\n\tInvalid selection... try again...";
			}

			if (addops == 1)
			{
				do
				{
					system("cls");


					cout << "\n\n Enter title of the book : ";
					cin >> booktitle;
					cout << "\n\n Enter the name of the author : ";
					cin >> bookauthor;
					cout << "\n\n Enter number of copies : ";
					cin >> no_copy;


					file.open("Books.txt", ios::out | ios::app);
					file << "  " << booktitle << "  " << bookauthor << "  " << no_copy << "\n";
					file.close();

					break;

				} while (addops != 0);
			}

			if (addops == 2)
			{
				do
				{
					system("cls");


					cout << "\n\n\t\t\t\t\t Display of all books";

					file.open("Books.txt", ios::in);

					if (!file)
						cout << "\n\nFile opening error";
					else
					{
						cout << "\n\n\nBook title"
							<< "\t\tAuthor\t\tNo. of "
							"Books\n\n";

						file >> booktitle;
						file >> bookauthor >> no_copy;

						while (!file.eof())
						{
							cout << "  " << booktitle
								<< "\t\t" << bookauthor
								<< "\t\t" << no_copy
								<< "\n\n";
							file >> booktitle;
							file >> bookauthor >> no_copy;
						}
						system("pause");
						file.close();
						
					}

				} while (addops != 0);


			}


		} while (addops != 0);



	}


	//DisplayBooksOptions : Her vil jeg kunne vise de gemte bøger ( dette sker altså hvis man indtaster 2)
	if (Sel == 2)
	{
		do
		{
			DisplayBooksOptions();

			do
			{
				error = 0;
				cout << "\n\n\tPlease enter your selection : ";
				cin >> dispops;

				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			switch (dispops)
			{
			case 1: dispops = 1; break;
			case 0: {system("pause"); return; } break;
			default: cout << "\n\tInvalid selection... try again...";
			}

			if (dispops == 1)
			{
				do
				{
					system("cls");


					cout << "\n\n\t\t\t\t\t Display of all books";

					file.open("Books.txt", ios::in);

					if (!file)
						cout << "\n\nFile opening error";
					else
					{
						cout << "\n\n\nBook title"
							<< "\t\tAuthor\t\tNo. of "
							"Books\n\n";

						file >> booktitle;
						file >> bookauthor >> no_copy;

						while (!file.eof())
						{
							cout << "  " << booktitle
								<< "\t\t" << bookauthor
								<< "\t\t" << no_copy
								<< "\n\n";
							file >> booktitle;
							file >> bookauthor >> no_copy;
						}
						system("pause");
						file.close();
						break;
					}
				} while (dispops != 0);
			}
		} while (dispops != 0);

	}

	// SearchOptions/searchops : Her kalder jeg funktionen "search books" ( dette sker altså hvis man indtaster 3)
	if (Sel == 40)
	{
		do
		{
			SearchOptions();

			do
			{
				error = 0;
				cout << "\n\n\tPlease enter your selection : ";
				cin >> searchops;

				if (cin.fail())
				{
					cout << "\n\tPlease enter a valid input : " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);
			switch (searchops)
			{
			case 1: break;
			case 2: break;
			case 0: break;
			default: cout << "\n\tInvalid selection... try again...";
			}
		} while (searchops != 0);
	}

	//DeleteOptions  dltops : Her kalder jeg funktionen "Delete books" (dette sker altså hvis man indtaster 4)
	if (Sel == 3)
		{
				do
				{
					DeleteOptions(); // Her bruger jeg menuen for delte books.

					do
					{
						error = 0;
						cout << "\n\n\tPlease enter your selection : ";
						cin >> dltops;

						if (cin.fail())
						{
							cout << "\n\tPlease enter a balid input : " << endl;
							error = 1;
							cin.clear();
							cin.ignore(80, '\n');
						}
					} while (error == 1);

					switch (dltops)
					{
					case 1: dltops = 1; break;
					case 2: break;
					case 3: break;
					case 0: break;
					default: cout << "\n\tInvaldig selection... Try again...";
					}



					if (dltops == 1)
					{
						string line, name;
						cout << "Please enter the title of the book you want to delete: ";
						cin >> name;
						
						
						file.open("Books.txt");
						ofstream temp;
						temp.open("temp.txt");
						
						while (getline(file, line));
						{
							if (line.substr(0, name.size()) != name)
								temp << line << endl;
						}
						cout << "The book with the title " << name << " had been deleted if it existed" << endl;

						file.close();
						temp.close();
						remove("Books.txt");
						rename("temp.txt", "Books.txt");
						
						system("pause");
						return;


					}





					/*{
						char filename[books_SIZE];
						char temp_filename[books_SIZE];
						char delete_line[MAX_LINE];
						char buffer[MAX_LINE];

						FILE* file, * file2;


						
						printf("Filename: "); 
						fgets(filename, books_SIZE, stdin);

						filename[strlen(filename) - 1] = '\0';


						strcpy(temp_filename, "temp____");
						strcat(temp_filename, filename);
						

						


						printf("\nDelete Book: ");
						fgets(delete_line, MAX_LINE, stdin);

						file = fopen(filename, "r");
						file2 = fopen(temp_filename, "w");

						if (file == NULL || file2 == NULL)
						{
							printf("Error opening file(s)\n");
							return;
						}

						bool keep_reading = true;
						do
						{
							fgets(buffer, MAX_LINE, file);
							if (feof(file)) keep_reading = false;
							else if (strcmp(buffer, delete_line) != 0)
								fputs(buffer, file2);

						} while (keep_reading);

						fclose(file);
						fclose(file2);

						remove(filename);
						rename(temp_filename, filename);


						return;
						
					}*/




					// Hvordan jeg ville have gjort hvis jeg havde brugt klasser
					/*if (dltops == 1)
					{
						do
						{

							system("cls");

							cout << "\n\n\t\t\tSEARCH AND DELETE BY BOOK TITLE";
							int countt = 0;
							file1.open("Books1.txt", ios::app | ios::out);
							file.open("Books.txt", ios::in);

							if (!file)
								cout << "\n\nOpening error...";
							else
							{
								cout << "\n\nEnter the title of the book : ";
								cin >> booktitle;
								file >> booktitle1 >> bookauthor1;
								file >> bookauthor >> no_copy;
								while (!file.eof())
								{
									if (booktitle == booktitle1)
									{
										system("cls");
										cout << "\n\n\t\t\t\t"
											<< "SEARCH AND DELETE BY BOOK TITLE";
										cout << "\n\nBook is deleted "
											"Successfullt...\n\n";
										countt++;
									}
									else
										file1 << " " << booktitle1
										<< " " << bookauthor1
										<< " " << bookauthor
										<< " " << no_copy
										<< "\n\n";
									file >> booktitle1 >> bookauthor1;
									file >> bookauthor >> no_copy;
								}
								if (count == 0)
									cout << "\n\n Book title"
									<< "Not found...";
							}
							system("pause");


							file.close();
							file1.close();
							if (rename("Books.txt", "Books1.txt") != 0)
								perror("Error moving file");
							else
								cout << "file moved";
							remove(" Books.txt");




						} while (dltops != 0);




						break;
					} while (dltops != 0);*/
				} while (dltops != 0);
	}
}
