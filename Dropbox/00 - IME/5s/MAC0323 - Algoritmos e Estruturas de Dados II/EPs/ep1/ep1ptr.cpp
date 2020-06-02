// Definir seed? (Treap)
//g++ -std=c++11 ep1ptr.cpp prob.cpp -o ep1


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

string minuscula(string s);

int main() {
    regex e {"(([_[:punct:]]|\")[ ]?)*"};
    ifstream f;
    f.open("texto.txt"); // dar close

    //listaDes<string, int> st(NULLITEM);
    //listaDes<string, int> st;
    //listaOrd<string, int> st(NULLITEM);
    arvore23<string, int> st(NULLITEM);

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (p == "") continue;
        p = minuscula(p);

        if (!st.contains(p)) {
            st.insere(p, 1);
        }
        else {
            int count = st.devolve(p);
            st.insere(p, ++count);
        }
    }
    //st.print();


    cout << st.devolve("to") << endl; // 13
    cout << st.devolve("has") << endl; // 6
    cout << st.devolve("that") << endl; // 2
    cout << st.devolve("anyone") << endl; // 1
    cout << st.devolve("blalbablablablas") << endl; // Não tem

    f.close();
}


string minuscula(string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}
