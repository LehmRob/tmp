#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct value {
    int index;
    char key;
} value;

typedef struct node {
    value *value;
    struct node *next;
} node_t;

typedef struct {
    node_t *root;
    size_t size;
} list_t;

static int initlist(list_t *l) {
    l->root = NULL;
    l->size = 0;

    return 0;
};

static int allocnode(node_t **node) {
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL) {
        return -ENOMEM;
    }

    n->value = malloc(sizeof(value));
    if (n->value == NULL) {
        free(n);
        return -ENOMEM;
    }

    *node = n;

    return 0;
}

static int addnode(node_t **node, int index, char key) {
    if (allocnode(node) != 0) {
        return -ENOMEM;
    }

    (*node)->value->index = index;
    (*node)->value->key = key;
    (*node)->next = NULL;

    return 0;
}

static int list_addnode(list_t *l, int index, char key) {
    if (l->root == NULL) {
        if(allocnode(&(l->root)) != 0) {
            return -ENOMEM;
        }

        l->root->value->index = index;
        l->root->value->key = key;
        l->root->next = NULL;

        return 0;
    }

    node_t *cur = l->root;

    // search for free position
    while (cur->next != NULL) {
        cur = cur->next;
    }

    return addnode(&(cur->next), index, key);
}

static void list_print(list_t *l) {
    node_t *cur = l->root;

    while(cur != NULL) {
        if (cur->value != NULL) {
            printf("Index [%d] - %c\n", cur->value->index, cur->value->key);
        }
        cur = cur->next;
    }
}

static void freenode(node_t *node) {
    if (node->next != NULL) {
        freenode(node->next);
    }

    free(node->value);
    free(node);
}

static void destroylist(list_t *l) {
    freenode(l->root);
    l->root = NULL;
}

int main(int ac, char** av) {
    list_t list;
    if (initlist(&list) != 0) {
        return -1;
    }

    if (list_addnode(&list, 0, 'a') != 0) {
        return -1;
    }
    if (list_addnode(&list, 1, 'b') != 0) {
        return -1;
    }
    if (list_addnode(&list, 2, 'c') != 0) {
        return -1;
    }

    list_print(&list);
    destroylist(&list);


    return 0;
}
