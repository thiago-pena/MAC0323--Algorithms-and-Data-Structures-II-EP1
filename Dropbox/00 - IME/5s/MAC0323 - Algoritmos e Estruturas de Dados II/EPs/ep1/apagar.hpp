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
