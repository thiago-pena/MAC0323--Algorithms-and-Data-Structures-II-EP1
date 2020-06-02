#ifndef LISTAORD_HPP
#define LISTAORD_HPP
using namespace std;

template <class Chave, class Item>
class listaOrd {
    public:
        listaOrd(Item nullItem);
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave); // value paired with key ( null if key is absent)
        //void remove (Chave chave);
        int rank(Chave chave); // find the number of keys less than a given key
        Chave seleciona(int k); // find the key with a given rank
        void print();
    
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
        Item nullItem;
};

template <class Chave, class Item>
listaOrd<Chave, Item>::listaOrd(Item nullItem): ini(nullptr), n(0), nullItem(nullItem) {};

template <class Chave, class Item>
void listaOrd<Chave, Item>::insere(Chave chave, Item valor) {
    if (ini == nullptr) {
        No *novo = new No(chave, valor);
        ini = novo;
        return;
    }
    if (chave < ini->chave) {
        No *novo = new No(chave, valor);
        novo->next = ini;
        ini = novo;
        return;
    }
    //

    No *x = ini;
    No *ant = ini;
    while (x != nullptr && x->chave < chave) {
        ant = x;
        x = x->next;
    }

    //cout << "x: " << x->chave << endl;
    if (x == nullptr) { // insere no fim
        No *novo = new No(chave, valor);
        ant->next = novo;
    }
    else

    if (x->chave != chave) {
        No *novo = new No(chave, valor);
        ant->next = novo;
        novo->next = x;
    }
    else {
        x->valor = valor;
    }
}

// tratar caso em que não existe
template <class Chave, class Item>
Item listaOrd<Chave, Item>::devolve(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return x->valor;
        if (x->chave > chave)
        ;
            //return; // ERRO
    }
}

template <class Chave, class Item>
int listaOrd<Chave, Item>::rank(Chave chave) {
    int r = 0;
    for (No *x = ini; x != nullptr; x = x->next, r++) {
        if (x->chave >= chave)
            break;
    }
    return r;
}

// acertar para listaOrd
template <class Chave, class Item>
bool listaOrd<Chave, Item>::contains(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return true;
    }
    return false;
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::print() {
    for (No *x = ini; x != nullptr; x = x->next) {
        cout << "(" << x->chave << "," << x->valor << ") ";
    }

    cout << "\n";
}



#endif
