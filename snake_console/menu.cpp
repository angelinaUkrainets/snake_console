#include "menu.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

//code for close program
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

//function for showing menu
void show_menu(menu& m)
{
	//this function setting color of console
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

	SetConsoleTextAttribute(console, 14);
	int sel = 0;
	cin >> sel;

	//select variant to do
	select(sel, m);
}

//select variants of game
void select(int sel, menu& m)
{
	switch(sel)
	{
		//play game
	case 1: 
	{
		system("cls");
		field f(m.get_height(), m.get_width());
		f.clear_field();
		position pos(0, 0);

			//key
		int input, input2 = 1;

		food food_;
		snake snake_(pos);
		food_.respamn(f);
		f.set_food(food_);
		f.set_snake(snake_);
		f.show_field(m.get_color());

		//is working while snake is alive
		while (snake_.get_is_alive())
		{
			//press key
			if(_kbhit())
			{
				input = _getch();

				f.clear_field();

				//when key UP
				if(input == 72 && input2 != 80)
				{
					do {
						system("cls");

						snake_.set_direction(UP);
						if (snake_.get_position().y-1 == -1)
						{
							snake_.set_is_alive(false);
							break;
						}
						
						if(snake_.is_eating(food_))
						{
							food_.respamn(f);
						}
						snake_.set_position(position{snake_.get_position().x, snake_.get_position().y-1 });
						f.clear_field();
						f.set_food(food_);
						f.set_snake(snake_);
						f.show_field(m.get_color());
						Sleep(100);
					} while (!_kbhit() || snake_.get_is_alive() == false);
				}

				//when key DOWN
				if(input == 80 && input2 != 72)
				{
					do {
						system("cls");

						snake_.set_direction(DOWN);
						if (snake_.get_position().y+1 == f.get_height())
						{
							snake_.set_is_alive(false);
							break;
						}
						if (snake_.is_eating(food_))
						{
							food_.respamn(f);
						}
						snake_.set_position(position{ snake_.get_position().x, snake_.get_position().y + 1 });
						f.clear_field();
						f.set_food(food_);
						f.set_snake(snake_);
						f.show_field(m.get_color());
						Sleep(100);

					} while (!_kbhit() || snake_.get_is_alive() == false);
				}

				//when key RIGHT
				if (input == 77 && input2 != 75)
				{
					
						auto pos = snake_.get_position();
						do {
							system("cls");

							if (snake_.get_position().x + 1 == f.get_width())
							{
								snake_.set_is_alive(false);
								break;
							}
							if (snake_.is_eating(food_))
							{
								food_.respamn(f);
							}


							snake_.set_position(position{ snake_.get_position().x + 1, snake_.get_position().y });

							snake_.set_direction(RIGHT);

							f.clear_field();
							f.set_food(food_);
							f.set_snake(snake_);
							f.show_field(m.get_color());
							Sleep(100);
						} while (!_kbhit() || snake_.get_is_alive() == false);
				}

				//when key LEFT
				if (input == 75 && input2 != 77)
				{
					auto pos = snake_.get_position();

					do {
						system("cls");

						snake_.set_direction(LEFT);
						if (snake_.get_position().x+1 == 0)
						{
							snake_.set_is_alive(false);
							break;
						}
						if (snake_.is_eating(food_))
						{
							food_.respamn(f);
						}
						snake_.set_position(position{ snake_.get_position().x-1, snake_.get_position().y });
						f.clear_field();
						f.set_food(food_);
						f.set_snake(snake_);
						f.show_field(m.get_color());
						Sleep(100);

					} while (!_kbhit() || snake_.get_is_alive() == false);
				}
				input2 = input;
			}
		}
		snake_.clear_snake();
		cout << "DEAD" << endl;

		close_code(m);
		break;
	}
		//set color of snake
	case 2:
	{
		m.set_color(choose_color());

		close_code(m);
		break;
	}
		//set size of field
	case 3:
	{
		position size = choose_size();
		m.set_height(size.y);
		m.set_width(size.x);

		close_code(m);
		break;
	}
	case 4:
	{
		break;
	}
	default:

		break;
	}
}

//function for choosing color 
int choose_color()
{
	//show colors in console
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

//show choose of size
position choose_size()
{
	int width, height;

	cout << "Enter height of field ";
	cin >> height;
	cout << "Enter width of field ";
	cin >> width;

	return position{ width, height };
}

//constructor
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

//destructor
field::~field()
{
	for(int i = 0; i<height; i++)
	{
		delete[] region[i];
	}
	delete[] region;
}

//getters
int field::get_width()
{
	return this->width;
}

int field::get_height()
{
	return this->height;
}

int menu::get_color()
{
	return this->color;
}

//show field
void field::show_field(int color)
{
	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			//show color depend of symbol
			if (region[i][j] == 3) {
				SetConsoleTextAttribute(console, 4);
				cout << region[i][j];
			}
			else if(region[i][j] == -37)
			{
				SetConsoleTextAttribute(console, color);
				cout << region[i][j];
			}
			else
			{
				SetConsoleTextAttribute(console, 15);
				cout << region[i][j];
			}
		}
		cout << endl;
	}
}

//set space to field
void field::clear_field()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			region[i][j] = ' ';
		}
	}
}

//menu constructor
menu::menu()
{
	this->height = 20;
	this->width = 35;
	this->color = 15;
}

//menu destructor
void menu::set_color(int color)
{
	this->color = color;
}

//setters
void menu::set_height(int height)
{
	if(height > 0)
		this->height = height;
}

void menu::set_width(int width)
{
	if(width > 0)
		this->width = width;
}

//getters
int menu::get_height()
{
	return this->height;
}

int menu::get_width()
{
	return this->width;
}

//default constuctor food
food::food()
{
	symbol = 3;
	position_.x = -1;
	position_.y = -1;
}

//setters
void field::set_food(food food_)
{
	region[food_.get_position().y][food_.get_position().x] = food_.get_symbol();
}

//getters
 position food::get_position()
 {
	 return this->position_;
 }

char food::get_symbol()
{
	return this->symbol;
}

//reset symbol in other position
void food::respamn(field& field)
{
	position_.x = rand() % field.get_width();
	position_.y = rand() % field.get_height();
}

//constructor of snake
snake::snake(position pos)
{
	direction = DOWN;
	snake_symbol = 219;
	speed = 1;
	body.clear();
	body.push_back(pos);
	is_alive = true;
}

//destructor
snake::~snake()
{
	direction = STOP;
	snake_symbol = ' ';
	speed = 0;
	body.clear();
	is_alive = false;
}

//when position of snake and position of food is same snake is eating food 
bool snake::is_eating(food& food_)
{
	if (food_.get_position().x == body[0].x && food_.get_position().y == body[0].y)
	{
		//add block to snake`s body
		body.push_back(position{ body[0].x, body[0].y });
		return true;
	}
	return false;
}

//setters
void snake::set_direction(en dir)
{
	this->direction = dir;
}

void field::set_snake(snake snake_)
{
	for (int i = 0; i < snake_.get_size(); i++)
	{
		region[snake_.get_tail()[i].y][snake_.get_tail()[i].x] = 219;
	}
}

void snake::set_position(position pos)
{

	if (body.size() > 1) {
		for (int i = body.size() - 1; i > 0; i--)
		{
			body[i].x = body[i - 1].x;
			body[i].y = body[i - 1].y;
		}
	}
	this->body[0].x = pos.x;
	this->body[0].y = pos.y;
}

void snake::set_is_alive(bool flag)
{
	this->is_alive = flag;
}

//getters
int snake::get_size()
{
	return this->body.size();
}

std::vector<position> snake::get_tail()
{
	return this->body;
}

bool snake::get_is_alive()
{
	return this->is_alive;
}

position& snake::get_position()
{
	return this->body[0];
}

en snake::get_direction()
{
	return this->direction;
}

//clear snake body
void snake::clear_snake()
{
	this->body.clear();
}
