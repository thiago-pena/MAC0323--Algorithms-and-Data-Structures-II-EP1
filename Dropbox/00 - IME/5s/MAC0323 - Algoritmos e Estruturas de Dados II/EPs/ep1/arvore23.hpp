#ifndef ARVORE23_HPP
#define ARVORE23_HPP

template <class Chave, class Item>
class arvore23 {
    public:
        arvore23(string nome_arquivo, Item nullItem, Chave nullKey);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
        void print();
        void printPre();

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
            No *pai;
            No(Chave ch, Item val) {
                chave1 = ch;
                valor1 = val;
                ap1 = ap2 = ap3 = pai = nullptr;
                doisNo = true;
            }
            bool ehFolha() {
                return ap1 == nullptr;
            }
        };
        No *raiz;
        Item nullItem;
        Chave nullKey;
        No * put23(No *, Chave, Item, bool &);
        Item get23(No *, Chave);
        int rankR(No*, Chave);
        No * max(No*);
        Chave maxChave(No *node);
        No * removeR(No *, Chave, bool &);
        void printR(No *);
        void printRpre(No *);
        int selecionaR(No *, int, bool &, Chave &, int);
};

template <class Chave, class Item>
arvore23<Chave, Item>::arvore23(string nome_arquivo, Item nullItem, Chave nullKey): raiz(nullptr), nullItem(nullItem), nullKey(nullKey)
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
void arvore23<Chave, Item>::insere(Chave chave, Item valor) {
    bool cresceu = false;
    raiz = put23(raiz, chave, valor, cresceu);
}

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
                node->chave1 = chave;
                node->valor1 = valor;
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

            meio->ap1->pai = meio;
            meio->ap2->pai = meio;

            return meio;
        }
    }
    // Não é folha

    // Não é folha
    if (chave < node->chave1) {
        No *p = put23(node->ap1, chave, valor, cresceu);
        if (!cresceu) {
            node->ap1 = p;
            node->ap1->pai = node;
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
            node->ap1->pai = node;
            node->ap2->pai = node;
            node->ap3->pai = node;
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

        maior->pai = node;
        maior->ap1->pai = maior;
        maior->ap2->pai = maior;
        node->ap1->pai = node;
        node->ap2->pai = node;
        node->ap3->pai = node;
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
            node->ap2->pai = node;
            return node;
        }
        node->chave2 = p->chave1;
        node->valor2 = p->valor1;
        node->ap2 = p->ap1;
        node->ap3 = p->ap2;
        node->doisNo = false;
        cresceu = false;

        node->ap1->pai = node;
        node->ap2->pai = node;
        node->ap3->pai = node;
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
            node->ap2->pai = node;
            return node;
        }
        // cresceu
        No *maior = new No(node->chave2, node->valor2);
        maior->ap2 = node->ap3;
        maior->ap1 = p->ap2;
        node->ap2 = p->ap1;
        p->ap1 = node;
        p->ap2 = maior;
        node->doisNo = true;
        // p e maior já são doisNo
        cresceu = true;

        maior->pai = p;
        maior->ap1->pai = maior;
        maior->ap2->pai = maior;
        node->ap1->pai = node;
        node->ap2->pai = node;
        node->ap3->pai = node;
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
        node->ap3->pai = node;
        return node;
    }
    // cresceu
    No *meio = new No(node->chave2, node->valor2);
    meio->ap1 = node;
    meio->ap2 = p;
    node->doisNo = true;
    // p e meio já são doisNo
    cresceu = true;

    meio->ap1->pai = meio;
    meio->ap2->pai = meio;
    return meio;
}

template <class Chave, class Item>
Item arvore23<Chave, Item>::devolve(Chave chave) {
    return get23(raiz, chave);
}

template <class Chave, class Item>
Item arvore23<Chave, Item>::get23(No * node, Chave chave) {
    if (node == nullptr)
        return nullItem;
    if (chave < node->chave1)
        return get23(node->ap1, chave);
    if (chave == node->chave1)
        return node->valor1;
    if (node->doisNo)
        return get23(node->ap2, chave);
    if (chave < node->chave2)
        return get23(node->ap2, chave);
    if (chave == node->chave2)
        return node->valor2;
    return get23(node->ap3, chave);
}

template <class Chave, class Item>
int arvore23<Chave, Item>::rank(Chave chave) {
    return rankR(raiz, chave);
}

template <class Chave, class Item>
int arvore23<Chave, Item>::rankR(No *raiz, Chave chave) {
    if (raiz == nullptr)
        return 0;
    int count = 0;
    if (raiz->chave1 < chave) {
        count++;
        count += rankR(raiz->ap2, chave);
        if (!raiz->doisNo && raiz->chave2 < chave) {
                count++;
                count += rankR(raiz->ap3, chave);
        }
    }
    count += rankR(raiz->ap1, chave);
    return count;
}


template <class Chave, class Item>
typename arvore23<Chave, Item>::No* arvore23<Chave, Item>::max(No *node) {
    if (node == nullptr || node->ehFolha())
        return node;
    if (node->doisNo) {
        return max(node->ap2);
    }
    return max(node->ap3);
}

template <class Chave, class Item>
void arvore23<Chave, Item>::remove(Chave chave) {
    bool diminuiu = false;
    raiz = removeR(raiz, chave, diminuiu);
}

template <class Chave, class Item>
typename arvore23<Chave, Item>::No *arvore23<Chave, Item>::removeR(No * node, Chave chave, bool &diminuiu) {
    if (node == nullptr) return nullptr;
    cout << "node: " << node->chave1 << endl;
    if (!node->doisNo) {
        cout << "\tnode: " << node->chave2 << endl;

    }


    // Fase 2 - The terminal cases
    if (node->ehFolha()) {
        if (!node->doisNo) { // 3-nó
            if (chave == node->chave1) {
                node->chave1 = node->chave2;
                node->valor1 = node->valor2;
                node->doisNo = true;
                diminuiu = false;
                return node;
            }
            if (chave == node->chave2) {
                node->doisNo = true;
                diminuiu = false;
                return node;
            }
            diminuiu = false;
            return node; // não encontrou
        }
        // Folha e 2-nó
        if (chave == node->chave1) {
            if (node->pai == nullptr) { // raiz é único nó da árvore
                delete node;
                return nullptr;
            }
            diminuiu = true; // remoção virtual do nó
            return node;
        }
        diminuiu = false;
        return node; // não encontrou
    }

    // Fase 1 (downward) - remover e deixar um buraco
    // Não é folha (nós intermediários)
    if (chave < node->chave1) {
        No *p = removeR(node->ap1, chave, diminuiu);
        if (!diminuiu) {
            node->ap1 = p;
            node->ap1->pai = node;
            return node;
        }
        // Se diminuiu
        // Caso 1 -> buraco tem: pai 2-nó; irmão 2-nó
        // Caso 2 -> buraco tem: pai 2-nó; irmão 3-nó
        // Caso 3 -> buraco tem: pai 3-nó; irmão 2-nó
        // Caso 4 -> buraco tem: pai 3-nó; irmão 3-nó

        No *irmao = node->ap2;
        if (node->doisNo) {
            if (irmao->doisNo) { // Caso 1
                irmao->chave2 = irmao->chave1;
                irmao->valor2 = irmao->valor1;
                irmao->chave1 = node->chave1;
                irmao->valor1 = node->valor1;
                irmao->doisNo = false;
                irmao->ap3 = irmao->ap2;
                irmao->ap2 = irmao->ap1;
                irmao->ap1 = p->ap1;
                node->ap1 = irmao;
                delete p;
                if (!irmao->ehFolha()) {
                    irmao->ap1->pai = irmao;
                    irmao->ap2->pai = irmao;
                    irmao->ap3->pai = irmao;
                }

                if (node->pai == nullptr) { // buraco subiu até a raiz, a árvore diminuiu
                    No *aux = node->ap1;
                    delete node;
                    aux->pai = nullptr;
                    return aux;
                }
                diminuiu = true;
            }
            else { // Caso 2
                p->chave1 = node->chave1;
                p->valor1 = node->valor1;
                node->chave1 = irmao->chave1;
                node->valor1 = irmao->valor1;
                irmao->chave1 = irmao->chave2;
                irmao->valor1 = irmao->valor2;
                irmao->doisNo = true;
                //node->ap1 = p;
                p->ap2 = irmao->ap1;
                irmao->ap1 = irmao->ap2;
                irmao->ap2 = irmao->ap3;
                if (!p->ehFolha()) {
                    p->ap1->pai = p;
                    p->ap2->pai = p;
                }
                node->ap1->pai = node;
                node->ap2->pai = node;
                diminuiu = false;
            }
            return node;
        }
        // node é 3-nó

        if (irmao->doisNo) { // Caso 3
            irmao->chave2 = irmao->chave1;
            irmao->valor2 = irmao->valor1;
            irmao->chave1 = node->chave1;
            irmao->valor1 = node->valor1;
            irmao->doisNo = false;
            node->chave1 = node->chave2;
            node->valor1 = node->valor2;
            node->doisNo = true;
            irmao->ap3 = irmao->ap2;
            irmao->ap2 = irmao->ap1;
            irmao->ap1 = p->ap1;
            node->ap1 = irmao;
            node->ap2 = node->ap3;
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
                irmao->ap3->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            diminuiu = false;
            delete p;
        }
        else { // Caso 4
            p->chave1 = node->chave1;
            p->valor1 = node->valor1;
            node->chave1 = irmao->chave1;
            node->valor1 = irmao->valor1;
            irmao->chave1 = irmao->chave2;
            irmao->valor1 = irmao->valor2;
            irmao->doisNo = true;
            p->ap2 = irmao->ap1;
            irmao->ap1 = irmao->ap2;
            irmao->ap2 = irmao->ap3;
            if (!p->ehFolha()) {
                p->ap1->pai = p;
                p->ap2->pai = p;
            }

            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            node->ap3->pai = node;
            diminuiu = false;
        }
        return node;
    }
    if (chave == node->chave1) {
        No *aux = max(node->ap1);
        if (aux->doisNo) {
            node->chave1 = aux->chave1;
            node->valor1 = aux->valor1;
        }
        else {
            node->chave1 = aux->chave2;
            node->valor1 = aux->valor2;
        }

        No *p = removeR(node->ap1, node->chave1, diminuiu);

        if (!diminuiu) {
            node->ap1 = p;
            node->ap1->pai = node;
            return node;
        }

        // Se diminuiu
        // Caso 1 -> buraco tem: pai 2-nó; irmão 2-nó
        // Caso 2 -> buraco tem: pai 2-nó; irmão 3-nó
        // Caso 3 -> buraco tem: pai 3-nó; irmão 2-nó
        // Caso 4 -> buraco tem: pai 3-nó; irmão 3-nó

        No *irmao = node->ap2;
        if (node->doisNo) {
            if (irmao->doisNo) { // Caso 1
                irmao->chave2 = irmao->chave1;
                irmao->valor2 = irmao->valor1;
                irmao->chave1 = node->chave1;
                irmao->valor1 = node->valor1;
                irmao->doisNo = false;
                irmao->ap3 = irmao->ap2;
                irmao->ap2 = irmao->ap1;
                irmao->ap1 = p->ap1;
                node->ap1 = irmao;
                delete p;
                if (!irmao->ehFolha()) {
                    irmao->ap1->pai = irmao;
                    irmao->ap2->pai = irmao;
                    irmao->ap3->pai = irmao;
                }

                if (node->pai == nullptr) { // buraco subiu até a raiz, a árvore diminuiu
                    No *aux = node->ap1;
                    delete node;
                    aux->pai = nullptr;
                    return aux;
                }
                diminuiu = true;
            }
            else { // Caso 2
                p->chave1 = node->chave1;
                p->valor1 = node->valor1;
                node->chave1 = irmao->chave1;
                node->valor1 = irmao->valor1;
                irmao->chave1 = irmao->chave2;
                irmao->valor1 = irmao->valor2;
                irmao->doisNo = true;
                node->ap1 = p;
                p->ap2 = irmao->ap1;
                irmao->ap1 = irmao->ap2;
                irmao->ap2 = irmao->ap3;
                if (!p->ehFolha()) {
                    p->ap1->pai = p;
                    p->ap2->pai = p;
                }
                node->ap1->pai = node;
                node->ap2->pai = node;
                diminuiu = false;
            }
            return node;
        }
        // node é 3-nó

        if (irmao->doisNo) { // Caso 3
            irmao->chave2 = irmao->chave1;
            irmao->valor2 = irmao->valor1;
            irmao->chave1 = node->chave1;
            irmao->valor1 = node->valor1;
            irmao->doisNo = false;
            node->chave1 = node->chave2;
            node->valor1 = node->valor2;
            node->doisNo = true;
            irmao->ap3 = irmao->ap2;
            irmao->ap2 = irmao->ap1;
            irmao->ap1 = p->ap1;
            node->ap1 = irmao;
            node->ap2 = node->ap3;
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
                irmao->ap3->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            diminuiu = false;
            delete p;
        }
        else { // Caso 4
            p->chave1 = node->chave1;
            p->valor1 = node->valor1;
            node->chave1 = irmao->chave1;
            node->valor1 = irmao->valor1;
            irmao->chave1 = irmao->chave2;
            irmao->valor1 = irmao->valor2;
            irmao->doisNo = true;
            p->ap2 = irmao->ap1;
            irmao->ap1 = irmao->ap2;
            irmao->ap2 = irmao->ap3;
            if (!p->ehFolha()) {
                p->ap1->pai = p;
                p->ap2->pai = p;
            }

            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            node->ap3->pai = node;
            diminuiu = false;
        }
        return node;
    }
    if (node->doisNo || (!node->doisNo && chave < node->chave2)) {
        No *p = removeR(node->ap2, chave, diminuiu);
        // @1
        if (!diminuiu) {
            node->ap2 = p;
            node->ap2->pai = node;
            return node;
        }
        // Se diminuiu
        // Caso 1 -> buraco tem: pai 2-nó; irmão 2-nó
        // Caso 2 -> buraco tem: pai 2-nó; irmão 3-nó
        // Caso 3 -> buraco tem: pai 3-nó; irmão 2-nó
        // Caso 4 -> buraco tem: pai 3-nó; irmão 3-nó

        No *irmao = node->ap1;
        if (node->doisNo) {
            if (irmao->doisNo) { // Caso 1
                irmao->chave2 = node->chave1;
                irmao->valor2 = node->valor1;
                irmao->doisNo = false;
                node->doisNo = true;
                irmao->ap3 = p->ap1;
                delete p;
                if (!irmao->ehFolha()) {
                    irmao->ap1->pai = irmao;
                    irmao->ap2->pai = irmao;
                    irmao->ap3->pai = irmao;
                }

                if (node->pai == nullptr) { // buraco subiu até a raiz, a árvore diminuiu
                    No *aux = node->ap1;
                    delete node;
                    aux->pai = nullptr;
                    return aux;
                }
                diminuiu = true;
            }
            else { // Caso 2
                p->chave1 = node->chave1;
                p->valor1 = node->valor1;
                node->chave1 = irmao->chave2;
                node->valor1 = irmao->valor2;
                irmao->doisNo = true;
                p->ap2 = p->ap1;
                p->ap1 = irmao->ap3;
                node->ap2 = p;
                if (!p->ehFolha()) {
                    p->ap1->pai = p;
                    p->ap2->pai = p;
                }
                node->ap1->pai = node;
                node->ap2->pai = node;
                diminuiu = false;
            }
            return node;
        }
        // node é 3-nó

        if (irmao->doisNo) { // Caso 3
            irmao->chave2 = node->chave1;
            irmao->valor2 = node->valor1;
            irmao->doisNo = false;
            node->chave1 = node->chave2;
            node->valor1 = node->valor2;
            node->doisNo = true;
            irmao->ap3 = p->ap1;
            node->ap2 = node->ap3;
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
                irmao->ap3->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            diminuiu = false;
        }
        else { // Caso 4
            p->chave1 = node->chave1;
            p->valor1 = node->valor1;
            node->chave1 = irmao->chave2;
            node->valor1 = irmao->valor2;
            irmao->doisNo = true;
            p->ap2 = p->ap1;
            p->ap1 = irmao->ap3;
            if (!p->ehFolha()) {
                p->ap1->pai = p;
                p->ap2->pai = p;
            }
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            node->ap3->pai = node;
            diminuiu = false;
        }
        return node;
    }

    if (chave == node->chave2) {
        No *aux = max(node->ap2);
        if (aux->doisNo) {
            node->chave2 = aux->chave1;
            node->valor2 = aux->valor1;
        }
        else {
            node->chave2 = aux->chave2;
            node->valor2 = aux->valor2;
        }

        No *p = removeR(node->ap2, chave, diminuiu);
        if (!diminuiu) {
            node->ap2 = p;
            node->ap2->pai = node;
            return node;
        }

        // Se diminuiu
        // Caso 1 -> buraco tem: pai 2-nó; irmão 2-nó
        // Caso 2 -> buraco tem: pai 2-nó; irmão 3-nó
        // Caso 3 -> buraco tem: pai 3-nó; irmão 2-nó
        // Caso 4 -> buraco tem: pai 3-nó; irmão 3-nó

        No *irmao = node->ap1;
        if (node->doisNo) {
            if (irmao->doisNo) { // Caso 1
                irmao->chave2 = node->chave1;
                irmao->valor2 = node->valor1;
                irmao->doisNo = false;
                node->doisNo = true;
                irmao->ap3 = p->ap1;
                delete p;
                if (!irmao->ehFolha()) {
                    irmao->ap1->pai = irmao;
                    irmao->ap2->pai = irmao;
                    irmao->ap3->pai = irmao;
                }

                if (node->pai == nullptr) { // buraco subiu até a raiz, a árvore diminuiu
                    No *aux = node->ap1;
                    delete node;
                    aux->pai = nullptr;
                    return aux;
                }
                diminuiu = true;
            }
            else { // Caso 2
                p->chave1 = node->chave1;
                p->valor1 = node->valor1;
                node->chave1 = irmao->chave2;
                node->valor1 = irmao->valor2;
                irmao->doisNo = true;
                p->ap2 = p->ap1;
                p->ap1 = irmao->ap3;
                node->ap2 = p;
                if (!p->ehFolha()) {
                    p->ap1->pai = p;
                    p->ap2->pai = p;
                }
                node->ap1->pai = node;
                node->ap2->pai = node;
                diminuiu = false;
            }
            return node;
        }
        // node é 3-nó

        if (irmao->doisNo) { // Caso 3
            irmao->chave2 = node->chave1;
            irmao->valor2 = node->valor1;
            irmao->doisNo = false;
            node->chave1 = node->chave2;
            node->valor1 = node->valor2;
            node->doisNo = true;
            irmao->ap3 = p->ap1;
            node->ap2 = node->ap3;
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
                irmao->ap3->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            diminuiu = false;
        }
        else { // Caso 4
            p->chave1 = node->chave1;
            p->valor1 = node->valor1;
            node->chave1 = irmao->chave2;
            node->valor1 = irmao->valor2;
            irmao->doisNo = true;
            p->ap2 = p->ap1;
            p->ap1 = irmao->ap3;
            if (!p->ehFolha()) {
                p->ap1->pai = p;
                p->ap2->pai = p;
            }
            if (!irmao->ehFolha()) {
                irmao->ap1->pai = irmao;
                irmao->ap2->pai = irmao;
            }
            node->ap1->pai = node;
            node->ap2->pai = node;
            node->ap3->pai = node;
            diminuiu = false;
        }
        return node;
    }

    // 3-nó e > ch2
    No *p = removeR(node->ap3, chave, diminuiu);
    if (!diminuiu) {
        node->ap3 = p;
        node->ap3->pai = node;
        return node;
    }

    // Se diminuiu (3-nó)
    // Caso 3 -> buraco tem: pai 3-nó; irmão 2-nó
    // Caso 4 -> buraco tem: pai 3-nó; irmão 3-nó

    // OBS: não pode ser raiz se diminuiu e node é 3-nó, pois nesse caso sempre absorve o buraco

    No *irmao = node->ap2;
    if (irmao->doisNo) { // Caso 3
        irmao->chave2 = node->chave2;
        irmao->valor2 = node->valor2;
        irmao->doisNo = false;
        node->doisNo = true;
        irmao->ap3 = p->ap1;
        if (!irmao->ehFolha()) {
            irmao->ap1->pai = irmao;
            irmao->ap2->pai = irmao;
            irmao->ap3->pai = irmao;
        }
        diminuiu = false;
    }
    else { // Caso 4
        p->chave1 = node->chave2;
        p->valor1 = node->valor2;
        node->chave2 = irmao->chave2;
        node->valor2 = irmao->valor2;
        irmao->doisNo = true;
        p->ap2 = p->ap1;
        p->ap1 = irmao->ap3;
        if (!p->ehFolha()) {
            p->ap1->pai = p;
            p->ap2->pai = p;
        }

        if (!irmao->ehFolha()) {
            irmao->ap1->pai = irmao;
            irmao->ap2->pai = irmao;
        }
        node->ap1->pai = p;
        node->ap2->pai = p;
        node->ap3->pai = p;
        diminuiu = false;
    }
    return node;
}

template <class Chave, class Item>
void arvore23<Chave, Item>::print() {
    printR(raiz);
}

template <class Chave, class Item>
void arvore23<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        cout << "\tTeste print :" << node->chave1;
        if (!node->doisNo) {
            cout << ", " << node->chave2;
        }
        cout << endl;

        printR(node->ap1);
        cout << node->chave1 << ": " << node->valor1 << " (ch1) | pai: " << (node->pai != nullptr ? node->pai->chave1 : "é raiz") << endl;
        printR(node->ap2);
        if (!node->doisNo) {
            cout << node->chave2 << ": " << node->valor2 << " (ch2) | pai: " << (node->pai != nullptr ? node->pai->chave1 : "é raiz") << endl;
            printR(node->ap3);
        }
    }
}

template <class Chave, class Item>
void arvore23<Chave, Item>::printPre() {
    printRpre(raiz);
}

template <class Chave, class Item>
void arvore23<Chave, Item>::printRpre(No *node) {
    if (node != nullptr) {
        cout << node->chave1 << " (ch1)";
        if (!node->doisNo) {
            cout << ", " << node->chave2 << " (ch2)";
        }
        cout << " [pai: " << (node->pai != nullptr ? node->pai->chave1 : "null") << "]" << endl;
        cout << "\tap1 (" << node->chave1 << ")" << endl;
        printRpre(node->ap1);
        cout << "\tap2 (" << node->chave1 << ")" << endl;
        printRpre(node->ap2);
        if (!node->doisNo) {
            cout << "\tap3 (" << node->chave1 << ")" << endl;
            printRpre(node->ap3);
        }
    }
}

template <class Chave, class Item>
Chave arvore23<Chave, Item>::seleciona(int k) {
    bool achou = false;
    Chave ch;
    selecionaR(raiz, k, achou, ch, 0);
    if (achou)
        return ch;
    return nullKey;
}

// in ordem
template <class Chave, class Item>
int arvore23<Chave, Item>::selecionaR(No *node, int k, bool &achou, Chave &chave, int count) {
    if (node == nullptr)
        return count;
    count = selecionaR(node->ap1, k, achou, chave, count);
    if (achou) return count;
    if (++count == k + 1) {
        achou = true;
        chave = node->chave1;
        return count;
    }
    count = selecionaR(node->ap2, k, achou, chave, count);
    if (node->doisNo) return count;
    if (achou) return count;
    if (++count == k + 1) {
        achou = true;
        chave = node->chave2;
        return count;
    }
    count = selecionaR(node->ap3, k, achou, chave, count);
    return count;
}

#endif
