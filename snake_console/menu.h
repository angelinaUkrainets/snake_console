#pragma once
#include <vector>

//header file where is all classes, global functions, enums and structures

class snake;
class food;
struct position;

enum en { STOP, UP, DOWN, RIGHT, LEFT };


class menu
{
	int height, width, color;
public:
	menu();

	void set_height(int height);
	void set_width(int width);
	void set_color(int color);

	int get_height();
	int get_width();
	int get_color();
};

void show_menu(menu &m);
void select(int sel, menu& m);
int choose_color();
position choose_size();
void close_code(menu& m);

struct position
{
	int x, y;

	position() = default;
	position(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class field
{
	int height, width;
	char** region;

public:
	field() = default;
	field(int height, int width);
	~field();

	void show_field(int color = 15);
	void clear_field();

	void set_food(food food_);
	void set_snake(snake snake_);

	int get_height();
	int get_width();
};

class food
{
	position position_;
	char symbol;

public:
	food();

	position get_position();
	char get_symbol();

	void respamn(field& field);
};

class snake
{
	en direction;
	char snake_symbol;
	std::vector<position> body;
	int speed;
	bool is_alive;

public:
	snake() = default;
	snake(position pos);
	~snake();

	bool is_eating(food& food_);
	void set_direction(en dir);
	void set_position(position pos);
	void set_is_alive(bool flag);

	int get_size();
	std::vector<position> get_tail();
	bool get_is_alive();
	position& get_position();
	en get_direction();

	void clear_snake();
};