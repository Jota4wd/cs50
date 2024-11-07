/*

 E s*ta função verifica se uma palavra está no dicionário.
 U sa a função hash para determinar em qual bucket da tabela* hash a palavra deve estar.
 Percorre a lista ligada nesse bucket, comparando a palavra com cada nó.
 Usa strcasecmp para comparação case-insensitive.
 Retorna true se encontrar a palavra, false caso contrário.

 */

bool check(const char *word)
{
    char lower_word[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
        lower_word[i] = tolower(word[i]);
    lower_word[len] = '\0';
    unsigned int index = hash(lower_word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(lower_word, cursor->word) == 0)
            return (true);
        cursor = cursor->next;
    }
    return (false);
}
