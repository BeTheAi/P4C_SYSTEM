#include <iostream>
using namespace std;
#define max_size 10

struct node {
public:
	int value; //노드값
	struct node* next; // 다음노드를 가르키는 링크
	//struct node* pre; //앞을 가르키는 노드
};

class List {
public:
	List() { //생성자로 head, tail 초기화
		head = nullptr; //표지판
		tail = nullptr; //여기가 줄끝이에요
	}

	node* head;
	node* tail;
	int length = 0; //길이 과정에서 오류 발생으로, list에 길이변수 추가..

	void insert(int pos, int item); //중간삽입
	void insert_last(int item); // 끝삽입
	void insert_first(int item); // 1번삽입
	bool is_empty(); //NULL 확인
	bool is_full();  //최대길이 확인
	int get_length(); //리스트 길이 반환
	void print_list(); //현재 리스트 출력
	int get_entry(int pos); //현재위치 출력
	void delete_node(int pos); //현재 위치한 노드 삭제
	void clear(); // 전체 삭제
	void setloop(); // 루프 임의설정
};

void List::insert(int pos, int item) {

	node* newnode = new node; //추가할 노드
	node* tmp = head; //위치를 찾을 임시 node

	newnode->next = nullptr;
	newnode->value = item;

	if (pos > get_length()) { //추가하려는 위치가 현재 리스트 길이보다 긴지 판별
		cout << "추가하려는 위치가 리스트의 길이보다 큽니다." << endl;
	}
	else {
		if (is_full()) {
			cout << "리스트가 가득찼습니다" << endl;
		}
		else {
			for (int i = 0; i < pos - 2; i++) { //0부터 카운트, 그러므로 pos-2번까지 반복
				//ex) 3번째 넣고 싶다 = 3번째 노드의 직전인 2번쨰 노드까지 반복ㄱ
				tmp = tmp->next;
			}
			newnode->next = tmp->next;
			tmp->next = newnode;
			length++;
		}
	}
}

void List::insert_first(int item) {
	node* newnode = new node; //추가할 노드
	newnode->value = item;
	newnode->next = nullptr;

	if (is_full()) {
		return;
	}
	else {
		newnode->next = head;
		head = newnode;
		length++;
	}
}

void List::insert_last(int item) {
	node* newnode = new node; //끝에 추가할 node 
	node* tmp = head;

	newnode->value = item;	
	newnode->next = nullptr;	

	if (is_full()) {
		cout << "리스트가 가득찼습니다" << endl;
	}
	else {
		if (is_empty()) {
			head = newnode;
			tail = newnode;
		}
		else {
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			tmp->next = newnode;
		}
		length++;
	}
}

bool List::is_empty() {
	if (get_length()==0) {
		return true;
	}
	else {
		return false;
	}
}

bool  List::is_full() {
	if (get_length() < max_size) {
		return false;
	}
	else {
		return true;
	}
}

int  List::get_length() {
	return length;
}

void List::print_list() {
	node* p = head;
	for (int i = 0; i <= get_length(); i++) {
		cout << p->value << "->";
		if (p->next == NULL){
			break;
		}
		else {
			p = p->next;
		}
	}
	cout << endl;
}

int List::get_entry(int pos) {

	if (get_length() < pos) {
		cout << "값을 찾으려는 위치가 리스트의 길이보다 큽니다." << endl;
		return 0;
	}
	else {
		node* tmp = head;
		if (is_empty()) {
			cout << " 리스트가 비어있습니다.!" << endl;
		}
		else {
			for (int i = 0; i < pos-1; i++) { //head=0부터 카운트, 그러므로 pos-1번까지 반복
				tmp = tmp->next;
			}
			cout << pos << "번째 node의 값은 " << tmp->value << "입니다." << endl;
		}
		return tmp->value;
	}
}

void List::delete_node(int pos) {
	if (is_empty()) {
		cout << "값을 찾으려는 위치가 리스트의 길이보다 큽니다." << endl;
	}
	else {
		node* del = new node; //삭제할 노드
		node* pre_del = head;//삭제할 노드의 직전노드
		if (is_empty()) {

		}
		else {
			for (int i = 0; i < pos - 2; i++) { //head=0부터 카운트, 그러므로 pos-1번까지 반복
				pre_del = pre_del->next;
			}
			del = pre_del->next;
			pre_del->next = del->next;
			cout << pos << "번째 node의 값" << del->value << "을 삭제했습니다." << endl;\
			delete(del);//free 소멸자
			length--;
		}
	}
}

void List::clear() {
	node* del = head;
	int a = 0;
	if (is_empty()) {
		cout << "리스트가 비어 있습니다." << endl;
	}
	else{
		head = nullptr;
		cout << "리스트의 노드를 모두 제거했습니다!" << endl;
		cout << "---------------------------------------" << endl;
		length = 0;
	}
}

void List::setloop() {
	node* set = head->next;
	if (get_length() == 1 || is_empty()) {
		cout << "리스트가 비어있거나 노드가 1개뿐입니다." << endl;
	}
	else if (get_length() == 2 || get_length() == 3) {
		set->next = head;
	}
	else {
		tail->next = set;
		//while (set == nullptr) {
		//	set = set->next;
		//}
		//set->next = 
		//for (int i = 0; i < 2; i++) {
		//	set = set->next;
		//}
	}

}

int hasCycle(List* a) {//인터넷에서 토끼와 거북이 알고리즘이라는게 있는걸 발견하고 적용하였습니다.
	node* rab = a->head->next;
	node* tur = a->head;
	if (rab == nullptr || rab->next == nullptr) {
		return 0;
	}
	else {
		while (rab != nullptr || tur != nullptr) {//rab과 tur 모두 nullptr이 되기전까지 반복
			tur = tur->next;
			rab = rab->next->next;
			if (rab == tur) {
				cout << "Cycle!" << endl;
				return true;
				//break;
			}
		}
		cout << "No Cycle!" << endl;
		return false;
	}
}


int main(void){
	List a, b;
	a.insert_last(10);
	a.insert_last(30);
	a.insert(2, 20);;
	a.insert_first(5);
	a.insert_last(60);
	a.insert_last(80);
	a.get_entry(2);
	a.print_list();
	hasCycle(&a);
	a.delete_node(3);
	a.print_list();
	a.clear();

	b.insert_last(10);
	b.insert_last(30);
	b.insert(2, 20);;
	b.insert_first(5);
	b.get_entry(2);
	b.print_list();
	b.delete_node(3);
	b.print_list();
	b.setloop();
	
	b.clear();


}


