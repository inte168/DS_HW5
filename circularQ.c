/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	printf("-----������ 2021041047-----");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()//queue ����.
{
	//QueueType���� ����, �����Ҵ�, front�� rear�� ����.
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)//free
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()//Ư���� �� ���� �Է�.
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear){//front�� rear�� ���� ��찡 �� ���.
		printf("Queue is Empty.");
		return 1;
	}
    else return 0;
}

int isFull(QueueType *cQ)
{
	if(cQ->front == (cQ->rear+1)%MAX_QUEUE_SIZE){//������ rear+1�� front�� ���� ��. �������� rear�� �������� ������ �������� �����־���.
		printf("Queue is Full");
		return 1;
	}
   	else return 0;
}

void enQueue(QueueType *cQ, element item)//�Էµ� element�� queue�� �ִ� �Լ�
{
	if(isFull(cQ)) return;//Full�̸� ��¿ �� ����.
	else{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear�� ��ĭ �ű��
		cQ->queue[cQ->rear] = item;//�� ĭ�� element ����
	}
}

void deQueue(QueueType *cQ, element *item)//queue�� element ����
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;//FIFO����̴� front�� �ű��(front�� ä�����ִ� index �� ��)
		*item = cQ->queue[cQ->front];//front�� ���� item�� �־��ش�.
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

