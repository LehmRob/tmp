#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_NAME_SIZE = 256 };

typedef struct node {
    int index;
    char name[MAX_NAME_SIZE];
    struct node *left;
    struct node *right;
    int height;
} node_t;

typedef struct tree {
    node_t *root;
} tree_t;

static node_t *create_node(int index, char *value) {
    node_t *ptr;

    ptr = (node_t *)malloc(sizeof(node_t));
    if (ptr == NULL) {
        return NULL;
    }

    ptr->index = index;
    strcpy(ptr->name, value);
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->height = 0;

    return ptr;
}

/*static void free_node(node_t *node) { free(node); }*/

static int insert_node(node_t *parent, node_t *node) {
    // choose left or richt
    if (parent->index < node->index) {
        if (parent->right != NULL) {
            return insert_node(parent->right, node);
        }
        parent->right = node;
        return 0;
    }

    if (parent->left != NULL) {
        return insert_node(parent->left, node);
    }
    parent->left = node;
    return 0;
}

static int tree_insert(tree_t *tree, node_t *node) {
    if (tree->root == NULL) {
        tree->root = node;
        tree->root->height = 0;
        return 0;
    }

    return insert_node(tree->root, node);
}

static void node_print(node_t *node) {
    if (node->left != NULL) {
        printf("L ");
        node_print(node->left);
    } else if (node->right != NULL) {
        printf("R ");
        node_print(node->right);
    }

    printf("[%d] %s\n", node->index, node->name);
}

static void tree_print(tree_t *tree) { node_print(tree->root); }

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    printf("hello world\n");

    tree_t tree;

    node_t *node1 = create_node(1, "helloworld");
    if (node1 == NULL) {
        return -1;
    }

    node_t *node2 = create_node(2, "jo");
    if (node2 == NULL) {
        return -1;
    }

    node_t *node0 = create_node(0, "thisis");
    if (node0 == NULL) {
        return -1;
    }

    if (tree_insert(&tree, node1) != 0) {
        return 1;
    }

    if (tree_insert(&tree, node2) != 0) {
        return 1;
    }

    if (tree_insert(&tree, node0) != 0) {
        return 1;
    }

    tree_print(&tree);

    return 0;
}
