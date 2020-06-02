#ifndef VETORDES_HPP
#define VETORDES_HPP
using namespace std;

// alterou para contains -> criar função, atualizar rank
///////////////////////////////////////////////////////////////////////////

template <class Chave, class Item>
class vetorDes {
    private:
        struct par {
            Chave chave;
            Item valor;
        };
        par *st;
        int size;
        int n;
        Item nullItem;
        bool null(Chave chave);
        void resize();
    public:
        vetorDes(Item nullItem); // inserir nome do arquivo de texto como parâmetro
        void insere(Chave chave, Item valor);
        Item devolve(Chave chave);
        //void remove (Chave chave);
        int rank(Chave chave);
        //Chave seleciona(int k);
};

template <class Chave, class Item>
vetorDes<Chave, Item>::vetorDes(Item nullItem): st(new par[2]), size(2), n(0), nullItem(nullItem) {}

template <class Chave, class Item>
void vetorDes<Chave, Item>::insere(Chave chave, Item valor) {
    int r = rank(chave);
    if (r >= 0) st[r].valor = valor;
    else {
        if (n == size) resize();
        st[n].chave = chave;
        st[n].valor = valor;
        n++;
    }
}

template <class Chave, class Item>
Item vetorDes<Chave, Item>::devolve(Chave chave) {
    int r = rank(chave);
    if (r >= 0) return st[r].valor;
    return nullItem;
}

// Rever se posso usar a definição do Sedgewick
// retorna -1 se a chave não pertence à ST
template <class Chave, class Item>
int vetorDes<Chave, Item>::rank(Chave chave) {
    for (int i = 0; i < n; i++) {
        if (chave == st[i].chave)
            return i;
    }
    return -1;
}

template <class Chave, class Item>
void vetorDes<Chave, Item>::resize() {
    par *novoVetor = new par[2*size];
    for (int i = 0; i < n; i++) {
        novoVetor[i].chave = st[i].chave;
        novoVetor[i].valor = st[i].valor;
    }
    delete [] st;
    st = novoVetor;
    size *= 2;
}

#endif
