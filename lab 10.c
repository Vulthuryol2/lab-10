#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie
{
    struct Trie *children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->isEndOfWord = 0;
    pTrie->count = 0;  // initialize count to 0

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        pTrie->children[i] = NULL;
    }
    return pTrie;
}


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
    {
        return;
    }
    struct Trie *pCrawl = pTrie;

    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] < 'a' || word[i] > 'z') // check if word[i] is a lowercase letter
        {
            return;
        }

        int index = word[i] - 'a';
        if (pCrawl == NULL) // check if pCrawl is NULL
        {
            printf("pCrawl is NULL\n");
            return;
        }

        if (!pCrawl->children[index])
            pCrawl->children[index] = createTrie();

        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = 1;
    pCrawl->count++;
}



// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *pCrawl = pTrie;

    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
        {
            return 0;
        }
        pCrawl = pCrawl->children[index];
    }

    return pCrawl->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (pTrie->children[i])
        {
            deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    // This function needs to be implemented based on how the dictionary file is structured.
    // Assuming each line in the file contains a single word, the function could look like this:

    FILE *file = fopen(filename, "r");
    char word[256];
    int i = 0;

    if (file == NULL)
    {
        printf("Could not open file %s", filename);
        return -1;
    }

    while (fgets(word, sizeof(word), file))
    {
        word[strcspn(word, "\n")] = 0;
        pInWords[i] = strdup(word);
        i++;
    }

    fclose(file);

    return i; // return the number of words read from the file
}

int main(void)
{
    char *inWords[256];

    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
    {
        printf("There is an error in this program\n");
    }
    return 0;
}
