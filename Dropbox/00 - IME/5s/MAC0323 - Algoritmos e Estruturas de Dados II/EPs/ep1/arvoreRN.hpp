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
        else if (chave < p->chave && p->esq != nullptr)
            p = p->dir;
        else if (chave < p->chave && p->esq == nullptr)
            achou = true;
        else achou = true; // ch == p->chave
    }

    cout << "\tinsereR | achou p (folha): " << p->chave << endl;
    cout << "\t\tinsereR() | cor p: " << p->getCor() << endl;

    if (chave == p->chave) {
        p->valor = valor;
        return raiz;
    }

    No *novo = new No(chave, valor);
    novo->pai = p;
    cout << "\t\tinsereR() | cria novo Nó: " << novo->chave << endl;
    cout << "\t\tinsereR() | Teste p: " << p->chave << endl;

    // by Pena
    if (chave < p->chave) {
        p->esq = novo;
        cout << "\t\tinsereR() | esq" << p->esq->chave << ", " << p->esq->valor << endl;
    }
    else {
        p->dir = novo;
        cout << "\t\tinsereR() | dir: " << p->dir->chave << ", " << p->dir->valor  << endl;
    }
    // by Pena (fim)
    cout << "\tFase Upward" << endl;

    No *filho = novo;
    while (p != nullptr) { // Upward -> sobe arrumando
        cout << "\t\tFase Upward 1" << endl;
        // p é pai de um nó vermelho
        if (p->cor == 1) { // se p é preto, está correto
            cout << "\t\tp é preto -> OK" << endl;
            break;
        }
        cout << "\t\tp é vermelho..." << endl;
        No *avo = p->pai;
        if (avo == nullptr) { // p é raiz da árvore
            cout << "\t\tNão tem avô... p é raiz: vermelho -> preto" << endl;
            p->cor = 1;
            cout << "\t\t\tTeste p: " << p->chave << endl;
            cout << "\t\t\tTeste raiz: " << raiz->chave << endl;
            break;
        }
        cout << "\t\tteste..." << endl;

        //No *tio = // outro filho do avô

        No *tio;
        if (avo->esq == p) {
            tio = avo->dir;
        }
        else if (avo->dir = p) {
            tio = avo->esq;
        }



        if (tio->cor == 0) {
            avo->cor = 0;
            p->cor = tio->cor = 1;
            p = avo->pai;
            filho = avo;
        }
        else { // Tio preto (ou nullptr)
            if (p->dir == filho && avo->esq == p) {
                p->dir = filho->esq;
                if (filho->esq != nullptr) filho->esq->pai = p;
                filho->esq = p;
                p->pai = filho;
                filho->pai = avo;
                avo->esq = filho;
                //p->dir->pai = p; //checar se precisa (prof não colocou)
                p = filho;
                filho = filho->esq;
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
                break;
            }

        }

    }
    cout << "\tfim insereR" << endl;
    return raiz; // @@@ precisa mesmo? Posso fazer retornar void e não ajustar a raiz na insere, ou até remover a insere
}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolve(Chave chave) {
    return devolveR(raiz, chave);
}

template <class Chave, class Item>
Item arvoreRN<Chave, Item>::devolveR(No *raiz, Chave chave) {
    if (raiz == nullptr) {
        cout << "\t\tdevolveR: raiz é NULL" << endl;
        return nullItem;
    }
    cout << "\t\tdevolveR: raiz não é NULL" << endl;
    cout << "\t\tdevolveR raiz:" << raiz->chave << endl;


    if (chave == raiz->chave) {
        cout << "\tdevolveR() | cor: " << raiz->getCor() << endl;
        return raiz->valor;
    }
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


///////////////////// Arvore BIN



// value paired with key ( null if key is absent)


// template <class Chave, class Item>
// void arvoreRN<Chave, Item>::remove(Chave chave) {
//     raiz = removeR(raiz, chave);
// }
//
// template <class Chave, class Item>
// typename arvoreRN<Chave, Item>::No* arvoreRN<Chave, Item>::removeR(No *node, Chave chave) {
//     if (node == nullptr) return nullptr;
//     if (chave < node->chave)
//         node->esq = removeR(node->esq, chave);
//     else if (chave > node->chave)
//         node->dir = removeR(node->dir, chave);
//     else {
//         if (node->esq == nullptr) {
//             No * aux = node->dir;
//             delete node;
//             return aux;
//         }
//         else if (node->dir == nullptr) {
//             No * aux = node->esq;
//             delete node;
//             return aux;
//         }
//         else {
//             No * aux = max(node->esq);
//             node->chave = aux->chave;
//             node->valor = aux->valor;
//             raiz->esq = removeR(node->esq, aux->chave);
//         }
//     }
//     return node;
// }

template <class Chave, class Item>
void arvoreRN<Chave, Item>::print() {
    printR(raiz);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        printR(node->esq);
        cout << node->chave << ": " << node->valor << "(" << node->getCor() << ")" << endl;
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
