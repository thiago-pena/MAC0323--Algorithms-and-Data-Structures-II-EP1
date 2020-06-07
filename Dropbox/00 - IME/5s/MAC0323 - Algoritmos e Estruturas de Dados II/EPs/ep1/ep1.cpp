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
#include "hashTable.hpp"
using namespace std;

#define NULLITEM -1
#define NULLKEY "NULL"

int main() {
    vetorDes<string, int> st("texto.txt", NULLITEM, NULLKEY);
    cout << st.devolve("to") << endl; // 13
    cout << st.devolve("has") << endl; // 6
    cout << st.devolve("that") << endl; // 2
    cout << st.devolve("anyone") << endl; // 1
    cout << st.devolve("blalbablablablas") << endl; // Não tem

    cout << endl;

    cout << st.devolve("a") << endl; // 4
    cout << st.devolve("b") << endl; // Não tem
    cout << st.devolve("c") << endl; // Não tem
}

// int criaTabela(string arquivo) {
//     regex e {"[_[:punct:]]"};
//     ifstream f;
//     f.open(arquivo);
//
//     vetorDes<string, int> st(NULLITEM);
//     listaOrd<string, int> st(NULLITEM);
//     listaDes<string, int> st(NULLITEM);
//     hashTable st;
//
//     string p;
//     while (f >> p) {
//         p = regex_replace(p, e, "");
//         if (p == "") continue;
//         p = minuscula(p);
//
//         int count = st.devolve(p);
//
//         if (count == NULLITEM)
//             st.insere(p, 1);
//         else
//             st.insere(p, ++count);
//     }
//
//     f.close();
// }
