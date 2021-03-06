// CompositePattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Element {
public:
	virtual string GetType() { return m_type; }

	virtual void Add(Element* object) {}
	virtual void Remove(Element* object){}

	virtual vector<Element*> GetInnerElements() {  
		vector<Element*> empty;
		return empty;
	}
protected:
	Element() { m_type = "BaseElement"; }
	string m_type;
};

class Line : public Element {
public:
	Line() { m_type = "Line"; }
};

class Circle : public Element {
public:
	Circle() { m_type = "Circle"; }
};

class CompositeElement : public Element {
public:
	virtual string GetType() { 
		std::vector<Element*>::iterator it = m_innerElements.begin();
		m_type += '<';
		while (it != m_innerElements.end()) {
			m_type += '(' + (*it)->GetType()+ ')';
			it++;
		}
		m_type += '>';
		return m_type; 
	}
	virtual void Add(Element* object) {
		m_innerElements.push_back(object);
	}
	virtual void Remove(Element* object) {
		std::vector<Element*>::iterator it;
		it = find(m_innerElements.begin(), m_innerElements.end(), object);

		if (it != m_innerElements.end()) {
			m_innerElements.erase(it);
		}
	}
	virtual vector<Element*> GetInnerElements() {
		return m_innerElements;
	}
protected:
	CompositeElement() {
		m_type = "Composite: ";
	}
private:
	vector<Element*> m_innerElements;
};

class Canvas : public CompositeElement{
public:
	Canvas() {}
};

int main()
{
	Line* line1 = new Line();
	Circle* circle1 = new Circle();

	Line* line2 = new Line();
	Circle* circle2 = new Circle();

	Line* line3 = new Line();
	Circle* circle3 = new Circle();

	Canvas* mainCanvas = new Canvas();
	Canvas* smallCanvas = new Canvas();

	mainCanvas->Add(line1);
	mainCanvas->Add(circle1);
	mainCanvas->Add(smallCanvas);

	smallCanvas->Add(line2);
	smallCanvas->Add(line3);
	smallCanvas->Add(circle2);
	smallCanvas->Add(circle3);

	cout << mainCanvas->GetType() << endl;

    return 0;
}

