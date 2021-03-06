// Singleton Pattern.cpp : Defines the entry point for the console application.
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
	virtual int get_y() { return m_y; };
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

class FancyLine : public Line {
public:
	FancyLine(Point origin, Point dest) : Line(origin, dest) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyLine";
	}
protected:
	int m_fancyType;
};

class Circle : public Shape {
public:
	Circle(int radius) {
		m_radius = radius;
	}
	string getType() {
		return "Circle";
	}
private:
	int m_radius;
};

class FancyCircle : public Circle {
public:
	FancyCircle(int radius) : Circle(radius) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyCircle";
	}
protected:
	int m_fancyType;
};

class SingletonFactory {
public:
	static SingletonFactory* getInstance() {
		if (m_factory == nullptr) {
			m_factory = new SingletonFactory();
		}
		return m_factory;
	}

	// Factory methods
	virtual Line* makeLine(Point origin, Point dest) {
		return new Line(origin, dest);
	}

	virtual Circle* makeCircle(int radius) {
		return new Circle(radius);
	}
protected:
	SingletonFactory() {}
private:
	static SingletonFactory* m_factory;
};



int main()
{
	SingletonFactory* factory = SingletonFactory::getInstance();
	Point start(34, 43);
	Point end(55, 93);

	Line* line = factory->makeLine(start, end);
	Circle* circle = factory->makeCircle(33);
    
	return 0;
}

