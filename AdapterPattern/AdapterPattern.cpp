// AdapterPattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Point {
public:
	Point() {
		m_x = 0;
		m_y = 0;
	}

	Point(int x, int y) {
		m_x = x;
		m_y = y;
	}
	virtual int get_x() { return m_x; }
	virtual int get_y() { return m_y; }
	string toString() { return '(' +  to_string(m_x) + ',' + to_string(m_y) + ')'; }
protected:
	int m_x = 0;
	int m_y = 0;
};

class Shape {
public:
	virtual string getType() = 0;
protected:
	string m_type;
};

class Line : public Shape {
public:
	Line(Point origin, Point dest) {
		m_orig = origin;
		m_dest = dest;
	}
	string getType() {
		return "Line";
	}
protected:
	Point m_orig;
	Point m_dest;
};

class ShapeCreator {
public:
	ShapeCreator(){}
	virtual void drawRectangle(Point a, Point b) { cout << "just drew a rectangle at " << a.toString() << b.toString() << endl; }
	virtual void drawTriangle(Point a, Point b, Point c) { cout << "triangle at " << a.toString() << b.toString() << c.toString() << endl; }
};

// class adaptor
class Rectangle : public Shape, private ShapeCreator {
public:
	Rectangle(Point a, Point b) {
		m_a = a;
		m_b = b;
	}
	void draw() {
		drawRectangle(m_a, m_b);
	}
	string getType() {
		return "Rectangle";
	}
private:
	Point m_a;
	Point m_b;
};

// object adaptor
class Rectangle_alt : public Shape {
public:
	Rectangle_alt(Point a, Point b) {
		m_shapeCreator = new ShapeCreator();
		m_a = a;
		m_b = b;
	}
	void draw() {
		m_shapeCreator->drawRectangle(m_a, m_b);
	}
	string getType() {
		return "Rectangle_alt";
	}
private:
	ShapeCreator* m_shapeCreator;
	Point m_a;
	Point m_b;
};

int main()
{
	Point a(1, 2);
	Point b(5, 6);

	Shape* shape = new Rectangle(a, b);
	cout << shape->getType() << endl;

	Rectangle* rectangle = static_cast<Rectangle*>(shape);
	rectangle->draw();

	cout << endl;

	Shape* shape_alt = new Rectangle_alt(a, b);
	cout << shape_alt->getType() << endl;

	Rectangle_alt* rectangle_alt = static_cast<Rectangle_alt*> (shape_alt);
	rectangle_alt->draw();

    return 0;
}

