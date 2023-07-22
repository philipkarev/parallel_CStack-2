#include "CStack.h"
#include "Factory.h"


CStack::CStack(size_t len, string s, vector <int> v) {
//    cout << "called constructor with 3 parameters" << endl;
    capacity = len;
    filename = s;
    for (size_t i = 0; i < v.size(); ++i)
        push(v[i]);
}


int CStack::push(int x) {

    if (isFull()) {
        cout << "Impossible to push value" << endl;
        return 1;
    }
    container.push(x);
    return 0;
}


int CStack::pop(int& result) {

    if (isEmpty()) {
        cout << "Cannot pop" << endl;
        return 0;
    }

    result = container.top();
    container.pop();
    return 1;
}


size_t CStack::size() {

    return container.size();
}


bool CStack::isEmpty() {

    if (container.size() == 0) {
        cout << "Stack is empty" << endl;
        return true;
    }
    return false;
}

 bool CStack::isFull() {

    if (container.size() == capacity) {
        cout << "Stack is full" << endl;
        return true;
    }
    return false;
}


CStack* CStack::create_by_Factory(string str, vector <Factory*> f) {

    int CDataType, x;
    stringstream stream(str);

    if (!(stream >> CDataType))
        throw -1;
    if (CDataType != 0 && CDataType != 1)
        throw -1; // incorrect type

    string filename;
    stream >> filename;

    string s;
    vector <int> vect;
    while (stream >> s) {
        if (isNumeric(s) == 0)
            throw -2;

        x = stoi(s);
        vect.push_back(x);
    }

    if (CDataType == 0)
        return f[0]->create(vect.size(), filename, vect);
    if (CDataType == 1)
        return f[1]->create(vect.size(), filename, vect);

    return nullptr;
}


CStack& CStack::operator++() { // prefix increment

    push(0);
    return (*this);
}


CStack& CStack::operator--() { // prefix decrement

    int tmp;
    pop(tmp);
    return (*this);
}


ostream& operator<<(ostream& stream, const CStack& s) {

    stack <int> tmp_container = s.container;
    stream << "[";
    while (true) {
        if (tmp_container.size() == 0)
            break;
        stream << tmp_container.top();
        tmp_container.pop();
        if (tmp_container.size() != 0)
            cout << ", ";
    }
    stream << "]";

    return stream;
}


int CData0::output() {
//    cout << this << " " << *this << " CData0::output" << endl;
    ofstream File(filename+".txt");
    stack <int> tmp = container;
    while (true) {
        if (tmp.size() == 0)
            break;
        File << tmp.top();
        tmp.pop();
        if (tmp.size() != 0)
            File << " ";
    }
    File.close();

    return 0;
}


int CData1::output() {
//    cout << this << " " << *this << " CData1::output" << endl;
    ofstream File(filename+".txt");
    stack <int> tmp = container;
    while (true) {
        if (tmp.size() == 0)
            break;
        File << tmp.top() << endl;
        tmp.pop();
//        if (tmp.size() != 0)
//            File << endl;
    }
    File.close();
    return 0;
}


CData0 operator++(CStack& a, int) {

    CData0 tmp(a);
    ++a;
    return tmp;
}


CData0 operator--(CStack& a, int) {

    CData0 tmp(a);
    --a;
    return tmp;
}


CData0 operator+(const CStack& a, const CStack& b) {

    CData0 result(a.capacity + b.capacity);

    stack <int> tmpContA = a.container;
    while (true) {
        if (tmpContA.size() == 0)
            break;
        (result.container).push(tmpContA.top());
        tmpContA.pop();
    }

    stack <int> tmpContB = b.container;
    while (true) {
        if (tmpContB.size() == 0)
            break;
        (result.container).push(tmpContB.top());
        tmpContB.pop();
    }
    
    stack <int> tmpContainer = result.container;
    
    while ((result.container).size() != 0)
    	result.container.pop();
    
    while (true) {
        if (tmpContainer.size() == 0)
            break;
        (result.container).push(tmpContainer.top());
        tmpContainer.pop();
    }

    result.filename = a.filename;

    return result;
}


bool isNumeric(string const& str)
{
    char* p;
    strtol(str.c_str(), &p, 10);
    return *p == 0;
}
