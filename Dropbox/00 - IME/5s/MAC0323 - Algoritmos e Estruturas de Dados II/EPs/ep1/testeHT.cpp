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


    //vetorDes<string, int> st(NULLITEM);
    //vetorOrd<string, int> st(NULLITEM);
    // listaOrd<string, int> st(NULLITEM);
    // treap<string, int> st(NULLITEM);
    hashTable st(3);

    st.insere("a", 1);
    st.insere("b", 2);
    st.insere("c", 3);
    st.insere("d", 4);

    cout << "devolve: " << st.devolve("a") << endl;
    cout << "devolve: " << st.devolve("b") << endl;
    cout << "devolve: " << st.devolve("c") << endl;
    cout << "devolve: " << st.devolve("d") << endl;

    st.insere("a", 5);
    st.insere("b", 6);
    st.insere("c", 7);
    st.insere("d", 8);

    cout << "devolve: " << st.devolve("a") << endl;
    cout << "devolve: " << st.devolve("b") << endl;
    cout << "devolve: " << st.devolve("c") << endl;
    cout << "devolve: " << st.devolve("d") << endl;


}
