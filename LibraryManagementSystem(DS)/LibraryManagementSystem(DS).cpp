#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include <fstream>
#include <string>
#include<time.h>
using namespace std;

COORD coord = { 0, 0 }; // sets coordinates to 0,0
						//COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res, cursor_size;
void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates... "." is used as an access operator 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int ForgC)
{
	WORD wColor;
	///We will need this handle to get the current background attribute
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	///We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		///Mask out all but the background attribute, and add in the foreground color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
void ClearConsoleToColors(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	///Get the handle to the current output buffer...
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	///This is used to reset the carat/cursor to the top left.
	COORD coord = { 0, 0 };
	///A return value... indicating how many chars were written
	///   not used but we need to capture this since it will be
	///   written anyway (passing NULL causes an access violation).
	DWORD count;
	///This is a structure containing all of the console info
	/// it is used here to find the size of the console.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	///Here we will set the current color
	SetConsoleTextAttribute(hStdOut, wColor);
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		///This fills the buffer with a given character (in this case 32=space).
		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		///This will set our cursor position for the next print statement.
		SetConsoleCursorPosition(hStdOut, coord);
	}
	return;
}
void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}

void TimeandDate()
{
	time_t t;
	time(&t);
	cout<<ctime(&t);
}
void HeaderandBorders()
{
	int i;
	ClearConsoleToColors(0, 15);
	gotoxy(20, 2);
	cout << (char)201;
	for (i = 21; i < 98; i++) //length of upper line 
	{
		gotoxy(i, 2);
		cout << (char)205;
	}
	gotoxy(98, 2);
	cout << (char)187;
	for (i = 3; i < 27; i++) //length of right
	{
		gotoxy(98, i);
		if (i == 8)
		{
			cout << (char)185;
		}
		else
		{
			cout << (char)186;
		}
	}
	gotoxy(98, 27);
	cout << (char)188;
	for (i = 97; i > 20; i--) //length of below line
	{
		gotoxy(i, 27);
		if (i == 55)
		{
			cout << (char)202;
		}
		else
		{
			cout << (char)205;
		}
	}
	gotoxy(20, 27);
	printf("%c", 200);
	for (i = 26; i > 2; i--) //length of left
	{
		gotoxy(20, i);
		if (i == 8)
		{
			cout << (char)204;
		}
		else
		{
			cout << (char)186;
		}
	}

	for (i = 21; i < 98; i++) //length of mid horizontal
	{
		gotoxy(i, 8);
		if (i == 55)
		{
			cout << (char)203;
		}
		else
		{
			cout << (char)205;
		}
	}

	for (i = 9; i < 27; i++)
	{
		gotoxy(55, i);
		cout << (char)186;
	}
	
	gotoxy(46, 4);
	SetColor(3);
	printf("LIBRARY MANAGEMENT SYSTEM");
	gotoxy(35, 5);
	printf("COMSATS INSTITUTE OF INFORMATION TECHNOLOGY, WAH");
	gotoxy(47, 6);
	TimeandDate();
}
void clearWindow()
{
	for (int i = 56; i <= 96; i++)
	{
		for (int j = 9; j <= 26; j++)
		{
			gotoxy(i, j);
			cout << " ";
		}

	}

	//gotoxy(96, 26);
	//cout << "a";
}

string password;
char categories[][15] = { "Computer","Electronics","Electrical","Mechanical","Civil","Mechatronics" };
struct book
{
	int category;
	int id;
	string name;
	string author;
	int  quantity;
	float price;
	int	 rack_no;
	book *left;
	book *right;
}; book *newBook, *root , *current, *current2, *pre, *temp;

struct issuedBookRecord
{
	string studentName;
	int issuedBookCategory;
	int issuedBookID;
	string issuedBookName;
	string issueDate;
	string returnDate;
	issuedBookRecord *left, *right;
}; issuedBookRecord *issuedRecord, *root2 = NULL, *c1, *c2, *pre2;

string searchName;
bool found = false;
ofstream outfile, outfile2, passFile;

void HeaderandBordersPassword();
void passwordScreen();
bool checkBookID(int);
void fillFile(book*);
void fillFile2(issuedBookRecord*);
void changePassword();
void mainMenu();
void addBook();
void searchBook();
void deleteNode(book*);
void deleteBook();
void editBook();
void insertInTree(int, int, string, string, int, float, int);
void insertInTree2(string, int, int, string, string);
void fillTree();
void fillTree2();
void inorder(book*);
void viewBooks();
void issueSection();
void issueBook();
void searchIssuedBook();
void viewIssuedBooks();
void removeIssuedBook();


void main()
{
	system("CLS");
	
	//passwordScreen();
	mainMenu();
	cout << endl;
	_getch();
	
}

void HeaderandBordersPassword()
{
	ClearConsoleToColors(15, 0);
	int i;
	gotoxy(20, 2);
	//printf("%c", 201);
	cout << (char)201;
	for (i = 21; i < 98; i++) //length of upper line
	{
		gotoxy(i, 2);
		printf("%c", 205);
	}
	gotoxy(98, 2);
	printf("%c", 187);
	for (i = 3; i < 27; i++) //length of right
	{
		gotoxy(98, i);
		if (i == 8)
		{
			printf("%c", 185);
		}
		else
		{
			printf("%c", 186);
		}
	}
	gotoxy(98, 27);
	printf("%c", 188);
	for (i = 97; i > 20; i--) //length of below line
	{
		gotoxy(i, 27);
		printf("%c", 205);
	}
	gotoxy(20, 27);
	printf("%c", 200);
	for (i = 26; i > 2; i--) //length of left
	{
		gotoxy(20, i);
		if (i == 8)
		{
			printf("%c", 204);
		}
		else
		{
			printf("%c", 186);
		}
	}

	for (i = 21; i < 98; i++) //length of mid horizontal
	{
		gotoxy(i, 8);
		printf("%c", 205);
	}
	gotoxy(46, 4);
	printf("LIBRARY MANAGEMENT SYSTEM");
	gotoxy(35, 5);
	printf("COMSATS INSTITUTE OF INFORMATION TECHNOLOGY, WAH");
	gotoxy(47, 6);
	TimeandDate();
}
void passwordScreen()
{
	HeaderandBordersPassword();
	char p[120] = "Password Protected";
	int i;
	int l = 0;
	char pass[10], ch = 0;
	gotoxy(50, 10);
	for (i = 0; p[i] != '\0'; i++)
	{
		Sleep(50);
		SetColorAndBackground(15, 9);
		printf("%c", p[i]);
	}
	gotoxy(50, 12);
	SetColorAndBackground(9, 0);
	printf("Enter Password: ");
	while (ch != 13)
	{
		ch = _getch();

		if (ch != 13 && ch != 8) {
			printf("*");
			pass[l] = ch;
			l++;
		}
	}
	pass[l] = '\0';
	string pswd = string(pass);
	char granted[15] = "ACCESS GRANTED";

	ifstream pfile;
	pfile.open("Pass.txt");
	if (!pfile) {
		cout << " Error opening file. " << endl;
	}
	pfile >> password;
	pfile.close();

	if ( pswd.compare(password) == 0 )
	{
		gotoxy(50, 14);
		printf("Password Matched\n");
		gotoxy(52, 16);
		for (i = 0; granted[i] != '\0'; i++)
		{
			Sleep(50);
			SetColorAndBackground(15, 10);
			printf("%c", granted[i]);
		}
		SetColorAndBackground(14, 0);
		Sleep(100);
		gotoxy(50, 18);
		printf("Loading");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		mainMenu();
	}
	else
	{
		gotoxy(50, 14);
		printf("\aWarning!!! Incorrect Password");
		SetColorAndBackground(15, 12);
		gotoxy(52, 16);
		printf("ACCESS DENIED");
		SetColorAndBackground(15, 0);
		gotoxy(50, 18);
		cout << "Press any key to try again...";
		_getch();
		system("CLS");
		passwordScreen();
	}
}
void changePassword()
{
	clearWindow();
	gotoxy(67, 10);
	cout << "CHANGE PASSWORD";
	gotoxy(57, 12);
	cout << "Enter old password: ";
	string oldPass, newPass;
	cin >> oldPass;

	ifstream pfile;
	pfile.open("Pass.txt");
	if (!pfile) {
		cout << " Error opening file. " << endl;
	}
	pfile >> password;
	pfile.close();
	if (password.compare(oldPass) == 0)
	{
		gotoxy(57, 14);
		cout << "Enter new password: ";

		passFile.open("Pass.txt");

		if (!passFile) {
			cout << "error" << endl;
		}
		cin >> password;
		passFile << password;
		passFile.close();

		gotoxy(57, 16);
		cout << "Password has been changed successfully!";
	}
	else
	{
		gotoxy(57, 14);
		cout << "\aWrong password!!!";
	}
	
	gotoxy(57, 25);
	printf("Press any key to return to Main Menu");
	fflush(stdin);
	if (_getch())
		mainMenu();
}
void insertInTree(int category, int id, string name, string author, int quantity, float price, int rack_no)
{
	newBook = new book;

	newBook->category = category;
	newBook->id = id;
	newBook->name = name;
	newBook->author = author;
	newBook->quantity = quantity;
	newBook->price = price;
	newBook->rack_no = rack_no;

	newBook->left = NULL;
	newBook->right = NULL;


	if (root == NULL)
	{
		root = newBook;
		//cout << "Root node is added!\n";
	}
	else if (root->left == NULL && id < root->id)
	{
		root->left = newBook;
		//cout << "Root left child is added!\n";
	}
	else if (root->right == NULL && id > root->id)
	{
		root->right = newBook;
		//cout << "Root right child is added\n";
	}
	else
	{
		if (id < root->id)
			current = root->left;
		else
			current = root->right;

		while (current != NULL)
		{
			pre = current;
			if (id > current->id)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
			}
		}
		if (id > pre->id)
		{
			pre->right = newBook;
			//cout << "Right child is added\n";
		}
		else
		{
			pre->left = newBook;
			//cout << "Left child is added\n";
		}
	}
}
void insertInTree2(string studentName, int issuedBookCategory, int issuedBookID, string issuedBookName, string issueDate, string returnDate)
{
	issuedRecord = new issuedBookRecord;

	issuedRecord->studentName = studentName;
	issuedRecord->issuedBookCategory = issuedBookCategory;
	issuedRecord->issuedBookID = issuedBookID;
	issuedRecord->issuedBookName = issuedBookName;
	issuedRecord->issueDate = issueDate;
	issuedRecord->returnDate = returnDate;

	issuedRecord->left = NULL;
	issuedRecord->right = NULL;


	if (root2 == NULL)
	{
		root2 = issuedRecord;
		//cout << "Root node is added!\n";
	}
	else if (root2->left == NULL && issuedBookID < root2->issuedBookID)
	{
		root2->left = issuedRecord;
		//cout << "Root left child is added!\n";
	}
	else if (root2->right == NULL && issuedBookID > root2->issuedBookID)
	{
		root2->right = issuedRecord;
		//cout << "Root right child is added\n";
	}
	else
	{
		if (issuedBookID < root2->issuedBookID)
			c1 = root2->left;
		else
			c1 = root2->right;

		while (c1 != NULL)
		{
			pre2 = c1;
			if (issuedBookID > c1->issuedBookID)
			{
				c1 = c1->right;
			}
			else
			{
				c1 = c1->left;
			}
		}
		if (issuedBookID > pre2->issuedBookID)
		{
			pre2->right = issuedRecord;
			//cout << "Right child is added\n";
		}
		else
		{
			pre2->left = issuedRecord;
			//cout << "Left child is added\n";
		}
	}
}
void fillFile(book* d)
{
	if (d != NULL)
	{
		fillFile(d->left);

		outfile << d->category << "\t";
		outfile << d->id << "\t";
		outfile << d->name << "\t";
		outfile << d->author << "\t";
		outfile << d->quantity << "\t";
		outfile << d->price << "\t";
		outfile << d->rack_no << "\n\n";
		
		fillFile(d->right);
	}
}
void fillTree()
{
	ifstream file;
	file.open("Books.txt");
	if (!file) {
		cout << " Error opening file. " << endl;
	}

	int category;
	int id;
	string name;
	string author;
	int  quantity;
	float price;
	int	 rack_no;

	while (file >> category >> id >> name >> author >> quantity >> price >> rack_no)
	{
		
		insertInTree(category, id, name, author, quantity, price, rack_no);
	}
	file.close();
}
void mainMenu()
{
	system("CLS");
	HeaderandBorders();
	gotoxy(22, 10);
	SetColor(4);
	cout << "\xDB\xDB\xDB\xDB\xB2 1. Add Books";
	gotoxy(22, 12);
	cout << "\xDB\xDB\xDB\xDB\xB2 2. Search Books";
	gotoxy(22, 14);
	cout << "\xDB\xDB\xDB\xDB\xB2 3. Delete Books";
	gotoxy(22, 16);
	cout << "\xDB\xDB\xDB\xDB\xB2 4. Issue Books";
	gotoxy(22, 18);
	cout << "\xDB\xDB\xDB\xDB\xB2 5. View Book List";
	gotoxy(22, 20);
	cout << "\xDB\xDB\xDB\xDB\xB2 6. Edit Book Record";
	gotoxy(22, 22);
	cout << "\xDB\xDB\xDB\xDB\xB2 7. Change Password";
	gotoxy(22, 24);
	cout << "\xDB\xDB\xDB\xDB\xB2 8. Close Application";
	gotoxy(22, 26);
	cout << "Select your choice:";
	switch (char c = _getch())
	{
	case '1':
		addBook();
		break;
	case '2':
		searchBook();
		break;
	case '3':
		deleteBook();
		break;
	case '4':
		issueSection();
		break;
	case '5':
		viewBooks();
		break;
	case '6':
		editBook();
		break;
	case '7':
		changePassword();
		break;
	case '8':
		exit(0);

	default:
		break;
	}
}
bool checkBookID(int BookID)
{
	bool check = false;

	ifstream file;
	file.open("Books.txt");
	if (!file) {
		cout << " Error opening file. " << endl;
	}

	int category;
	int id;
	string name;
	string author;
	int  quantity;
	float price;
	int	 rack_no;

	while (file >> category >> id >> name >> author >> quantity >> price >> rack_no)
	{

		if (id == BookID)
		{
			check = true;
			break;
		}
	}
	file.close();

	if (check)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void addBook()
{
	clearWindow();
	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "SELECT CATEGORY";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "1. Computer";
	gotoxy(57, 14);
	cout << "2. Electronics";
	gotoxy(57, 16);
	cout << "3. Electrical";
	gotoxy(57, 18);
	cout << "4. Mechanical";
	gotoxy(57, 20);
	cout << "5. Civil";
	gotoxy(57, 22);
	cout << "6. Mechatronics";
	gotoxy(57, 24);
	cout << "7.Back to Main Menu";
	gotoxy(57, 26);
	cout << "Enter your Choice:";
	fflush(stdin);
	char choice = _getch();
	
	if (choice == '7')
		mainMenu();
	
	choice -= '1';
	clearWindow();
	gotoxy(67, 10);
	SetColorAndBackground(1, 3);
	cout << "ADD BOOK";

	int category;
	int id;
	string name;
	string author;
	int  quantity;
	float price;
	int	 rack_no;

	gotoxy(63, 12);
	SetColorAndBackground(0, 15);
	cout << "Enter the Information Below";
	gotoxy(63, 13);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(63, 14);
	cout << "\xB2"; gotoxy(89, 14); cout << "\xB2";
	gotoxy(63, 15);
	cout << "\xB2"; gotoxy(89, 15); cout << "\xB2";
	gotoxy(63, 16);
	cout << "\xB2"; gotoxy(89, 16); cout << "\xB2";
	gotoxy(63, 17);
	cout << "\xB2"; gotoxy(89, 17); cout << "\xB2";
	gotoxy(63, 18);
	cout << "\xB2"; gotoxy(89, 18); cout << "\xB2";
	gotoxy(63, 19);
	cout << "\xB2"; gotoxy(89, 19); cout << "\xB2";
	gotoxy(63, 20);
	cout << "\xB2"; gotoxy(89, 20); cout << "\xB2";
	gotoxy(63, 21);
	cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	gotoxy(64, 14);
	cout << "Category:";
	gotoxy(74, 14);
	cout << categories[choice];
	
	
	
	gotoxy(64, 15);
	fflush(stdin);
	cout << "Book ID: ";
	cin >> id;

	ifstream checkFile("Books.txt");

	if (checkFile) {
		if (checkBookID(id))
		{
			gotoxy(63, 22);
			getchar();
			printf("\aThe book id already exists\a");

			_getch();
			mainMenu();
		}
	}
	

	outfile.open("Books.txt", ios::app);

	if (!outfile) {
		cout << "error" << endl;
	}

	category = (int)choice;
	outfile << category << "\t";
	outfile << id << "\t";
	gotoxy(64, 16);
	cout << "Book Name: ";
	cin >> name;
	outfile << name << "\t";
	gotoxy(64, 17);
	cout << "Author: ";
	cin >> author;
	outfile << author << "\t";

	gotoxy(64, 18);
	cout << "Quantity: ";
	cin >> quantity;
	outfile << quantity << "\t";
	gotoxy(64, 19);
	cout << "Price: Rs.";
	cin >> price;
	outfile << price << "\t";
	gotoxy(64, 20);
	cout << "Rack No: ";
	cin >> rack_no;
	outfile << rack_no << "\n\n";

	outfile.close();

	gotoxy(61, 23);
	cout << "The record is successfully saved.";
	gotoxy(61, 25);
	cout << "Press ENTER to add more books or";
	gotoxy(61, 26);
	cout << "ESC to go back to MAIN MENU";
	char ch = _getch();
	if (ch == 13)
	{
		clearWindow();
		addBook();
	}
	else if (ch == 27)
	{
		mainMenu();
	}
}
void searchBook()
{
	clearWindow();

	fillTree();

	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "SEARCH BOOK";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "1. Search by ID";
	gotoxy(57, 14);
	cout << "2. Search by Name";
	gotoxy(57, 16);
	cout << "3. Back to Main Menu";
	gotoxy(57, 18);
	cout << "Enter your choice:";

	char c = _getch();
	if (c == '1')
	{
		clearWindow();
		gotoxy(60, 10);
		SetColorAndBackground(15, 3);
		cout << "SEARCH BOOK BY ID";
		gotoxy(57, 12);
		SetColorAndBackground(0, 15);
		cout << "Enter the Book ID: ";
		int BookID;
		cin >> BookID;

		bool check = false;

		if (root == NULL)
		{
			cout << "Tree is empty!\n";
		}
		else
		{
			current = root;

			while (current != NULL)
			{
				if (current->id == BookID)
				{
					check = true;
					break;
				}

				if (BookID < current->id)
				{
					current = current->left;
				}
				else if (BookID > current->id)
					current = current->right;
			}
		}

		if (check)
		{
			gotoxy(59, 14);
			printf("The Book is available");
			gotoxy(59, 15);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(59, 16);
			printf("\xB2 ID:%d", current->id); gotoxy(86, 16); printf("\xB2");
			gotoxy(59, 17);
			cout << "\xB2 Name:" << current->name; gotoxy(86, 17); printf("\xB2");
			gotoxy(59, 18);
			cout << "\xB2 Author:" << current->author << " "; gotoxy(86, 18); printf("\xB2");
			gotoxy(59, 19);
			printf("\xB2 Quantity:%d ", current->quantity); gotoxy(86, 19); printf("\xB2");
			gotoxy(59, 20);
			printf("\xB2 Price:Rs.%.2f", current->price); gotoxy(86, 20); printf("\xB2");
			gotoxy(59, 21);
			printf("\xB2 Rack No:%d ", current->rack_no); gotoxy(86, 21); printf("\xB2");
			gotoxy(59, 22);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		}
		else
		{
			gotoxy(59, 14);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
			gotoxy(59, 16);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(61, 15); printf("\aNo Record Found");

		}
		gotoxy(57, 24);
		printf("Try another search? (Y/N)");
		fflush(stdin);
		if (_getch() == 'y')
		{
			searchBook();
		}
		else
		{
			mainMenu();
		}
	}
	else if (c == '2')
	{
		clearWindow();
		gotoxy(60, 10);
		SetColorAndBackground(15, 3);
		cout << "SEARCH BOOK BY NAME";
		gotoxy(57, 12);
		SetColorAndBackground(0, 15);
		cout << "Enter the Book Name: ";
		cin >> searchName;

		inorder(root);

		if (found)
		{
			gotoxy(59, 14);
			printf("The Book is available");
			gotoxy(59, 15);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(59, 16);
			printf("\xB2 ID:%d", current2->id); gotoxy(86, 16); printf("\xB2");
			gotoxy(59, 17);
			cout << "\xB2 Name:" << current2->name; gotoxy(86, 17); printf("\xB2");
			gotoxy(59, 18);
			cout << "\xB2 Author:" << current2->author << " "; gotoxy(86, 18); printf("\xB2");
			gotoxy(59, 19);
			printf("\xB2 Quantity:%d ", current2->quantity); gotoxy(86, 19); printf("\xB2");
			gotoxy(59, 20);
			printf("\xB2 Price:Rs.%.2f", current2->price); gotoxy(86, 20); printf("\xB2");
			gotoxy(59, 21);
			printf("\xB2 Rack No:%d ", current2->rack_no); gotoxy(86, 21); printf("\xB2");
			gotoxy(59, 22);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			found = false;
		}
		else
		{
			gotoxy(59, 14);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
			gotoxy(59, 16);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(61, 15); printf("\aNo Record Found");

		}
		gotoxy(57, 24);
		printf("Try another search? (Y/N)");
		fflush(stdin);
		if (_getch() == 'y')
		{
			searchBook();
		}
		else
		{
			mainMenu();
		}
	}
}
void deleteNode(book* curr)
{

	if (curr->left == NULL && curr->right == NULL)
	{
		if (curr == root)
		{
			delete curr;
			root = NULL;
		}
		else if (pre->left == curr)
		{
			temp = curr;
			pre->left = NULL;
			delete temp;
		}
		else if (pre->right == curr)
		{
			temp = curr;
			pre->right = NULL;
			delete temp;
		}
	}
	else if (curr->left != NULL && curr->right == NULL)
	{
		temp = curr;
		pre->left = curr->left;
		delete curr;
	}
	else if (curr->right != NULL && curr->left == NULL)
	{
		temp = current;
		pre->right = curr->right;
		delete curr;
	}
	else
	{
		current2 = curr->right;
		while (current2->left != NULL)
		{
			pre = current2;
			current2 = current2->left;
		}

		curr->id = current2->id;
		temp = current2;
		pre->left = NULL;
	}
}
void deleteBook()
{
	clearWindow();

	fillTree();
	int BookID;
	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "DELETE BOOKS RECORD";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "Enter the Book ID to delete: ";
	fflush(stdin);
	cin >> BookID;

	bool check = false;

	if (root == NULL)
	{
		//cout << "Tree is empty!\n";
	}
	else
	{
		current = root;

		while (current != NULL)
		{
			if (current==root)
			{
				pre = current;
			}
			if (current->id == BookID)
			{
				check = true;
				break;
			}

			pre = current;

			if (BookID < current->id)
			{
				current = current->left;
			}
			else if (BookID > current->id)
				current = current->right;
		}
	}

	if (check)
	{
		gotoxy(59, 14);
		printf("The Book is available");
		gotoxy(59, 15);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 16);
		printf("\xB2 ID:%d", current->id); gotoxy(86, 16); printf("\xB2");
		gotoxy(59, 17);
		cout << "\xB2 Name:" << current->name; gotoxy(86, 17); printf("\xB2");
		gotoxy(59, 18);
		cout << "\xB2 Author:" << current->author << " "; gotoxy(86, 18); printf("\xB2");
		gotoxy(59, 19);
		printf("\xB2 Quantity:%d ", current->quantity); gotoxy(86, 19); printf("\xB2");
		gotoxy(59, 20);
		printf("\xB2 Price:Rs.%.2f", current->price); gotoxy(86, 20); printf("\xB2");
		gotoxy(59, 21);
		printf("\xB2 Rack No:%d ", current->rack_no); gotoxy(86, 21); printf("\xB2");
		gotoxy(59, 22);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 23);
		cout << "Do you want to delete it? (Y/N)";
		fflush(stdin);
		if (_getch() == 'y')
		{
			deleteNode(current);

			if (root!=NULL)
			{
				outfile.open("Books.txt");

				if (!outfile) {
					cout << "error" << endl;
				}
				fillFile(root);
				outfile.close();
			}
			

			gotoxy(59, 25);
			cout << "The record is successfully deleted";

		}
	}
	else
	{
		gotoxy(59, 14);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(61, 15); printf("\aNo Record Found");

	}
	gotoxy(57, 26);
	printf("Delete another Record? (Y/N)");
	//fflush(stdin);
	if (_getch() == 'y')
	{
		deleteBook();
	}
	else
	{
		mainMenu();
	}
}
void editBook()
{
	clearWindow();
	fillTree();
	gotoxy(66, 9);
	SetColorAndBackground(15, 3);
	printf("EDIT BOOK RECORD");
	gotoxy(57, 11);
	SetColorAndBackground(0, 15);
	printf("Enter the Book ID to be edited: ");
	int BookID;
	cin >> BookID;

	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = root;

		while (current != NULL)
		{
			if (current->id == BookID)
			{
				check = true;
				break;
			}

			if (BookID < current->id)
			{
				current = current->left;
			}
			else if (BookID > current->id)
				current = current->right;
		}
	}

	if (check)
	{
		clearWindow();
		gotoxy(59, 9);
		printf("The Book is available");
		gotoxy(59, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 11);
		printf("\xB2 ID:%d", current->id); gotoxy(85, 11); printf("\xB2");
		gotoxy(59, 12);
		cout << "\xB2 Name:" << current->name; gotoxy(85, 12); printf("\xB2");
		gotoxy(59, 13);
		cout << "\xB2 Author:" << current->author << " "; gotoxy(85, 13); printf("\xB2");
		gotoxy(59, 14);
		printf("\xB2 Quantity:%d ", current->quantity); gotoxy(85, 14); printf("\xB2");
		gotoxy(59, 15);
		printf("\xB2 Price:Rs.%.2f", current->price); gotoxy(85, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2 Rack No:%d ", current->rack_no); gotoxy(85, 16); printf("\xB2");
		gotoxy(59, 17);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	}
	else
	{
		gotoxy(59, 14);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(61, 15); printf("\aNo Record Found");

	}
	gotoxy(59, 18);
	cout << "Enter the new record ";

	gotoxy(59, 19);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(59, 20);
	cout << "\xB2 ID: "; gotoxy(85, 20); printf("\xB2");
	gotoxy(59, 21);
	cout << "\xB2 Name:";  gotoxy(85, 21); printf("\xB2");
	gotoxy(59, 22);
	cout << "\xB2 Author:"; cout << " "; gotoxy(85, 22); printf("\xB2");
	gotoxy(59, 23);
	printf("\xB2 Quantity: "); gotoxy(85, 23); printf("\xB2");
	gotoxy(59, 24);
	printf("\xB2 Price:Rs.");  gotoxy(85, 24); printf("\xB2");
	gotoxy(59, 25);
	printf("\xB2 Rack No:"); gotoxy(85, 25); printf("\xB2");
	gotoxy(59, 26);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(65, 20); cin >> current->id;
	gotoxy(67, 21); cin >> current->name;
	gotoxy(69, 22); cin >> current->author;
	gotoxy(72, 23); cin >> current->quantity;
	gotoxy(70, 24); cin >> current->price;
	gotoxy(70, 25); cin >> current->rack_no;

	outfile.open("Books.txt");

	if (!outfile) {
		cout << "error" << endl;
	}
	fillFile(root);
	outfile.close();

	gotoxy(59, 26);
	cout << "The record is successfully modified";



	gotoxy(59, 27);
	cout << "Modify another record? (Y/N)";
	fflush(stdin);
	if (_getch() == 'y')
	{
		searchBook();
	}
	else
	{
		mainMenu();
	}
}
void inorder(book* c)
{
	if (c != NULL)
	{
		inorder(c->left);
		if (searchName.compare(c->name) == 0)
		{
			found = true;
			current2 = c;
		}
		inorder(c->right);
	}
}

void fillTree2()
{
	ifstream file;
	file.open("IssuedData.txt");
	if (!file) {
		cout << " Error opening file. " << endl;
	}

	string studentName;
	int issuedBookCategory;
	int issuedBookID;
	string issuedBookName;
	string issueDate;
	string returnDate;

	while (file >> studentName >> issuedBookCategory >> issuedBookID >> issuedBookName >> issueDate >> returnDate)
	{
		insertInTree2(studentName, issuedBookCategory, issuedBookID, issuedBookName, issueDate, returnDate);
	}
	file.close();
}

void viewBooks()
{
	int total = 0, j = 6;
	system("CLS");
	gotoxy(15, 3);
	SetColor(38);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(14, 4);
	printf("  CATEGORY   |   ID   |      BOOK NAME      |      AUTHOR      |  QTY  |   PRICE  |  RackNo ");
	gotoxy(15, 5);
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

	ifstream file;
	file.open("Books.txt");
	if (!file) {
		cout << " Error opening file. " << endl;
	}

	int category;
	int id;
	string name;
	string author;
	int  quantity;
	float price;
	int	 rack_no;

	while (file >> category >> id >> name >> author >> quantity >> price >> rack_no)
	{
		gotoxy(15, j);
		cout << categories[category];
		gotoxy(27, j);
		cout << "| " << id;
		gotoxy(36, j);
		cout << "| " << name;
		gotoxy(58, j);
		cout << "| " << author;
		gotoxy(77, j);
		cout << "| " << quantity;
		total += quantity;
		gotoxy(85, j);
		cout << "| " << price;
		gotoxy(96, j);
		cout << "| " << rack_no;
		j++;
	}


	gotoxy(15, j + 1);
	cout << "Total Books: " << total;

	file.close();

	gotoxy(57, j + 1);
	cout << "Press ENTER to return to MAIN MENU";
	if (_getch())
		mainMenu();

}

void issueSection()
{
	clearWindow();

	//fillTree();

	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "ISSUE SECTION";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "1. Issue a Book";
	gotoxy(57, 14);
	cout << "2. View issued Books";
	gotoxy(57, 16);
	cout << "3. Search issued Book";
	gotoxy(57, 18);
	cout << "4. Remove issued Book";
	gotoxy(57, 20);
	cout << "5. Back to MAIN MENU";
	gotoxy(57, 22);
	cout << "Enter your choice:";

	char c = _getch();
	switch (c)
	{
	case'1':
		issueBook();
		break;
	case'2':
		viewIssuedBooks();
		break;
	case'3':
		searchIssuedBook();
		break;
	case'4':
		break;
	case'5':
		mainMenu();
		break;


	default:
		break;
	}
}

void issueBook()
{
	clearWindow();

	fillTree();
	int BookID = 0;
	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "ISSUE BOOK SECTION";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "Enter the Book ID: ";
	cin >> BookID;
	bool check = false;

	if (root == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		current = root;

		while (current != NULL)
		{
			if (current->id == BookID)
			{
				check = true;
				break;
			}

			if (BookID < current->id)
			{
				current = current->left;
			}
			else if (BookID > current->id)
				current = current->right;
		}
	}

	if (check)
	{
		if (current->quantity < 1)
		{
			gotoxy(57, 14);
			cout << "The book is not available.";

			gotoxy(57, 24);
			printf("Do you want to issue more books? (Y/N)");
			//fflush(stdin);
			if (_getch() == 'y')
			{
				issueBook();
			}
			else
			{
				issueSection();
			}
		}

		outfile2.open("IssuedData.txt", ios::app);

		if (!outfile2) {
			cout << "error" << endl;
		}

		char date[9];
		_strdate_s(date);
		string dt = string(date);


		gotoxy(57, 14);
		cout << "The book record is available.";
		gotoxy(57, 15);
		cout << "There are " << current->quantity << " unissued books in library.";
		gotoxy(57, 16);
		cout << "Book name: " << current->name;
		gotoxy(57, 18);
		cout << "Enter student name: ";
		string studentName;
		cin >> studentName;
		outfile2 << current->name << "\t";
		outfile2 << current->category << "\t";
		outfile2 << current->id << "\t";
		outfile2 << studentName << "\t";
		gotoxy(57, 19);
		cout << "Issued Date: "<<dt;
		outfile2 << dt << "\t";
		gotoxy(57, 20);
		cout << "Return Date: " << dt;
		outfile2 << dt << "\n\n";
		gotoxy(57, 22);
		cout << "The book named \"" << current->name << "\" is issued";
		int nn = current->quantity - 1;
		current->quantity = nn;

		outfile.open("Books.txt");

		if (!outfile) {
			cout << "error" << endl;
		}

		fillFile(root);

		outfile.close();
		outfile2.close();


		gotoxy(57, 24);
		printf("Do you want to issue more books? (Y/N)");
		//fflush(stdin);
		if (_getch() == 'y')
		{
			issueBook();
		}
		else
		{
			issueSection();
		}

	}
	else
	{
		gotoxy(59, 14);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(61, 15); printf("\aNo Record Found");

	}
}
void viewIssuedBooks()
{
	int total = 0, j = 6;
	system("CLS");
	gotoxy(15, 3);
	SetColor(38);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(14, 4);
	printf("  STUDENT NAME    |  CATEGORY   |   ID   |      BOOK NAME      |  ISSUE DATE  |  RETURN DATE  ");
	gotoxy(15, 5);
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	
	ifstream file;
	file.open("IssuedData.txt");
	if (!file) {
		cout << " Error opening file. " << endl;
	}

	string studentName;
	int issuedBookCategory;
	int issuedBookID;
	string issuedBookName;
	string issueDate;
	string returnDate;

	while (file >> studentName >> issuedBookCategory >> issuedBookID >> issuedBookName >> issueDate >> returnDate)
	{
		gotoxy(14, j);
		cout << issuedBookName;
		gotoxy(32, j);
		cout << "| " << categories[issuedBookCategory];
		gotoxy(55, j);
		cout << "| " << studentName;
		gotoxy(46, j);
		cout << "| " << issuedBookID;
		gotoxy(77, j);
		cout << "| " << issueDate;
		gotoxy(92, j);
		cout << "| " << returnDate;
		j++;
	}
	file.close();
	gotoxy(70, j + 1);
	cout << "Press ENTER to return to MAIN MENU";
	if (_getch())
		mainMenu();
}
void searchIssuedBook()
{
	clearWindow();

	fillTree2();
	int BookID;
	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "SEARCH ISSUED BOOK";
	gotoxy(57, 12);
	SetColorAndBackground(0, 15);
	cout << "Enter the Book ID to delete: ";
	fflush(stdin);
	cin >> BookID;

	bool check = false;

	if (root2 == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		c1 = root2;

		while (c1 != NULL)
		{
			if (c1->issuedBookID == BookID)
			{
				check = true;
				break;
			}

			if (BookID < c1->issuedBookID)
			{
				c1 = c1->left;
			}
			else if (BookID > c1->issuedBookID)
				c1 = c1->right;
		}
	}

	if (check)
	{
		int total = 0, j = 6;
		system("CLS");
		gotoxy(15, 3);
		SetColor(38);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(14, 4);
		printf("  STUDENT NAME    |  CATEGORY   |   ID   |      BOOK NAME      |  ISSUE DATE  |  RETURN DATE  ");
		gotoxy(15, 5);
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

		ifstream file;
		file.open("IssuedData.txt");
		if (!file) {
			cout << " Error opening file. " << endl;
		}

		string studentName;
		int issuedBookCategory;
		int issuedBookID;
		string issuedBookName;
		string issueDate;
		string returnDate;

		while (file >> studentName >> issuedBookCategory >> issuedBookID >> issuedBookName >> issueDate >> returnDate)
		{
			if (issuedBookID==c1->issuedBookID)
			{
				gotoxy(14, j);
				cout << issuedBookName;
				gotoxy(32, j);
				cout << "| " << categories[issuedBookCategory];
				gotoxy(55, j);
				cout << "| " << studentName;
				gotoxy(46, j);
				cout << "| " << issuedBookID;
				gotoxy(77, j);
				cout << "| " << issueDate;
				gotoxy(92, j);
				cout << "| " << returnDate;
				j++;
			}
		}

		file.close();

		gotoxy(70, j + 1);
		cout << "Press ENTER to return to MAIN MENU";
		if (_getch())
			mainMenu();
	}
	else
	{
		gotoxy(59, 14);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(61, 15); printf("\aNo Record Found");

	}
	gotoxy(57, 24);
	printf("Try another search? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		searchIssuedBook();
	}
	else
	{
		issueSection();
	}
}
void removeIssuedBook()
{
	clearWindow();

	fillTree();
	int BookID;
	gotoxy(67, 10);
	SetColorAndBackground(15, 3);
	cout << "DELETE BOOKS RECORD";
	gotoxy(57, 12);
	cout << "Enter the Book ID to delete: ";
	fflush(stdin);
	cin >> BookID;

	bool check = false;

	if (root2 == NULL)
	{
		cout << "Tree is empty!\n";
	}
	else
	{
		c1 = root2;

		while (c1 != NULL)
		{
			if (c1->issuedBookID == BookID)
			{
				check = true;
				break;
			}

			if (BookID < c1->issuedBookID)
			{
				c1 = c1->left;
			}
			else if (BookID > c1->issuedBookID)
				c1 = c1->right;
		}
	}

	if (check)
	{
		int total = 0, j = 6;
		system("CLS");
		gotoxy(15, 3);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(14, 4);
		printf("  STUDENT NAME    |  CATEGORY   |   ID   |      BOOK NAME      |  ISSUE DATE  |  RETURN DATE  ");
		gotoxy(15, 5);
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

		ifstream file;
		file.open("IssuedData.txt");
		if (!file) {
			cout << " Error opening file. " << endl;
		}

		string studentName;
		int issuedBookCategory;
		int issuedBookID;
		string issuedBookName;
		string issueDate;
		string returnDate;

		while (file >> studentName >> issuedBookCategory >> issuedBookID >> issuedBookName >> issueDate >> returnDate)
		{
			if (issuedBookID == c1->issuedBookID)
			{
				gotoxy(14, j);
				cout << issuedBookName;
				gotoxy(32, j);
				cout << "| " << categories[issuedBookCategory];
				gotoxy(55, j);
				cout << "| " << studentName;
				gotoxy(46, j);
				cout << "| " << issuedBookID;
				gotoxy(77, j);
				cout << "| " << issueDate;
				gotoxy(92, j);
				cout << "| " << returnDate;
				j++;
				total++;
			}
		}

		file.close();

		gotoxy(70, j + 1);
		cout << "Press ENTER to return to MAIN MENU";
		if (_getch())
			mainMenu();
	}
	else
	{
		gotoxy(59, 14);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(59, 15); printf("\xB2");  gotoxy(77, 15); printf("\xB2");
		gotoxy(59, 16);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(61, 15); printf("\aNo Record Found");

	}
	gotoxy(57, 24);
	printf("Try another search? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		searchIssuedBook();
	}
	else
	{
		issueSection();
	}
}