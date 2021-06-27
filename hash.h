#ifndef HASH_H
#define HASH_H
#include<list>
#include<utility>
#include"thing.h"
#include<string.h>
using namespace std;
typedef pair<Thing, int> dupla;
class Hash
{
    int max;
public:
    dupla *vet;
    Hash();
    Hash(int max);
    ~Hash(){delete []vet;}
    int insert(string k, pairr par);
    bool remove(string k);
    bool search(string k, list<pairr> *d);
    int hash1(string k);
    int hash2(string k);
};
Hash::Hash()
{
    max=456;
    vet=new dupla[max];
    for(int i=0;i<max;i++)
        vet[i].second=-1;
}
Hash::Hash(int max)
{
    this->max=max;
    vet=new dupla[max];
    for(int i=0;i<max;i++)
        vet[i].second=-1;
}
int Hash::hash1(string k)
{
    int S=0;
    int X=1;
    for(int i=k.size()-1;i>=0;i--)
    {
        S=S+k[i]*X;
        X*=256;
    }
    return (((27*S+39)%457)%max);
}
int Hash::hash2(string k)
{
    int S=0;
    int X=1;
    for(int i=k.size()-1;i>=0;i--)
    {
        S=S+k[i]*X;
        X*=256;
    }
    return (((21*S+49)%457)%max);
}

int Hash::insert(string k, pairr par)
{
    int x,cont, i, j;
    i=hash1(k);
    j=hash2(k);
    for(x=cont=0; vet[i].second != -1; x++)
    {
        if(vet[i].first.key==k)
        {
            vet[i].first.listDocuments.push_back(par);
            return i;
        }
        if(++cont==max)return -2;
        i=(i+j)%max;
    }
    vet[i].first.key=k;
    vet[i].first.listDocuments.push_back(par);

    vet[i].second=1;
    return i;
}

bool Hash::remove(string k)
{
    int i = hash1(k);
    int j = hash2(k);
    int cont;
    for (cont=0; (vet[i].first.key != k || vet[i].second==-1) && cont<max;i = (i + j) % max, cont++);
    if(cont==max) return false;

    vet[i].second=-1;
    vet[i].first.key="removido";
    return true;
}

bool Hash::search(string k, list<pairr> *d)
{
    int i = hash1(k);
    int j = hash2(k);
    int cont;
    for (cont=0; (vet[i].first.key != k || vet[i].second==-1) && cont<max;i = (i + j) % max, cont++);
    if(cont==max) return false;

    *d=vet[i].first.listDocuments;
    return true;
}

#endif // HASH_H
