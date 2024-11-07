/*

 Libera toda a memória alocada para o dicionário.
 P ercorre cada bucket da tabela hash.
 Para cada bucket, percorre a lista ligada e libera cada nó.
 Retorna true quando toda a memória for liberada.

 */

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return (true);
}
