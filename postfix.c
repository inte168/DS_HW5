/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("-----������ 2021041047-----");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)//postfix stack�� push
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfix stack�� pop
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)//��� stack push
{
    evalStack[++evalStackTop] = x;
}

int evalPop()//��� stack pop
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()//infix�� �Է�
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)//�� ��ū�� �ν��Ͽ� ������ ���� return
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)//typeof�� ���� ����ü �ڷ����� ����=>getToken�� return�� �ٽ� �ٲپ� �켱���� ����
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')//
		strncpy(postfixExp, c, 1);//c�� postfixExp�� 1�� ����(����ֱ� ����)
	else
		strncat(postfixExp, c, 1);//c�� postfixExp�� 1�� �ٿ��ֱ�.
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')//�ι��ڰ� �ƴϸ� ��� ����
	{
		if(getPriority(*exp) == operand){//�ǿ�����(operand)�� x�� �ְ� charCat�� ���ڷ�(=>postfixExp�� ����)
			x = *exp;
			charCat(&x);
		}
		else if (getPriority(*exp) == lparen){//���� ��ȣ�̸� postfix stack�� push
			postfixPush(*exp);
		}
		else if (getPriority(*exp) == rparen){//������ ��ȣ�̸� 
			while((x=postfixPop()) != '('){//postfix stack���� ����(pop)�� ���� ��ȣ�� �ƴ� ����
				charCat(&x);				//charCat�� ���ڷ�(=>postfixExp�� ����)
			}
		}
		else{//�� ���� ��� == ������(operator)
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){//stack�� Top �κ��� �켱���� exp�켱�� �̻��� ��
				//�ϳ��� postfix stack���� ������(pop) charCat���� �ѱ�(=>postfixExp�� ����)
				x = postfixPop();
				charCat(&x);
			}
			postfixPush(*exp);
		}
		exp++;//exp�� �����Ͷ� �ּҿ� +1�� �� == infixExp�� ���� ���ڷ� �ѱ�

	}

	while(postfixStackTop != -1){//postfixStack�� ����������(Top�� -1�� �ƴ�) Pop�Ͽ� charCat����(=>postfixExp�� ����)
		x = postfixPop();
		charCat(&x);
	}

}
void debug()//�����. �Ʒ��� ������ ����Ѵ�.
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()//���� ����
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	int op1, op2;
	int leng = strlen(postfixExp);
	char sym;
	evalStackTop = -1;

	for(int i =0;i<leng;i++){//postfixExp ���̸�ŭ �ݺ�
		sym = postfixExp[i];//�ϳ��� ���� ��
		if(getToken(sym) == operand){//sym�� ��(==postfixExp[i]�� ��)�� �ǿ�����(����)�� push
			evalPush(sym - '0');//���ڷ� ó���Ǿ��־ ���� 0�� ���� ���ڷ� ��ȯ.
		}
		else{//�����ڸ� ������ �ֱ� 2���� pop(������ ���ڶ� �� ���ڰ� ����)�Ͽ� ����
			op2 = evalPop();
			op1 = evalPop();
			switch(getToken(sym)){//sym�� ���� ���� ����. token�Լ��� ����.
				case plus:
					evalPush(op1+op2);
					break;
				case minus:
					evalPush(op1 - op2);
					break;
				case times:
					evalPush(op1 * op2);
					break;
				case divide:
					evalPush(op1 / op2);
					break;
				default: 
					break;
			}
		}
	}
	evalResult = evalPop();//���������� eval stack���� ��� ������ ���� ���� �����Ƿ� �� ���� evalResult��.
}