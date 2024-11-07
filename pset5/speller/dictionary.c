// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536;
// adicionando variavel global
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
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

// Hashes word to a number
// Função de hash djb2
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long hash = 5381;
    int c;
    while ((c = tolower(*word++)))
        hash = ((hash << 5) + hash) + c;
    return (hash % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
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

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return (word_count);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
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
