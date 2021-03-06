// BridgePattern.cpp : Defines the entry point for the console application.
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
	Line(){}
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
	Circle(){}
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
	FancyCircle(){}
	FancyCircle(Point& a, int radius) : Circle(a, radius) {
		m_fancyType = 0;
	}
	string getType() {
		return "FancyCircle";
	}
protected:
	int m_fancyType;
};

class RenderImp {
public:
	RenderImp(){}
	virtual void drawLine(Point& a, Point& b) {}
	virtual void drawCircle(Point& a, int radius) {}
};

class SimpleRenderImp : public RenderImp, private Line, private Circle {
public:
	SimpleRenderImp(){ cout << "SimpleRenderImp ctr!" << endl; }
	void drawLine(Point& a, Point& b) {
		Line* myLine = new Line(a, b);
		cout << "ImpDrawLine : " << myLine->getType() << endl ;
	}
	void drawCircle(Point& a, int radius) {
		Circle* myCircle = new Circle(a, radius);
		cout << "ImpDrawCircle: " << myCircle->getType() << endl;
	}
};

class FancyRenderImp : public RenderImp, private FancyLine, private FancyCircle {
public:
	FancyRenderImp() { cout << "FancyRenderImp ctr!" << endl; }
	void drawLine(Point& a, Point& b) {
		FancyLine* myLine = new FancyLine(a, b);
		cout << "ImpDrawLine: " << myLine->getType() << endl;
	}
	void drawCircle(Point& a, int radius) {
		FancyCircle* myCircle = new FancyCircle(a, radius);
		cout << "ImpDrawCircle: " << myCircle->getType() << endl;
	}


};
class Render {
public:
	Render() {}
	virtual void drawRect(Point& a, Point& b) {
		return;
	}
	virtual void drawCircle(Point& a, int radius) {
		return;
	}
	virtual void drawTriangle(Point& a, Point& b, Point& c) {
		return;
	}
protected:
	RenderImp * m_imp;
};

class Face : protected Render {
public:
	Face() { 
		cout << "Face ctr!" << endl;
		m_imp = new SimpleRenderImp();
		// OR
		// m_imp = new FancyRenderImp();
	}
	void drawRect(Point& a, Point& b) {
		Point c(b.get_x(), a.get_y());
		Point d(a.get_x(), b.get_x());

		m_imp->drawLine(a, c);
		m_imp->drawLine(a, d);
		m_imp->drawLine(c, b);
		m_imp->drawLine(b, d);

		return;
	}
	void drawCircle(Point& a, int radius) {
		m_imp->drawCircle(a, radius);
		cout << "drawCircle" << endl;
		return;
	}
	void drawTriangle(Point& a, Point& b, Point& c) {
		m_imp->drawLine(a, b);
		m_imp->drawLine(b, c);
		m_imp->drawLine(c, a);
		cout << "drawTriangle" << endl;
		return;
	}
	void drawFace() {
		Point center(50, 50);

		// draw head
		drawCircle(center, 30);

		// draw eyes
		Point leftEye(25, 70);
		Point rightEye(75, 70);
		drawCircle(leftEye, 5);
		drawCircle(rightEye, 5);

		//draw mouth - ugly one
		Point mouthStart(25, 40);
		Point mouthEnd(75, 30);
		drawRect(mouthStart, mouthEnd);
	}
};
int main()
{
	Face* face = new Face();
	face->drawFace();

    return 0;
}

