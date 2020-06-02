#ifndef LISTADES_HPP
#define LISTADES_HPP
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
        int n; // número de elementos na Tabela de Símbolos
    public:
        listaDes();
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave); // value paired with key ( null if key is absent)
        //void remove (Chave chave);
        int rank(Chave chave); // find the number of keys less than a given key
        Chave seleciona(int k); // find the key with a given rank
};

template <class Chave, class Item>
listaDes<Chave, Item>::listaDes(): ini(nullptr), n(0) {};

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
}


// tratar caso em que não existe
template <class Chave, class Item>
Item listaDes<Chave, Item>::devolve(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return x->valor;
    }
}

// rank tem que retornar se é menor tb
// faz sentido rank em EDs não ordenadas?
template <class Chave, class Item>
int listaDes<Chave, Item>::rank(Chave chave) {
    int r = 0;
    for (No *x = ini; x != nullptr; x = x->next, r++) {
        if (x->chave == chave) return r;
    }
}


template <class Chave, class Item>
bool listaDes<Chave, Item>::contains(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return true;
    }
    return false;
}






#endif
