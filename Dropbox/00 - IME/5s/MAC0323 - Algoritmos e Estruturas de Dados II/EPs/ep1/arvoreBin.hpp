#ifndef ARVOREBIN_HPP
#define ARVOREBIN_HPP

template <class Chave, class Item>
class arvoreBin {
    public:
        arvoreBin(Item nullItem);
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave); // value paired with key ( null if key is absent)
        void remove (Chave chave);
        int rank(Chave chave); // find the number of keys less than a given key
        Chave seleciona(int k); // find the key with a given rank -> pré-ordem
        void print();
    private:
        struct No {
            Chave chave;
            Item valor;
            No *dir;
            No *esq;
            //int N;          // # nodes in subtree rooted here
            No(Chave ch, Item val) {
                chave = ch;
                valor = val;
                dir = esq = nullptr;
            }
        };
        No *raiz;
        Item nullItem;
        No * insereR(No*, Chave, Item);
        Item devolveR(No*, Chave);
        bool containsR(No*, Chave);
        int rankR(No*, Chave);
        No * max(No*);
        No * removeR(No *, Chave);
        void printR(No *);
        int selecionaR(No *, int, bool &, Chave &, int);
};

template <class Chave, class Item>
arvoreBin<Chave, Item>::arvoreBin(Item nullItem): raiz(nullptr), nullItem(nullItem){};

template <class Chave, class Item>
void arvoreBin<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
typename arvoreBin<Chave, Item>::No* arvoreBin<Chave, Item>::insereR(No *node, Chave chave, Item valor) {
    if (node == nullptr) {
        return new No(chave, valor);
    }
    if (chave == node->chave)
        node->valor = valor;
    else if (chave < node->chave)
        node->esq = insereR(node->esq, chave, valor);
    else
        node->dir = insereR(node->dir, chave, valor);
    return node;
}



// value paired with key ( null if key is absent)
template <class Chave, class Item>
Item arvoreBin<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item arvoreBin<Chave, Item>::devolveR(No *raiz, Chave chave) {
    if (raiz == nullptr)
        return nullItem;
    if (chave == raiz->chave)
        return raiz->valor;
    if (chave < raiz->chave)
        return devolveR(raiz->esq, chave);
    return devolveR(raiz->dir, chave);
}


template <class Chave, class Item>
bool arvoreBin<Chave, Item>::contains(Chave chave) {
    return containsR(raiz, chave);
}

template <class Chave, class Item>
bool arvoreBin<Chave, Item>::containsR(No *no, Chave chave) {
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
int arvoreBin<Chave, Item>::rank(Chave chave) {
    return rankR(raiz, chave);
}

template <class Chave, class Item>
int arvoreBin<Chave, Item>::rankR(No *raiz, Chave chave) {
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
typename arvoreBin<Chave, Item>::No* arvoreBin<Chave, Item>::max(No *node) {
    if (node == nullptr || node->dir == nullptr)
        return node;
    return max(node->dir);
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::remove(Chave chave) {
    raiz = removeR(raiz, chave);
}

template <class Chave, class Item>
typename arvoreBin<Chave, Item>::No* arvoreBin<Chave, Item>::removeR(No *node, Chave chave) {
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
void arvoreBin<Chave, Item>::print() {
    printR(raiz);
}

template <class Chave, class Item>
void arvoreBin<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        printR(node->esq);
        cout << node->chave << ": " << node->valor << endl;
        printR(node->dir);
    }
}

// find the key with a given rank -> pré-ordem
template <class Chave, class Item>
Chave arvoreBin<Chave, Item>::seleciona(int k) {
    bool achou = false;
    Chave ch;
    selecionaR(raiz, k, achou, ch, 0);
    if (achou)
        return ch;
    return "Erro! Rank não encontrado.";
}

// in ordem
template <class Chave, class Item>
int arvoreBin<Chave, Item>::selecionaR(No *node, int k, bool &achou, Chave &chave, int count) {
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


#endif
