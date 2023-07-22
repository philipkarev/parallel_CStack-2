#ifndef CSTACK_CSTACK_H
#define CSTACK_CSTACK_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
//#include "Factory.h"

struct Factory;

using namespace std;

struct CStack {
    size_t capacity;
    stack <int> container;
    string filename;

    CStack() = default;
    CStack(size_t len) : capacity(len) {}
    CStack(size_t len, string s) : capacity(len) , filename(s) {}
    CStack(size_t, string, vector <int>);
    CStack(const CStack&) = default;
    CStack(CStack&&) noexcept = default;
    virtual ~CStack() = default;

    int push(int);
    int pop(int&);
//    int peek(int&);
    size_t size();
    bool isEmpty();
    bool isFull();

    virtual int output() = 0; // pure virtual function

    static CStack *create_by_Factory(string, vector <Factory*>);

    CStack& operator=(const CStack&) = default;
    CStack& operator=(CStack&&) = default;
    CStack& operator++();
    CStack& operator--();

    friend ostream& operator<<(ostream&, const CStack&);
};


struct CData0 : public CStack {
    CData0(size_t len) : CStack(len) {}
    CData0(size_t len, string s) : CStack(len, s) {}
    CData0(size_t len, string s, vector <int> v) : CStack(len, s, v) {}
    CData0(const CStack& other) : CStack(other) {}
    CData0(CStack&& other) : CStack(other) {}

    int output() override;
};

CData0 operator++(CStack& a, int);
CData0 operator--(CStack& a, int);
CData0 operator+(const CStack&, const CStack&);

struct CData1 : public CStack {
    CData1(size_t len) : CStack(len) {}
    CData1(size_t len, string s) : CStack(len, s) {}
    CData1(size_t len, string s, vector <int> v) : CStack(len, s, v) {}
    CData1(const CStack& other) : CStack(other) {}
    CData1(CStack&& other) : CStack(other) {}

    int output() override;
};

bool isNumeric(string const&);

#endif //CSTACK_CSTACK_H