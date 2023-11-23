#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Структура для узла бинарного дерева
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Функция для создания нового узла
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Функция для вычисления значения булевой формулы
bool evaluate(TreeNode* root, int* values) {
    if (root == NULL) {
        return true;  // Пустое поддерево считается истинным
    }

    if (root->data == '0') {
        return false;
    } else if (root->data == '1') {
        return true;
    } else if (root->data == '&') {
        return evaluate(root->left, values) && evaluate(root->right, values);
    } else if (root->data == '|') {
        return evaluate(root->left, values) || evaluate(root->right, values);
    } else if ('a' <= root->data && root->data <= 'z') {
        int index = root->data - 'a';  // Переменные представлены буквами a, b, c, ...
        return values[index];
    }

    return false;
}

// Функция для освобождения памяти, занятой деревом
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <путь_к_файлу>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    // Чтение булевой формулы из файла
    char formula[100];
    fgets(formula, sizeof(formula), file);
    fclose(file);

    // Построение бинарного дерева выражения
    // Реализация этой части зависит от конкретных требований и может потребовать парсера
    // Например, вы можете использовать стек и обратную польскую запись для построения дерева

    // Для примера, создадим простое дерево вручную
    TreeNode* root = createNode('|');
    root->left = createNode('&');
    root->left->left = createNode('a');
    root->left->right = createNode('b');
    root->right = createNode('1');

    // Вывод заголовка таблицы истинности
    printf("Таблица истинности для формулы: %s\n", formula);
    printf("==================================\n");
    printf(" ");

    // Вывод заголовков переменных
    for (int i = 0; i < 26; ++i) {
        if (strchr(formula, 'a' + i)) {
            printf("%c ", 'a' + i);
        }
    }

    printf("| Result\n");

    // Вычисление и вывод значений таблицы истинности
    int numVariables = 26;
    int values[26];

    for (int i = 0; i < (1 << numVariables); ++i) {
        // Генерация всех возможных комбинаций значений переменных
        for (int j = 0; j < numVariables; ++j) {
            values[j] = (i >> j) & 1;
        }

        // Вывод значений переменных
        for (int j = 0; j < numVariables; ++j) {
            if (strchr(formula, 'a' + j)) {
                printf("%d ", values[j]);
            }
        }

        // Вычисление и вывод результата
        printf("| %d\n", evaluate(root, values));
    }

    // Освобождение памяти, занятой деревом
    freeTree(root);

    return EXIT_SUCCESS;
}
