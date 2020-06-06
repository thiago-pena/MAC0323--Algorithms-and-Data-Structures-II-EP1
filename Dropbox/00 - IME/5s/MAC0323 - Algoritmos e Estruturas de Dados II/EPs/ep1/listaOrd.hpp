#ifndef LISTAORD_HPP
#define LISTAORD_HPP
using namespace std;

template <class Chave, class Item>
class listaOrd {
    public:
        listaOrd(Item nullItem);
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
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
    if (ini == nullptr) { // lista vazia
        No *novo = new No(chave, valor);
        ini = novo;
        n++;
        return;
    }
    if (chave < ini->chave) { // insere no início
        No *novo = new No(chave, valor);
        novo->next = ini;
        ini = novo;
        n++;
        return;
    }

    No *prox = ini;
    No *ant = ini;
    while (prox != nullptr && chave > prox->chave) {
        ant = prox;
        prox = prox->next;
    }

    if (prox == nullptr) { // insere no fim
        No *novo = new No(chave, valor);
        ant->next = novo;
        n++;
    }
    else if (prox->chave != chave) { // chave ainda não existe na ST
        No *novo = new No(chave, valor);
        ant->next = novo;
        novo->next = prox;
        n++;
    }
    else { // chave já existe na ST
        prox->valor = valor;
    }
}

template <class Chave, class Item>
Item listaOrd<Chave, Item>::devolve(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return x->valor;
        if (x->chave > chave)
            break;
    }
    return nullItem;
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

template <class Chave, class Item>
bool listaOrd<Chave, Item>::contains(Chave chave) {
    for (No *x = ini; x != nullptr; x = x->next) {
        if (x->chave == chave)
            return true;
    }
    return false;
}

template <class Chave, class Item>
Chave listaOrd<Chave, Item>::seleciona(int k) {
    if (k < 0 || k >= n) return "Erro! Rank não encontrado.";
    int i = 0;
    for (No *x = ini; x != nullptr; x = x->next, i++) {
        if (i == k) return x->chave;
    }
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::print() {
    for (No *x = ini; x != nullptr; x = x->next) {
        cout << "(" << x->chave << "," << x->valor << ") ";
    }

    cout << "\n";
}

template <class Chave, class Item>
void listaOrd<Chave, Item>::remove(Chave chave) {
    if (chave == ini->chave) {
        No *aux = ini;
        ini = ini->next;
        delete aux;
        n--;
        return;
    }
    if (ini->next == nullptr) return;
    No *anterior = ini;
    for (No *x = ini->next; x != nullptr && x->chave <= chave; x = x->next) {
        if (chave == x->chave) {
            anterior->next = x->next;
            delete x;
            n--;
            return;
        }
        anterior = x;
    }
}

#endif
