#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "vetorDes.hpp"
#include "vetorOrd.hpp"
#include "listaDes.hpp"
#include "hashTable.hpp"
using namespace std;

#define NULLITEM -1

string minuscula(string s);


int main() {
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open("texto.txt");

    //listaDes<string, int> st(NULLITEM);
    // listaDes<string, int> st();
    hashTable st(3);

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (p == "") continue;
        p = minuscula(p);

        int count = st.devolve(p);

        string t = "to";
        if (p == t)
            cout << p << ", " << count << endl;
        if (count == NULLITEM)
            st.insere(p, 1);
        else
            st.insere(p, ++count);

        if (p == t)
            cout << "\t" << p << ", " << st.devolve(p) << endl;
    }
    //st.print();


    cout << st.devolve("to") << endl; // 13
    cout << st.devolve("has") << endl; // 6
    cout << st.devolve("that") << endl; // 2
    cout << st.devolve("anyone") << endl; // 1
    cout << st.devolve("blalbablablablas") << endl; // Não tem

    cout << endl;

    cout << st.devolve("a") << endl; // 4
    cout << st.devolve("b") << endl; // Não tem
    cout << st.devolve("c") << endl; // Não tem
    f.close();

    cout << "Teste contains" << endl;
    cout << st.contains("to") << endl;
    cout << st.contains("blablabla") << endl;
}


string minuscula(string s) {
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}
