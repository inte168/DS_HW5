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

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

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

	printf("-----허정윤 2021041047-----");

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

void postfixPush(char x)//postfix stack에 push
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfix stack에 pop
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)//계산 stack push
{
    evalStack[++evalStackTop] = x;
}

int evalPop()//계산 stack pop
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()//infix식 입력
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)//각 토큰을 인식하여 지정된 약어로 return
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

precedence getPriority(char x)//typeof로 위의 구조체 자료형을 가짐=>getToken의 return을 다시 바꾸어 우선도로 읽음
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')//
		strncpy(postfixExp, c, 1);//c를 postfixExp에 1개 복사(비어있기 때문)
	else
		strncat(postfixExp, c, 1);//c를 postfixExp에 1개 붙여넣기.
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')//널문자가 아니면 계속 실행
	{
		if(getPriority(*exp) == operand){//피연산자(operand)면 x에 넣고 charCat에 인자로(=>postfixExp로 복사)
			x = *exp;
			charCat(&x);
		}
		else if (getPriority(*exp) == lparen){//왼쪽 괄호이면 postfix stack에 push
			postfixPush(*exp);
		}
		else if (getPriority(*exp) == rparen){//오른쪽 괄호이면 
			while((x=postfixPop()) != '('){//postfix stack에서 꺼낸(pop)게 왼쪽 괄호가 아닌 동안
				charCat(&x);				//charCat에 인자로(=>postfixExp로 복사)
			}
		}
		else{//이 외의 경우 == 연산자(operator)
			while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){//stack의 Top 부분의 우선도가 exp우선도 이상일 때
				//하나씩 postfix stack에서 꺼내서(pop) charCat으로 넘김(=>postfixExp로 복사)
				x = postfixPop();
				charCat(&x);
			}
			postfixPush(*exp);
		}
		exp++;//exp는 포인터라 주소에 +1이 됨 == infixExp의 다음 문자로 넘김

	}

	while(postfixStackTop != -1){//postfixStack이 남아있으면(Top이 -1이 아님) Pop하여 charCat으로(=>postfixExp로 복사)
		x = postfixPop();
		charCat(&x);
	}

}
void debug()//디버그. 아래의 값들을 출력한다.
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

void reset()//전부 리셋
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

	for(int i =0;i<leng;i++){//postfixExp 길이만큼 반복
		sym = postfixExp[i];//하나씩 값을 뺌
		if(getToken(sym) == operand){//sym의 값(==postfixExp[i]의 값)이 피연산자(숫자)면 push
			evalPush(sym - '0');//문자로 처리되어있어서 문자 0을 빼서 숫자로 전환.
		}
		else{//연산자를 만나면 최근 2개를 pop(넣은건 숫자라 다 숫자가 나옴)하여 연산
			op2 = evalPop();
			op1 = evalPop();
			switch(getToken(sym)){//sym에 따라 연산 결정. token함수로 구분.
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
	evalResult = evalPop();//최종적으로 eval stack에는 모든 연산이 끝난 값이 남으므로 그 값을 evalResult로.
}