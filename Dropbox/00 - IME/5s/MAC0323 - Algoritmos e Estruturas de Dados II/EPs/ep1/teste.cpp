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

    cout << "\nTestes\n";
    cout << "Teste 1 - rank com elemento não pertencente\n";
    // cout << "rank: " << st.rank("a") << endl; // 0

    cout << "\nTeste 2 - insere elemento não pertencente\n";
    st.insere("a", 14);
     // cout << "rank: " << st.rank("a") << endl; // 0


    cout << "\nTeste 3 - devolve elemento não pertencente\n";
    cout << st.devolve("a") << endl; // 14

    cout << "\nTeste 4 - insere elemento não pertencente\n";
    st.insere("a", 7); // 1
    cout << st.devolve("a") << endl; // 7
    st.insere("a", 7); // 1
    cout << st.devolve("a") << endl; // 7
    st.insere("a", 8); // 1
    cout << st.devolve("a") << endl; // 7
    st.insere("a", 9); // 1
    cout << st.devolve("a") << endl; // 7
    /*

    cout << "\nTeste 5 - devolve elemento pertencente\n";
    cout << "devolve (7): " << st.devolve("b") << endl; // 7
    cout << "rank (a / 0):  " << st.rank("a") << endl; // 0
    cout << "rank (b / 1):  " << st.rank("b") << endl; // 1
    cout << "rank (c / 2):  " << st.rank("c") << endl; // 2

    cout << "\nTeste 6 - insere elemento na posição 1\n";
    st.insere("ab", 6);
    cout << "devolve: " << st.devolve("ab") << endl; // 6
    cout << "rank (a / 0):  " << st.rank("a") << endl; // 0
    cout << "rank (ab / 1):  " << st.rank("ab") << endl; // 1
    cout << "rank (b / 1):  " << st.rank("b") << endl; // 2
    cout << "rank (c / 2):  " << st.rank("c") << endl; // 3

    cout << "\nTeste 7 - contains()\n";
    cout << "contains:  " << st.contains("a") << endl; // 1
    cout << "contains:  " << st.contains("ab") << endl; // 0
    cout << "contains:  " << st.contains("b") << endl; // 1
    cout << "contains:  " << st.contains("c") << endl; // 0

    cout << "\nTeste 8 - devolve()\n";
    cout << "devolve:  " << st.devolve("a") << endl; // 1
    cout << "devolve:  " << st.devolve("ab") << endl; // 0
    cout << "devolve:  " << st.devolve("b") << endl; // 1
    cout << "devolve:  " << st.devolve("c") << endl; // 0

    cout << "\nTeste 9 - insere existente com novo valor()\n";
    st.insere("a", 15);
    st.insere("b", 16);
    cout << "devolve:  " << st.devolve("a") << endl; // 15
    cout << "devolve:  " << st.devolve("b") << endl; // 16
    */
}
