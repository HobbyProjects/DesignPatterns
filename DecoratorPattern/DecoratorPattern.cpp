// DecoratorPattern.cpp : Defines the entry point for the console application.
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
	string toString() { return '(' + to_string(m_x) + ',' + to_string(m_y) + ')'; }
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
	Line() {}
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

class Circle : public Shape {
public:
	Circle() {}
	Circle(Point& a, int radius) {
		m_radius = radius;
	}
	string getType() {
		return "Circle";
	}
private:
	int m_radius;
};

class FancyLine : public Line {
public:
	FancyLine() {}
	FancyLine(Point a, Point b) : Line(a, b) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyLine";
	}
protected:
	int m_fancyType;
};

class FancyCircle : public Circle {
public:
	FancyCircle() {}
	FancyCircle(Point& a, int radius) : Circle(a, radius) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyCircle";
	}
protected:
	int m_fancyType;
};

class Decorator : public Shape {
public:
	string getType() {
		string type = m_shape->getType();
		return type;
	}
protected:
	Decorator(Shape* shape) {
		m_shape = shape;

	};
	Shape* m_shape;
};

class ShadeDecorator : public Decorator {
public:
	string getType() {
		string type = Decorator::getType();
		type += "-Shaded";
		return type;
	}
	ShadeDecorator(Shape* shape) : Decorator(shape) {}
};
int main()
{
	Point point1 (1, 2);
	Point point2 (3, 4);

	Line* line1 = new Line(point1, point2);
	FancyLine* line2 = new FancyLine(point1, point2);

	Circle* cirlce1 = new Circle(point1,3);
	FancyCircle* cirlce2 = new FancyCircle(point2, 3);

	// get types:
	cout << line1->getType() << endl;
	cout << line2->getType() << endl;
	cout << cirlce1->getType() << endl;
	cout << cirlce2->getType() << endl;

	// now let's decorate them:
	ShadeDecorator* forLines1 = new ShadeDecorator(line1);
	cout << forLines1->getType() << endl;

	ShadeDecorator* forLines2 = new ShadeDecorator(line2);
	cout << forLines2->getType() << endl;

	ShadeDecorator* forCircles1 = new ShadeDecorator(cirlce1);
	cout << forCircles1->getType() << endl;

	ShadeDecorator* forCircles2 = new ShadeDecorator(cirlce2);
	cout << forCircles2->getType() << endl;

    return 0;
}

