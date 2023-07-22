#ifndef CSTACK_FACTORY_H
#define CSTACK_FACTORY_H

#include "CStack.h"
//#include <string>
//#include <vector>

//using namespace std;

//struct CStack;

struct Factory {

    virtual CStack* create(size_t, string, vector <int>) = 0;
    virtual ~Factory() {}
};


struct FactoryCData0 : public Factory{

    CStack* create(size_t, string, vector <int>) override;
};


struct FactoryCData1 : public Factory{

    CStack* create(size_t, string, vector <int>) override;
};

#endif //CSTACK_FACTORY_H
