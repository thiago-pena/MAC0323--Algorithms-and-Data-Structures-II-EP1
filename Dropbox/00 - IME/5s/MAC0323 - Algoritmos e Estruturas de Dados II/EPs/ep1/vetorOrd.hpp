#ifndef VETORORD_HPP
#define VETORORD_HPP
using namespace std;

template <class Chave, class Item>
class vetorOrd {
    private:
        struct par {
            Chave chave;
            Item valor;
        };
        par *st;
        int size; // Tamanho do vetor
        int n; // número de elementos na Tabela de Símbolos
        Item nullItem;
        bool null(Chave chave);
        bool isEmpty();
        void resize();
    public:
        vetorOrd(Item nullItem);
        bool contains(Chave chave);
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        void remove (Chave chave);
        int rank(Chave chave);
        Chave seleciona(int k);
};

template <class Chave, class Item>
vetorOrd<Chave, Item>::vetorOrd(Item nullItem): st(new par[2]), size(2), n(0), nullItem(nullItem) {}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::isEmpty() {
    return n == 0;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::insere(Chave chave, Item valor) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave) { // já existe
        st[r].valor = valor;
    }
    else { // chave é nova
        if (n == size) resize();
        for (int i = n; i > r; i--) {
            st[i].chave = st[i - 1].chave;
            st[i].valor =  st[i - 1].valor;
        }
        st[r].chave = chave;
        st[r].valor = valor;
        n++;
    }
}

template <class Chave, class Item>
Item vetorOrd<Chave, Item>::devolve(Chave chave) {
    if (n == 0) return nullItem;
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return st[r].valor;
    return nullItem;
}

template <class Chave, class Item>
int vetorOrd<Chave, Item>::rank(Chave chave) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = ini + (fim - ini)/2;
        if (chave < st[meio].chave)
            fim = meio - 1;
        else if (chave > st[meio].chave)
            ini = meio + 1;
        else
            return meio;
    }
    return ini;
}

template <class Chave, class Item>
Chave vetorOrd<Chave, Item>::seleciona(int k) {
    if (k < 0 || k >= n) return "Erro! Rank não encontrado.";
    return st[k].chave;
}

template <class Chave, class Item>
bool vetorOrd<Chave, Item>::contains(Chave chave) {
    int r = rank(chave);
    if (r < n && st[r].chave == chave)
        return true;
    return false;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::resize() {
    par *novoVetor = new par[2*size];
    for (int i = 0; i < n; i++) {
        novoVetor[i].chave = st[i].chave;
        novoVetor[i].valor = st[i].valor;
    }
    st = novoVetor;
    size *= 2;
}

template <class Chave, class Item>
void vetorOrd<Chave, Item>::remove(Chave chave) {
    bool achou = false;
    int i = rank(chave);
    if (chave != st[i].chave) return; // chave não pertence à ST
    while (i < n - 1) {
        st[i] = st[i + 1];
        i++;
    }
    n--;
}

#endif
