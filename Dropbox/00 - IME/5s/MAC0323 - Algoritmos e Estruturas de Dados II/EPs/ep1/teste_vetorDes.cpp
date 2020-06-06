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
#include "hashTable.hpp"
using namespace std;

#define NULLITEM -1

int main() {
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open("texto.txt");

    string s = "AbDeFaPf";
    cout << s << endl;

    cout << s << endl;


    // vetorDes<string, int> st(NULLITEM);
    // vetorOrd<string, int> st(NULLITEM);
    // listaDes<string, int> st(NULLITEM);
    //listaOrd<string, int> st(NULLITEM);
    //treap<string, int> st(NULLITEM);
    //arvoreBin<string, int> st(NULLITEM);
    hashTable st;
    // hashTable st(151);


    cout << "\nTeste 1 - inserir elementos1\n";
    st.insere("s05", 3);

    st.insere("s05", 5);
    st.insere("s03", 3);
    st.insere("s02", 2);
    st.insere("s07", 7);
    st.insere("s06", 6);
    st.insere("s01", 1);

    cout << "\nTeste 2 - Devolve\n";
    cout << "Devolve 01: " << st.devolve("s01") << endl;
    cout << "Devolve 02: " << st.devolve("s02") << endl;
    cout << "Devolve 03: " << st.devolve("s03") << endl;
    cout << "Devolve 04: " << st.devolve("s04") << endl;
    cout << "Devolve 05: " << st.devolve("s05") << endl;
    cout << "Devolve 06: " << st.devolve("s06") << endl;
    cout << "Devolve 07: " << st.devolve("s07") << endl;

    cout << "\nTeste 3 - Rank\n";
    cout << "Rank 01: " << st.rank("s01") << endl; // r 0
    cout << "Rank 02: " << st.rank("s02") << endl; // r 1
    cout << "Rank 03: " << st.rank("s03") << endl; // r 2
    cout << "Rank 04: " << st.rank("s04") << endl; // r 3
    cout << "Rank 05: " << st.rank("s05") << endl; // r 3
    cout << "Rank 06: " << st.rank("s06") << endl; // r 4
    cout << "Rank 07: " << st.rank("s07") << endl; // r 5

    cout << "\nTeste 4 - Seleciona\n";
    cout << "Seleciona 0: " << st.seleciona(0) << endl;
    cout << "Seleciona 1: " << st.seleciona(1) << endl;
    cout << "Seleciona 2: " << st.seleciona(2) << endl;
    cout << "Seleciona 3: " << st.seleciona(3) << endl;
    cout << "Seleciona 4: " << st.seleciona(4) << endl;
    cout << "Seleciona 5: " << st.seleciona(5) << endl;
    cout << "Seleciona 6: " << st.seleciona(6) << endl;
    cout << "Seleciona 7: " << st.seleciona(7) << endl;

    cout << "\nTeste 5 - Remove\n";
    cout << "Remove s07: " << endl;
    st.remove("s07");

    cout << "\nTeste 4 - Seleciona\n";
    cout << "Seleciona 0: " << st.seleciona(0) << endl;
    cout << "Seleciona 1: " << st.seleciona(1) << endl;
    cout << "Seleciona 2: " << st.seleciona(2) << endl;
    cout << "Seleciona 3: " << st.seleciona(3) << endl;
    cout << "Seleciona 4: " << st.seleciona(4) << endl;
    cout << "Seleciona 5: " << st.seleciona(5) << endl;
    cout << "Seleciona 6: " << st.seleciona(6) << endl;
    cout << "Seleciona 7: " << st.seleciona(7) << endl;

}
