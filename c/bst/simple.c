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
    strncpy(ptr->name, value, MAX_NAME_SIZE);
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->height = 0;

    return ptr;
}

static int insert_node(node_t *parent, int index, const char *name) {
    // choose left or right
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
        strncpy(parent->name, name, MAX_NAME_SIZE);
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
        strncpy(resp, node->name, MAX_NAME_SIZE);
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

static node_t *node_find_left_leaf(node_t *node) {
    if (node->left != NULL) {
        node = node->left;
        return node_find_left_leaf(node);
    }

    return node;
}

static void node_free(node_t *node) { free(node); }

static int node_delete(node_t *current, int index) {
    if (current->index < index) {
        return node_delete(current->right, index);
    }

    if (current->index > index) {
        return node_delete(current->left, index);
    }

    // there are different cases for deletion
    // 1) delete a leaf (left and right are NULL)
    // 2) delete a node with one child node
    // 3) delete a node with two child nodes
    if (current->left != NULL && current->right != NULL) {
        node_t *successor = node_find_left_leaf(current->right);
        current->index = successor->index;
        strncpy(current->name, successor->name, MAX_NAME_SIZE);
        return node_delete(successor, successor->index);
    } else if (current->left != NULL) {
        current->index = current->left->index;
        strncpy(current->name, current->left->name, MAX_NAME_SIZE);
        current->left = current->left->left;
        node_free(current->left);
        current->left = NULL;
    } else if (current->right != NULL) {
        current->index = current->right->index;
        strncpy(current->name, current->right->name, MAX_NAME_SIZE);
        current->right = current->right->right;
        node_free(current->right);
        current->right = NULL;
    } else {
        node_free(current);
        current = NULL;
    }

    return 0;
}

static int tree_delete(tree_t *tree, int index) { return node_delete(tree->root, index); }

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

    if (tree_insert(&tree, 7, "johnny") != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    if (tree_insert(&tree, 4, "tim") != 0) {
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

    printf("after get\n");

    if (tree_delete(&tree, 8) != 0) {
        fprintf(stderr, "Something bad happendes\n");
        exit(EXIT_FAILURE);
    }

    tree_print(&tree);

    return 0;
}
