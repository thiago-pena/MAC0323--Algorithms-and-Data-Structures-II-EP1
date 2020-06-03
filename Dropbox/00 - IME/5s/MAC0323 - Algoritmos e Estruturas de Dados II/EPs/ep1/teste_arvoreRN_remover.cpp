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

    //         [10]
    //       /      \
    //     (5)        (30)
    //   /   \      /     \
    // [2]   [8]  [20]     [40]
    //              \     /
    //             (25) (35)
    // remover 30 (troca com 25)

    cout << "\nTeste 1 - remoção de vermelho\n";
    // st.insere("30", 1);
    // st.insere("25", 1);
    // st.insere("40", 1);
    // st.insere("35", 1);
    // st.insere("50", 1);
    // st.insere("60", 1);
    // st.insere("45", 1);

    // Teste
    st.insere("30", 1);
    st.insere("25", 1);
    st.insere("40", 1);
    st.insere("35", 1);
    st.remove("35");

    cout << "-------------------------" << endl;
    cout << "PRINT" << endl;
    st.print();
    cout << "-------------------------" << endl;


    cout << "Remove 40" << endl;
    st.remove("40");

    cout << "-------------------------" << endl;
    cout << "PRINT" << endl;
    st.print();
}
