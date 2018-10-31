// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// size of array
#define ARRAY_SIZE 5000

typedef struct _node
{
    char word[LENGTH + 1];
    struct _node *next;
}
NODE;

NODE *hashtable[ARRAY_SIZE];


//add to front function
NODE *addfront(NODE *head, NODE *newp)
{
    newp -> next = head;
    return newp;
}

unsigned int wordsInDictionary = 0;

// hash function

//hash function by Neel Mehta at:
//https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int getIndex(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % ARRAY_SIZE;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int word_index = getIndex(word);
    NODE *head = hashtable[word_index];
    NODE *cursor = head;

    while (cursor != NULL)
    {
        int is_word = strcasecmp(cursor->word, word);
        if (is_word == 0)
        {

            return true;
        }

        cursor = cursor->next;
    }

    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        NODE *new_node = malloc(sizeof(NODE));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;

        int hashIndex = getIndex(word);

        hashtable[hashIndex] = addfront(hashtable[hashIndex], new_node);
        wordsInDictionary++;

    }

    // TODO
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordsInDictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        NODE *head = hashtable[i];
        NODE *cursor = head;
        while (cursor != NULL)
        {
            NODE *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);

    }

    // TODO
    return true;
}


