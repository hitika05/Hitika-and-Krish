#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For sleep() on Windows

// Node structure for the expression tree
typedef struct Node {
    char value; // Node value as char to handle operators
    struct Node* left; // Pointer to left child
    struct Node* right; 
} Node;

// Function to create a new node
Node* createNode(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to evaluate the expression tree
int evaluate(Node* root) {
    if (root->left == NULL && root->right == NULL)
        return root->value; // Return integer value

    int leftEval = evaluate(root->left);
    int rightEval = evaluate(root->right);

    switch (root->value) {
        case '+': return leftEval + rightEval;
        case '-': return leftEval - rightEval;
        case '*': return leftEval * rightEval;
        case '/': return leftEval / rightEval;
        default: return 0;
    }
}

// Function to generate expressions for different levels
Node* generateEasyExpression1() {
    Node* root = createNode('*');
    Node* left = createNode('+');
    left->left = createNode(2);
    left->right = createNode(3);
    root->left = left;
    root->right = createNode(4);
    return root;
}

Node* generateEasyExpression2() {
    Node* root = createNode('/');
    root->left = createNode(10);
    Node* right = createNode('+');
    right->left = createNode(2);
    right->right = createNode(3);
    root->right = right;
    return root;
}

Node* generateMediumExpression() {
    Node* root = createNode('*');
    Node* left = createNode('+');
    left->left = createNode(2);
    left->right = createNode(3);
    
    Node* right = createNode('-');
    right->left = createNode(4);
    right->right = createNode(1);

    root->left = left;
    root->right = right;
    return root;
}

Node* generateHardExpression() {
    Node* root = createNode('*');
    root->left = createNode('/');
    root->right = createNode('-');
    root->left->left = createNode(10);

    Node* right = createNode('+');
    right->left = createNode(2);
    right->right = createNode(3);
    root->left->right = right;

    root->right->left = createNode(4);
    root->right->right = createNode(1);

    return root;
}

// Function to print the expression tree in a structured format
void printTree(Node* root, int space) {
    if (root == NULL) return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    printTree(root->right, space);

    // Print current node after space count
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    
    if (root->left == NULL && root->right == NULL) {
        printf("%d", root->value); // Print as integer if it's a leaf node
    } else {
        printf("%c", root->value); // Print as operator for non-leaf node
    }

    // Process left child
    printTree(root->left, space);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux and macOS
    #endif
}

// Function to display loading animation
void loadingAnimation() {
    printf("Loading");
    fflush(stdout);  // Ensure "Loading" is printed before dots
    for (int i = 0; i < 20; i++) {
        printf(".");
        fflush(stdout);
        Sleep(100);  // 100ms delay between each dot
    }
    clear_screen();
}

void welcomeArt() {
    clear_screen();
    printf(" _       __     __                               \n");
    printf("| |     / /__  / /________  ____ ___  ___   \n");
    printf("| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\  \n");
    printf("| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/      \n");
    printf("|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/     \n");
    printf("\n");
}

void thankYouArt() {
   printf("\n\n");
    printf("  _______ _                 _        __     __          \n");
    printf(" |__   __| |               | |       \\ \\   / /          \n");
    printf("    | |  | |__   __ _ _ __ | | __     \\ \\_/ /_ _   _    \n");
    printf("    | |  | '_ \\ / _` | '_ \\| |/ /      \\   / _` | | | | \n");
    printf("    | |  | | | | (_| | | | |   <        | | (_| | |_| | \n");
    printf("    |_|  |_| |_|\\__,_|_| |_|_|\\_\\       |_|\\__,_|\\__, | \n");
  
    printf("\n              Thank you for using the program!\n\n");
}

// Function to play the game
void playGame() {
    int score = 0;

    // Easy Level
    printf("=== Easy Level ===\n");
    for (int i = 0; i < 2; i++) {
        Node* expression;
        int userAnswer = 0;
        int validInput = 0; // Flag to check for valid input
        
        if (i == 0) {
            expression = generateEasyExpression1();
            printf("Expression Tree:\n");
            printTree(expression, 0); // Print tree for easy expression 1
            printf("\nGuess the result of the expression: (2 + 3) * 4\n");
        } else {
            expression = generateEasyExpression2();
            printf("Expression Tree:\n");
            printTree(expression, 0); // Print tree for easy expression 2
            printf("\nGuess the result of the expression: 10 / (2 + 3)\n");
        }

        // Input validation loop
        while (!validInput) {
            printf("Enter your answer: ");
            if (scanf("%d", &userAnswer) == 1) {
                validInput = 1; // Valid input received
            } else {
                printf("Invalid input. Please enter an integer.\n");
                while (getchar() != '\n'); // Clear the input buffer
            }
        }

        int correctAnswer = evaluate(expression);
        if (userAnswer == correctAnswer) {
            printf("Correct! The result is %d\n", correctAnswer);
            score += 1;
        } else {
            printf("Incorrect. The correct result is %d\n", correctAnswer);
        }
        free(expression); // Free memory
    }

    // Medium Level
    printf("=== Medium Level ===\n");
    Node* expression = generateMediumExpression();
    printf("Expression Tree:\n");
    printTree(expression, 0); // Print tree for medium expression

    int userAnswerMedium = 0;
    int validInputMedium = 0; // Flag to check for valid input
    printf("\nGuess the result of the expression: (2 + 3) * (4 - 1)\n");

    // Input validation loop
    while (!validInputMedium) {
        printf("Enter your answer: ");
        if (scanf("%d", &userAnswerMedium) == 1) {
            validInputMedium = 1; // Valid input received
        } else {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }

    if (userAnswerMedium == evaluate(expression)) {
        printf("Correct! The result is %d\n", evaluate(expression));
        score += 1;
    } else {
        printf("Incorrect. The correct result is %d\n", evaluate(expression));
    }
    free(expression); // Free memory

    // Hard Level
    printf("=== Hard Level ===\n");
    expression = generateHardExpression();
    printf("Expression Tree:\n");
    printTree(expression, 0); // Print tree for hard expression

    int userAnswerHard = 0;
    int validInputHard = 0; // Flag to check for valid input
    printf("\nGuess the result of the expression: 10 / (2 + 3) * (4 - 1)\n");

    // Input validation loop
    while (!validInputHard) {
        printf("Enter your answer: ");
        if (scanf("%d", &userAnswerHard) == 1) {
            validInputHard = 1; // Valid input received
        } else {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }

    if (userAnswerHard == evaluate(expression)) {
        printf("Correct! The result is %d\n", evaluate(expression));
        score += 1;
    } else {
        printf("Incorrect. The correct result is %d\n", evaluate(expression));
    }
    free(expression); // Free memory

    printf("\nYour final score is: %d\n", score);
    thankYouArt(); // Display thank you ASCII art
}

int main() {
    welcomeArt(); // Display welcome ASCII art
    loadingAnimation(); // Display loading animation
    playGame(); // Start the game
    return 0;
}
