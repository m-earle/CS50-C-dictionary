// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <strings.h>
#include <string.h>
#include <stdio.h>

#include <ctype.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int n = strlen(word); //need to convert word to lower case and then hash that, I think to ensure same hash value
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
        {
            word_copy[i] = tolower(word[i]);
        }
    // Adds null terminator to end string
        word_copy[n] = '\0';
    int x = hash(word_copy); //hash the word
    node *cursor  = table[x]; //create a pointer to the head of the linked list located at the hash value
    while (cursor != NULL) //while you're not at the end of the list
    {
        if (strcasecmp(cursor -> word , word_copy) == 0) //if the two words match
        {
        return true;
        break;
        }
        else
        {
            cursor = cursor -> next; //if they don't match, move the cursor
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
        unsigned int hash_value = 0;
        for (int i = 0, n = strlen(word); i < n; i++)
        {
             hash_value = (hash_value << 2) ^ word[i];
        }
        return hash_value % N; //N is size of hashtable //Shrey Tripathi on Stack Exchange
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //open dictonary file //check if able to open file, if NULL, function should return false
    //N = 26;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open.\n");
        return 1;
    }
    //read strings from file one at a time
    char dict[LENGTH + 1]; //dict is word we're getting from dictionary file, intialize to be same length as word above
    while (fscanf(file, "%s", dict) != EOF) //while we haven't reached end of file
    {
       //fscanf(file, "%s", dict); //reading characters into a word (an array stored in memory where you can access each character)
       node *w = malloc(sizeof(node)); //alloc memory to store a new node (ie create a new node for each word)
       if (w == NULL) //check for null
       {
           return 1;
       }
           // hash word to obtain hash value
        strcpy(w -> word , dict); //strcpy to copy from dict into "word" part of node
        int x = hash(dict);
        node *head = table[x]; //initializes head to point to hashtable index/bucket
    // insert node into hash table at that location
       if (head == NULL) //if this is the first word
       {
            w -> next = NULL; //set new nodes pointer to null
            table[x] = w; //set header to point at new node
       }
       else
       {
            w -> next = table[x]; //set w pointer to whatever header is pointing at
            table[x] = w; //then change header pointer to point at new node
       }
    }
   // node *n = malloc(sizeof(node));
   // strcpy (n -> word, "Hello"); //copy word Hellow into node
    //n -> next = NULL; //set the pointer to null (or could set it to something specific if you knew where it was going)
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;
    for (int i = 0; i < N; i ++)
    {
        node *cursor = table[i]; //set cursor to head
        while (cursor != NULL) //while cursor is not at end of list
        {
            count ++; //add 1 to count
            cursor = cursor -> next; //move the cursor to next
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i ++) //for each linked list
    {
        node *cursor = table[i]; //set cursor to head
        while (cursor != NULL) //while cursor is not at end of list
        {
            node *tmp = cursor; //set temp equal to cursor
            cursor = cursor -> next; //move the cursor to next
            free(tmp); //free temp
        }

    }
    return true;
}
