/*

 E s*ta é uma implementação do algoritmo de hash djb2.
 C onverte cada caractere para minúsculo e incorpora-o no valor hash.
 Retorna o valor hash módulo N para garantir que esteja dentro do intervalo da tabela.

 */

// Função de hash djb2
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c;
    return (hash % N);
}
