#pragma once

#include <iostream>
#include <string>
#include "dist/json/json.h"
#include <fstream>
#include <math.h>

using namespace std;

class Canvas {
protected:
	char emptyPixelSymbol;
	int width, height;
	char** canvas = nullptr;
public:
	Canvas(int, int, char);
	virtual void print() = 0;

	friend class Rectangle;
	friend class Square;
	friend class Circle;

	friend bool checkGivenData(Canvas&, int, int, int, int);
	friend bool checkGivenData(Canvas&, int, int, int);
};

class ASCIICanvas : public Canvas {
public:
	ASCIICanvas(int, int, char);
	~ASCIICanvas();
	void print();
	void print(fstream&);
};

class Point {
	int x, y;
public:
	Point(int x, int y) : x(x), y(y) {};
	inline int getX() {
		return x;
	}
	inline int getY() {
		return y;
	}
};

class Figure {
protected:
	char symbol;
	Point middle;
public:
	Figure(int x, int y, char symbol) : middle(x - 1, y - 1), symbol(symbol) {};
	virtual void draw(Canvas& c) = 0;
};

class Rectangle : protected Figure {
protected:
	int width, height;
public:
	void draw(Canvas& c) override;
	Rectangle(int x, int y, int width, int height, char symbol) : width(width), height(height), Figure(y, x, symbol) {};
};

class Square : protected Rectangle {
public:
	void draw(Canvas& c) override;
	Square(int x, int y, int a, char symbol) : Rectangle(x, y, a, a, symbol) {};
};

class Circle : protected Figure {
	int radius;
public:
	void draw(Canvas& c) override;
	Circle(int x, int y, int r, char symbol) : radius(r), Figure(y, x, symbol) {};
};

void calucateCenterComponent(int, int*, int*, int);

bool checkGivenData(Canvas&, int, int, int, int);
bool checkGivenData(Canvas&, int, int, int);
