// PrototypePattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	Color(const Color& other) {
		m_color = other.m_color;
	}
	string getColor() {
		return m_color;
	}
	virtual void init(string color) {
		m_color = color;
	}
	virtual Color* clone() {
		return new Color(*this);
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
	Line(const Line& other) {
		m_xOrig = other.m_xOrig;
		m_yOrig = other.m_yOrig;
		m_xDest = other.m_xDest;
		m_yDest = other.m_yDest;
	}
	string getType() {
		return "Line";
	}
	virtual void init(int xOrig, int yOrig, int xDest, int yDest) {
		m_xOrig = xOrig;
		m_yOrig = yOrig;
		m_xDest = xDest;
		m_yDest = yDest;
	}
	virtual Line* clone() const {
		return new Line(*this);
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
	FancyLine(const FancyLine& other) : Line(other) {
		m_fancyType = other.m_fancyType;
	}
	string getType() {
		return "FancyLine";
	}
	Line* clone() const {
		return new FancyLine(*this);
	}
protected:
	int m_fancyType;
};

class Circle : public Shape {
public:
	Circle(int radius) {
		m_radius = radius;
	}
	Circle(const Circle& other) {
		m_radius = other.m_radius;
	}
	string getType() {
		return "Circle";
	}
	virtual void init(int radius) {
		m_radius = radius;
	}
	virtual Circle* clone() {
		return new Circle(*this);
	}
private:
	int m_radius;
};

class FancyCircle : public Circle {
public:
	FancyCircle(int radius) : Circle(radius) {
		m_fancyType = 0;
	}
	FancyCircle(const FancyCircle& other) : Circle (other){
		m_fancyType = other.m_fancyType;
	}
	string getType() {
		return "FancyCircle";
	}

	Circle* clone() {
		return new FancyCircle(*this);
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

	virtual Line*  createLine(int xOrig, int yOrig, int xDest, int yDest) = 0;
	virtual Circle* createCircle(int radius) = 0;
	virtual Color* createColor() = 0;
};

class PrototypeFactory : public AbstractFactory {
public:
	PrototypeFactory(Line* line, Circle* circle, Color* color) {
		cout << "PrototypeFactory constructor Called!" << endl;
		m_pLine = line;
		m_pCircle = circle;
		m_pColor = color;
	}
	Line*  createLine(int xOrig, int yOrig, int xDest, int yDest) {
		Line* temp = m_pLine->clone();
		temp->init(xOrig, yOrig, xDest, yDest);
		return temp;
	}
	Circle* createCircle(int radius) {
		Circle* temp = m_pCircle->clone();
		temp->init(radius);
		return temp;
	}
	Color* createColor() {
		Color* temp = m_pColor->clone();
		return temp;
	}
private:
	Line* m_pLine;
	Circle* m_pCircle;
	Color* m_pColor;
};


// Client code 
void createShapes(AbstractFactory* factory) {
	Line* line = factory->createLine(0, 0, 1, 1);
	Circle* circle = factory->createCircle(22);
	Color* color = factory->createColor();

	cout << "Created a line of type: " << line->getType() << endl;
	cout << "Created a circle of type: " << circle->getType() << endl;
	cout << "Created a color of: " << color->getColor() << endl;
}

int main()
{
	Line* simpleLine = new Line(1, 2, 3, 4);
	Circle* simpleCircle = new Circle(2);
	Color* simpleColor = new Color("Red");

	FancyLine* fancyline = new FancyLine(1, 2, 3, 4);
	FancyCircle* fancyCircle = new FancyCircle(2);
	Color* fancyColor = new Color("Sapphire");

	PrototypeFactory* factory = new PrototypeFactory(simpleLine, simpleCircle, simpleColor);
	createShapes(factory);

	std::cout << "\n";

	PrototypeFactory* fancyFactory = new PrototypeFactory(fancyline, fancyCircle, fancyColor);
	createShapes(fancyFactory); 

    std::cout << "Finished!\n"; 
}

/* Final output
AbstractFactory Constructor Called!
PrototypeFactory constructor Called!
Created a line of type: Line
Created a circle of type: Circle
Created a color of: Red

AbstractFactory Constructor Called!
PrototypeFactory constructor Called!
Created a line of type: FancyLine
Created a circle of type: FancyCircle
Created a color of: Sapphire
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
