// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Count 
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *a = table[index];
    while (a != NULL) 
    {
        if (strcasecmp(a->word, word) == 0)
        {
            return true;
        }
        else
        {
            a = a->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[45];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *a = malloc(sizeof(node));
        if (a == NULL)
        {
            return false;
        }
        strcpy(a->word, word);
        int index = hash(word);
        a->next = table[index];
        table[index] = a;
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 100000; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
