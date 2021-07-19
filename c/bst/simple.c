#include <errno.h>
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

static node_t *create_node(int index, const char *value) {
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

static int insert_node(node_t *parent, int index, const char *name) {
    // choose left or richt
    if (index > parent->index) {
        if (parent->right != NULL) {
            return insert_node(parent->right, index, name);
        }

        node_t *node = create_node(index, name);
        if (node == NULL) {
            return -ENOMEM;
        }

        parent->right = node;

    } else if (index < parent->index) {
        if (parent->left != NULL) {
            return insert_node(parent->left, index, name);
        }

        node_t *node = create_node(index, name);
        if (node == NULL) {
            return -ENOMEM;
        }

        parent->left = node;

    } else {
        strcpy(parent->name, name);
    }

    return 0;
}

static int tree_insert(tree_t *tree, int index, const char *name) {
    if (tree->root == NULL) {
        node_t *node = create_node(index, name);
        if (node == NULL) {
            return -ENOMEM;
        }

        tree->root = node;

        return 0;
    }

    return insert_node(tree->root, index, name);
}

static void node_print(node_t *node) {
    // check if we reached the end of the tree
    if (node == NULL) {
        return;
    }

    printf("[%d] %s", node->index, node->name);

    if (node->left != NULL) {
        printf("<-- ");
        node_print(node->left);
        printf("\n");
    }

    if (node->right != NULL) {
        printf("--> ");
        node_print(node->right);
        printf("\n");
    }
}

static int node_get(node_t *node, int index, char *resp) {
    if (node == NULL) {
        return -EINVAL;
    }

    if (node->index == index) {
        strcpy(resp, node->name);
        return 0;
    }

    if (node->left != NULL) {
        if (node_get(node->left, index, resp) == 0) {
            return 0;
        }
    }

    if (node->right != NULL) {
        if (node_get(node->right, index, resp) == 0) {
            return 0;
        }
    }

    return -ENOKEY;
}

static int tree_get(tree_t *tree, int index, char *resp) {
    return node_get(tree->root, index, resp);
}

static void tree_print(tree_t *tree) { node_print(tree->root); }

int main(int ac, char **av) {
    (void)ac;
    (void)av;

    tree_t tree;

    if (tree_insert(&tree, 5, "robert") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    if (tree_insert(&tree, 1, "sarah") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    if (tree_insert(&tree, 8, "max") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    if (tree_insert(&tree, 13, "tim") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    if (tree_insert(&tree, 2, "tom") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    tree_print(&tree);

    char resp[MAX_NAME_SIZE];

    if (tree_get(&tree, 8, resp) != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    printf("Found name %s\n", resp);

    if (tree_get(&tree, 9, resp) == 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
