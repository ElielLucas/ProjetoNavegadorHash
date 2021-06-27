#ifndef DOCUMENTO_H
#define DOCUMENTO_H
#include<iostream>
using namespace std;

class Documento
{
private:
    string nome_do_arquivo;
    int qnt_palavras_distintas;
    double relevancia;
public:
    Documento();
    void setQnt_palavras_distintas(int qnt){qnt_palavras_distintas=qnt;}
    void setNome_do_arquivo(string nome){nome_do_arquivo=nome;}
    string getNome_do_arquivo()const{return nome_do_arquivo;}
    int getQnt_palavras_distintas()const{return qnt_palavras_distintas;}
    void setRelevancia(double x){relevancia=x;}
    double getRelevancia(){return relevancia;}
};
Documento::Documento()
{
   nome_do_arquivo="nada";
   qnt_palavras_distintas=0;
   relevancia=0;
}

#endif // DOCUMENTO_H
