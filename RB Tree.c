#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the RB-tree
typedef struct node {
    int data;           // Data stored in the node
    int color;          // Color of the node (0 = black, 1 = red)
    int size;           // Number of nodes in the subtree rooted at this node
    struct node* parent;    // Parent node
    struct node* left;      // Left child
    struct node* right;     // Right child
} Node;

// Function to create a new node with given data
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->color = 1;    // New node is always red
    new_node->size = 1;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_no…
 // Function to fix the violations of RB-tree properties after insertion
void fix_insertion(Node** root, Node* node) {
    while (node != *root && node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotate_left(root, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotate_right(root, node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotate_right(root, node);
                }
                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotate_left(root, node->parent->parent);
            }
        }
    }
    (*root)->color = 0;     // The root is always black
}

// Function to insert a node into the RB-tree
void insert_node(Node** root, int data) {
    Node* new_node = create_node(data);
    Node* parent = NULL;
    Node* current = *root;
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current->size++;
            current = current->left;
        } else {
            current->size++;
            current = current->right;
        }
    }
    new_node->parent = parent;
    if (parent == NULL) {
        *root = new_node;
    } else if (data < parent->data) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    fix_insertion(root, new_node);
}

// Function to get the node with minimum value in the subtree rooted at a node
Node* get_min_node(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to fix the violations of RB-tree properties after deletion
void fix_deletion(Node** root, Node* node, Node* parent) {
    while (node != *root && (node == NULL || node->color == 0)) {
        if (node == parent->left) {
            Node* sibling = parent->right;
            if (sibling->color == 1) {
                sibling->color = 0;
                parent->color = 1;
                rotate_left(root, parent);
                sibling = parent->right;
            }
            if ((sibling->left == NULL || sibling->left->color == 0) && (sibling->right == NULL || sibling->right->color == 0)) {
                sibling->color = 1;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == 0) {
                    sibling->left->color = 0;
                    sibling->color = 1;
                    rotate_right(root, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = 0;
                sibling->right->color = 0;
                rotate_left(root, parent);
                node = *root;
            }
        } else {
            Node* sibling = parent->left;
            if (sibling->color == 1) {
                sibling->color = 0;
                parent->color = 1;
                rotate_right(root, parent);
                sibling = parent->left;
            }
            if ((sibling->left == NULL || sibling->left->color == 0) && (sibling->right == NULL || sibling->right->color == 0)) {
                sibling->color = 1;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == 0) {
                    sibling->right->color = 0;
                    sibling->color = 1;
                    rotate_left(root, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = 0;
                sibling->left->color = 0;
                rotate_right(root, parent);
                node = *root;
            }
        }
    }
    if (node != NULL) {
        node->color = 0;
    }
}

// Function to delete a node from the RB-tree
void delete_node(Node** root, int data) {
    Node* node = *root;
    while (node != NULL) {
        if (data < node->data) {
            node->size--;
            node = node->left;
        } else if (data > node->data) {
            node->size--;
            node = node->right;
        } else {
            if (node->left == NULL || node->right == NULL) {
                Node* child = node->left == NULL ? node->right : node->left;
                if (child == NULL) {
                    if (node == *root) {
                        *root = NULL;
                    } else {
                        if (node == node->parent->left) {
                            node->parent->left = NULL;
                        } else {
                            node->parent->right = NULL;
                        }
                        node = node->parent;
                    }
                } else {
                    if (node == *root) {
                        child->parent = NULL;
                        *root = child;
                    } else {
                        child->parent = node->parent;
                        if (node == node->parent->left) {
                        node->parent->left = child;
                    } else {
                        node->parent->right = child;
                    }
                }
                free(node);
            } else {
                Node* successor = node->right;
                while (successor->left != NULL) {
                    successor->size--;
                    successor = successor->left;
                }
                node->data = successor->data;
                node->size--;
                node = successor;
            }
            break;
        }
    }
    if (node != NULL) {
        fix_deletion(root, node, node->parent);
    }
}

// Function to print nodes of the RB-tree in inOrder
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function to split the RB-tree into two RB-trees based on a key value
Node** split(Node** root, int key) {
    Node* curr = *root;
    Node* prev = NULL;
    Node* new_root1 = NULL;
    Node* new_root2 = NULL;
    int size1 = 0, size2 = 0;

    while (curr != NULL) {
        if (curr->data < key) {
            if (prev == NULL || prev->data >= key) {
                new_root1 = curr;
            }
            prev = curr;
            size1 += curr->size - (curr->right == NULL ? 0 : curr->right->size);
            curr = curr->right;
        } else if (curr->data > key) {
            if (prev == NULL || prev->data <= key) {
                new_root2 = curr;
            }
            prev = curr;
            size2 += curr->size - (curr->left == NULL ? 0 : curr->left->size);
            curr = curr->left;
        } else {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->data = key;
            new_node->size = 1;
            new_node->color = 1;
            new_node->parent = curr;
            new_node->left = NULL;
            new_node->right = NULL;

            if (curr->left == NULL) {
                curr->left = new_node;
            } else {
                Node* temp = curr->left;
                while (temp->right != NULL) {
                    temp = temp->right;
                }
                temp->right = new_node;
                new_node->parent = temp;
            }

            if (curr->right == NULL) {
                curr->right = new_node;
            } else {
                Node* temp = curr->right;
                while (temp->left != NULL) {
                    temp = temp->left;
                }
                temp->left = new_node;
                new_node->parent = temp;
            }

            if (prev == NULL || prev->data < key) {
                new_root1 = curr;
            } else if (prev == NULL || prev->data > key) {
                new_root2 = curr;
            }
            break;
        }
    }

    if (new_root1 != NULL) {
        delete_node(root, new_root1->data);
    }

    if (new_root2 != NULL) {
        delete_node(root, new_root2->data);
    }

    Node** result = (Node*)malloc(2 * sizeof(Node));
    result[0] = new_root1;
    result[1] = new_root2;

    return result;
}

// Function to join two RB-trees into one RB-tree
Node* join(Node* root1, Node* root2, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = key;
    new_node->size = 1;
    new_node->color = 1;
    new_node->left = root1;
    new_node->right = root2;

    if (root1 != NULL) {
        root1->parent = new_node;
        new_node->size += root1->size;
    }

    if (root2 != NULL) {
        root2->parent = new_node;
        new_node->size += root2->size;
    }

    fix_insertion(&new_node, new_node);

    return new_node;
}

int main() {
    Node* root = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 9; i++) {
        root = insert_node(root, arr[i]);
    }

    printf("Before splitting:\n");
    inOrder(root);
    printf("\n");

    Node** result = split(&root, 4);
    Node* root1 = result[0];
    Node* root2 = result[1];

    printf("After splitting:\n");
    printf("First tree: ");
    inOrder(root1);
    printf("\n");
    printf("Second tree: ");
    inOrder(root2);
    printf("\n");

    Node* new_root = join(root1, root2, 4);

    printf("After joining:\n");
    inOrder(new_root);
    printf("\n");

    return 0;
}
