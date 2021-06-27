#ifndef PROJETO_H
#define PROJETO_H
#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<math.h>
#include"hash.h"
#include"thing.h"
#include<string>
#include<ctype.h>
using namespace std;
typedef pair<Documento*, int> pairr;
typedef pair<queue<string>,Documento*> parQueueDoc;
typedef pair<pairr,bool> pairrBool;
typedef vector<pairrBool> vecPairrBool;

class Projeto
{
    Hash tabela;
    int qntDocumentos;

public:
    Projeto(string nomeArquivo);
    parQueueDoc analyzeFile(string nameFile);
    void inserirTabela(parQueueDoc x);
    void separateWords(string x, queue<string> *listWords, int *qntDist);
    int wordOccurrences(string word, queue<string>*listWords);
    string searchOnlyWord(string w);
    string searchDiverseWord(queue<string> w, string op);
    bool searchDat_Vecc(vector<pairrBool> v,string name);
    void opWord(string x, queue<string> *opWords);
    string convertMinus(string x);
    string printDoc(string nameArquivo, int num);
    void calculoRelevanciaDoc(queue<pair<pairr,string> > x);
    void bubbleSort(vector<pairr> &V);
};
Projeto::Projeto(string nomeArquivo)
{
    fstream arquivo;
    arquivo.open(nomeArquivo.c_str(), std::ios::in);
    while(!arquivo.is_open())
    {
       cout<<"O arquivo de entrada nao foi aberto! Tente novamente\nNome do arquivo: \n";
       nomeArquivo="";
       cin>>nomeArquivo;
       arquivo.open(nomeArquivo.c_str(), std::ios::in);
    }
    string linha;
    getline(arquivo, linha);
    qntDocumentos= std::stoi(linha);
    for(int i=0;i<=qntDocumentos;i++)
    {
        if(i>0)
        {
            parQueueDoc aux=analyzeFile(linha);
            inserirTabela(aux);
        }
        getline(arquivo, linha);
    }
    arquivo.close();
}

parQueueDoc Projeto::analyzeFile(string nameFile)
{
    string linha;
    int contWordsDist=0;
    queue<string> listWords;

    fstream arquivo;
    arquivo.open(nameFile, std::ios::in);

    if(!arquivo.is_open())
       cout<<"O arquivo nao foi aberto!\n";

    Documento *doc=new Documento;
    doc->setNome_do_arquivo(nameFile);

    getline(arquivo, linha);
    while(!arquivo.eof())
    {
        separateWords(convertMinus(linha),&listWords,&contWordsDist);
        getline(arquivo, linha);
    }
    separateWords(convertMinus(linha),&listWords,&contWordsDist);

    doc->setQnt_palavras_distintas(contWordsDist);
    arquivo.close();

    parQueueDoc saida=make_pair(listWords,doc);
    return saida;
}

void Projeto::inserirTabela(parQueueDoc x)
{
    int oW;
    pairr dupla;
    queue<pair<pairr,string> > queueDuplas;
    string word=convertMinus(x.first.front());

    x.first.push("OJogo");
    x.first.pop();
    while(!x.first.empty())
    {
        oW=wordOccurrences(word,&x.first);
        dupla=make_pair(x.second,oW);
        queueDuplas.push(make_pair(dupla,word));
        tabela.insert(word,dupla);
        word=convertMinus(x.first.front());
        x.first.pop();
    }
    calculoRelevanciaDoc(queueDuplas);
}

string Projeto::searchOnlyWord(string w)
{
    int cont=1;
    list<pairr> listt;
    vector<pairr> vec;
    string saida="";

    tabela.search(convertMinus(w),&listt);
    while(!listt.empty())
    {
        vec.push_back(listt.front());
        listt.pop_front();
    }
    bubbleSort(vec);
    for(int i=0;i<(int)vec.size();cont++,i++)
        saida+=printDoc(vec[i].first->getNome_do_arquivo(),cont)+"\n";

    return saida;
}

string Projeto::searchDiverseWord(queue<string> w, string op)
{
    string saida="";
    list<pairr> listt;
    vector<pairrBool> vecc;
    vector<vecPairrBool> matrix;
    vector<pairr> filaDocs;

    matrix.resize(w.size());
    for(int i=0;!w.empty();i++)
    {
        tabela.search(convertMinus(w.front()),&listt);
        w.pop();
        while(!listt.empty())
        {
            matrix[i].push_back(make_pair(listt.front(),false));
            listt.pop_front();
        }
    }
    for(int i=0;i<(int)matrix.size();i++)
    {
        for(int j=0; j<(int)matrix[i].size();j++)
        {
            if(!searchDat_Vecc(vecc,matrix[i][j].first.first->getNome_do_arquivo()))
                vecc.push_back(matrix[i][j]);
        }
    }
    for(int i=0,cont;i<(int)vecc.size();i++)
    {
        cont=0;
        for(int j=0;j<(int)matrix.size();j++)
        {
            if(searchDat_Vecc(matrix[j],vecc[i].first.first->getNome_do_arquivo()))
                cont++;
        }
        if(op=="2" && cont==(int)matrix.size())
            vecc[i].second=true;
        else if(op=="3" && cont>=1)
            vecc[i].second=true;
    }
    int i, cont=1;
    for(i=0;i<(int)vecc.size();i++)
    {
        if(vecc[i].second)
           filaDocs.push_back(vecc[i].first);
    }
    bubbleSort(filaDocs);

    for(i=0;i<(int)filaDocs.size();i++,cont++)
        saida+=printDoc(filaDocs[i].first->getNome_do_arquivo(),cont);

    return saida;
}

void Projeto::separateWords(string x, queue<string> *listWords, int *qntDist)
{
    if(x=="")return;
    string aux="";
    int i;
    for(i=0;i<(int)x.size() && x[i] != ',' && x[i] != ' ' && x[i] != '!' && x[i] != '?' && x[i] != '.';aux+=x[i], i++);
    i++;
    if(aux.size()>=2 && aux[0]>57)
    {
        queue<string> aa=*listWords;
        bool ok=true;
        while(!listWords->empty())
        {
            string z=listWords->front();
            listWords->pop();
            if(z==aux)ok=false;
        }
        if(ok)*(qntDist)+=1;
        *listWords=aa;
        listWords->push(aux);
    }
    aux="";
    for(;i<(int)x.size();i++)
        aux+=x[i];
    separateWords(aux,listWords,qntDist);
}
int Projeto::wordOccurrences(string word, queue<string>* listWords)
{
    queue<string> listAux;
    int eqWord=1;
    while(!listWords->empty())
    {
        string w=convertMinus(listWords->front());
        listWords->pop();
        if(word!=w)
            listAux.push(w);
        else
            eqWord++;
    }
    *listWords=listAux;
    return eqWord;
}
void Projeto::opWord(string x, queue<string> *opWords)
{
    if(x=="")return;
    string aux="";
    int i;
    for(i=0;i<(int)x.size()&& x[i] != ',' && x[i] != ' ' && x[i] != '!' && x[i] != '?' && x[i] != '.';aux+=x[i], i++);
    i++;
    if(aux!=" " && aux!="")opWords->push(aux);
    aux="";
    for(;i<(int)x.size();i++)
        aux+=x[i];
    opWord(aux,opWords);
}
string Projeto::printDoc(string nameArquivo, int num)
{
    fstream doc;
    string linha="",saida="";
    saida="\n\nNome do Documento "+to_string(num)+": "+nameArquivo+"\n";
    doc.open(nameArquivo.c_str(), std::ios::in);
    saida+="\nCONTEUDO DO DOCUMENTO "+to_string(num)+"\n\n";
    getline(doc,linha);
    while(!doc.eof())
    {
       saida+=" | "+linha+" |\n";
       getline(doc,linha);
    }
    saida+=" | "+linha+" |\n\n";
    doc.close();
    return saida;
}
bool Projeto::searchDat_Vecc(vector<pairrBool> v,string name)
{
    int i;
    for(i=0;i<(int)v.size() && name!=v[i].first.first->getNome_do_arquivo();i++);
    if(i<(int)v.size())return true;
    return false;
}
string Projeto::convertMinus(string x)
{
    string saida="";
    for(int i=0; i<(int)x.size();i++)
    {
        saida+=tolower(x[i]);
    }
    return saida;
}
void Projeto::calculoRelevanciaDoc(queue<pair<pairr,string>> x)
{
    list<pairr> aux;
    Documento* doc=x.front().first.first;
    double peso=0;
    while(!x.empty())
    {
        tabela.search(x.front().second,&aux);
        peso+=(x.front().first.second)*(log(qntDocumentos)/aux.size());
        x.pop();
    }

    double R = (1/(double)doc->getQnt_palavras_distintas())*peso;
    doc->setRelevancia(R);
}

void Projeto::bubbleSort(vector<pairr> &V)
{
    pairr aux;
    int troca = 1;
    while (troca == 1)
    {
        troca = 0;
        for (int i = 0; i <= (int)V.size()-2; i++)
        {
            if (V[i].first->getRelevancia()<V[i+1].first->getRelevancia())
            {
                troca = 1;
                aux=V[i];
                V[i]=V[i+1];
                V[i+1]=aux;
            }
        }
    }
}

#endif // PROJETO_H
