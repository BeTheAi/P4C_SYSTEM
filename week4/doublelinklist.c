#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int value; //노드값
	struct node* next; // 다음노드를 가르키는 링크
	struct node* prev;
}node;
int length = 0;

void add(node* now) {  //노드 추가 함수
	int adval;		//입력받을 값 저장 변수
	node* add = (node*)malloc(sizeof(node)); //추가할 노드 생성
	scanf("%d", &adval); //값 입력
	add->value = adval; // 생성한 노드의 값 저장
	now->next = add; //현재 위치 now의 다음으로 생성한 노드 add 추가
	add->prev = now; //add의 이전 블록으로 prev지정
}

void printfr(node* print, int len) { // 정방향 출력
	print = print->next;	//head 다음 노드 부터
	printf("정방향 출력\nhead"); 
	for (int i = 0;i < len;i++) { //길이 만큼 노드 출력
		printf(" <-> %d", print->value);
		if (i >= len - 1) {	// 끝노드일 경우, 마지막에 tail 문자열 출력후, 반복문 종료
			printf(" <-> tail\n");
			break;
		}
		print = print->next; //다음노드로 이동
	}
}

void printprev(node* print, int len) { //역방향 출력
	print = print->prev;	// tail 다음 노드 부터
	printf("역방향 출력\ntail");
	for (int i = 0;i < len;i++) {
		printf(" <-> %d", print->value);
		if (i >= len - 1) {	//첫노드 일경우, head문자열 출력후 반복문 종료
			printf(" <-> head\n");
			break;
		}
		print = print->prev; //이전 노드로 이동
	}
}

void deleteendnode(node* now, node* tail) { //끝 노드 삭제 함수
	tail->prev = now->prev;	//tail의 이전 노드를 삭제할 노드 now의 이전 노드로 지정
	now = now->prev; //now를 이전 노드로 이동
	now->next = tail; //now의 next를 tail로 지정
	length--; //길이 1 감소
}

int main() { // 추가, 탐색, 삭제 3가지 기능 구현 목표

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
	print->prev = head;

	printf("연결리스트 길이 : %d\n", length);
	printfr(head, length);
	printprev(tail, length);
	deleteendnode(now, tail);
	printfr(head, length);
	printprev(tail, length);


	free(head);
	free(tail);
	free(now);
	free(print);
	return 0;
}
