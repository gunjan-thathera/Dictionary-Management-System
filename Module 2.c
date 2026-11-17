#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char word[100];
    char meaning[200];
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(char word[], char meaning[]) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to compare two words
int compareWords(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && b[i] != '\0') {
        if (tolower((unsigned char)a[i]) !=
            tolower((unsigned char)b[i]))
            return tolower((unsigned char)a[i]) -
                   tolower((unsigned char)b[i]);

        i++;
    }

    return tolower((unsigned char)a[i]) -
           tolower((unsigned char)b[i]);
}

// Function to insert word into BST
struct Node* insertWord(struct Node *root,
                        char word[], char meaning[]) {

    if (root == NULL)
        return createNode(word, meaning);

    int result = compareWords(word, root->word);

    if (result < 0)
        root->left = insertWord(root->left, word, meaning);

    else if (result > 0)
        root->right = insertWord(root->right, word, meaning);

    else {
        strcpy(root->meaning, meaning);
        printf("Word already exists. Meaning updated!\n");
    }

    return root;
}

// Function to search a word in BST
struct Node* searchWord(struct Node *root, char word[]) {

    if (root == NULL)
        return NULL;

    int result = compareWords(word, root->word);

    if (result == 0)
        return root;

    else if (result < 0)
        return searchWord(root->left, word);

    else
        return searchWord(root->right, word);
}

// Function to display dictionary
void displayDictionary(struct Node *root) {

    if (root == NULL)
        return;

    displayDictionary(root->left);

    printf("\nWord: %s", root->word);
    printf("\nMeaning: %s\n", root->meaning);

    displayDictionary(root->right);
}

// Main function
int main() {

    struct Node *root = NULL;
    struct Node *result;

    char word[100], meaning[200];
    int choice;

    do {
        printf("\n--- DICTIONARY MANAGEMENT SYSTEM ---\n");
        printf("1. Insert Word\n");
        printf("2. Search Word and Meaning\n");
        printf("3. Display Dictionary\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                printf("Enter word: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                if (word[0] == '\0') {
                    printf("Word cannot be empty!\n");
                    break;
                }

                printf("Enter meaning: ");
                fgets(meaning, sizeof(meaning), stdin);
                meaning[strcspn(meaning, "\n")] = '\0';

                if (meaning[0] == '\0') {
                    printf("Meaning cannot be empty!\n");
                    break;
                }

                root = insertWord(root, word, meaning);

                printf("Word inserted successfully!\n");
                break;

            case 2:
                printf("Enter word to search: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                if (word[0] == '\0') {
                    printf("Word cannot be empty!\n");
                    break;
                }

                result = searchWord(root, word);

                if (result != NULL) {
                    printf("\nWord Found!\n");
                    printf("Word: %s\n", result->word);
                    printf("Meaning: %s\n", result->meaning);
                }
                else {
                    printf("\nWord not found!\n");
                }

                break;

            case 3:
                if (root == NULL)
                    printf("Dictionary is empty!\n");
                else {
                    printf("\n--- DICTIONARY WORDS ---\n");
                    displayDictionary(root);
                }
                break;

            case 4:
                printf("Exiting...");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
