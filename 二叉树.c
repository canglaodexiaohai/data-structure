#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"BinaryTree.h"
#include"queue.h"
#include"stack.h"
BTNode* BuyBTNode(DataType x)
{
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	assert(node);
	node->_data = x;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}
BTNode* CreateBTree(DataType* a, size_t *pIndex, DataType invalid)
{
	BTNode* root = NULL;
	if (a[*pIndex] != invalid)
	{
		root = BuyBTNode(a[*pIndex]);
		(*pIndex)++;
		root->_left = CreateBTree(a, pIndex, invalid);
		(*pIndex)++;
		root->_right = CreateBTree(a, pIndex, invalid);
	}
	return root;
}
void BTreePrevOrder(BTNode* root)
{
	if (root == NULL)
		return;
	printf("%d ", root->_data);
	BTreePrevOrder(root->_left);
	BTreePrevOrder(root->_right);
}
void BTreeInOrder(BTNode* root)
{
	if (root == NULL)
		return;
	BTreeInOrder(root->_left);
	printf("%d ", root->_data);
	BTreeInOrder(root->_right);
}
void BTreePostOrder(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreePostOrder(root->_left);
	BTreePostOrder(root->_right);
	printf("%d ", root->_data);
}
size_t BTreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	return BTreeSize(root->_left) + BTreeSize(root->_right) + 1;
}
size_t BTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->_left == NULL&&root->_right == NULL)
		return 1;
	return BTreeLeafSize(root->_left) + BTreeLeafSize(root->_right);
}
size_t BTreeKlevelSize(BTNode* root, size_t k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;
	return BTreeKlevelSize(root->_left, k - 1) + BTreeKlevelSize(root->_right, k - 1);
}
static void _BTreeSize1(BTNode* root, size_t* psize)
{
	if (root == NULL)
		return ;
	++(*psize);
	_BTreeSize1(root->_left, psize);
	_BTreeSize1(root->_right, psize);
}
size_t BTreeSize1(BTNode* root)//运用遍历的思想
{
	size_t size = 0;
	_BTreeSize1(root, &size);
	return size;
}
size_t BTreeDepth(BTNode* root)
{
	size_t leftdepth;
	size_t rightdepth;
	if (root == NULL)
		return 0;
	leftdepth = BTreeDepth(root->_left);
	rightdepth = BTreeDepth(root->_right);
	return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
}
BTNode* BTreeFind(BTNode* root, DataType x)
{
	BTNode *leftret;
	BTNode *rightret;
	if (root == NULL)
		return NULL;
	if (root->_data == x)
		return root;
	leftret = BTreeFind(root->_left, x);
	if (leftret)
		return leftret;
	rightret = BTreeFind(root->_right, x);
	if (rightret)
		return rightret;
	return NULL;
}
void _BTreeLevelOrder(BTNode* root, size_t i)
{
	if (root == NULL || i == 0)
	{
		return;
	}
	if (i == 1)
	{
		printf("%d ", root->_data);
		return;
	}
	_BTreeLevelOrder(root->_left, i - 1);
	_BTreeLevelOrder(root->_right, i - 1);
}

void BTreeLevelOrder(BTNode* root)
{
	if (root == NULL)
		return;
	int dep = BTreeDepth(root);
	for (int i = 1; i <= dep; i++)
	{
		_BTreeLevelOrder(root, i);
	}
}
void BTreeLevelOrderNonR(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (QueueEmpty(&q) != 0)
	{
		BTNode* front = QueueFront(&q);
		printf("%d ", front->_data);
		QueuePop(&q);
		if (front->_left)
		{
			QueuePush(&q, front->_left);
		}
		if (front->_right)
		{
			QueuePush(&q, front->_right);
		}
	}
	printf("\n");
}
int IsCompleteBTree1(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	while (QueueEmpty(&q) != 0)
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front == NULL)
		{
			break;
		}
		else
		{
			QueuePush(&q, front->_left);
			QueuePush(&q, front->_right);
		}
	}
	while (QueueEmpty(&q) != 0)
	{
		BTNode* front = QueueFront(&q);
		if (front)
		{
			return 0;
		}
		QueuePop(&q);
	}
	return 1;
}

int IsCompleteBTree2(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	if (root)
		QueuePush(&q, root);
	int flag = 1;
	while (QueueEmpty(&q) != 0)
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front->_left)
		{
			if (flag == 0)
			{
				return 0;
			}
			QueuePush(&q, front->_left);
		}
		else
			flag = 0;
		if (front->_right)
		{
			if (flag == 0)
			{
				return 0;
			}
			QueuePush(&q, front->_right);
		}
		else
			flag = 0;
	}
	return 1;
}
void BTreePrevOrderNonR(BTNode* root)
{
	Stack s;
	BTNode* cur=root;
	StackInit(&s);

	while (cur||StackEmpty(&s) != 0)
	{
		printf("%d ", cur->_data);
		StackPush(&s, cur);
		cur = cur->_left;
		while (cur==NULL &&StackEmpty(&s)!=0)
		{
			cur = StackTop(&s);
			StackPop(&s);
			cur = cur->_right;
		}
	}
}
void BTreeInOrderNonR(BTNode* root)
{
	Stack s;
	StackInit(&s);
	BTNode* cur = root;
	while (cur != NULL || StackEmpty(&s) != 0)
	{
		if (cur->_left!=NULL)
		{
			StackPush(&s, cur);
			cur = cur->_left;
		}
		else
		{
			printf("%d ", cur->_data);
			cur = cur->_right;
			while (cur == NULL&&StackEmpty(&s) != 0)
			{
				cur = StackTop(&s);
				printf("%d ", cur->_data);
				StackPop(&s);
				cur = cur->_right;
			}
		}
	}
}
void BTreePostOrderNonR(BTNode* root)
{
	BTNode* cur = root;
	BTNode* prev = NULL;
	Stack s;
	StackInit(&s);
	while (cur != NULL || StackEmpty(&s) != 0)
	{
		while (cur != NULL)
		{
			StackPush(&s, cur);
			cur = cur->_left;
		}
		BTNode* top = StackTop(&s);
		if (top->_right==NULL||top->_right==prev)
		{
			printf("%d ", top->_data);
			prev = top;
			StackPop(&s);
		}
		else
		{
			cur = top->_right;
		}
	}	
}
void TestBinaryTree()
{
	DataType a[] = { 1, 2, 3, '#',7,'#', '#', 4, '#', '#', 5, 6, '#', '#','#' };
	size_t index = 0;
	BTNode* tree = CreateBTree(a, &index, '#');
	printf("前序遍历递归  ：");
	BTreePrevOrder(tree);
	printf("\n");
	printf("前序遍历非递归：");
	BTreePrevOrderNonR(tree);
	printf("\n");
	printf("中序遍历递归  ：");
	BTreeInOrder(tree);
	printf("\n");
	printf("中序遍历非递归：");
	BTreeInOrderNonR(tree);
	printf("\n");
	printf("后序遍历递归  ：");
	BTreePostOrder(tree);
	printf("\n");
	printf("后序遍历非递归：");
	BTreePostOrderNonR(tree);
	printf("\n");
	printf("层序遍历递归  ：");
	BTreeLevelOrder(tree);
	printf("\n");
	printf("层序遍历非递归：");
	BTreeLevelOrderNonR(tree);


	printf("节点个数：%d\n", BTreeSize(tree));
	printf("节点个数：%d\n", BTreeSize1(tree));

	printf("叶子结点个数：%d\n", BTreeLeafSize(tree));
	printf("第k层节点个数：%d\n", BTreeKlevelSize(tree, 3));
	printf("树的深度：%d\n", BTreeDepth(tree));
	printf("查找结点: %d\n", BTreeFind(tree, 6)->_data);
	printf("是否是满二叉树：%d\n", IsCompleteBTree1(tree));
	printf("是否是满二叉树：%d\n", IsCompleteBTree2(tree));
}
