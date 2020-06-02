#ifndef ARVORE23_HPP
#define ARVORE23_HPP

template <class Chave, class Item>
class arvore23 {
    public:
        arvore23(Item nullItem);
        //bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        //Item devolve(Chave chave); // value paired with key ( null if key is absent)
        //void remove (Chave chave);
        //int rank(Chave chave); // find the number of keys less than a given key
        // Chave seleciona(int k); // find the key with a given rank

    private:
        struct No {
            Chave chave1;
            Item valor1;
            Chave chave2;
            Item valor2;
            No *ap1;
            No *ap2;
            No *ap3;
            bool doisNo;
            No(Chave ch, Item val) {
                chave1 = ch;
                valor1 = val;
                ap1 = ap2 = ap3 = nullptr;
                doisNo = true;
            }
            bool ehFolha(No *node) {
                return node->ap1 == nullptr;
            }
            // bool ehFolha
            // -> basta olhar para o 1º apontador, se for null, é folha (todos os nós null de uma árvore 2-3 estão no mesmo nível)
        };
        No *raiz;
        Item nullItem;
        No * put23(No *, Chave, Item, bool &);
};

template <class Chave, class Item>
arvore23<Chave, Item>::arvore23(Item nullItem): raiz(nullptr), nullItem(nullItem) {};

template <class Chave, class Item>
void arvore23<Chave, Item>::insere(Chave chave, Item valor) {
    bool cresceu = false;
    raiz = put23(raiz, chave, valor, cresceu);
}

// template <class Chave, class Item>
// typename treap<Chave, Item>::No* treap<Chave, Item>::insereR(No *node, Chave chave, Item valor) {
// }


template <class Chave, class Item>
typename arvore23<Chave, Item>::No *arvore23<Chave, Item>::put23(No * node, Chave chave, Item valor, bool &cresceu) {
    if (node == nullptr) { // árvore vazia
        node = new No(chave, valor);
        cresceu = true;
        return node;
    }
    if (node->ehFolha()) { // se é folha, precisa inserir
        // Folha, 2-nó
        if (node->doisNo) {
            if (chave < node->chave1) {
                node->chave2 = node->chave1;
                node->valor2 = node->valor1;
                node->chave1 = node->chave;
                node->valor1 = node->valor;
                node->doisNo = false;
            }
            else if (chave > node->chave1) {
                node->chave2 = chave;
                node->valor2 = valor;
                node->doisNo = false;
            }
            else {
                node->valor1 = valor;
                node->doisNo = true;
            }
            cresceu = false;
            return node;
        }
        else { // Folha, 3-nó
            if (chave == node->chave1) {
                node->valor1 = valor;
                cresceu = false;
                return node;
            }
            if (chave == node->chave2) {
                node->valor2 = valor;
                cresceu = false;
                return node;
            }
            Chave chaveMeio;
            Item valorMeio;
            if (chave < node->chave1) {
                chaveMeio = node->chave1;
                valorMeio = node->valor1;
                node->chave1 = chave;
                node->valor1 = valor;
            }
            else if (chave > node->chave2) {
                chaveMeio = node->chave2;
                valorMeio = node->valor2;
                node->chave2 = chave;
                node->valor2 = valor;
            }
            else {
                chaveMeio = chave;
                valorMeio = valor;
            }
            No *meio = new No(chaveMeio, valorMeio);
            No *maior = new No(node->chave2, node->valor2);
            node->doisNo = true;
            meio->ap1 = node;
            meio->ap2 = maior;
            cresceu = true;
            return meio;
        }
    }
    // Não é folha

    // Não é folha
    if (chave < node->chave1) {
        No *p = put23(node->ap1, chave, valor, cresceu);
        if (!cresceu) {
            node->ap1 = p;
            return node;
        }
        // cresceu
        if (node->doisNo) { // 2-nó
            node->chave2 = node->chave1;
            node->valor2 = node->valor1;
            node->chave1 = p->chave1;
            node->valor1 = p->valor1;
            node->ap3 = node->ap2;
            node->ap1 = p->ap1;
            node->ap2 = p->ap2;
            node->doisNo = false;
            cresceu = false;
            delete p;
            return node;
        }
        // 3-nó
        No *maior = new No(node->chave2, node->valor2);
        maior->ap2 = node->ap3;
        maior->ap1 = node->ap2;
        node->ap2 = maior;
        node->ap1 = p;
        node->doisNo = true;
        cresceu = true;
        return node;
    }

    // Não é folha
    // >= ch1

    if (chave == node->chave1) {
        node->valor1 = valor;
        cresceu = false;
        return node;
    }

    // Não é folha
    // > ch1

    if(node->doisNo) {
        No *p = put23(node->ap2, chave, valor, cresceu);
        if (!cresceu) {
            node->ap2 = p;
            return node;
        }
        node->chave2 = p->chave1;
        node->valor2 = p->valor1;
        node->ap2 = p->ap1;
        node->ap3 = p->ap2;

        node->doisNo = false;
        cresceu = false;
        delete p;
        return node;
    }

    // Não é folha
    // >= ch1
    // 3-nó

    if (chave < node->chave2) {
        No *p = put23(node->ap2, chave, valor, cresceu);
        if (!cresceu) {
            node->ap2 = p;
            return node;
        }
        // cresceu
        No *maior = new No(node->chave2, node->valor2);
        maior->ap2 = node->ap3;
        maior->ap1 = p->ap2;
        maior->ap2 = p->ap2;
        node->ap2 = p->ap1;
        p->ap1 = node;
        p->ap2 = maior;
        node->doisNo = true;
        // p e maior já são doisNo
        cresceu = true;
        return p;
    }

    // Não é folha
    // >= ch1
    // 3-nó
    // >= ch2

    if (chave == node->chave2) {
        node->valor2 = valor;
        cresceu = false;
        return node;
    }


    // Não é folha
    // >= ch1
    // 3-nó
    // > ch2

    No *p = put23(node->ap3, chave, valor, cresceu);
    if (!cresceu) {
        node->ap3 = p;
        return node;
    }
    // cresceu
    No *meio = new No(node->chave2, node->valor2);
    meio->ap1 = node;
    meio->ap2 = p;
    node->doisNo = true;
    // p e meio já são doisNo
    cresceu = true;
    return meio;
}


#endif
