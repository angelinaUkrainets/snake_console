#pragma once

struct position;

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
};

void show_menu(menu &m);
void select(int sel, menu& m);
int choose_color();
position choose_size();
void close_code(menu& m);

struct position
{
	int x, y;
};

class field
{
	int height, width;
	char** region;

public:
	field() = default;
	field(int height, int width);
	~field();

	void show_field();
	void clear_field();
};