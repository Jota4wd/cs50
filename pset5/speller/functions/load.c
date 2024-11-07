/*

 C arrega o dicionário do arquivo para a memória.
 Abre o arquivo do dicionário.
 Lê cada palavra do arquivo.
 Para cada palavra, cria um novo nó, preenche-o com a palavra.
 Insere o nó na tabela hash no bucket apropriado.
 Incrementa o contador de palavras.
 Retorna true se bem-sucedido, false em caso de erro.

*/

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return (false);
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return (false);
        }
        strcpy(new_node->word, word);
        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    fclose(file);
    return (true);
}
