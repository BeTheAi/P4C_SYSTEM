#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int value; //노드값
	struct node* next; // 다음노드를 가르키는 링크
	struct node* prev;
}node;

void add(node* now) {
	int adval;
	node* add = (node*)malloc(sizeof(node));
	scanf("%d", &adval);
	add->value = adval;
	now->next = add;
	add->prev = now;
}

int main() { // 추가, 탐색, 삭제 3가지 기능 구현 목표
	int length = 0;
	int input;
	node* head = (node*)malloc(sizeof(node)); //연결리스트 head 부분 선언 + node 구조체 크기만큼 메모리 동적할당
	node* tail = (node*)malloc(sizeof(node)); //연결리스트 tail 부분 선언 + node 구조체 크기만큼 메모리 동적할당
	head->next = NULL;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = NULL;
	node* now = head;

	printf("연결리스트에 넣을 원소 수를 입력해주세요 : \n ");
	scanf("%d", &input);
	printf("%d개 값을 입력해주세요 : \n", input);
	for (int i = 0;i < input;i++) {
		add(now);
		now = now->next;
		length++;
	}
	now->next = tail;
	tail->prev = now;
	node* print = head->next;
	
	printf("연결리스트 길이 : %d\n", length);
	printf("정방향 출력\n");
	for (int i = 0;i < length;i++) {
		printf("head <-> %d", print->value);
		if (i < length-1) {
			printf(" <-> ");
			print = print->next;
		}
		else {
			printf("<-> tail\n");
			break;
		}	
	}

	printf("역방향 출력\n");
	for (int i = 0;i < length;i++) {
		printf("head <-> %d", now->value);
		if (i < length-1)
			printf(" <-> ");
		else {
			printf(" <-> tail\n");
			break;
		}
		now = now->prev;
	}
	
	free(head);
	free(tail);
	free(now);
	free(print);
	return 0;
}
