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

// Function to insert words into BST
struct Node* insertWord(struct Node *root,
                        char word[], char meaning[]) {

    if (root == NULL)
        return createNode(word, meaning);

    int result = compareWords(word, root->word);

    if (result < 0)
        root->left = insertWord(root->left, word, meaning);

    else if (result > 0)
        root->right = insertWord(root->right, word, meaning);

    return root;
}

// Function to display dictionary using inorder traversal
void displayDictionary(struct Node *root) {

    if (root == NULL)
        return;

    displayDictionary(root->left);

    printf("\nWord: %s", root->word);
    printf("\nMeaning: %s\n", root->meaning);

    displayDictionary(root->right);
}

// Function to count total words
int countWords(struct Node *root) {

    if (root == NULL)
        return 0;

    return 1 + countWords(root->left)
             + countWords(root->right);
}

// Function to find first word alphabetically
struct Node* firstWord(struct Node *root) {

    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

// Function to find last word alphabetically
struct Node* lastWord(struct Node *root) {

    if (root == NULL)
        return NULL;

    while (root->right != NULL)
        root = root->right;

    return root;
}

// Main function
int main() {

    struct Node *root = NULL;
    struct Node *result;

    int choice;

    // Sample dictionary entries
    root = insertWord(root, "Mango", "A sweet tropical fruit");
    root = insertWord(root, "Apple", "A round edible fruit");
    root = insertWord(root, "Banana", "A long yellow fruit");
    root = insertWord(root, "Orange", "A citrus fruit");
    root = insertWord(root, "Grapes", "Small juicy fruits");

    do {
        printf("\n--- DICTIONARY DISPLAY MODULE ---\n");
        printf("1. Display Dictionary\n");
        printf("2. Count Total Words\n");
        printf("3. Find First Word\n");
        printf("4. Find Last Word\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                if (root == NULL)
                    printf("Dictionary is empty!\n");
                else {
                    printf("\n--- DICTIONARY WORDS ---\n");
                    displayDictionary(root);
                }
                break;

            case 2:
                printf("\nTotal number of words: %d\n",
                       countWords(root));
                break;

            case 3:
                result = firstWord(root);

                if (result == NULL)
                    printf("Dictionary is empty!\n");
                else
                    printf("\nFirst word: %s\n", result->word);

                break;

            case 4:
                result = lastWord(root);

                if (result == NULL)
                    printf("Dictionary is empty!\n");
                else
                    printf("\nLast word: %s\n", result->word);

                break;

            case 5:
                printf("Exiting...");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
