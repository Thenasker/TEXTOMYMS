/*
*   Questão 17.
*
*       Ao inserir texto no teclado digital de um telefone, é posivel que uma determinada
*   combinaçao de digitos corresponda a mais de uma palavra. Tais sao chamados Textonyms.
*   Supondo que as teclas de digito sao mapeadas para letras da seguinte maneira:
*
*        2 --> ABC
*        2 --> DEF
*        2 --> GHI
*        2 --> JKL
*        2 --> MNO
*        2 --> PQRS
*        2 --> TUV
*        2 --> WXYZ
*
*    Tarefa:
*        Escreva um programa que encontre Textonyms em uma lista de palavras como do arquivo
*    listaDePalavras.txt (http://www.puzzlers.org/pub/wordlists/unixdict.txt). A tarefa
*    deve produzir um relatorio:
*
*        Existem #0 palavras em #1 que podem ser representadas pelo mapeamento de teclas de digitos.
*        Eles requerem #2 combinaçoes de digitos para representa-los. As combinaçoes de digitos #3
*        representam Textonyms.
*
*    Onde:
*        a) #0 é o numero de palavras na lista que pode ser representado pelo mapeamento de teclas
*        de digitos.
*        b) #1 é a URL da lista de palavras que está sendo usada.
*        c) #2 é o numero de combinaçoes de digitos necessarias para representar as palavras em #0.
*        d) #3 é o numero de #2 que representa mais de uma palavra.
*
*    A seu criterio, mostre alguns exemplos de sua soluçao exibindo Textonyms.
*    POR EXEMPLO:
*        2748424767 --> Briticisms, criticas
*
*
*
*   1-relatorio de arquivo padrao
*   2-relatorio de arquivo proprio
*   3-mostrar combinaçoes com mais textonyms de um arquivo
*   4-Buscar palavras por numero num arquivo
*   5-Obter textonyms de uma palavra (diccionario)
*   0-Sair

*   Instruçoes:
*       1º abrir o projeto da biblioteca e compilar ela.
*       2º Sttings -> Compiler -> Linker settings -> Add -> Rota da biblioteca (arquivo .a)
*       3º Compilar e executar o programa
*/

/////////////////////////////INCLUDES
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
//Input/output manipulation. É usada para modificar a estrutura da saida de resultados.
#include <iomanip>
//Biblioteca usada para gerar os arquivos com nomes baseados na data (ao estilo dos logs)
#include <ctime>
//Incluimos nossa biblioteca particular
#include "textonymsLIB.h"
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1--Relatorio de arquivo padrao\n\n2--Relatorio de arquivo proprio\n\n3--Mostrar combinaçoes com mais textonyms de um arquivo\n\n4--Buscar palavras por numero num arquivo\n\n5--Obter textonyms de uma palavra (diccionario)\n\n0--Sair\n\n"
//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define FORMATO_NOME "texttonyms_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME 31
//Definiçao de um caracter padrao para inicializar as variaveis tipo char
#define CHAR_VACIO '_'
#define STRING_VACIO "_"
/////////////////////////////DEFINES

using namespace std;

//funçao que mostra o relatorio de um arquivo padrao requerido nas tarefas do exercicio.
bool opcao1(){

    vector<elemento> elementos;
    string relatorio;
    string arquivo_salvar;
    char exemplo = CHAR_VACIO;

    //chamamos ao metodo encherVetor() para obter todas as palavras do arquivo
    encherVetor(elementos,"textonyms.txt");

    ////////////////////////////////////////////DEBUG
    //encherVetor(elementos,"textonyms_short.txt");
    ////////////////////////////////////////////DEBUG

    //chamamos ao metodo obterNum() para obter os numeros referentes a cada palavra.
    obterNum(elementos);

    //chamamos ao metodo mostrarRelatorio() para mostrar o relatorio requerido. pasamos para ele o vetor de elementos, um string relatorio para armazenar ele e uma string para armazenar o nome do arquivo no caso que quiser ser salvo.
    mostrarRelatorio(elementos,relatorio,arquivo_salvar);

    //Loop que pergunta se o usuario quer mostrar eemplos de textonyms ou nao.
    while(exemplo!= 'S' && exemplo!= 's' && exemplo!= 'N' && exemplo!= 'n'){
        cout << "Voce quer mostrar exemplos de textonyms? (S/N)" << endl;
        cin >> exemplo;
    }
    if(exemplo == 'S' || exemplo == 's'){
        //chamamos ao metodo mostrarExemplos() e pasamos o vetor de elementos, o nome do arquivo no qual salvamos o relatorio e "false" que significa que nao queremos que os exemplos sejam ordenados.
        mostrarExemplos(elementos,arquivo_salvar,false);
    }

    return finalizar();
}

//O mesmo que a opçao 1 pero com um arquivo indicado pelo usuario.
bool opcao2(){

    vector<elemento> elementos;
    string relatorio;
    string arquivo_salvar;
    char exemplo = CHAR_VACIO;
    int erro = 0;
    string nome_arquivo;

    system("cls");

    //Loop para nos asegurar que o usuario insire um arquivo existente.
    while(erro==0){
        cout << "Escreva o path de seu arquivo:" << endl;
        cin >> nome_arquivo;

        ifstream ifs(nome_arquivo.c_str());

        if(!ifs.is_open()){
            cout << "Erro ao abrir o arquivo!" << endl;
            erro=0;
        }
        else{
            erro=1;
            ifs.close();
        }
    }

    encherVetor(elementos,nome_arquivo.c_str());

    /////////////////////////////////////////////////DEBUG
    //encherVetor(elementos,"textonyms_short.txt");
    /////////////////////////////////////////////////DEBUG

    obterNum(elementos);
    mostrarRelatorio(elementos,relatorio,arquivo_salvar);

    while(exemplo!= 'S' && exemplo!= 's' && exemplo!= 'N' && exemplo!= 'n'){
        cout << "Voce quer mostrar exemplos de textonyms? (S/N)" << endl;
        cin >> exemplo;
    }
    if(exemplo == 'S' || exemplo == 's'){
        mostrarExemplos(elementos,arquivo_salvar,false);
    }

    return finalizar();
}

//Essa funçao é muito parecida as anteriores só que nao mostra o relatorio, só os eemplos.
bool opcao3(){

    vector<elemento> elementos;
    int erro = 0;
    string nome_arquivo;
    string arquivo_salvar = STRING_VACIO;

    system("cls");

    while(erro==0){
        cout << "Escreva o path de seu arquivo:" << endl;
        cin >> nome_arquivo;

        ifstream ifs(nome_arquivo.c_str());

        if(!ifs.is_open()){
            cout << "Erro ao abrir o arquivo!" << endl;
            erro=0;
        }
        else{
            erro=1;
            ifs.close();
        }
    }

    encherVetor(elementos,nome_arquivo.c_str());
    obterNum(elementos);
    //Neste caso podemos ver que pasamos a string arquivo_salvar vazia o que vai gerar um arquivo novo. tambem pasamos o ultimo argumento como "true" para o programa ordenar os elementos.
    mostrarExemplos(elementos,arquivo_salvar, true);

    return finalizar();
}


//Funçao que recebe um numero e mostra as palavras que sao textonyms em relaçao a esse numero.
bool opcao4(){

    vector<elemento> elementos;
    int erro = 0;
    string nome_arquivo;
    string numero = STRING_VACIO;
    char buscar = CHAR_VACIO;

    system("cls");

    while(erro==0){
        cout << "Escreva o path de seu arquivo:" << endl;
        cin >> nome_arquivo;

        ifstream ifs(nome_arquivo.c_str());

        if(!ifs.is_open()){
            cout << "Erro ao abrir o arquivo!" << endl;
            erro=0;
        }
        else{
            erro=1;
            ifs.close();
        }
    }

    cout << "Preparando arquivo..." << endl;
    system("cls");

    encherVetor(elementos,nome_arquivo.c_str());

    ////////////////////////////////////////////////DEBUG
    //encherVetor(elementos,"textonyms_short.txt");
    ////////////////////////////////////////////////DEBUG

    obterNum(elementos);

    //loop para repeter a busca de palavas tantas vezes como o usuario quiser.
    while(buscar != 'N' && buscar != 'n'){
        system("cls");
        //Loop que asegura que o numero tem um formato valido (só numeros. No caso o usuario escreva mais de um nunmero separados por espaços, o programa só vai pegar o primeiro).
        while (numero == STRING_VACIO || numero == ""){
            cout << "Escreva um numero valido." << endl;
            cin >> numero;
            for(int i = 0; i < numero.length(); i++){
                if(numero.at(i)<48 || numero.at(i)>57) numero = STRING_VACIO;
            }
        }
        //Chamamos a funçao mostrarPalavras() pasando o vetor de elementos e o numero pelo qual a busca vai ser realizada.
        buscar = mostrarPalavras(elementos,numero);
        //"esvaziamos" a variavel numero para inserir um novo numero.
        numero = STRING_VACIO;
    }

    return finalizar();
}


//Funçao que recebe uma palavra e mostra todas as palavras que sao textonyms dela dentro de um dicionario.
bool opcao5(){

    vector<elemento> elementos;
    string palavra = STRING_VACIO;
    elemento novo;
    char buscar = CHAR_VACIO;

    //Obtemos as palavras do dicionario.
    encherVetor(elementos,"dicionario30000.txt");

    while(buscar != 'N' && buscar != 'n'){
        system("cls");

        //Loop para asegurar que a palavra tem o formato correto.
        while(palavra == STRING_VACIO){
            cout << "Escreva uma palavra para buscar textonyms." << endl;
            cin >> palavra;
            for(int i = 0; i < palavra.length(); i++){
                if(palavra.at(i)<65 || (palavra.at(i)>90 && palavra.at(i)<97) || palavra.at(i)>122) palavra = STRING_VACIO;
            }
        }

        // inicializamos as variaveis do elemento auxiliar "novo".
        novo.numero=STRING_VACIO;
        novo.textonyms=0;

        //Convertemos a palavra a maiusculas
        maiusculas(palavra);
        novo.palavra = palavra;

        //Botamos o elemento novo no final do vetor.
        elementos.push_back(novo);

        obterNum(elementos);

        //Chamamos ao metodo mostrarPalavras() pasando o vetor de elementos e o numero do ultimo elemento (que contém nossa palavra).
        buscar = mostrarPalavras(elementos,elementos.back().numero);

        //"Esvaciamos" a string palavra e tiramos do vetor o elemento auxiliar "novo".
        palavra = STRING_VACIO;
        elementos.pop_back();
    }
    return finalizar();
}

//Funçao main
int main(){

    bool finalizar = false;

    //Mostramos a introduçao
    cout << "Linguagem de programacao" << endl;
    cout << "Questao 17. Textonyms." << endl;
    cout << "Pablo Rufat Munoz" << endl;
    cout << "Marcos Marques" << endl;
    cout << "2017/1\n\n" << endl;
    system("pause");

    //enquanto a funçao finalizar() nao devolva true, vamos chamar a funçao que mostra o menu.
    while(!finalizar){
        switch(mostrarMenu()){
            case(0):
                finalizar = true;
                break;
            case(1):
                finalizar = opcao1();
                break;
            case(2):
                finalizar = opcao2();
                break;
            case(3):
                finalizar = opcao3();
                break;
            case(4):
                finalizar = opcao4();
                break;
            case(5):
                finalizar = opcao5();
                break;
            default:
                finalizar = true;
                break;
        };
    }
    return 0;
}
