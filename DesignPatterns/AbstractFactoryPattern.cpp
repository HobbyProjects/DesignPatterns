// AbstractFactoryPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Color {
public:
	Color(string color) {
		m_color = color;
	}
	string getColor() {
		return m_color;
	}
protected:
	string m_color;
};

class Shape {
public:
	virtual string getType() = 0;
protected:
	string m_type;
};

class Line : public Shape {
public:
	Line(int xOrig, int yOrig, int xDest, int yDest) {
		m_xOrig = xOrig;
		m_yOrig = yOrig;
		m_xDest = xDest;
		m_yDest = yDest;
	}
	string getType() {
		return "Line";
	}
protected:
	int m_xOrig;
	int m_yOrig;
	int m_xDest;
	int m_yDest;
};

class FancyLine : public Line {
public:
	FancyLine(int xOrig, int yOrig, int xDest, int yDest) : Line(xOrig, yOrig, xDest, yDest) {
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
	FancyCircle(int radius) : Circle (radius) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyCircle";
	}
protected:
	int m_fancyType;
};

class AbstractFactory
{
public:
	AbstractFactory() {
		cout << "AbstractFactory Constructor Called!" << endl;
	}

	virtual Line*  createLine(int xOrig, int yOrig, int xDest, int yDest) {
		return new Line(xOrig, yOrig, xDest, yDest);
	}
	virtual Circle* createCircle(int radius) {
		return new Circle(radius);
	}
	virtual Color* createColor(string color) {
		return new Color(color);
	}
};

class FancyShapesFactory : public AbstractFactory {
public:
	FancyShapesFactory() {
		cout << "FancyShapesFactory constructor Called!" << endl;
	}
	Line*  createLine(int xOrig, int yOrig, int xDest, int yDest) {
		return new FancyLine(xOrig, yOrig, xDest, yDest);
	}
	Circle* createCircle(int radius) {
		return new FancyCircle(radius);
	}
	Color* createColor(string color) {
		return new Color(color);
	}

};


// Client code 
void createShapes(AbstractFactory* factory) {
	Line* line = factory->createLine(0, 0, 1, 1);
	Circle* circle = factory->createCircle(22);
	Color* color = factory->createColor("Blue");
	
	cout << "Created a line of type: " << line->getType() << endl;
	cout << "Created a circle of type: " << circle->getType() << endl;
	cout << "Created a color of: " << color->getColor() << endl;
}

int main()
{
	AbstractFactory* simpleFactory = new AbstractFactory();
	createShapes(simpleFactory);

	std::cout << "\n";

	FancyShapesFactory* fancyFactory = new FancyShapesFactory();
	createShapes(fancyFactory);

    std::cout << "Finished!\n"; 
}

/* Final Output
AbstractFactory Constructor Called!
Created a line of type: Line
Created a circle of type: Circle
Created a color of: Blue

AbstractFactory Constructor Called!
FancyShapesFactory constructor Called!
Created a line of type: FancyLine
Created a circle of type: FancyCircle
Created a color of: Blue
*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
