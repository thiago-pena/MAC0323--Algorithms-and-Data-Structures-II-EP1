#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "vetorDes.hpp"
#include "vetorOrd.hpp"
#include "listaDes.hpp"
#include "listaOrd.hpp"
#include "arvoreBin.hpp"
#include "treap.hpp"
#include "arvore23.hpp"
#include "arvoreRN.hpp"
using namespace std;

#define NULLITEM -1

int main() {
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open("texto.txt");

    string s = "AbDeFaPf";
    cout << s << endl;

    cout << s << endl;


    //vetorDes<string, int> st(NULLITEM);
    //vetorOrd<string, int> st(NULLITEM);
    // listaOrd<string, int> st(NULLITEM);
    // treap<string, int> st(NULLITEM);
    //arvore23<string, int> st(NULLITEM);
    arvoreRN<string, int> st(NULLITEM);

    // cout << "\nTeste 1 - insere elemento não pertencente\n";
    // st.insere("a", 7); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 7); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 8); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 9); // 1
    // cout << st.devolve("a") << endl; // 7

    //42 54 19 25 30 74 17 6 10 62 33 40


    cout << "\nTeste 2 - inserir elementos de árvores de exemplo 1\n";
    cout << "Insere s42 15" << endl;
    st.insere("s42", 15);
    cout << "\tTeste/Devolve | s42: " << st.devolve("s42") << endl;
    cout << "Insere s42 14" << endl;
    st.insere("s42", 42);
    cout << "\tTeste/Devolve | s42: " << st.devolve("s42") << endl;
    cout << "Insere s54 7" << endl;
    st.insere("s54", 54);
    cout << "\tTeste/Devolve | s42: " << st.devolve("s42") << endl;
    cout << "\tTeste/Devolve | s54: " << st.devolve("s54") << endl;

    cout << "Insere s19 91" << endl;
    st.insere("s19", 19);
    cout << "\tTeste/Devolve | s19: " << st.devolve("s19") << endl;
    cout << "\tTeste/Devolve | s54: " << st.devolve("s54") << endl;
    cout << "\tTeste/Devolve | s42: " << st.devolve("s42") << endl;

    cout << "Insere s25 25" << endl;
    st.insere("s25", 25);
    cout << "\tTeste/Devolve | s19: " << st.devolve("s19") << endl;
    cout << "\tTeste/Devolve | s25: " << st.devolve("s25") << endl;
    cout << "\tTeste/Devolve | s54: " << st.devolve("s54") << endl;
    cout << "\tTeste/Devolve | s42: " << st.devolve("s42") << endl;

    cout << "Insere s30 30" << endl;
    st.insere("s30", 30);

    cout << "Insere s74 74" << endl;
    st.insere("s74", 74);

    cout << "Insere s17 17" << endl;
    st.insere("s17", 17);

    cout << "Insere s06 6" << endl;
    st.insere("s06", 6);

    cout << "PRINT" << endl;
    st.print();


}
