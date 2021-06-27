#ifndef THING_H
#define THING_H
#include<iostream>
#include"documento.h"
#include<list>
#include<utility>
using namespace std;
typedef pair<Documento*, int> pairr;
class Thing
{
public:
    string key;
    list<pairr> listDocuments;
    Thing(){}
    Thing(string key, pairr obj);
};
Thing::Thing(string key, pairr obj)
{
    this->key=key;
    listDocuments.push_back(obj);
}

#endif // THING_H
