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


    //vetorDes<string, int> st(NULLITEM);
    //vetorOrd<string, int> st(NULLITEM);
    // listaOrd<string, int> st(NULLITEM);
    // treap<string, int> st(NULLITEM);
    arvore23<string, int> st(NULLITEM);

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
    st.insere("A", 0);
    st.insere("L", 1);
    st.insere("G", 2);
    st.insere("O", 3);
    st.insere("R", 4);
    st.insere("I", 5);
    st.insere("T", 6);
    st.insere("H", 7);
    st.insere("M", 8);
    st.insere("S", 9);

    cout << "\nTeste - Devolve\n";
    cout << "A: " << st.devolve("A") << endl;
    cout << "L: " << st.devolve("L") << endl;
    cout << "G: " << st.devolve("G") << endl;
    cout << "O: " << st.devolve("O") << endl;
    cout << "R: " << st.devolve("R") << endl;
    cout << "I: " << st.devolve("I") << endl;
    cout << "T: " << st.devolve("T") << endl;
    cout << "H: " << st.devolve("H") << endl;
    cout << "M: " << st.devolve("M") << endl;
    cout << "S: " << st.devolve("S") << endl;
    cout << "B: " << st.devolve("B") << endl;
    cout << "xxx: " << st.devolve("xxx") << endl;

    cout << endl;

    cout << "\nTeste - Insere 2\n";
    st.insere("A", 0 + 1);
    st.insere("L", 1 + 1);
    st.insere("G", 2 + 1);
    st.insere("O", 3 + 1);
    st.insere("R", 4 + 1);
    st.insere("T", 5 + 1);
    st.insere("H", 6 + 1);
    st.insere("M", 7 + 1);
    st.insere("S", 8 + 1);

    cout << endl;

    cout << "\nTeste - Devolve 2\n";
    cout << "A: " << st.devolve("A") << endl;
    cout << "L: " << st.devolve("L") << endl;
    cout << "G: " << st.devolve("G") << endl;
    cout << "O: " << st.devolve("O") << endl;
    cout << "R: " << st.devolve("R") << endl;
    cout << "I: " << st.devolve("I") << endl;
    cout << "T: " << st.devolve("T") << endl;
    cout << "H: " << st.devolve("H") << endl;
    cout << "M: " << st.devolve("M") << endl;
    cout << "S: " << st.devolve("S") << endl;
    cout << "B: " << st.devolve("B") << endl;
    cout << "xxx: " << st.devolve("xxx") << endl;

    cout << endl;

    cout << "\nTeste rank\n";
    cout << "A: " << st.rank("A") << endl;
    cout << "G: " << st.rank("G") << endl;
    cout << "H: " << st.rank("H") << endl;
    cout << "I: " << st.rank("I") << endl;
    cout << "L: " << st.rank("L") << endl;
    cout << "M: " << st.rank("M") << endl;
    cout << "O: " << st.rank("O") << endl;
    cout << "R: " << st.rank("R") << endl;
    cout << "S: " << st.rank("S") << endl;
    cout << "T: " << st.rank("T") << endl;
    cout << "B: " << st.rank("B") << endl;
    cout << "xxx: " << st.rank("xxx") << endl;

    cout << "----------------" << endl;
    cout << "PRINT" << endl;
    st.printPre();
    cout << "----------------" << endl;


    cout << "======= Teste seleciona =======" << endl;

    cout << "0: " << st.seleciona(0) << endl;
    cout << "1: " << st.seleciona(1) << endl;
    cout << "2: " << st.seleciona(2) << endl;
    cout << "3: " << st.seleciona(3) << endl;
    cout << "4: " << st.seleciona(4) << endl;
    cout << "5: " << st.seleciona(5) << endl;
    cout << "6: " << st.seleciona(6) << endl;
    cout << "7: " << st.seleciona(7) << endl;
    cout << "8: " << st.seleciona(8) << endl;
    cout << "9: " << st.seleciona(9) << endl;
    cout << "10: " << st.seleciona(10) << endl;



    //
    // cout << "\nTeste Remove\n";
    // cout << "--- Remove s4 ---\n";
    // st.remove("s4");
    // cout << "--- Remove A ---\n";
    // st.remove("A");
    // cout << "--- Remove L ---\n";
    // st.remove("L");
    // cout << "--- Remove G ---\n";
    // st.remove("G");
    // cout << "--- Remove O ---\n";
    // st.remove("O");
    // cout << "--- Remove R ---\n";
    // st.remove("R");
    // cout << "--- Remove I ---\n";
    // st.remove("I");
    // cout << "--- Remove T ---\n";
    // st.remove("T");
    // cout << "--- Remove H ---\n";
    // st.remove("H");
    // cout << "--- Remove M ---\n";
    // st.remove("M");
    // cout << "--- Remove S ---\n";
    // st.remove("S");
    //
    //
    // cout << "----------------" << endl;
    // cout << "PRINT" << endl;
    // st.printPre();
    // cout << "----------------" << endl;
    //
    // cout << "\nTeste rank 2\n";
    // cout << "A: " << st.rank("A") << endl;
    // cout << "G: " << st.rank("G") << endl;
    // cout << "H: " << st.rank("H") << endl;
    // cout << "I: " << st.rank("I") << endl;
    // cout << "L: " << st.rank("L") << endl;
    // cout << "M: " << st.rank("M") << endl;
    // cout << "O: " << st.rank("O") << endl;
    // cout << "R: " << st.rank("R") << endl;
    // cout << "S: " << st.rank("S") << endl;
    // cout << "T: " << st.rank("T") << endl;
    // cout << "B: " << st.rank("B") << endl;
    // cout << "xxx: " << st.rank("xxx") << endl;

}
