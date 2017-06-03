/////////////////////////////INCLUDES
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
//Input/output manipulation. É usada para modificar a estrutura da saida de resultados.
#include <iomanip>
//Biblioteca usada para gerar os arquivos com nomes baseados na data (ao estilo dos logs)
#include <ctime>
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1--Relatorio de arquivo padrao\n\n2--Relatorio de arquivo proprio\n\n3--Mostrar combinaçoes com mais textonyms\n\n4--Buscar palavras por numero\n\n5--Obter textonyms de uma palavra (diccionario)\n\n0--Sair\n\n"
//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define FORMATO_NOME "texttonyms_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME 31
//Definiçao de um caracter padrao para inicializar as variaveis tipo char
#define CHAR_VACIO '_'
#define STRING_VACIO "_"
//Definiçao da string do relatorio
#define RELATORIO "Existem %d palavras em \"%s\" que podem ser representadas pelo mapeamento de teclas de digitos.\nEles requerem %d combinaçoes de digitos para representa-los.\nAs combinaçoes de digitos %d representam Textonyms.\n\n"
//Definiçao da string da URL do arquivo.
#define URL "http://www.puzzlers.org/pub/wordlists/unixdict.txt"
/////////////////////////////DEFINES

using namespace std;

//estrutura de dados que contem a palavra, o numero correspondente no teclado telefonico e o numero de textonyms dentro do arquivo.
struct elemento {
    string palavra;
    string numero;
    int textonyms;
};

//estrutura de dados que contem cada letra e o numero correspondente no teclado telefonico.
struct letra {
    char letra;
    char num;
};

//array de estruturas de dados "letra" que contem todas as letras com o respectivo numero.
const letra letras[26] = {{'A','2'},{'B','2'},{'C','2'},{'D','3'},{'E','3'},{'F','3'},{'G','4'},{'H','4'},
                            {'I','4'},{'J','5'},{'K','5'},{'L','5'},{'M','6'},{'N','6'},{'O','6'},{'P','7'},
                            {'Q','7'},{'R','7'},{'S','7'},{'T','8'},{'U','8'},{'V','8'},{'W','9'},{'X','9'},
                            {'Y','9'},{'Z','9'}};

//Metodo para transformar uma palavra em maiusculas.
void maiusculas(string &palavra){

    for(int i = 0; i<palavra.length();i++){
        palavra.at(i) = toupper(palavra.at(i));
    }
}

//Funçao que mostra o menu de opçoes inicial
int mostrarMenu(){

    int opcao=-1;

    //Enquanto o usuario nao escreva uma opçao valida o menu vai se mostrar uma e outra vez.
    while(opcao<0 || opcao>5){
        system("cls");
        //Usamos a variavel definida 'menu'
        cout << menu << endl;
        cin >> opcao;
        if(opcao<0 || opcao>5){
            cout << "Inserir uma opcao valida (0-5)" << endl;
            Sleep(2000);
        }
    }
    return opcao;
}

//Funçao que obtem as palavras de um arquivo e enche o vetor de elementos com elas
void encherVetor(vector<elemento> &elementos, string nome){

    vector<string> lista;
    string aux;
    elemento elem;

    //enchemos um vetor de strings com todas as palavras do arquivo, linha a linha
    ifstream arquivo(nome.c_str());
    while (std::getline(arquivo, aux))
    {
        lista.push_back (aux);
    }

    //Usamos o metodo random_shuffle para embarajar o vetor de palavras
    random_shuffle(lista.begin(), lista.end());

    //Usamos uma variavel auxiliar 'elem' de tipo elemento para obter as palavras da lista e adicionamos ele ao vetor de elementos.
    while (!lista.empty()){
        elem.numero = "";
        elem.textonyms = 1;
        //back() extrai o conteudo da ultima posiçao
        elem.palavra=lista.back();
        //pop_back() elimina o objeto na ultima posiçao reduzindo o tamanho do vetor
        lista.pop_back();
        //push_back() insire um elemento no vetor na ultima posiçao.
        elementos.push_back(elem);
    }
}

//Funçao que devolve o unmero correspondente a uma palavra
string strToNum(string str){

    string num;

    //Por cada letra da palavra o loop vai acionar o numero correspondente à variavel num
    for(int i = 0; i < str.length(); i++){

        for(int j = 0; j < 26 ; j++){
            if(toupper(str.at(i))==letras[j].letra){
                num+=letras[j].num;
            }
        }

        //comprobaçao de que sejam só letras (a-z, A-Z)
        if(str.at(i)<65 || (str.at(i)>90 && str.at(i)<97) || str.at(i)>122){
            //No caso achar um caracter nao valido, a string num se devolve vazia.
            num = STRING_VACIO;
            i=str.length();
        }
    }

return num;
}


//Metodo que adiciona os numeros correspondentes a cada palavra no vetor de elementos.
void obterNum(vector<elemento> &elementos){

    system("cls");
    cout << "Buscando textonyms..." << endl;

    //Para cada elemento do vetor vamos chamar ao metodo strToNum() pasando a palavra para obter o numero.
    for(int i = 0; i < elementos.size(); i++){
        elementos.at(i).numero = strToNum(elementos.at(i).palavra);

        //percorremos os elementos que ja tem numero e comprobamos as repetiçoes (dos que nao sao nulos '_')
        for(int j = 0; j < i; j++){
            if(elementos.at(i).numero == elementos.at(j).numero && elementos.at(j).numero!=STRING_VACIO){
                //incrementamos em um a variavel textonyms dos dois elementos.
                elementos.at(i).textonyms++;
                elementos.at(j).textonyms++;
            }
        }
    }
}

//Metodo para salvar num arquivo os exemplos mostrados no metodo mostrarExemplos().
void salvarExemplos(vector<string> resultado, string arquivo_salvar){

    ofstream arquivoSalvar;

    //No caso o parametro arquivo_salvar esteja vazio criamos um novo arquivo
    if(arquivo_salvar==STRING_VACIO){

        //Formatamos o nome do arquivo com a data e hora do momento da criaçao do arquivo segundo o formato definido acima.
        char nome[TAMANHO_NOME];
        time_t timestamp = time(0);
        strftime(nome, sizeof(nome), FORMATO_NOME, localtime(&timestamp));

        arquivoSalvar.open (nome);
    //No caso ja tenhamos um arquivo_salvo com o relatorio do ponto 1, abrimos ele em modo append para adicionar linhas ao final.
    }else{

        arquivoSalvar.open(arquivo_salvar.c_str(), ios::app);
        arquivoSalvar << "\n\nExemplos:\n\n";

    }

    //Loop para adicionar todas as linhas do vetor resultado.
    for(int i=0;i<resultado.size();i++){
        arquivoSalvar << resultado.at(i) << endl;
    }

    arquivoSalvar.close();
}

//Metodo para mostrar o relatorio mostrado no metodo mostrarRelatorio.
string salvarRelatorio(string &relatorio){

    ofstream arquivoSalvar;

    //Formatamos o nome do arquivo com a data e hora do momento da criaçao do arquivo segundo o formato definido acima.
    char nome[TAMANHO_NOME];
    time_t timestamp = time(0);
    strftime(nome, sizeof(nome), FORMATO_NOME, localtime(&timestamp));

    arquivoSalvar.open (nome);

    //Escrevemos as linhas que contem a string relatorio que vem como parametro.
    arquivoSalvar << "\n\n" << relatorio<< endl;

    arquivoSalvar.close();

    return nome;

}

//Metodo que cria e mostra o relatorio requerido na tarefa.
void mostrarRelatorio(vector<elemento> &elementos, string &relatorio, string &arquivo_salvar){

    int rel0=0;
    double rel3=0;
    vector<string> strNumsUnique;
    char salvar = CHAR_VACIO;

    system("cls");

    cout << "Mostrando relatorio..." << endl;

    for(int i = 0; i < elementos.size(); i++){

        //Os elementos que tem um numero nao nulo sao os que podemos mostrar com teclado telefonico (só caracteres a-z, A-Z)
        if(elementos.at(i).numero!= STRING_VACIO){

            rel0++;

            //para saber a quantidade de numeros que formam textonyms temos que achar os elementos com a variavel textonyms maior que 1. O problema e que todos os textonyms tem armazenado nessa variavel o numero total (p.e. palavra abg - num. 224 - textonyms 2 || palavra aci - num. 224 - textonyms 2). A soluçao foi somar 1/textonyms para que no final tenhamos quantidade de numeros sem repetiçao.
            if(elementos.at(i).textonyms > 1){
                    rel3 += (1/(double)elementos.at(i).textonyms);
            }

            //enchemos o vetor strNumsUnique para ter todos os numeros diferentes (tenham ou nao mais de um textonym). Para isso percorremos o vetor strNumsUnique e se chegamos ao fim (strNumsUnique.end()) significa que nao existe ese elemento e entao adicionamos ele.
            if(find(strNumsUnique.begin(), strNumsUnique.end(), elementos.at(i).numero) == strNumsUnique.end()){

                strNumsUnique.push_back(elementos.at(i).numero);

            }
        }
    }
////////////////////////////////////////DEBUG
//    ofstream arquivoSalvar;
//   arquivoSalvar.open ("prova.txt");
//    for(int i=0;i<elementos.size();i++){
//        arquivoSalvar <<"\t"<<left<<setw(20)<<elementos.at(i).palavra<<setw(20)<<elementos.at(i).numero<<right<<setw(20)<<setprecision(3)<<elementos.at(i).textonyms<<"--"<< endl;
//    }
//   arquivoSalvar.close();
////////////////////////////////////////DEBUG
    system("cls");

    //Usamos um array de char de 500 posiçoes para armazenar nele o string final do relatorio formatado com sprintf().
    char buffer[500];
    sprintf(buffer,RELATORIO,rel0,URL,strNumsUnique.size(),(int)round(rel3));

    //convertemos o buffer à string.
    relatorio = string(buffer);

    cout << endl;

    //Mostramos o relatorio.
    cout << relatorio;

    //Perguntamos ao usuario se quer salvar o arquivo (o loop é necesario para que o usuario so possa marcar S ou N).
    while(salvar!= 'S' && salvar!= 's' && salvar!= 'N' && salvar!= 'n'){
        cout << "Voce quer salvar o relatorio? (S/N)" << endl;
        cin >> salvar;
    }
    if(salvar == 'S' || salvar == 's'){
        arquivo_salvar = salvarRelatorio(relatorio);
    }
}


//Metodo para ordenar de maior a menor os elementos do vetor em referencia ao numero de textonyms de cada numero. Usamos o metodo simples bubble sort.
void ordenarNumeros(vector<elemento> &elementos){
    elemento aux;
    int n = elementos.size();
    int m = 0;

    cout << "Ordenando..." << endl;


    while(n>0){
        m=0;
        //Para cada elemento de 1 a n comprobamos se o anterior e menor. No caso de ser certo trocamos eles.
        for(int i = 1; i < n; i++){
            if(elementos.at(i-1).textonyms < elementos.at(i).textonyms){
                aux = elementos.at(i-1);
                elementos.at(i-1) = elementos.at(i);
                elementos.at(i) = aux;
                m = i;
            }
        }
        //O ultimo valor de m significa que o resto dos valores ja tao ordenados, entao reduzimos o valor de n e fazemos outra pasada.
        n = m;
    }
}

//metodo que mostra os exemplos de textonyms que tem cada numero.
void mostrarExemplos(vector<elemento> &elementos, string &arquivo_salvar, bool ordenar){

    vector<string> numeros;
    vector<string> resultado;
    string aux;
    char cont = CHAR_VACIO;
    char salvar = CHAR_VACIO;

    system("cls");
    cout << "Mostrando exemplos\n" << endl;

    //No caso recebamos o parametro ordenar == true, chamamos ao metodo que ordena o vetor de maior a menor.
    if(ordenar){
        ordenarNumeros(elementos);
    }

    //Vamos encher um vetor de strings "numero" com os numeros diferentes que tem mais de um textonym
    for(int i = 0; i < elementos.size(); i++){
        //Usamos o metodo find() do mesmo modo que em casos anteriores.
        if(elementos.at(i).textonyms > 1 && (find(numeros.begin(), numeros.end(), elementos.at(i).numero) == numeros.end())){
            numeros.push_back(elementos.at(i).numero);
        }
    }

    for(int j = 0; j < numeros.size(); j++){

        //Para cada numero em "numeros" mostramos ele e vamos formando a string aux com o metodo append, que adiciona texto ao final de uma string.
        cout <<left<<setw(10)<< numeros.at(j) <<left<<setw(5) <<" --> ";
        aux = numeros.at(j);
        aux.append("\t\t-->\t\t");

        //Percorremos o vetor "elementos" na busca das palavras que compartilham o numero correspondente do for anterior.
        for(int k = 0; k < elementos.size(); k++){

            //Quando achar uma palavra nova, mostramos ela e adicionamos ela a string aux.
            if(elementos.at(k).numero == numeros.at(j)){
                cout << left<<setw(10)<<elementos.at(k).palavra;
                aux.append(elementos.at(k).palavra);
                aux.append("\t\t");
            }
        }
        cout << endl;

        //adicionamos a string aux ao vetor resultado para usar ele depois se o usuario quer salvar os exemplos.
        aux.append("\n\n");
        resultado.push_back(aux);
        aux="";

        //Usamos o loop já usado no exercicio anterior para perguntar ao usuario se quer continuar mostrando os dados.
        if(j%100==0 && j!=0 && cont!='F' && cont!='f'){
            cont=CHAR_VACIO;
            while(cont!='S' && cont!='s' && cont!='N' && cont!='n' && cont!='F' && cont!='f'){

                cout << "\n\nContinuar? (S/N. F para continuar ate o fim.)" << endl;

                cin >> cont;

                if(cont == 'N' || cont == 'n'){
                    j = numeros.size();
                }else if(cont == 'S' || cont == 's' || cont == 'F' || cont == 'f'){
                    //Se o usuario decidir continuar mostramos uma cabezera.
                    cout <<"\n\n\CONTINUACAO\n\n"<< endl;
                }
            }
        }
    }

    //Perguntamos ao usuario se quer salvar os exemplos no arquivo.
    while(salvar!= 'S' && salvar!= 's' && salvar!= 'N' && salvar!= 'n'){
        cout << "Voce quer salvar os exemplos? (S/N)" << endl;
        cin >> salvar;
    }
    if(salvar == 'S' || salvar == 's'){
        //Caso queramos salvar o arquivo, pasamos ao metodo salvarExemplos() o vetor resultado que temos ido criando e contem o mesmo que tem sido mostrado na tela e o nome do arquivo a ser salvo, que pode estar vazio ou nao.
        salvarExemplos(resultado,arquivo_salvar);
    }
}

//Metodo para mostrar as Palavras que sao textonyms de um numero.
char mostrarPalavras(vector<elemento> &elementos,string &numero){

    char buscar = CHAR_VACIO;
    int cont = 0;
    int pos = 0;

    system("cls");
    cout << "\n\nTexttonyms do numero " << numero << ": ";

    //Percorremos todo o vetor elementos
    for(int i = 0; i < elementos.size(); i++){
        //Quando achar um numero igual ao que o usuario inseriu mostramos a palavra e incrementamos o contador. tambem modificamos o valor da variavel pos.
        if(elementos.at(i).numero == numero){
            cout << elementos.at(i).palavra << " ";
            cont++;
            pos = i;
        }
    }

    //No caso de nao ter nenhum textonym ou que o unico que tiver esteja na ultima posiçao do vetor (para isso usamos a variavel pos), onde se encontra o elemento que nós adicionamos para fazer a busca e nao tem que ser contado, entao mostramos o seguinte texto.
    if(cont == 0 || (cont == 1 && pos == elementos.size()-1)) cout << "Nao tem nenhum textonym da busqueda no arquivo.";

    cout << "\n" << endl;

    //Usamos o seguinte loop para perquntar ao usuario se deseja buscar outro numero ou palavra.
    while(buscar != 'S' && buscar != 's' && buscar != 'N' && buscar != 'n'){
        cout << "Deseja buscar mais textonyms? (S/N)" << endl;
        cin >> buscar;
    }
    return buscar;
}
//funçao para perguntar ao usuario se ele quer finalizar o apicativo o mostrar o menu inicial outra vez
bool finalizar(){

    char fim = CHAR_VACIO;

    //Se pergunta ao usuario se que sair e devolve um valor booleano para a funçao main
    while(fim!='S' && fim!='s' && fim!='N' && fim!='n'){
        cout << "\n\n\nDeseja finalizar o programa? (S/N)" << endl;
        cin >> fim;
    }

    if(fim=='S' || fim == 's'){
        return true;
    }else{
        return false;
    }

}
