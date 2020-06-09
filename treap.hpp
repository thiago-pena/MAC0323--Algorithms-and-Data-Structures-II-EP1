#ifndef ARVOREBIN3_HPP
#define ARVOREBIN3_HPP
#include<limits.h>
#include <stdlib.h>
#include <string>
using namespace std;

#define MAXHEIGHT 1000000

int randInteger(int a, int b);
double randProb();

template <class Chave, class Item>
class treap {
    public:
        treap(string nome_arquivo, Item nullItem, Chave nullKey);
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
            int height;
            No *dir;
            No *esq;
            No(Chave ch, Item val) {
                chave = ch;
                valor = val;
                height = randInteger(0, MAXHEIGHT);
                dir = esq = nullptr;
            }
        };
        No *raiz;
        Item nullItem;
        Chave nullKey;
        No * insereR(No*, Chave, Item);
        Item devolveR(No*, Chave);
        bool containsR(No*, Chave);
        int rankR(No*, Chave);
        No * max(No*);
        No * removeR(No *, Chave);
        No * rightRotate(No*);
        No * leftRotate(No*);
        void printR(No *);
        int selecionaR(No *, int, bool &, Chave &, int);
};

template <class Chave, class Item>
treap<Chave, Item>::treap(string nome_arquivo, Item nullItem, Chave nullKey): raiz(nullptr), nullItem(nullItem), nullKey(nullKey)
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
void treap<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
typename treap<Chave, Item>::No* treap<Chave, Item>::insereR(No *node, Chave chave, Item valor) {
    if (node == nullptr) {
        return new No(chave, valor);
    }
    if (chave == node->chave)
        node->valor = valor;
    else if (chave < node->chave) {
        node->esq = insereR(node->esq, chave, valor);

        if (node->esq->height > node->height)
        node = rightRotate(node);
    }
    else {
        node->dir = insereR(node->dir, chave, valor);

        if (node->dir->height > node->height)
            node = leftRotate(node);
    }
    return node;
}

template <class Chave, class Item>
typename treap<Chave, Item>::No* treap<Chave, Item>::rightRotate(No* node) {
    if (node == nullptr || node->esq == nullptr)
        return node;
    No *aux = node->esq;
    node->esq = aux->dir;
    aux->dir = node;
    return aux;
}

template <class Chave, class Item>
typename treap<Chave, Item>::No* treap<Chave, Item>::leftRotate(No* node) {
    No *aux = node->dir;
    node->dir = aux->esq;
    aux->esq = node;
    return aux;
}

// value paired with key ( null if key is absent)
template <class Chave, class Item>
Item treap<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item treap<Chave, Item>::devolveR(No *raiz, Chave chave) {
    if (raiz == nullptr)
        return nullItem;
    if (chave == raiz->chave)
        return raiz->valor;
    if (chave < raiz->chave)
        return devolveR(raiz->esq, chave);
    return devolveR(raiz->dir, chave);
}


template <class Chave, class Item>
bool treap<Chave, Item>::contains(Chave chave) {
    return containsR(raiz, chave);
}

template <class Chave, class Item>
bool treap<Chave, Item>::containsR(No *no, Chave chave) {
    if (no == nullptr)
        return false;
    if (chave == no->chave)
        return true;
    if (chave < no->chave)
        return containsR(no->esq, chave);
    if (chave > no->chave)
        return containsR(no->dir, chave);
}

template <class Chave, class Item>
int treap<Chave, Item>::rank(Chave chave) {
    return rankR(raiz, chave);
}

template <class Chave, class Item>
int treap<Chave, Item>::rankR(No *raiz, Chave chave) {
    if (raiz == nullptr)
        return 0;
    int count = 0;
    if (raiz->chave < chave) {
        count++;
        count += rankR(raiz->dir, chave);
    }
    count += rankR(raiz->esq, chave);
    return count;
}

template <class Chave, class Item>
typename treap<Chave, Item>::No* treap<Chave, Item>::max(No *node) {
    if (node == nullptr || node->dir == nullptr)
        return node;
    return max(node->dir);
}


template <class Chave, class Item>
void treap<Chave, Item>::remove(Chave chave) {
    raiz = removeR(raiz, chave);
}

template <class Chave, class Item>
typename treap<Chave, Item>::No* treap<Chave, Item>::removeR(No *node, Chave chave) {
    if (node == nullptr) return nullptr;
    if (chave < node->chave)
        node->esq = removeR(node->esq, chave);
    else if (chave > node->chave)
        node->dir = removeR(node->dir, chave);
    else {
        if (node->esq == nullptr) {
            No * aux = node->dir;
            delete node;
            return aux;
        }
        else if (node->dir == nullptr) {
            No * aux = node->esq;
            delete node;
            return aux;
        }
        else {
            No * aux = max(node->esq);
            node->chave = aux->chave;
            node->valor = aux->valor;
            node->esq = removeR(node->esq, aux->chave);
        }
    }
    return node;
}

template <class Chave, class Item>
void treap<Chave, Item>::print() {
    printR(raiz);
}

template <class Chave, class Item>
void treap<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        printR(node->esq);
        cout << node->chave << ": " << node->valor << endl;
        printR(node->dir);
    }
}

template <class Chave, class Item>
Chave treap<Chave, Item>::seleciona(int k) {
    bool achou = false;
    Chave ch;
    selecionaR(raiz, k, achou, ch, 0);
    if (achou)
        return ch;
    return nullKey;
}

// in ordem
template <class Chave, class Item>
int treap<Chave, Item>::selecionaR(No *node, int k, bool &achou, Chave &chave, int count) {
    if (node == nullptr)
        return count;
    count = selecionaR(node->esq, k, achou, chave, count);
    if (achou) return count;
    if (++count == k + 1) {
        achou = true;
        chave = node->chave;
        return count;
    }
    count = selecionaR(node->dir, k, achou, chave, count);
    return count;
}

// A função randomInteger devolve um inteiro
// aleatório entre low e high inclusive,
// ou seja, no intervalo fechado low..high.
// Vamos supor que low <= high e que
// high - low <= RAND_MAX. (O código foi copiado
// da biblioteca random de Eric Roberts.)
int randInteger(int a, int b) {
    double d = (double) rand() / ((double) RAND_MAX + 1);
    // 0 <= d < 1
    int k = d * (b - a + 1); // 0 <= k <= b-a
    return a + k;
}

// A função randProb() devolve uma probabilidade aleatória entre 0 e 1.
double randProb() {
   double r;
   r = rand() / ((double) RAND_MAX);
   return r;
}

#endif
