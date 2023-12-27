#include "Header.h"

Canvas::Canvas(int width, int height, char symbol) {
	this->width = width;
	this->height = height;
	this->emptyPixelSymbol = symbol;
};

ASCIICanvas::ASCIICanvas(int numberOfChars, int numberOfLines, char symbol) : Canvas(numberOfChars, numberOfLines, symbol) {
	canvas = new char* [height];
	for (int i = 0; i < height; i++) {
		canvas[i] = new char[width];
		for (int j = 0; j < width; j++) {
			canvas[i][j] = emptyPixelSymbol;
		}
	}
};

ASCIICanvas::~ASCIICanvas() {
	for (int i = 0; i < width; i++) {
		delete[] canvas[i];
	}
	delete[] canvas;
};

void ASCIICanvas::print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << canvas[i][j] << " ";
		}
		cout << endl;
	}
}

void ASCIICanvas::print(fstream &file) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			file << canvas[i][j];
		}
		file << "\n";
	}
}

void Rectangle::draw(Canvas& c) {
	int x = middle.getX();
	int y = middle.getY();
	int beginX, endX, beginY, endY;
	
	calucateCenterComponent(x, &beginX, &endX, width);
	calucateCenterComponent(y, &beginY, &endY, height);
	
	for (int i = beginX; i <= endX; i++) {
		for (int j = beginY; j <= endY; j++) {
			c.canvas[i][j] = symbol;
		}
	}
}

void Square::draw(Canvas& c) {
	int x = middle.getX();
	int y = middle.getY();
	int beginX, endX, beginY, endY;

	calucateCenterComponent(x, &beginX, &endX, width);
	calucateCenterComponent(y, &beginY, &endY, height);

	for (int i = beginX; i <= endX; i++) {
		for (int j = beginY; j <= endY; j++) {
			c.canvas[i][j] = symbol;
		}
	}
}

void Circle::draw(Canvas& c) {
	int x = middle.getX();
	int y = middle.getY();

	int beginX = x - radius, 
		endX = x + radius,
		beginY = y - radius,
		endY = y + radius;
	
	for (int i = beginX; i <= endX; i++) {
		for (int j = beginY; j <= endY; j++) {
			int distance = ceil(sqrt(pow(abs(x - i), 2) + pow(abs(y - j), 2)));
			if (distance <= radius) {
				c.canvas[i][j] = symbol;
			}
		}
	}
}

void calucateCenterComponent(int m, int* begin, int* end, int a) {
	int tempBegin = m - (a / 2) * (a % 2), tempEnd;

	if (a % 2 == 0) {
		tempEnd = m + a - 1;
	}
	else {
		tempEnd = m + (a / 2);
	}

	*begin = tempBegin;
	*end = tempEnd;
}

bool checkGivenData(Canvas &c, int x, int y, int width, int height) {
	if (x <= 0 || y <= 0 || width <= 0 || height <= 0) {
		return false;
	}

	int tempX = x - (width / 2) * (width % 2),
		tempY = y - (height / 2) * (height % 2);

	if (tempX + width > c.width) {
		return false;
	}
	if (tempY + height > c.width) {
		return false;
	}
	if (width % 2 == 0 && tempX - width < 0) {
		return false;
	}
	if (width % 2 == 0 && tempY - height < 0) {
		return false;
	}

	return true;
}

bool checkGivenData(Canvas &c, int x, int y, int a) {
	if (x <= 0 || y <= 0 || a <= 0) {
		return false;
	}
	if (x + a > c.width || x - a < 0) {
		return false;
	}
	if (y + a > c.width || y - a < 0) {
		return false;
	}
	return true;
}