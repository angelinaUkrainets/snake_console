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
		system("cls");
		field f(m.get_height(), m.get_width());
		f.clear_field();
		position pos(0, 0);
		int input;

		food food_;
		snake snake_(pos);
		food_.respamn(f);
		f.set_food(food_);
		f.set_snake(snake_);
		f.show_field(m.get_color());


		while (snake_.get_is_alive())
		{

			if(_kbhit())
			{
				input = _getch();
				int input2 = input;

				f.clear_field();

				if(input == 72 && snake_.get_direction() != DOWN)
				{
					//auto pos = snake_.get_position();
					do {
						system("cls");

						snake_.set_direction(UP);
						if (snake_.get_position().y-1 == -1)
						{
							snake_.set_is_alive(false);
							break;
						}
						//pos.y -= 1;
						//snake tmp_snake(pos);
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
				if(input == 80 && snake_.get_direction() != UP)
				{
					//auto pos = snake_.get_position();

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
						//pos.y += 1;
						//snake tmp_snake(position{ snake_.get_position().x, snake_.get_position().y + 1 });
						snake_.set_position(position{ snake_.get_position().x, snake_.get_position().y + 1 });
						f.clear_field();
						f.set_food(food_);
						f.set_snake(snake_);
						f.show_field(m.get_color());
						Sleep(100);

					} while (!_kbhit() || snake_.get_is_alive() == false);
				}
				if (input == 77 )
				{
					
						auto pos = snake_.get_position();
						do {
							system("cls");

							auto curDir = RIGHT;
							if (snake_.get_position().x + 1 == f.get_width())
							{
								snake_.set_is_alive(false);
								break;
							}
							pos.x -= 1;
							if (snake_.is_eating(food_))
							{
								food_.respamn(f);
							}
							//snake tmp_snake(pos);


							snake_.set_position(position{ snake_.get_position().x + 1, snake_.get_position().y });

							snake_.set_direction(RIGHT);

							f.clear_field();
							f.set_food(food_);
							f.set_snake(snake_);
							f.show_field(m.get_color());
							Sleep(100);
						} while (!_kbhit() || snake_.get_is_alive() == false);
				}
				if (input == 75 && snake_.get_direction() != RIGHT)
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
						pos.x += 1;
						if (snake_.is_eating(food_))
						{
							food_.respamn(f);
						}
						//snake tmp_snake(pos);
						snake_.set_position(position{ snake_.get_position().x-1, snake_.get_position().y });
						f.clear_field();
						f.set_food(food_);
						f.set_snake(snake_);
						f.show_field(m.get_color());
						Sleep(100);

					} while (!_kbhit() || snake_.get_is_alive() == false);
				}
			}
			else
			{
				system("cls");
			}
		}
		snake_.clear_snake();
		cout << "DEAD" << endl;

		/*while(snake_.get_is_alive() == true)
		{
			f.clear_field();
			snake_.set_direction();

			try {
				snake_.move(f);
			}
			catch (const char* er) {
				f.clear_field();
				cerr << er << endl;
				system("pause");
			}
			f.set_snake(snake_);

			if (snake_.is_eating(food_))
			{
				food_.respamn(f);
			}
			f.show_field();

			Sleep(100);
			system("cls");
		}*/

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

void field::show_field(int color)
{
	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
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
	if(height > 0)
		this->height = height;
}

void menu::set_width(int width)
{
	if(width > 0)
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

food::food()
{
	symbol = 3;
	position_.x = -1;
	position_.y = -1;
}

void field::set_food(food food_)
{
	region[food_.get_position().y][food_.get_position().x] = food_.get_symbol();
}

 position food::get_position()
 {
	 return this->position_;
 }

char food::get_symbol()
{
	return this->symbol;
}

void food::respamn(field& field)
{
	position_.x = rand() % field.get_width();
	position_.y = rand() % field.get_height();
}

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

snake::snake(position pos)
{
	direction = DOWN;
	snake_symbol = 219;
	speed = 1;
	body.clear();
	body.push_back(pos);
	is_alive = true;
}

bool snake::is_eating(food& food_)
{
	if (food_.get_position().x == body[0].x && food_.get_position().y == body[0].y)
	{
		body.push_back(position{ body[0].x, body[0].y });
		return true;
	}
	return false;
}

void snake::set_direction(en dir)
{
	this->direction = dir;
}

//void snake::move(field& f) {
//	position next = { 0, 0 };
//	switch (direction) {
//	case UP:
//		next.y = -speed;
//		break;
//	case DOWN:
//		next.y = speed;
//		break;
//	case LEFT:
//		next.x = -speed;
//		break;
//	case RIGHT:
//		next.x = speed;
//	}
//	for (int c = tail.size() - 1; c > 0; --c) {
//		tail[c] = tail[c - 1];
//	}
//	head.x += next.x;
//	head.y += next.y;
//
//	if (head.x < 0 || head.y < 0 || head.x >= f.get_width() || head.y >= f.get_height()) {
//		throw "DEADD!!!!";
//	}
//}

int snake::get_size()
{
	return this->body.size();
}

std::vector<position> snake::get_tail()
{
	return this->body;
}

void field::set_snake(snake snake_)
{
	for(int i = 0; i<snake_.get_size(); i++)
	{
		region[snake_.get_tail()[i].y][snake_.get_tail()[i].x] = 219;
	}
}

bool snake::get_is_alive()
{
	return this->is_alive;
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

position& snake::get_position()
{
	return this->body[0];
}

void snake::set_is_alive(bool flag)
{
	this->is_alive = flag;
}

void move(field& f)
{
	
}

void snake::clear_snake()
{
	this->body.clear();
}

en snake::get_direction()
{
	return this->direction;
}
