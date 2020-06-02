#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "vetorDes.hpp"
#include "vetorOrd.hpp"
#include "listaDes.hpp"
using namespace std;

#define NULLITEM -1

int main() {
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open("texto.txt");

    //listaDes<string, int> st(NULLITEM);
    listaDes<string, int> st();

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (!st.contains(p)) {
            st.insere(p, 1);
        }
        else {
            int count = st.devolve(p);
            cout << p << ", count: " << count << endl;
            st.insere(p, ++count);
        }
    }

    cout << st.devolve("to") << endl; // 13
    cout << st.devolve("has") << endl; // 6
    cout << st.devolve("that") << endl; // 2
    cout << st.devolve("anyone") << endl; // 1
    cout << st.devolve("blalbablablablas") << endl; // Não tem


}
