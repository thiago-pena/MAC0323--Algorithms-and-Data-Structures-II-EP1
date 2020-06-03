#ifndef ARVORERN_HPP
#define ARVORERN_HPP
#include <iostream>
#include <string>


template <class Chave, class Item>
class arvoreRN {
    public:
        arvoreRN(Item nullItem);
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
            int cor; // 0 -> vermelho, 1 -> preto, 2 -> duplo preto
            No *pai;
            //int N;          // # nodes in subtree rooted here
            No(Chave ch, Item val) {
                chave = ch;
                valor = val;
                dir = esq = pai = nullptr;
                cor = 0;
            }
            string getCor() {
                if (this->cor == 0) return "vermelho";
                if (this->cor == 1) return "preto";
                if (this->cor == 2) return "duplo preto";
                return "ERRO! Cor não encontrada!";
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
arvoreRN<Chave, Item>::arvoreRN(Item nullItem): raiz(nullptr), nullItem(nullItem){};

template <class Chave, class Item>
void arvoreRN<Chave, Item>::insere(Chave chave, Item valor) {
    raiz = insereR(raiz, chave, valor);
}

template <class Chave, class Item>
typename arvoreRN<Chave, Item>::No* arvoreRN<Chave, Item>::insereR(No *node, Chave chave, Item valor) {
    if (raiz == nullptr) // árvore vazia
        raiz = new No(chave, valor);
    No *p = raiz;
    bool achou = false;

    while (!achou) { // downward -> chegar até uma folha
        if (chave < p->chave && p->esq != nullptr)
            p = p->esq;
        else if (chave < p->chave && p->esq == nullptr)
            achou = true;
        else if (chave > p->chave && p->dir != nullptr)
            p = p->dir;
        else if (chave > p->chave && p->dir == nullptr)
            achou = true;
        else achou = true; // ch == p->chave
    }

    if (chave == p->chave) {
        p->valor = valor;
        return raiz;
    }

    No *novo = new No(chave, valor);
    novo->pai = p;

    // by Pena
    if (chave < p->chave)
        p->esq = novo;
    else
        p->dir = novo;
    // by Pena (fim)

    No *filho = novo;
    while (p != nullptr) { // Upward -> sobe arrumando (no final ajusta 'p' e 'filho' e vai subindo)
        // p é pai de um nó vermelho
        if (p->cor == 1) // se p é preto, está correto
            break;
        No *avo = p->pai;
        if (avo == nullptr) { // p é raiz da árvore
            p->cor = 1;
            break;
        }

        No *tio; // outro filho do avô
        if (avo->esq == p)
            tio = avo->dir;
        else if (avo->dir = p)
            tio = avo->esq;


        if (tio != nullptr && tio->cor == 0) { // pai vermelho => avô preto
            avo->cor = 0; // avô: preto -> vermelho
            p->cor = tio->cor = 1; // pai, tio: preto -> vermelho
            p = avo->pai; // sobe para o pai do avô [novo p no loop]
            filho = avo;
        }
        else { // Tio preto (ou nullptr)
            if (p->dir == filho && avo->esq == p) { // precisa alinhar
                p->dir = filho->esq;
                if (filho->esq != nullptr) filho->esq->pai = p;
                filho->esq = p;
                p->pai = filho;
                filho->pai = avo;
                avo->esq = filho;
                p = filho;
                filho = filho->esq;
            }
            else if (p->esq == filho && avo->dir == p) { // precisa alinhar (caso 2)
                p->esq = filho->dir;
                if (filho->dir != nullptr) filho->dir->pai = p;
                filho->dir = p;
                p->pai = filho;
                filho->pai = avo;
                avo->dir = filho;
                p = filho;
                filho = filho->dir;
            }
            if (p == avo->esq && filho == p->esq) { // os 2 do mesmo lado
                avo->esq = p->dir;

                if (p->dir != nullptr)
                    p->dir->pai = avo;
                p->dir = avo;
                p->pai = avo->pai;
                avo->pai = p;
                p->cor = 1;
                avo->cor = 0;
                if (avo == raiz)
                    raiz = p;
                if (p->pai != nullptr) { // acerta o ponteiro do pai do avô para p
                    if (p->pai->esq == avo)
                        p->pai->esq = p;
                    else if (p->pai->dir == avo)
                        p->pai->dir = p;
                }
                break;
            }
            else if (p == avo->dir && filho == p->dir) { // os 2 do mesmo lado (outro caso)
                avo->dir = p->esq;
                if (p->esq != nullptr)
                    p->esq->pai = avo;
                p->esq = avo;
                p->pai = avo->pai;
                avo->pai = p;
                p->cor = 1;
                avo->cor = 0;
                if (avo == raiz)
                    raiz = p;
                if (p->pai != nullptr) { // acerta o ponteiro do pai do avô para p
                    if (p->pai->esq == avo)
                        p->pai->esq = p;
                    else if (p->pai->dir == avo)
                        p->pai->dir = p;
                }

                break;
            }

        }

    }
    return raiz; // @@@ precisa mesmo? Posso fazer retornar void e não ajustar a raiz na insere, ou até remover a insere
}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolveR(No *raiz, Chave chave) {
    if (raiz == nullptr)
        return nullItem;
    if (chave == raiz->chave)
        return raiz->valor;
    if (chave < raiz->chave)
        return devolveR(raiz->esq, chave);
    return devolveR(raiz->dir, chave);
}

template <class Chave, class Item>
bool arvoreRN<Chave, Item>::contains(Chave chave) {
    return containsR(raiz, chave);
}

template <class Chave, class Item>
bool arvoreRN<Chave, Item>::containsR(No *no, Chave chave) {
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
int arvoreRN<Chave, Item>::rank(Chave chave) {
    return rankR(raiz, chave);
}

template <class Chave, class Item>
int arvoreRN<Chave, Item>::rankR(No *raiz, Chave chave) {
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
typename arvoreRN<Chave, Item>::No* arvoreRN<Chave, Item>::max(No *node) {
    if (node == nullptr || node->dir == nullptr)
        return node;
    return max(node->dir);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::print() {
    printR(raiz);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        cout << node->chave << ": " << node->valor << "(" << node->getCor() << ")" << endl;
        printR(node->esq);
        printR(node->dir);
    }
}

// find the key with a given rank -> pré-ordem
template <class Chave, class Item>
Chave arvoreRN<Chave, Item>::seleciona(int k) {
    bool achou = false;
    Chave ch;
    selecionaR(raiz, k, achou, ch, 0);
    if (achou)
        return ch;
    return "Erro! Rank não encontrado.";
}

// in ordem
template <class Chave, class Item>
int arvoreRN<Chave, Item>::selecionaR(No *node, int k, bool &achou, Chave &chave, int count) {
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
