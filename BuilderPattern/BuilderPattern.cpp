// BuilderPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

// Builder interface
class IBuilder {
public:
	virtual void drawLine(int xOrg, int yOrg, int xDest, int yDest) { return; };
	virtual void drawCircle(int radius) { return; };

	virtual Drawing* getDrawing() { return nullptr; };
protected:
	Drawing* m_drawing = nullptr;
};

// Builders
class SimpleBuilder : public IBuilder {
public:
	SimpleBuilder() { 
		cout << "SimpleBuilder Constructor called!" << endl;
		if(m_drawing == nullptr)
			m_drawing = new Drawing();
		return; 
	};
	void drawLine(int xOrg, int yOrg, int xDest, int yDest) {
		Line* line = new Line(xOrg, yOrg, xDest, yDest);
		m_drawing->addShape(line);
	}
	void drawCircle(int radius) {
		Circle* circle = new Circle(radius);
		m_drawing->addShape(circle);
	}
	Drawing* getDrawing() {
		return m_drawing;
	}
};

class FancyBuilder : public IBuilder {
public:
	FancyBuilder() {
		cout << "FancyBuilder Constructor called!" << endl;
		if (m_drawing == nullptr)
			m_drawing = new Drawing();
		return;
	};
	void drawLine(int xOrg, int yOrg, int xDest, int yDest) {
		Line* line = new FancyLine(xOrg, yOrg, xDest, yDest);
		m_drawing->addShape(line);
	}
	void drawCircle(int radius) {
		Circle* circle = new FancyCircle(radius);
		m_drawing->addShape(circle);
	}
	Drawing* getDrawing() {
		return m_drawing;
	}
};


// Directors
void createHappyFaceDirector(IBuilder& builder) {
	builder.drawLine(2, 3, 4, 5);
	builder.drawLine(6, 7, 8, 9);

	builder.drawCircle(1);
	builder.drawCircle(3);
}

void createSadFaceDirector(IBuilder& builder) {
	builder.drawLine(21, 23, 42, 52);
	builder.drawLine(61, 71, 81, 91);

	builder.drawCircle(300);
}

// Client
int main()
{
	// create the desired builder
	SimpleBuilder* simpleBuilder = new SimpleBuilder();

	// draw using the desired director
	createHappyFaceDirector(*simpleBuilder);

	//get result
	Drawing* happyFace = simpleBuilder->getDrawing();

	Shape* currentShape = nullptr;
	while (currentShape = happyFace->getNextShape()) {
		cout << currentShape->getType() << endl;
	}

	cout << "\n";

	// create another builder
	FancyBuilder* fancyBuilder = new FancyBuilder();

	// draw using the desired director
	createSadFaceDirector(*fancyBuilder);

	//get result
	Drawing* sadFace = fancyBuilder->getDrawing();

	currentShape = nullptr;
	while (currentShape = sadFace->getNextShape()) {
		cout << currentShape->getType() << endl;
	}

    std::cout << "\nFinished!\n"; 
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
