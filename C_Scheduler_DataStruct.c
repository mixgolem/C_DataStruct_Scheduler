#define _CRT_SECURE_NO_WARNNINGS //Visual C에서 strcpy() 함수 사용시 보안 경고 출력을 무시해준다.
//헤더 파일은 다음과 같이 포함시켰다
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strcpy()함수 사용


//에러 출력 함수
void error(char* str){
	fprintf(stderr, "%s\n", str);
	exit(1);
}

//입력 버퍼(키보드)에서 엔터키를 입력했을 시의 개행문자를 제거
void my_fflush() {
	while (getchar() != '\n');
}






//연결리스틀 이용한 스택
typedef char Element;
typedef struct LinkedNode {
	Element schedule[256];
	struct LinkedNode* link;
} Node;
Node* top = NULL;

//스택이 비어있는지 확인하는 함수
int is_empty() { return top == NULL; }

//스택 초기화 함수
void init_stack() { top = NULL; }

//스택 안의 요소의 개수를 반환하는 함수
int size() {
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link) count++;
	return count;
}

//스택 삽입 연산 : 문자열을 노드에 저장해야 하기 때문에 문자열 전달받음
void push(Element e[]) {
	Node* p = (Node*)malloc(sizeof(Node));

	//노드의 data에 문자열을 저장해야 하기 때문에 strcpy()함수 사용
	strcpy(p->schedule, e);
	p->link = top;
	top = p;
}

//스택 삭제연산
Element* pop() {
	Node* p;

	//문자열을 반환하기 위해 문자열 선언
	Element e[256];

	if (is_empty())
		error("스택 공백 에러");
	p = top;
	top = p->link;

	//pop()하는 노드의 문자열을 e로 복사
	strcpy(e, p->schedule);
	free(p);
	return e;
}

//스택 peek연산
Element* peek() {
	if (is_empty())
		error("스택 공백 에러");
	return top->schedule;
}

//스택 화면 출력 함수 : 스택이 비어있을 때 까지 pop() 출력
void display() {
	while (!is_empty()) {
		printf("%s\n", pop());
	}
}






//연결리스트를 이용한 큐의 구현
typedef char Element_queue;
typedef struct LinkedNode_queue {
	Element_queue schedule_queue[256];
	struct LinkedNode_queue* link_queue;
} Node_queue;

//front와 rear의 선언
Node_queue* front = NULL, * rear = NULL;

//큐가 비어있는지 확인하는 함수
int is_empty_queue() { return front == NULL; }

//큐를 초기화하는 함수
void init_queue() { front = rear = NULL; }

//큐 안의 요소의 개수를 반환하는 함수
int size_queue() {
	Node_queue* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link_queue) count++;
	return count;
}

//큐 삽입 연산 : 문자열을 노드에 저장해야 하기 때문에 문자열을 전달받음
void enqueue(Element_queue e[]) {
	Node_queue* p = (Node_queue*)malloc(sizeof(Node_queue));

	//노드의 data에 문자열을 저장해야 하기 때문에 strcpy()함수 사용
	strcpy(p->schedule_queue, e);
	p->link_queue = NULL;
	if (is_empty_queue()) front = rear = p;
	else {
		rear->link_queue = p;
		rear = p;
	}
}

//큐 삭제 연산
Element_queue* dequeue() {
	Node_queue* p;

	//문자열을 반환하기 위해 문자열로 선언
	Element_queue e[256];

	if (is_empty_queue())
		error("큐 공백 오류");
	p = front;
	front = front->link_queue;
	if (front == NULL) rear = NULL;
	
	//dequeue하려는 노드의 문자열을 e로 복사
	strcpy(e, p->schedule_queue);
	free(p);
	return e;
}

//큐 peek 연산
Element_queue* peek_queue() {
	if (is_empty_queue())
		error("큐 공백 오류");
	return front->schedule_queue;
}

//큐 화면 출력 함수 : 큐가 비어있을 때 까지 dequeue() 출력
void display_queue() {
	while (!is_empty_queue()) {
		printf("%s\n", dequeue());
	}
}







//메인함수
int main(int argc, char* argv[]) {
	
	int check;
	char command;
	Node Schedule;
	Node_queue Schedule_queue;

	//올바르지 않은 명령어 입력 시 에러 출력
	if (argc != 2) {
		error("exe check(0 or 1)\n");
	}

	//0번 큐 모드로 실행할 것인지, 1번 스택 모드로 실행할 것인지 결정하기 위해 사용
	check = atoi(argv[1]);
	
	//스택 및 큐의 초기화
	init_stack();
	init_queue();



	//큐를 이용하여 실행
	if (check == 0) {
		printf("\n큐를 이용하여 스케줄러를 실행합니다. 입력한 순서대로 출력됩니다.\n");
		do {

			printf(" I:(input the schedule) s:(Show the schedule) q:(quit the program) : ");
			command = getchar();
			my_fflush();
			switch (command) {
			case 'i'://스케줄 입력 모드
				printf(" Input your schedule : ");
				fgets(Schedule_queue.schedule_queue, 256, stdin);//node_queue의 멤버인 schedule_queue에 스케줄 내용을 입력받음
				enqueue(Schedule_queue.schedule_queue);//입력받은 스케줄을 큐에 삽입
				break;

			case 's'://스케줄 출력 모드 : 큐는 선입선출 방식이기에 입력한 순서대로 출력함
				display_queue();
				break;

			case 'q'://스케줄러 종료
				printf("\n프로그램을 종료합니다.\n");
				break;
			}
			
		} while (command != 'q');

	}



	//스택을 이용하여 실행
	else if (check == 1) {
		printf("\n스택을 이용하여 스케줄러를 실행합니다. 입력한 역순으로 출력됩니다.\n");
			do {
				
				printf("I:(input the schedule) s:(Show the schedule) q:(quit the program) : ");
				command = getchar();
				my_fflush();
				switch (command) {
				case 'i'://스케줄 입력 모드
					printf(" Input your schedule : ");
					fgets(Schedule.schedule, 256, stdin);//node의 멤버인 schedule에 스케줄 내용을 입력받음
					push(Schedule.schedule);//입력받은 스케줄을 스택에 삽입
					break;

				case 's'://스케줄 출력 모드 : 스택은 후입선출 방식이기에 입력한 순서의 반대로 출력함
					display();
					break;

				case 'q'://스케줄러 종료
					printf("\n프로그램을 종료합니다.\n");
					break;
				}
				
			} while (command != 'q');

	}
	

	//check값이 0 또는 1이 아닐 경우 에러 출력
	else {
		error("exe check(0 or 1)\n");
	}
	


	return 0;
}