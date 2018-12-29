// FactoryMethodPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
	FancyCircle(int radius) : Circle(radius) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyCircle";
	}
protected:
	int m_fancyType;
};

class Drawing {
public:
	virtual void addShape(Shape* shape) {
		m_shapes.push_back(shape);
		return;
	};
	virtual Shape* getNextShape() {
		Shape* result = nullptr;
		if (m_shapes.size() != 0) {
			result = m_shapes.back();
			m_shapes.pop_back();
		}
		return result;
	};
private:
	vector<Shape*> m_shapes;
};

class SimpleCreator {
public:
	Drawing* createProduct() {
		Line* oneLine = makeLine(1, 2, 3, 4);
		Circle* oneCircle = makeCircle(34);

		m_drawing = new Drawing();

		if (m_drawing) {
			m_drawing->addShape(oneLine);
			m_drawing->addShape(oneCircle);
		}
		return m_drawing;
	}

	// Factory methods
	virtual Line* makeLine(int xOrg, int yOrg, int xDest, int yDest) {
		return new Line(xOrg, yOrg, xDest, yDest);
	}

	virtual Circle* makeCircle(int radius) {
		return new Circle(radius);
	}
protected:
	Drawing* m_drawing = nullptr;
};

class FancyCreator : public SimpleCreator {
	virtual Line* makeLine(int xOrg, int yOrg, int xDest, int yDest) {
		return new FancyLine(xOrg, yOrg, xDest, yDest);
	}

	virtual Circle* makeCircle(int radius) {
		return new FancyCircle(radius);
	}
};

int main()
{
	SimpleCreator* defaultCreator = new SimpleCreator();
	Drawing* result = defaultCreator->createProduct();

	Shape* currentShape = nullptr;
	while (currentShape = result->getNextShape()) {
		cout << currentShape->getType() << endl;
	}

    std::cout << "\n"; 

	FancyCreator* fancyCreator = new FancyCreator();
	result = fancyCreator->createProduct();

	currentShape = nullptr;
	while (currentShape = result->getNextShape()) {
		cout << currentShape->getType() << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
