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
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
        void print();
    private:
        struct No {
            Chave chave;
            Item valor;
            No *dir;
            No *esq;
            int cor; // 0 -> vermelho, 1 -> preto, 2 -> duplo preto
            No *pai;
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
            void duploPreto() { this->cor += 1; }
        };
        No *raiz;
        Item nullItem;
        Item devolveR(No*, Chave);
        bool containsR(No*, Chave);
        int rankR(No*, Chave);
        No * max(No*);
        No * min(No*);
        No * removeRN(No *, Chave);
        void printR(No *);
        int selecionaR(No *, int, bool &, Chave &, int);

};

template <class Chave, class Item>
arvoreRN<Chave, Item>::arvoreRN(Item nullItem): raiz(nullptr), nullItem(nullItem){};

template <class Chave, class Item>
void arvoreRN<Chave, Item>::insere(Chave chave, Item valor) {
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
        return;
    }

    No *novo = new No(chave, valor);
    novo->pai = p;

    if (chave < p->chave)
        p->esq = novo;
    else
        p->dir = novo;

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


        if (tio != nullptr && tio->cor == 0) { // tio vermelho => avô preto
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
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::remove(Chave chave) {
    raiz = removeRN(raiz, chave);
}

template <class Chave, class Item>
typename arvoreRN<Chave, Item>::No* arvoreRN<Chave, Item>::removeRN(No *node, Chave chave) {
    if (node == nullptr) // árvore vazia
        return nullptr;
    No *p = node;
    bool achou = false;

    while (!achou) { // downward -> chegar até uma folha ou até a chave (intermediária)
        if (chave < p->chave && p->esq != nullptr)
            p = p->esq;
        else if (chave < p->chave && p->esq == nullptr)
            achou = true;
        else if (chave > p->chave && p->dir != nullptr)
            p = p->dir;
        else if (chave > p->chave && p->dir == nullptr)
            achou = true;
        else achou = true; // ch == p->chave || não tem a chave na ST
    }

    if (chave != p->chave) return node;

    if (p->cor == 0) { // p é vermelho
        if (p->esq == nullptr && p->dir == nullptr) { // p é folha
            if (p == node) { // p é raiz da sub-árvore
                delete p;
                return nullptr;
            }
            // p não é raiz
            if (p->pai->esq == p) p->pai->esq = nullptr;
            else if (p->pai->dir == p) p->pai->dir = nullptr;
            delete p;
            return node;
        }
        else {
            if (p->esq != nullptr) {
                No *aux = max(p->esq);
                p->chave = aux->chave;
                p->valor = aux->valor;
                p->esq = removeRN(p->esq, aux->chave);
            }
            else {
                No *aux = min(p->dir);
                p->chave = aux->chave;
                p->valor = aux->valor;
                p->dir = removeRN(p->dir, aux->chave);
            }
        }
        //return node; // @@@ Pode quebrar algo acima
    }
    else if (p->cor == 1) { // p é preto

        if (p->esq == nullptr && p->dir == nullptr) { // p é folha
            // cria um duplo preto
            if (p == node) { // p é raiz da sub-árvore
                delete p;
                return nullptr;
            }

            // p não é raiz
            No *irmao;
            No *pai = p->pai;
            bool pEsquerda;
            if (p == p->pai->esq) {
                irmao = p->pai->dir;
                pEsquerda = true;
            }
            else {
                irmao = p->pai->esq;
                pEsquerda = false;
            }

            if (irmao->cor == 1) { // irmão preto
                // Caso 2.1. (Folha) Irmão preto com filhos pretos (ou NULLs)
                if ((irmao->esq == nullptr || irmao->esq->cor == 1) &&
                    (irmao->dir == nullptr || irmao->dir->cor == 1))
                {
                    irmao->cor = 0;
                    No *pai = p->pai;
                    pai->duploPreto(); // empurra o DP para o pai
                    if (pai->esq == p) pai->esq = nullptr;
                    else if (pai->dir == p) pai->dir = nullptr;
                    No *aux = p;


                    p = p->pai; // Tratar o pai na subida
                    delete aux;
                }

                No *sobrinhoPerto;
                No *sobrinhoLonge;

                if (pEsquerda) {
                    sobrinhoPerto = irmao->esq;
                    sobrinhoLonge = irmao->dir;
                }
                else {
                    sobrinhoPerto = irmao->dir;
                    sobrinhoLonge = irmao->esq;
                }

                // Caso 2.3. Irmão preto, sobrinho mais perto vermelho, sobrinho mais longe preto [Folha]
                if ((sobrinhoPerto != nullptr && sobrinhoPerto->cor == 0) &&
                    (sobrinhoLonge == nullptr || sobrinhoLonge->cor == 1))
                {
                    irmao->cor = 0;
                    sobrinhoPerto->cor = 1;
                    if (pEsquerda) {
                        pai->dir = sobrinhoPerto;
                        sobrinhoPerto->pai = pai;
                        irmao->esq = sobrinhoPerto->dir;
                        if (sobrinhoPerto->dir != nullptr) sobrinhoPerto->dir->pai = irmao;
                        sobrinhoPerto->dir = irmao;
                        irmao->pai = sobrinhoPerto;
                    }
                    else {
                        pai->esq = sobrinhoPerto;
                        sobrinhoPerto->pai = pai;
                        irmao->dir = sobrinhoPerto->esq;
                        if (sobrinhoPerto->esq != nullptr) sobrinhoPerto->esq->pai = irmao;
                        sobrinhoPerto->esq = irmao;
                        irmao->pai = sobrinhoPerto;
                    }
                    // mantém o 'p', porque cai no caso 2.4 -> não precisa remover agora, 'p' é quem vai tentar remover no 2.4
                    irmao = sobrinhoPerto;
                    if (pEsquerda) { // recalcula os sobrinhos para cair no caso 2.4
                        sobrinhoPerto = irmao->esq;
                        sobrinhoLonge = irmao->dir;
                    }
                    else {
                        sobrinhoPerto = irmao->dir;
                        sobrinhoLonge = irmao->esq;
                    }
                }
                // Caso 2.4. Irmão preto, sobrinho mais longe vermelho [Folha]
                if (sobrinhoLonge != nullptr && sobrinhoLonge->cor == 0) {
                    int corAux = pai->cor;
                    pai->cor = irmao->cor;
                    irmao->cor = corAux;

                    if (pai->pai != nullptr) { // mantém o ponteiro do pai->pai durante a rotação
                        if (pai->pai->esq == pai)
                            pai->pai->esq = irmao;
                        else
                            pai->pai->dir = irmao;
                    }
                    else { // pai era raiz
                        this->raiz = irmao; // nova raiz
                    }
                    if (pai == node) {node = irmao; // corrige a refêrencia a node após a rotação
                    }

                    irmao->pai = pai->pai;
                    if (pEsquerda) {
                        pai->dir = sobrinhoPerto;
                        if (sobrinhoPerto != nullptr) sobrinhoPerto->pai = pai;
                        irmao->esq = pai;
                        pai->pai = irmao;
                    }
                    else {
                        pai->esq = sobrinhoPerto;
                        if (sobrinhoPerto != nullptr) sobrinhoPerto->pai = pai;
                        irmao->dir = pai;
                        pai->pai = irmao;
                    }

                    sobrinhoLonge->duploPreto(); // p passa DP para sobrinhoLonge
                    if (pai->esq == p) pai->esq = nullptr; // acerta ponteiros do pai para remoção de p
                    else if (pai->dir == p) pai->dir = nullptr;
                    No *aux = p;
                    p = irmao; // corrigiu tudo até aqui (irmao --> novo pai após a rotação)
                    delete aux;
                }
            }
            else { // irmão vermelho (Caso 2.2 Folha)
                pai->cor = 0;
                irmao->cor = 1;
                if (pai->pai != nullptr) { // mantém o ponteiro do pai->pai durante a rotação
                    if (pai->pai->esq == pai)
                        pai->pai->esq = irmao;
                    else
                        pai->pai->dir = irmao;
                }
                else { // pai era raiz
                    this->raiz = irmao; // nova raiz
                }
                if (pai == node) node = irmao; // corrige a refêrencia a node após a rotação
                irmao->pai = pai->pai;
                if (pEsquerda) {
                    pai->dir = irmao->esq;
                    if (irmao->esq != nullptr) irmao->esq->pai = pai;
                    irmao->esq = pai;
                    pai->pai = irmao;
                    pai->esq = nullptr;
                }
                else {
                    pai->esq = irmao->dir;
                    if (irmao->dir != nullptr) irmao->dir->pai = pai;
                    /////////
                    irmao->dir = pai;
                    pai->pai = irmao;
                    pai->dir = nullptr;
                }
                delete p;
                pai->cor = 1;
                // return node;
            }
        }
        else {
            // p não é folha
            // trocar com uma folha e remover a folha
            if (p->esq != nullptr) {
                No *aux = max(p->esq);
                p->chave = aux->chave;
                p->valor = aux->valor;
                p->esq = removeRN(p->esq, aux->chave);
            }
            else {
                No *aux = min(p->dir);
                p->chave = aux->chave;
                p->valor = aux->valor;
                p->dir = removeRN(p->dir, aux->chave);
            }
        }
    }

    // Fase de subida
    while (p != nullptr) {
        if (p->cor < 2)
            return node;
        else { // p é duplo preto
            if (p == raiz) {
                p->cor = 1; // raiz: dp --> p
            }

            // p não é raiz
            No *irmao;
            No *pai = p->pai;
            bool pEsquerda;
            if (p == p->pai->esq) {
                irmao = p->pai->dir;
                pEsquerda = true;
            }
            else {
                irmao = p->pai->esq;
                pEsquerda = false;
            }

            // p é DP + Irmão preto com filhos pretos/NULLs
            if (irmao->cor == 1) { // irmão preto
                // Caso 2.1. Irmão preto com filhos pretos (ou NULLs) v2
                if ((irmao->esq == nullptr || irmao->esq->cor == 1) &&
                    (irmao->dir == nullptr || irmao->dir->cor == 1))
                {
                    irmao->cor = 0;
                    No *pai = p->pai;
                    pai->duploPreto(); // empurra o DP para o pai
                    p = p->pai; // Tratar o pai na subida
                }

                No *sobrinhoPerto;
                No *sobrinhoLonge;

                if (pEsquerda) {
                    sobrinhoPerto = irmao->esq;
                    sobrinhoLonge = irmao->dir;
                }
                else {
                    sobrinhoPerto = irmao->dir;
                    sobrinhoLonge = irmao->esq;
                }

                // Caso 2.3. Irmão preto, sobrinho mais perto vermelho, sobrinho mais longe preto
                if ((sobrinhoPerto != nullptr && sobrinhoPerto->cor == 0) &&
                    (sobrinhoLonge == nullptr || sobrinhoLonge->cor == 1))
                {
                    irmao->cor = 0;
                    sobrinhoPerto->cor = 1;
                    if (pEsquerda) {
                        pai->dir = sobrinhoPerto;
                        sobrinhoPerto->pai = pai;
                        irmao->esq = sobrinhoPerto->dir;
                        if (sobrinhoPerto->dir != nullptr) sobrinhoPerto->dir->pai = irmao;
                        sobrinhoPerto->dir = irmao;
                        irmao->pai = sobrinhoPerto;
                    }
                    else {
                        pai->esq = sobrinhoPerto;
                        sobrinhoPerto->pai = pai;
                        irmao->dir = sobrinhoPerto->esq;
                        if (sobrinhoPerto->esq != nullptr) sobrinhoPerto->esq->pai = irmao;
                        sobrinhoPerto->esq = irmao;
                        irmao->pai = sobrinhoPerto;
                    }
                    // mantém o 'p', porque cai no caso 2.4 -> não precisa remover agora, 'p' é quem vai tentar remover no 2.4
                    irmao = sobrinhoPerto;
                    if (pEsquerda) { // recalcula os sobrinhos para cair no caso 2.4
                        sobrinhoPerto = irmao->esq;
                        sobrinhoLonge = irmao->dir;
                    }
                    else {
                        sobrinhoPerto = irmao->dir;
                        sobrinhoLonge = irmao->esq;
                    }
                }
                // Caso 2.4. Irmão preto, sobrinho mais longe vermelho
                if (sobrinhoLonge != nullptr && sobrinhoLonge->cor == 0) {
                    int corAux = pai->cor;
                    pai->cor = irmao->cor;
                    irmao->cor = corAux;

                    if (pai->pai != nullptr) { // mantém o ponteiro do pai->pai durante a rotação
                        if (pai->pai->esq == pai)
                            pai->pai->esq = irmao;
                        else
                            pai->pai->dir = irmao;
                    }
                    else { // pai era raiz
                        this->raiz = irmao; // nova raiz
                    }
                    if (pai == node) node = irmao; // corrige a refêrencia a node após a rotação
                    irmao->pai = pai->pai;

                    if (pEsquerda) {
                        pai->dir = sobrinhoPerto;
                        if (sobrinhoPerto != nullptr) sobrinhoPerto->pai = pai;
                        irmao->esq = pai;
                        pai->pai = irmao;
                    }
                    else {
                        pai->esq = sobrinhoPerto;
                        if (sobrinhoPerto != nullptr) sobrinhoPerto->pai = pai;
                        irmao->dir = pai;
                        pai->pai = irmao;
                    }
                    // p passa DP para sobrinhoLonge
                    p->cor = 1;
                    sobrinhoLonge->duploPreto();
                    p = irmao; // corrigiu tudo até aqui
                }
                // Caso 2.5. Irmão preto, os dois sobrinhos são vermelhos
                if ((sobrinhoPerto != nullptr && sobrinhoPerto->cor == 0) &&
                    (sobrinhoLonge != nullptr && sobrinhoLonge->cor == 0))
                {
                }
            }
            else { // irmão vermelho
                // Caso 2.2. Irmão vermelho (=> pai é preto)
                pai->cor = 0;
                irmao->cor = 1;
                if (pai->pai != nullptr) { // mantém o ponteiro do pai->pai durante a rotação
                    if (pai->pai->esq == pai)
                        pai->pai->esq = irmao;
                    else
                        pai->pai->dir = irmao;
                }
                else { // pai era raiz
                    this->raiz = irmao; // nova raiz
                }
                if (pai == node) node = irmao; // corrige a refêrencia a node após a rotação
                irmao->pai = pai->pai;
                if (pEsquerda) { // rotação (com p à esquerda)
                    pai->dir = irmao->esq;
                    if (irmao->esq != nullptr) irmao->esq->pai = pai;
                    irmao->esq = pai;
                    pai->pai = irmao;
                }
                else {
                    pai->esq = irmao->dir;
                    if (irmao->dir != nullptr) irmao->dir->pai = pai;
                    irmao->dir = pai;
                    pai->pai = irmao;
                }
                pai->duploPreto();
                p = p->pai;
            }

        }
    }

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
typename arvoreRN<Chave, Item>::No* arvoreRN<Chave, Item>::min(No *node) {
    if (node == nullptr || node->esq == nullptr)
        return node;
    return min(node->esq);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::print() {
    if (raiz == nullptr) cout << "Árvore vazia!" << endl;
    else
        printR(raiz);
}

template <class Chave, class Item>
void arvoreRN<Chave, Item>::printR(No *node) {
    if (node != nullptr) {
        cout << node->chave << ": " << node->valor << " (" << node->getCor() << ")";
        if (node->pai == nullptr) cout << " raiz" << endl;
        else cout << "| pai: " << node->pai->chave << "(" << node->pai->getCor() << ")" << endl;
        printR(node->esq);
        printR(node->dir);
    }
}

template <class Chave, class Item>
Chave arvoreRN<Chave, Item>::seleciona(int k) {
    bool achou = false;
    Chave ch;
    selecionaR(raiz, k, achou, ch, 0);
    if (achou)
        return ch;
    return "Erro! Rank não encontrado.";
}

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
