//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////
//
#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// int insertSortedLL(LinkedList *ll, int item)
// {
// 	/* add your code here */

// 	ListNode *cur = ll->head;
// 	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
// 	temp->item = item;
// 	int cnt = 0;
// 	if (ll->head == NULL) // 헤드가 없으면
// 	{
// 		ll->head = temp;
// 		ll->size++;
// 		return cnt;
// 	}

// 	while (cur->next != NULL && cur->next->item < item)
// 	{
// 		cur = cur->next;
// 		cnt++;
// 	}
// 	if (cur->item == item)
// 	{ // 현재와 같으면 -1 리턴

// 		return -1;
// 	}

// 	else if (item < cur->item) //
// 	{
// 		temp->next = cur;
// 		ll->head = temp;
// 		ll->size++;
// 		return ++cnt;
// 	}
// 	else if (cur->next == NULL)
// 	{
// 		cur->next = temp;
// 		ll->size++;
// 		return ++cnt;
// 	}
// 	else
// 	{
// 		if (cur->next->item == item)
// 		{ // 현재와 같으면 -1 리턴

// 			return -1;
// 		}
// 		ListNode *temp2;
// 		temp2 = cur->next;
// 		cur->next = temp;
// 		temp->next = temp2;
// 		ll->size++;
// 		return ++cnt;
// 	}

// 	return -1;
// }

///////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if (!temp) return -1; // malloc 실패 체크
    temp->item = item;
    temp->next = NULL;

    ListNode *cur = ll->head;
    ListNode *prev = NULL;
    int cnt = 0;

    // 중복 체크 및 삽입 위치 탐색
    while (cur != NULL && cur->item < item) {
        prev = cur;
        cur = cur->next;
        cnt++;
    }

    // 중복된 값이 있는 경우
    if (cur != NULL && cur->item == item) {
        free(temp);
        return -1;
    }

    // 앞에 삽입 (맨 앞)
    if (prev == NULL) {
        temp->next = ll->head;
        ll->head = temp;
    }
    // 중간 혹은 맨 끝 삽입
    else {
        prev->next = temp;
        temp->next = cur;
    }

    ll->size++;
    return cnt;
}

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
