// <Doubly Circular linked list>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // (typedef�� ����Ͽ�) Node ����ü ����
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

// �Լ� ����Ʈ
int initialize(listNode** h); // ���������͸� �Ű������� ����
int freeList(listNode* h); // �̱������͸� �Ű������� ����
int insertLast(listNode* h, int key); // list�� key�� ���� ��� �߰�
int deleteLast(listNode* h); // ������ ��� ����
int insertFirst(listNode* h, int key); // ó���� ��� �߰�
int deleteFirst(listNode* h); // ��� ����
int invertList(listNode* h); // ���ġ

int insertNode(listNode* h, int key); // �˻� ��, ��� ����
int deleteNode(listNode* h, int key); // list�� key�� ���� ��� ����

void printList(listNode* h); // ���

int main()
{
	char command; // ���� command
	int key; // ���� key
	listNode* headnode=NULL;

    printf("[----- [�����]  [2020039102] -----]\n"); 

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // �� �ޱ�

		switch(command) {
		case 'z': case 'Z':  // ���� z �Ǵ� Z �� ���
			initialize(&headnode);
			break;
		case 'p': case 'P': // ���� p �Ǵ� P �� ���
			printList(headnode);
			break;
		case 'i': case 'I': // ���� i �Ǵ� I �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // ���� d �Ǵ� D �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // ���� n �Ǵ� N �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // ���� e �Ǵ� E �� ���
			deleteLast(headnode);
			break;
		case 'f': case 'F': // ���� f �Ǵ� F �� ���
			printf("Your Key = ");
			scanf("%d", &key); // �� �ޱ�
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // ���� t �Ǵ� T �� ���
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // ���� r �Ǵ� R �� ���
			invertList(headnode);
			break;
		case 'q': case 'Q': // ���� q �Ǵ� Q �� ���
			freeList(headnode);
			break;
		default:
			printf("\n  >>>>>   Concentration!!   <<<<< \n"); // ��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); // ���� q �Ǵ� Q �� ���� �� ���� ����

	return 1;
}

int initialize(listNode** h) {

	// headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if(*h != NULL) // NULL�� �ƴ�
		freeList(*h); // ����

	// headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� 
	*h = (listNode*)malloc(sizeof(listNode));  // *h�� 'headNode' Ÿ������ �ּ� �ޱ�
	(*h)->rlink = *h; // h ����Ű�� rlink�� h ����Ű�� �ּ� ����
	(*h)->llink = *h; // h ����Ű�� link�� h ����Ű�� �ּ� ����
	(*h)->key = -9999; // key -9999 �ʱ�ȭ
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) // h ����Ű�� rlink �� h ���ٸ�
	{
		free(h); // ����
		return 1;
	}

	// h�� ����� listNode �޸� ����
	// headNode�� �����Ǿ�� ��
	listNode* p = h->rlink; // p �����, h ����Ű�� rlink �� �ּ� ����
	listNode* prev = NULL; // Stack ������ prev �����, NULL ����

	while(p != NULL && p != h) { // p �� NULL �� �ƴϸ�
		prev = p; // p �� �ּ� prev ����
		p = p->rlink; // p ����Ű�� rlink �� �ּ� p �� ����
		free(prev); // ����
	}
	free(h); // ����
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // NULL �̸�
		printf("Nothing to print....\n"); // ��� ���
		return;
	}

	p = h->rlink; // h ����Ű�� rlink �� �ּ� p �� ����

	while(p != NULL && p != h) { // NULL �� �ƴϸ� 
		printf("[ [%d]=%d ] ", i, p->key); // i ��° ��� �� key �� ���
		p = p->rlink; // p ����Ű�� rlink �� �ּ� p �� ����
		i++; // i+1 ����
	}
	printf("  items = %d\n", i);


	// print addresses
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	// h ����Ű�� link, rlink �� �ּ� ���

	i = 0; // i �� 0 ����
	p = h->rlink; // h ����Ű�� rlink �� �ּ� p �� ����
	while(p != NULL && p != h) { // NULL �� �ƴϸ�
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		// i ��° �ּ� , �� ��� �� llink �� rlink �� �ּ� ���
		p = p->rlink; // p ����Ű�� rlink �� �ּ� p �� ����
		i++; // i+1 ����
	}

}

// list�� key�� ���� ����ϳ��� �߰�
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // NULL �̸�

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �ּ� �ޱ�
	node->key = key; // node ����Ű�� key �Է� key ����
	node->rlink = NULL; // node ����Ű�� rlink �� NULL ����
	node->llink = NULL; // node ����Ű�� link �� NULL ����

	if (h->rlink == h) // h ����Ű�� rlink �� h ����Ű��
	{
		h->rlink = node; // h ����Ű�� rlink �� node �� �ּ� ����
		h->llink = node; // �ּ� ����
		node->rlink = h; // node ����Ű�� rlink �� NULL ����
		node->llink = h; // �ּ� ����
	} else {
		h->llink->rlink = node; // h ����Ű�� link ����Ű��  rlink �� node �� �ּ� ����
		node->llink = h->llink; // �ּ� ����
		h->llink = node; // �ּ� ����
		node->rlink = h; // �ּ� ����
	}

	return 1;
}


// list�� ������ ��� ����
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // NULL �̸�
	{
		printf("nothing to delete.\n"); // �˸��� ���
		return 1;
	}

	listNode* nodetoremove = h->llink; // Stack �� nodetoremove �����, h ����Ű�� lonk �� �ּ� ����

	// link ���� 
	nodetoremove->llink->rlink = h; // �ּ� ����
	h->llink = nodetoremove->llink; // �ּ� ����

	free(nodetoremove); // ����

	return 1;
}

// list ó���� key�� ���� ����ϳ��� �߰�
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �ּҹޱ�
	node->key = key; // node ����Ű�� key �� key ����
	node->rlink = NULL; // NULL ����
	node->llink = NULL; // NULL ����

	node->rlink = h->rlink; // node ����Ű�� rlink �� h ����Ű�� rlink �� �ּ� ����
	h->rlink->llink = node; // �ּ� ����
	node->llink = h; // �ּ� ����
	h->rlink = node; // �ּ� ����

	return 1;
}

// list�� ù��° ��� ����
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // NULL �̸�
	{
		printf("nothing to delete.\n"); // �˸��� ���
		return 0;
	}

	listNode* nodetoremove = h->rlink; 

	// link ���� 
	nodetoremove->rlink->llink = h; // �ּ� ����
	h->rlink = nodetoremove->rlink; // �ּ� ����

	free(nodetoremove); // ����
	return 1;

}

// ����Ʈ�� ��ũ�� �������� �� ��ġ
int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) { // NULL �̸�
		printf("nothing to invert...\n"); // �˸��� ���
	}
	listNode *n = h->rlink; // Stack �� n �����, h ����Ű�� rlink �� �ּ� ����
	listNode *trail = h; // trail �����, h �� �ּ� ����
	listNode *middle = h; // middle �����, h �� �ּ� ����

	// ���� �ٲ� ��ũ ����
	h->llink = h->rlink;

	while(n != NULL && n != h){ // NULL �ƴϸ�
		trail = middle; // trail �� middle �ּ� ����
		middle = n; // middle �� n �� �ּ� ����
		n = n->rlink; // n �� n ����Ű�� rlink �� �ּ� ����
		middle->rlink = trail; // middle ����Ű�� rlink �� trail �ּ� ����
		middle->llink = n; // middle ����Ű�� llink �� n �� �ּ� ����
	}

	h->rlink = middle; // ���ġ
	return 0;
}

// ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �ּҹޱ�
	node->key = key; // node ����Ű�� key �� key ����
	node->llink = node->rlink = NULL; // node ����Ű�� llik, rlink �� NULL ����

	if (h->rlink == h) // h ����Ű�� rlink �� h ���ٸ�
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	// key�� �������� ������ ��ġ�� ã�´� 
	while(n != NULL && n != h) {
		if(n->key >= key) {
			// n ����Ű�� key �Է¹��� key ����
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { 
				node->rlink = n; // node ����Ű�� rlink �� n �� �ּ� ����
				node->llink = n->llink; // �ּ� ����
				n->llink->rlink = node; // �ּ� ����
				n->llink = node; // �߰�
			}
			return 0;
		}
		n = n->rlink; //n �� n ����Ű�� rlink �ּ� ����
	}

	// ������ ������ ã�� ���� ���, �������� ���� 
	insertLast(h, key); 
	return 0;
}


int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) // NULL �̸�
	{
		printf("nothing to delete.\n"); // �˸��� ���
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) { // NULL �� �ƴϸ�
		if(n->key == key) { // n ����Ű�� key �Է��� key �� ������
			if(n == h->rlink) { // n �� h ����Ű�� rlink �� ������
				deleteFirst(h); // ����
			} else if (n->rlink == h){ // n ����Ű�� rlink �� h �� ������
				deleteLast(h); // ����
			} else { 
				n->llink->rlink = n->rlink; // n ����Ű�� llink ����Ű�� rlink �� n ����Ű�� rlink �ּ� ����
				n->rlink->llink = n->llink; // n ����Ű�� rlink ����Ű�� llink �� n ����Ű�� llink �ּ� ����
				free(n); // ����
			}
			return 0;
		}
		n = n->rlink; // n�� n ����Ű�� rlink �� �ּ� ����
	}

	// ã�� �� �Ѱ��
	printf("cannot find the node for key = %d\n", key); // ��� ���
	return 0;
}