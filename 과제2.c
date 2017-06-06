#define Black 1
#define Red 0
#include <stdio.h>
#include <stdlib.h>
int bh = 0;
int tb = 0;
int tr = 0;
int total = 0;

typedef struct Node*NodePtr;
struct Node {
	int val;
	NodePtr parent, left, right;
	int color;
};


NodePtr node_alloc(int newval) {
	NodePtr self = (NodePtr)malloc(sizeof(struct Node));
	self->val = newval;
	self->parent = NULL;
	self->left = NULL;
	self->right = NULL;
	self->color = Black;
	return self;
}


typedef struct RBT* RBTPtr;
struct RBT {
	NodePtr root;
};


RBTPtr rbt_alloc() {
	RBTPtr self = (RBTPtr)malloc(sizeof(struct RBT));
	self->root = NULL;
	return self;
}


void Left_Rotate(RBTPtr self, NodePtr n) {
	NodePtr y;
	y = n->right;
	n->right = y->left;
	if (y->left != NULL)
		y->left->parent = n;
	y->parent = n->parent;
	if (n->parent == NULL)
		self->root = y;
	else if (n == n->parent->left)
		n->parent->left = y;
	else
		n->parent->right = y;
	y->left = n;
	n->parent = y;
}


void Right_Rotate(RBTPtr self, NodePtr n) {
	NodePtr y;
	y = n->left;
	n->left = y->right;
	if (y->right != NULL)
		y->right->parent = n;
	y->parent = n->parent;
	if (n->parent == NULL)
		self->root = y;
	else if (n == n->parent->right)
		n->parent->right = y;
	else
		n->parent->left = y;
	y->right = n;
	n->parent = y;
}


void rbt_insert_fixup(RBTPtr self, NodePtr n) {
	NodePtr y;
	while (n->parent != NULL && n->parent->color == Red) {
		if (n->parent == n->parent->parent->left) {
			y = n->parent->parent->right;
			if (y != NULL && y->color == Red) {
				n->parent->color = Black;
				y->color = Black;
				n->parent->parent->color = Red;
				n = n->parent->parent;
			}
			else if (n == n->parent->right) {
				n = n->parent;
				Left_Rotate(self, n);
			}
			else {
				n->parent->color = Black;
				n->parent->parent->color = Red;
				Right_Rotate(self, n->parent->parent);
			}
		}
		else if (n->parent == n->parent->parent->right) {
			y = n->parent->parent->left;
			if (y != NULL && y->color == Red) {
				n->parent->color = Black;
				y->color = Black;
				n->parent->parent->color = Red;
				n = n->parent->parent;
			}
			else if (n == n->parent->left) {
				n = n->parent;
				Right_Rotate(self, n);
			}
			else {
				n->parent->color = Black;
				n->parent->parent->color = Red;
				Left_Rotate(self, n->parent->parent);
			}
		}
	}
	self->root->color = Black;
}


void rbt_insert(RBTPtr self, NodePtr n) {
	NodePtr y = NULL;
	NodePtr x = self->root;
	while (x != NULL) {
		y = x;
		if (n->val < x->val)
			x = x->left;
		else
			x = x->right;
	}
	n->parent = y;
	if (y == NULL)
		self->root = n;
	else if (n->val < y->val)
		y->left = n;
	else
		y->right = n;
	n->left = NULL;
	n->right = NULL;
	n->color = Red;
	rbt_insert_fixup(self, n);
}

void rbt_print(RBTPtr self, NodePtr tree, int level) {
	if (tree->right != NULL)
		rbt_print(self, tree->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("    ");
	if (tree->color == Black) {
		printf("%dB\n", tree->val);
		tb = tb + 1;
	}
	if (tree->color == Red) {
		printf("%dR\n", tree->val);
		tr = tr + 1;
	}
	if (tree->left != NULL)
		rbt_print(self, tree->left, level + 1);
}


int rbt_bh(RBTPtr self, NodePtr tree, int bh) {
	if (tree == NULL) {
		return bh;
	}
	else {
		if (tree->color == Black)
			rbt_bh(self, tree->right, bh + 1);
		else if (tree->color == Red)
			rbt_bh(self, tree->right, bh);
	}
}

struct node
{
	int data;
	struct node *next;
};
void push(struct node** head_ref, int new_data)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void deleteNode(struct node **head_ref, int key)
{
	struct node* temp = *head_ref, *prev;

	if (temp != NULL && temp->data == key)
	{
		*head_ref = temp->next;
		free(temp);
		return;
	}


	while (temp != NULL && temp->data != key)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return;

	prev->next = temp->next;

	free(temp);
}

void printList(struct node *node)
{
	while (node != NULL)
	{
		printf(" %d ", node->data);
		node = node->next;
	}
}

int main()
{
	struct node* cur = NULL;
	struct node* head = NULL;
	RBTPtr rbt = rbt_alloc();
	FILE *fp;
	int data;
	fp = fopen("C:\\Users\\Á¤À±Àç\\Desktop\\ÀÚ±¸\\input.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%d", &data);
		if (data >0)
			push(&head, data);
		else if (data < 0) {
			deleteNode(&head, -1 * data);
		}
		else if (data == 0) {
			break;
		}
	}
	cur = head;
	while (cur != NULL)
	{
		rbt_insert(rbt, node_alloc(cur->data));
		cur = cur->next;

	}
	fclose(fp);
	rbt_print(rbt, rbt->root, 0);
	printf("\n\n\n\n");
	printf("bh is %d\n", rbt_bh(rbt, rbt->root, bh));
	printf("nb is %d\n", tb);
	printf("total is %d\n", tb + tr);
	return 0;
}