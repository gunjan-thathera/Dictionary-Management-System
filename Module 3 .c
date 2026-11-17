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

// Function to update meaning of a word
struct Node* updateWord(struct Node *root, char word[]) {

    if (root == NULL)
        return NULL;

    int result = compareWords(word, root->word);

    if (result == 0)
        return root;

    else if (result < 0)
        return updateWord(root->left, word);

    else
        return updateWord(root->right, word);
}

// Function to find the smallest node
struct Node* findMin(struct Node *root) {

    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

// Function to delete a word from BST
struct Node* deleteWord(struct Node *root, char word[]) {

    if (root == NULL)
        return NULL;

    int result = compareWords(word, root->word);

    if (result < 0)
        root->left = deleteWord(root->left, word);

    else if (result > 0)
        root->right = deleteWord(root->right, word);

    else {

        // Node with no child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Node with one child
        else if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        else {
            struct Node *temp = findMin(root->right);

            strcpy(root->word, temp->word);
            strcpy(root->meaning, temp->meaning);

            root->right = deleteWord(root->right, temp->word);
        }
    }

    return root;
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

    // Sample dictionary entries
    root = insertWord(root, "Mango", "A sweet tropical fruit");
    root = insertWord(root, "Apple", "A round edible fruit");
    root = insertWord(root, "Banana", "A long yellow fruit");
    root = insertWord(root, "Orange", "A citrus fruit");

    do {
        printf("\n--- UPDATE AND DELETE MODULE ---\n");
        printf("1. Update Meaning\n");
        printf("2. Delete Word\n");
        printf("3. Display Dictionary\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                printf("Enter word to update: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                result = updateWord(root, word);

                if (result != NULL) {
                    printf("Enter new meaning: ");
                    fgets(meaning, sizeof(meaning), stdin);
                    meaning[strcspn(meaning, "\n")] = '\0';

                    if (meaning[0] == '\0') {
                        printf("Meaning cannot be empty!\n");
                        break;
                    }

                    strcpy(result->meaning, meaning);
                    printf("Meaning updated successfully!\n");
                }
                else {
                    printf("Word not found!\n");
                }

                break;

            case 2:
                printf("Enter word to delete: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = '\0';

                if (word[0] == '\0') {
                    printf("Word cannot be empty!\n");
                    break;
                }

                result = updateWord(root, word);

                if (result != NULL) {
                    root = deleteWord(root, word);
                    printf("Word deleted successfully!\n");
                }
                else {
                    printf("Word not found!\n");
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
