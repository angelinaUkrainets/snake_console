#include "menu.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void close_code(menu& m)
{
	int n;
	cout << "CONTINUE ? \t[1] - yes [2] - no" << endl;
	cin >> n;
	if (n == 1)
	{
		system("cls");
		show_menu(m);
	}
	else
		return;
}

void show_menu(menu& m)
{
	system("cls");
	
	SetConsoleTextAttribute(console, 14);
	cout << endl;
	cout << "\t\t\t*******\t SNAKE\t*******" << endl;
	cout << endl;

	SetConsoleTextAttribute(console, 95);
	cout << "\t MENU :" << endl;
	
	SetConsoleTextAttribute(console, 14);
	cout << "[1] - PLAY (default color of snake is white)" << endl;

	SetConsoleTextAttribute(console, 95);
	cout << "[2] - CHOOSE SNAKE COLOR" << endl;

	SetConsoleTextAttribute(console, 14);
	cout << "[3] - SET FIELD SIZE" << endl;

	SetConsoleTextAttribute(console, 95);
	cout << "[4] - EXIT" << endl;
	
	int sel;
	cin >> sel;

	select(sel, m);
}

void select(int sel, menu& m)
{
	switch(sel)
	{
	case 1: 
	{
		field f(m.get_height(), m.get_width());
		f.clear_field();
		f.show_field();

		close_code(m);
		break;
	}
	case 2:
	{
		m.set_color(choose_color());

		close_code(m);
		break;
	}
	case 3:
	{
		position size = choose_size();
		m.set_height(size.y);
		m.set_width(size.x);

		close_code(m);
		break;
	}
	default:
		break;
	}
}

int choose_color()
{
	for (int i = 1; i < 16; i++)
	{
		SetConsoleTextAttribute(console, i);
		std::cout << "["<<i<<"] - choose this one" << std::endl;
	}

	int color;
	std::cin >> color;

	if (color > 15 || color < 1)
		return 15;
	return color;
}

field::field(int height, int width)
{
	this->height = height;
	this->width = width;
	region = new char* [this->height];
	for(int i = 0; i<width; i++)
	{
		region[i] = new char[this->width];
	}
}

field::~field()
{
	for(int i = 0; i<height; i++)
	{
		delete[] region[i];
	}
	delete[] region;
}

void field::show_field()
{
	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			cout << region[i][j];
		}
		cout << endl;
	}
}

void field::clear_field()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			region[i][j] = '*';
		}
	}
}

menu::menu()
{
	this->height = 20;
	this->width = 35;
	this->color = 15;
}

void menu::set_color(int color)
{
	this->color = color;
}

void menu::set_height(int height)
{
	this->height = height;
}

void menu::set_width(int width)
{
	this->width = width;
}

int menu::get_height()
{
	return this->height;
}

int menu::get_width()
{
	return this->width;
}

position choose_size()
{
	int width, height;
	
	cout << "Enter height of field ";
	cin >> height;
	cout << "Enter width of field ";
	cin >> width;

	return position{ width, height };
}