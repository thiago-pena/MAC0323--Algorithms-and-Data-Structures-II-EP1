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
using namespace std;

#define NULLITEM -1

int main() {
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open("texto.txt");

    string s = "AbDeFaPf";
    cout << s << endl;

    cout << s << endl;


    vetorDes<string, int> st(NULLITEM);
    //vetorOrd<string, int> st(NULLITEM);
    // listaOrd<string, int> st(NULLITEM);
    //treap<string, int> st(NULLITEM);
    //arvoreBin<string, int> st(NULLITEM);

    // cout << "\nTeste 1 - insere elemento não pertencente\n";
    // st.insere("a", 7); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 7); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 8); // 1
    // cout << st.devolve("a") << endl; // 7
    // st.insere("a", 9); // 1
    // cout << st.devolve("a") << endl; // 7

    cout << "\nTeste 2 - inserir elementos de árvores de exemplo 1\n";
    st.insere("s18", 18); // 1
    cout << "Devolve 18: " << st.devolve("s18") << endl;


    // st.insere("s4", 4); // 1
    // st.insere("s29", 29); // 1
    // st.insere("s26", 26); // 1
    // st.insere("s37", 37); // 1
    // st.insere("s25", 25); // 1
    // st.insere("s19", 19); // 1
    // st.insere("s41", 41); // 1
    // st.insere("s46", 46); // 1
    //
    // cout << st.devolve("s18") << endl;
    // cout << st.devolve("s4") << endl;
    // cout << st.devolve("s29") << endl;
    // cout << st.devolve("s26") << endl;
    // cout << st.devolve("s37") << endl;
    // cout << st.devolve("s25") << endl;
    // cout << st.devolve("s19") << endl;
    // cout << st.devolve("s41") << endl;
    // cout << st.devolve("s46") << endl;
    //
    // cout << endl;
    //
    // st.insere("s18", 18 + 1);
    // st.insere("s4", 4 + 1);
    // st.insere("s29", 29 + 1);
    // st.insere("s26", 26 + 1);
    // st.insere("s37", 37 + 1);
    // st.insere("s25", 25 + 1);
    // st.insere("s19", 19 + 1);
    // st.insere("s41", 41 + 1);
    // st.insere("s46", 46 + 1);
    //
    // cout << endl;
    //
    // cout << st.devolve("s18") << endl;
    // cout << st.devolve("s4") << endl;
    // cout << st.devolve("s29") << endl;
    // cout << st.devolve("s26") << endl;
    // cout << st.devolve("s37") << endl;
    // cout << st.devolve("s25") << endl;
    // cout << st.devolve("s19") << endl;
    // cout << st.devolve("s41") << endl;
    // cout << st.devolve("s46") << endl;
    //
    // cout << endl;
    //
    // cout << st.devolve("a") << endl;
    // cout << st.devolve("s6") << endl;
    // cout << st.devolve("s15") << endl;
    // cout << st.devolve("s19") << endl;
    // cout << st.devolve("s19") << endl;
    // cout << st.devolve("s22") << endl;
    // cout << st.devolve("s26") << endl;
    // cout << st.devolve("s27") << endl;
    // cout << st.devolve("s30") << endl;
    // cout << st.devolve("s38") << endl;
    // cout << st.devolve("s42") << endl;
    // cout << st.devolve("s50") << endl;
    //
    // cout << "\nTeste rank\n";
    // cout << "s18: " << st.rank("s18") << endl;
    // cout << "s19: " << st.rank("s19") << endl;
    // cout << "s25: " << st.rank("s25") << endl;
    // cout << "s26: " << st.rank("s26") << endl;
    // cout << "s29: " << st.rank("s29") << endl;
    // cout << "s37: " << st.rank("s37") << endl;
    // cout << "s4: " << st.rank("s4") << endl;
    // cout << "s41: " << st.rank("s41") << endl;
    // cout << "s46: " << st.rank("s46") << endl;
    // cout << "aaa: " << st.rank("aaa") << endl;
    // cout << "xxx: " << st.rank("xxx") << endl;
    //
    // cout << "----------------" << endl;
    // cout << "PRINT" << endl;
    // st.print();
    // cout << "----------------" << endl;
    //
    // cout << "\nTeste Remove\n";
    // st.remove("s37");
    //
    // cout << "----------------" << endl;
    // cout << "PRINT" << endl;
    // st.print();
    // cout << "----------------" << endl;
    //
    // cout << "s18: " << st.rank("s18") << endl;
    // cout << "s19: " << st.rank("s19") << endl;
    // cout << "s25: " << st.rank("s25") << endl;
    // cout << "s26: " << st.rank("s26") << endl;
    // cout << "s29: " << st.rank("s29") << endl;
    // cout << "s4: " << st.rank("s4") << endl;
    // cout << "s41: " << st.rank("s41") << endl;
    // cout << "s46: " << st.rank("s46") << endl;
    // cout << "aaa: " << st.rank("aaa") << endl;
    // cout << "xxx: " << st.rank("xxx") << endl;
    //
    // cout << "======= Teste seleciona =======" << endl;
    //
    // cout << "0: " << st.seleciona(0) << endl;
    // cout << "1: " << st.seleciona(1) << endl;
    // cout << "2: " << st.seleciona(2) << endl;
    // cout << "3: " << st.seleciona(3) << endl;
    // cout << "4: " << st.seleciona(4) << endl;
    // cout << "5: " << st.seleciona(5) << endl;
    // cout << "6: " << st.seleciona(6) << endl;
    // cout << "7: " << st.seleciona(7) << endl;
    // cout << "8: " << st.seleciona(8) << endl;
    // cout << "9: " << st.seleciona(9) << endl;
    // cout << "10: " << st.seleciona(10) << endl;

}
