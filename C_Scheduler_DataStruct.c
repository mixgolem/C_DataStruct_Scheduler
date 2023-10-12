#define _CRT_SECURE_NO_WARNNINGS //Visual C���� strcpy() �Լ� ���� ���� ��� ����� �������ش�.
//��� ������ ������ ���� ���Խ��״�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//strcpy()�Լ� ���


//���� ��� �Լ�
void error(char* str){
	fprintf(stderr, "%s\n", str);
	exit(1);
}

//�Է� ����(Ű����)���� ����Ű�� �Է����� ���� ���๮�ڸ� ����
void my_fflush() {
	while (getchar() != '\n');
}






//���Ḯ��Ʋ �̿��� ����
typedef char Element;
typedef struct LinkedNode {
	Element schedule[256];
	struct LinkedNode* link;
} Node;
Node* top = NULL;

//������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty() { return top == NULL; }

//���� �ʱ�ȭ �Լ�
void init_stack() { top = NULL; }

//���� ���� ����� ������ ��ȯ�ϴ� �Լ�
int size() {
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link) count++;
	return count;
}

//���� ���� ���� : ���ڿ��� ��忡 �����ؾ� �ϱ� ������ ���ڿ� ���޹���
void push(Element e[]) {
	Node* p = (Node*)malloc(sizeof(Node));

	//����� data�� ���ڿ��� �����ؾ� �ϱ� ������ strcpy()�Լ� ���
	strcpy(p->schedule, e);
	p->link = top;
	top = p;
}

//���� ��������
Element* pop() {
	Node* p;

	//���ڿ��� ��ȯ�ϱ� ���� ���ڿ� ����
	Element e[256];

	if (is_empty())
		error("���� ���� ����");
	p = top;
	top = p->link;

	//pop()�ϴ� ����� ���ڿ��� e�� ����
	strcpy(e, p->schedule);
	free(p);
	return e;
}

//���� peek����
Element* peek() {
	if (is_empty())
		error("���� ���� ����");
	return top->schedule;
}

//���� ȭ�� ��� �Լ� : ������ ������� �� ���� pop() ���
void display() {
	while (!is_empty()) {
		printf("%s\n", pop());
	}
}






//���Ḯ��Ʈ�� �̿��� ť�� ����
typedef char Element_queue;
typedef struct LinkedNode_queue {
	Element_queue schedule_queue[256];
	struct LinkedNode_queue* link_queue;
} Node_queue;

//front�� rear�� ����
Node_queue* front = NULL, * rear = NULL;

//ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty_queue() { return front == NULL; }

//ť�� �ʱ�ȭ�ϴ� �Լ�
void init_queue() { front = rear = NULL; }

//ť ���� ����� ������ ��ȯ�ϴ� �Լ�
int size_queue() {
	Node_queue* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link_queue) count++;
	return count;
}

//ť ���� ���� : ���ڿ��� ��忡 �����ؾ� �ϱ� ������ ���ڿ��� ���޹���
void enqueue(Element_queue e[]) {
	Node_queue* p = (Node_queue*)malloc(sizeof(Node_queue));

	//����� data�� ���ڿ��� �����ؾ� �ϱ� ������ strcpy()�Լ� ���
	strcpy(p->schedule_queue, e);
	p->link_queue = NULL;
	if (is_empty_queue()) front = rear = p;
	else {
		rear->link_queue = p;
		rear = p;
	}
}

//ť ���� ����
Element_queue* dequeue() {
	Node_queue* p;

	//���ڿ��� ��ȯ�ϱ� ���� ���ڿ��� ����
	Element_queue e[256];

	if (is_empty_queue())
		error("ť ���� ����");
	p = front;
	front = front->link_queue;
	if (front == NULL) rear = NULL;
	
	//dequeue�Ϸ��� ����� ���ڿ��� e�� ����
	strcpy(e, p->schedule_queue);
	free(p);
	return e;
}

//ť peek ����
Element_queue* peek_queue() {
	if (is_empty_queue())
		error("ť ���� ����");
	return front->schedule_queue;
}

//ť ȭ�� ��� �Լ� : ť�� ������� �� ���� dequeue() ���
void display_queue() {
	while (!is_empty_queue()) {
		printf("%s\n", dequeue());
	}
}







//�����Լ�
int main(int argc, char* argv[]) {
	
	int check;
	char command;
	Node Schedule;
	Node_queue Schedule_queue;

	//�ùٸ��� ���� ��ɾ� �Է� �� ���� ���
	if (argc != 2) {
		error("exe check(0 or 1)\n");
	}

	//0�� ť ���� ������ ������, 1�� ���� ���� ������ ������ �����ϱ� ���� ���
	check = atoi(argv[1]);
	
	//���� �� ť�� �ʱ�ȭ
	init_stack();
	init_queue();



	//ť�� �̿��Ͽ� ����
	if (check == 0) {
		printf("\nť�� �̿��Ͽ� �����ٷ��� �����մϴ�. �Է��� ������� ��µ˴ϴ�.\n");
		do {

			printf(" I:(input the schedule) s:(Show the schedule) q:(quit the program) : ");
			command = getchar();
			my_fflush();
			switch (command) {
			case 'i'://������ �Է� ���
				printf(" Input your schedule : ");
				fgets(Schedule_queue.schedule_queue, 256, stdin);//node_queue�� ����� schedule_queue�� ������ ������ �Է¹���
				enqueue(Schedule_queue.schedule_queue);//�Է¹��� �������� ť�� ����
				break;

			case 's'://������ ��� ��� : ť�� ���Լ��� ����̱⿡ �Է��� ������� �����
				display_queue();
				break;

			case 'q'://�����ٷ� ����
				printf("\n���α׷��� �����մϴ�.\n");
				break;
			}
			
		} while (command != 'q');

	}



	//������ �̿��Ͽ� ����
	else if (check == 1) {
		printf("\n������ �̿��Ͽ� �����ٷ��� �����մϴ�. �Է��� �������� ��µ˴ϴ�.\n");
			do {
				
				printf("I:(input the schedule) s:(Show the schedule) q:(quit the program) : ");
				command = getchar();
				my_fflush();
				switch (command) {
				case 'i'://������ �Է� ���
					printf(" Input your schedule : ");
					fgets(Schedule.schedule, 256, stdin);//node�� ����� schedule�� ������ ������ �Է¹���
					push(Schedule.schedule);//�Է¹��� �������� ���ÿ� ����
					break;

				case 's'://������ ��� ��� : ������ ���Լ��� ����̱⿡ �Է��� ������ �ݴ�� �����
					display();
					break;

				case 'q'://�����ٷ� ����
					printf("\n���α׷��� �����մϴ�.\n");
					break;
				}
				
			} while (command != 'q');

	}
	

	//check���� 0 �Ǵ� 1�� �ƴ� ��� ���� ���
	else {
		error("exe check(0 or 1)\n");
	}
	


	return 0;
}