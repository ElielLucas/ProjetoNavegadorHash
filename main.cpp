#include "projeto.h"

int main()
{
    queue<string> opWordd;
    string nomeArquivo,op,word="";
    printf("Forneca o nome do arquivo de entrada: ");
    cin>>nomeArquivo;
    Projeto pro(nomeArquivo);
    cin.ignore();
    while(1)
    {
        op="";
        system("cls");
        printf("1 - Busca de documentos por uma unica palavra\n");
        printf("2 - Busca de documentos que contenham todas as palavras de um conjunto de duas ou mais palavras\n");
        printf("3 - Busca de documentos que tenham pelo menos uma das palavras de um conjunto de duas ou mais palavras\n");
        printf("Escolha o tipo de pesquisa pelo numero da alternativa: ");
        cin>>op;
        if(op=="1")
        {
            while(op=="1")
            {
                word="";
                system("cls");
                printf("1 - Busca de documentos por uma unica palavra\n\nSEARCH:  ");
                cin>>word;
                cout<<pro.searchOnlyWord(word);

                printf("\nDIGITE 1 PARA CONTINUAR NESSA CATEGORIA DE PESQUISA: ");
                cin>>op;
            }
        }else if(op=="2")
        {
            while(op=="2")
            {
                word="";
                system("cls");
                printf("2 - Busca de documentos que contenham todas as palavras de um conjunto de duas ou mais palavras\n\nSEARCH:  ");
                cin.ignore();
                getline(cin,word);
                pro.opWord(word,&opWordd);
                cout<<pro.searchDiverseWord(opWordd,op);

                printf("\nDIGITE 2 PARA CONTINUAR NESSA CATEGORIA DE PESQUISA: ");
                cin>>op;
                while(!opWordd.empty())
                    opWordd.pop();
            }
        }else if(op=="3")
        {
            while(op=="3")
            {
                word="";
                system("cls");
                printf("3 - Busca de documentos que tenham pelo menos uma das palavras de um conjunto de duas ou mais palavras\n\nSEARCH:   ");
                cin.ignore();
                getline(cin,word);
                pro.opWord(word,&opWordd);
                cout<<pro.searchDiverseWord(opWordd,op);

                printf("\nDIGITE 3 PARA CONTINUAR NESSA CATEGORIA DE PESQUISA: ");
                cin>>op;
                while(!opWordd.empty())
                    opWordd.pop();
            }
        }else break;
        while(!opWordd.empty())
            opWordd.pop();
    }
}
