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

	printf("-----허정윤 2021041047-----");

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

QueueType *createQueue()//queue 생성.
{
	//QueueType으로 생성, 동적할당, front와 rear값 설정.
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

element getElement()//특별할 것 없는 입력.
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear){//front와 rear가 같은 경우가 빈 경우.
		printf("Queue is Empty.");
		return 1;
	}
    else return 0;
}

int isFull(QueueType *cQ)
{
	if(cQ->front == (cQ->rear+1)%MAX_QUEUE_SIZE){//보통은 rear+1이 front와 같을 때. 마지막에 rear가 가있으면 나머지 연산으로 돌려넣어줌.
		printf("Queue is Full");
		return 1;
	}
   	else return 0;
}

void enQueue(QueueType *cQ, element item)//입력된 element를 queue에 넣는 함수
{
	if(isFull(cQ)) return;//Full이면 어쩔 수 없고.
	else{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear를 한칸 옮기고
		cQ->queue[cQ->rear] = item;//그 칸에 element 삽입
	}
}

void deQueue(QueueType *cQ, element *item)//queue의 element 삭제
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;//FIFO방식이니 front를 옮기고(front는 채워져있는 index 앞 값)
		*item = cQ->queue[cQ->front];//front의 값을 item에 넣어준다.
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

