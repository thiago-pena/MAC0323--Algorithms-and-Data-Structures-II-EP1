#ifndef LISTADES_HPP
#define LISTADES_HPP
#include "vetorDes.hpp" // contém as funções de sorting de arrays
using namespace std;

template <class Chave, class Item>
class listaDes {
    private:
        struct No {
            Chave chave;
            Item valor;
            No *next;
            No(Chave ch, Item val) {
                chave = ch;
                valor = val;
                next = nullptr;
            }
        };
        No *ini;
        int n;
        Item nullItem;
        Chave nullKey;

    public:
        listaDes(string nome_arquivo, Item nullItem, Chave nullKey);
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes
(string nome_arquivo, Item nullItem, Chave nullKey): ini(nullptr), n(0), nullItem(nullItem), nullKey(nullKey)
{
    regex e {"[_[:punct:]]"};
    ifstream f;
    f.open(nome_arquivo);

    string p;
    while (f >> p) {
        p = regex_replace(p, e, "");
        if (p == "") continue;
        for (int i = 0; (unsigned)i < p.length(); i++)
            p[i] = tolower(p[i]);

        int count = devolve(p);

        if (count == nullItem)
            insere(p, 1);
        else
            insere(p, ++count);
    }

    f.close();
};

template <class Chave, class Item>
void listaDes<Chave, Item>::insere(Chave chave, Item valor) {
    // verifica se existe
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave) {
            x->valor = valor;
            return;
        }
    }
    // não existe -> insere no início
    No *x = new No(chave, valor);
    x->next = ini;
    ini = x;
    n++;
}

template <class Chave, class Item>
Item listaDes<Chave, Item>::devolve(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return x->valor;
    }
    return nullItem;
}

template <class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave) {
        Chave arr[n];
        int i = 0;
        for (No *x = ini; x != nullptr; x = x->next, i++) {
            arr[i] = x->chave;
        }
        quicksort<Chave>(arr, 0, n);
        int ini = 0, fim = n - 1;
        while (ini <= fim) {
            int meio = ini + (fim - ini)/2;
            if (chave < arr[meio])
                fim = meio - 1;
            else if (chave > arr[meio])
                ini = meio + 1;
            else
                return meio;
        }
        return ini;
}


template <class Chave, class Item>
bool listaDes<Chave, Item>::contains(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return true;
    }
    return false;
}

template <class Chave, class Item>
void listaDes<Chave, Item>::remove(Chave chave) {
    if (chave == ini->chave) {
        No *aux = ini;
        ini = ini->next;
        delete aux;
        n--;
        return;
    }
    if (ini->next == nullptr) return;
    No *anterior = ini;
    for (No *x = ini->next; x != nullptr; x = x->next) {
        if (chave == x->chave) {
            anterior->next = x->next;
            delete x;
            n--;
            return;
        }
        anterior = x;
    }
}

template <class Chave, class Item>
Chave listaDes<Chave, Item>::seleciona(int k) {
    if (k < 0 || k >= n) return nullKey;
    Chave arr[n];
    int i = 0;
    for (No *x = ini; x != nullptr; x = x->next, i++) {
        arr[i] = x->chave;
    }
    quicksort<Chave>(arr, 0, n);
    return arr[k];
}

#endif
