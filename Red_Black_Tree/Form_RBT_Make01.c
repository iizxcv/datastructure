
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////
// void levelOrderTraversal(BSTNode *node);

void insertNode(Node **node, int value);
void removeAll(Node **node);
Node *search_uncle(Node *cur);

void restructuring(Node **node);


//////////////////////////////////////////////////////////////////////////////
typedef struct _node
{
	int item;
	char Color;
	struct _node *parent;
	struct _node *left;
	struct _node *right;
} Node; // You should not change the definition of Node

typedef struct _bstree
{
	struct _node *root;
	int black_depth;

} BSTree;

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	Node *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////

void insertNode(Node **node, int value)
{
	if (*node == NULL)
	{
		*node = malloc(sizeof(Node));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->Color = 'R';
			(*node)->left = NULL;
			(*node)->right = NULL;
			(*node)->parent = NULL;

			return;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertNode(&((*node)->left), value);
			if (&(*node)->left->parent == NULL)
			{
				(*node)->left->parent = (*node);
			}
			if ((*node)->Color == (*node)->left->Color)
			{
			}
			Node *bro = search_bro((*node));
			if (bro != NULL) // 부모가 널이 아니면 삼촌노드 black인지 확인
			{
				if(bro->Color == 'B'){
					restructuring(&(*node)->parent);
				}
			}
		}

		else if (value > (*node)->item)
		{
			insertNode(&((*node)->right), value);
			if (&(*node)->right->parent == NULL)
			{
				(*node)->right->parent = (*node);
			}
		}
		else
			return;
		// 자신이 root면 parent가 없음. 즉. root이므로 B.
		if ((*node)->parent = NULL)
		{
			(*node)->Color = 'B';
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////

void removeAll(Node **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}

void restructuring(Node **node)
{

}

Node *search_bro(Node *cur)
{
	if (cur->parent == NULL)
	{
		return NULL;
	}
	if (cur->parent->left == cur)
	{
		return cur->parent->right;
	}
	else if (cur->parent->right == cur)
	{
		return cur->parent->left;
	}
}


