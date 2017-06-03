#ifndef TEXTONYMSLIB_H_INCLUDED
#define TEXTONYMSLIB_H_INCLUDED

using namespace std;

struct elemento {
    string palavra;
    string numero;
    int textonyms;
};

//Cabezera das funçoes da biblioteca
int mostrarMenu();
bool finalizar();
void encherVetor(vector<elemento> &elementos, string nomeArquivo);
void obterNum(vector<elemento> &elementos);
void mostrarRelatorio(vector<elemento> &elementos, string &relatorio, string &arquivo_salvar);
void mostrarExemplos(vector<elemento> &elementos, string &arquivo_salvar, bool ordenar);
char mostrarPalavras(vector<elemento> &elementos,string &numero);
void maiusculas(string &palavra);

#endif // TEXTONYMSLIB_H_INCLUDED
