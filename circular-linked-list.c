// <Doubly Circular linked list>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // (typedef를 사용하여) Node 구조체 생성
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

// 함수 리스트
int initialize(listNode** h); // 이중포인터를 매개변수로 받음
int freeList(listNode* h); // 싱글포인터를 매개변수로 받음
int insertLast(listNode* h, int key); // list에 key에 대한 노드 추가
int deleteLast(listNode* h); // 마지막 노드 삭제
int insertFirst(listNode* h, int key); // 처음에 노드 추가
int deleteFirst(listNode* h); // 노드 삭제
int invertList(listNode* h); // 재배치

int insertNode(listNode* h, int key); // 검색 후, 노드 삽입
int deleteNode(listNode* h, int key); // list에 key에 대한 노드 삭제

void printList(listNode* h); // 출력

int main()
{
	char command; // 변수 command
	int key; // 변수 key
	listNode* headnode=NULL;

    printf("[----- [노관범]  [2020039102] -----]\n"); 

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
		scanf(" %c", &command); // 값 받기

		switch(command) {
		case 'z': case 'Z':  // 값이 z 또는 Z 일 경우
			initialize(&headnode);
			break;
		case 'p': case 'P': // 값이 p 또는 P 일 경우
			printList(headnode);
			break;
		case 'i': case 'I': // 값이 i 또는 I 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // 값이 n 또는 N 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // 값이 e 또는 E 일 경우
			deleteLast(headnode);
			break;
		case 'f': case 'F': // 값이 f 또는 F 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // 값 받기
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // 값이 t 또는 T 일 경우
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // 값이 r 또는 R 일 경우
			invertList(headnode);
			break;
		case 'q': case 'Q': // 값이 q 또는 Q 일 경우
			freeList(headnode);
			break;
		default:
			printf("\n  >>>>>   Concentration!!   <<<<< \n"); // 경고문 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // 값이 q 또는 Q 가 나올 때 까지 진행

	return 1;
}

int initialize(listNode** h) {

	// headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if(*h != NULL) // NULL이 아님
		freeList(*h); // 해제

	// headNode에 대한 메모리를 할당하여 리턴 
	*h = (listNode*)malloc(sizeof(listNode));  // *h에 'headNode' 타입으로 주소 받기
	(*h)->rlink = *h; // h 가리키는 rlink에 h 가리키는 주소 삽입
	(*h)->llink = *h; // h 가리키는 link에 h 가리키는 주소 삽입
	(*h)->key = -9999; // key -9999 초기화
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) // h 가리키는 rlink 와 h 같다면
	{
		free(h); // 해제
		return 1;
	}

	// h와 연결된 listNode 메모리 해제
	// headNode도 해제되어야 함
	listNode* p = h->rlink; // p 만들고, h 가리키는 rlink 안 주소 삽입
	listNode* prev = NULL; // Stack 영역에 prev 만들고, NULL 삽입

	while(p != NULL && p != h) { // p 가 NULL 이 아니면
		prev = p; // p 안 주소 prev 삽입
		p = p->rlink; // p 가리키는 rlink 안 주소 p 에 삽입
		free(prev); // 해제
	}
	free(h); // 해제
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // NULL 이면
		printf("Nothing to print....\n"); // 경고문 출력
		return;
	}

	p = h->rlink; // h 가리키는 rlink 안 주소 p 에 삽입

	while(p != NULL && p != h) { // NULL 이 아니면 
		printf("[ [%d]=%d ] ", i, p->key); // i 번째 노드 안 key 값 출력
		p = p->rlink; // p 가리키는 rlink 안 주소 p 에 삽입
		i++; // i+1 증가
	}
	printf("  items = %d\n", i);


	// print addresses
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	// h 가리키는 link, rlink 안 주소 출력

	i = 0; // i 를 0 으로
	p = h->rlink; // h 가리키는 rlink 안 주소 p 에 삽입
	while(p != NULL && p != h) { // NULL 이 아니면
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		// i 번째 주소 , 그 노드 안 llink 와 rlink 안 주소 출력
		p = p->rlink; // p 가리키는 rlink 안 주소 p 에 삽입
		i++; // i+1 증가
	}

}

// list에 key에 대한 노드하나를 추가
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // NULL 이면

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 주소 받기
	node->key = key; // node 가리키는 key 입력 key 삽입
	node->rlink = NULL; // node 가리키는 rlink 에 NULL 삽입
	node->llink = NULL; // node 가리키는 link 에 NULL 삽입

	if (h->rlink == h) // h 가리키는 rlink 가 h 가리키면
	{
		h->rlink = node; // h 가리키는 rlink 에 node 안 주소 삽입
		h->llink = node; // 주소 삽입
		node->rlink = h; // node 가리키는 rlink 에 NULL 삽입
		node->llink = h; // 주소 삽입
	} else {
		h->llink->rlink = node; // h 가리키는 link 가리키는  rlink 에 node 안 주소 삽입
		node->llink = h->llink; // 주소 삽입
		h->llink = node; // 주소 삽입
		node->rlink = h; // 주소 삽입
	}

	return 1;
}


// list의 마지막 노드 삭제
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL) // NULL 이면
	{
		printf("nothing to delete.\n"); // 알림문 출력
		return 1;
	}

	listNode* nodetoremove = h->llink; // Stack 에 nodetoremove 만들고, h 가리키는 lonk 안 주소 삽입

	// link 정리 
	nodetoremove->llink->rlink = h; // 주소 삽입
	h->llink = nodetoremove->llink; // 주소 삽입

	free(nodetoremove); // 삭제

	return 1;
}

// list 처음에 key에 대한 노드하나를 추가
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 주소받기
	node->key = key; // node 가리키는 key 에 key 삽입
	node->rlink = NULL; // NULL 삽입
	node->llink = NULL; // NULL 삽입

	node->rlink = h->rlink; // node 가리키는 rlink 에 h 가리키는 rlink 안 주소 삽입
	h->rlink->llink = node; // 주소 삽입
	node->llink = h; // 주소 삽입
	h->rlink = node; // 주소 삽입

	return 1;
}

// list의 첫번째 노드 삭제
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // NULL 이면
	{
		printf("nothing to delete.\n"); // 알림문 출력
		return 0;
	}

	listNode* nodetoremove = h->rlink; 

	// link 정리 
	nodetoremove->rlink->llink = h; // 주소 삽입
	h->rlink = nodetoremove->rlink; // 주소 삽입

	free(nodetoremove); // 삭제
	return 1;

}

// 리스트의 링크를 역순으로 재 배치
int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) { // NULL 이면
		printf("nothing to invert...\n"); // 알림문 출력
	}
	listNode *n = h->rlink; // Stack 에 n 만들고, h 가리키는 rlink 안 주소 삽입
	listNode *trail = h; // trail 만들고, h 안 주소 삽입
	listNode *middle = h; // middle 만들고, h 안 주소 삽입

	// 최종 바뀔 링크 유지
	h->llink = h->rlink;

	while(n != NULL && n != h){ // NULL 아니면
		trail = middle; // trail 에 middle 주소 삽입
		middle = n; // middle 에 n 안 주소 삽입
		n = n->rlink; // n 에 n 가리키는 rlink 안 주소 삽입
		middle->rlink = trail; // middle 가리키는 rlink 에 trail 주소 삽입
		middle->llink = n; // middle 가리키는 llink 에 n 안 주소 삽입
	}

	h->rlink = middle; // 재배치
	return 0;
}

// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 주소받기
	node->key = key; // node 가리키는 key 에 key 삽입
	node->llink = node->rlink = NULL; // node 가리키는 llik, rlink 에 NULL 삽입

	if (h->rlink == h) // h 가리키는 rlink 와 h 같다면
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	// key를 기준으로 삽입할 위치를 찾는다 
	while(n != NULL && n != h) {
		if(n->key >= key) {
			// n 가리키는 key 입력받은 key 삽입
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { 
				node->rlink = n; // node 가리키는 rlink 에 n 안 주소 삽입
				node->llink = n->llink; // 주소 삽입
				n->llink->rlink = node; // 주소 삽입
				n->llink = node; // 추가
			}
			return 0;
		}
		n = n->rlink; //n 에 n 가리키는 rlink 주소 삽입
	}

	// 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 
	insertLast(h, key); 
	return 0;
}


int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) // NULL 이면
	{
		printf("nothing to delete.\n"); // 알림문 출력
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) { // NULL 이 아니면
		if(n->key == key) { // n 가리키는 key 입력한 key 와 같으면
			if(n == h->rlink) { // n 이 h 가리키는 rlink 와 같으면
				deleteFirst(h); // 삭제
			} else if (n->rlink == h){ // n 가리키는 rlink 가 h 와 같으면
				deleteLast(h); // 삭제
			} else { 
				n->llink->rlink = n->rlink; // n 가리키는 llink 가리키는 rlink 에 n 가리키는 rlink 주소 삽입
				n->rlink->llink = n->llink; // n 가리키는 rlink 가리키는 llink 에 n 가리키는 llink 주소 삽입
				free(n); // 삭제
			}
			return 0;
		}
		n = n->rlink; // n에 n 가리키는 rlink 안 주소 삽입
	}

	// 찾지 못 한경우
	printf("cannot find the node for key = %d\n", key); // 경고문 출력
	return 0;
}