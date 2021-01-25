#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10
#define MAXBUFFER       10

typedef char ElemType;

typedef struct {
	ElemType* bottom;
	ElemType* top;
	int stackSize;
}Stack;

void InitStack(Stack* s) {
	s->bottom = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(STACKINCREMENT));
	if (!s->bottom)
		exit(1);

	s->top = s->bottom;
	s->stackSize = STACK_INIT_SIZE;
}

void Push(Stack* s, ElemType data) {
	if (s->top - s->bottom >= s->stackSize) {
		s->bottom = (ElemType*)realloc(s->bottom, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
		if (!s->bottom)
			exit(1);

		s->top = s->bottom + s->stackSize;
		s->stackSize += STACKINCREMENT;
	}

	*(s->top) = data;
	s->top++;
}

void Pop(Stack* s, ElemType* data) {
	if (s->top == s->bottom)
		return;
	s->top--;
	*data = *(s->top);
}

int StackLen(Stack* s) {
	return(s->top - s->bottom);
}

void DestoryStack(Stack* s) {
	int i, len;
	len = StackLen(s);
	for (i = 0; i < len; i++) {
		free(s->bottom);
		s->bottom++;
	}
	s->bottom = s->top = nullptr;
	s->stackSize = 0;
}

void Input(char expression[]) {
	scanf_s("%c", &expression[0], 1);

	for (int index = 0; expression[index] != '#'; index++) {
		scanf_s("%c", &expression[index + 1], 1);
	}
}

bool UNwanted(char input) {
	switch (input) {
	case('+'):
	case('-'):
	case('*'):
	case('/'):
	case('.'):
	case('('):
	case(')'):
	case('\n'):
	case(' '):
	case('\t'):
	case('1'):
	case('2'):
	case('3'):
	case('4'):
	case('5'):
	case('6'):
	case('7'):
	case('8'):
	case('9'):
	case('0'):
		return false;
	default:
		return true;
	}

}


bool Transform(Stack* Origin, char expression[]) {
	
	ElemType signal;
	Stack Sign;
	InitStack(&Sign);


	for (int index = 0; expression[index] != '#'; index++) {
		if (UNwanted(expression[index])) {
			printf("«Î ‰»Î ˝◊÷£°£°£°\n");
			DestoryStack(&Sign);
			return false;
		}
		else if (isdigit(expression[index]) || expression[index] == '.') {
			Push(Origin, expression[index]);
		}
		else if (expression[index] == '(') {
			Push(&Sign, expression[index]);
		}
		else if (expression[index] == ')') {
			Pop(&Sign, &signal);
			while (signal != '('&& StackLen(&Sign)) {
				Push(Origin, ' ');
				Push(Origin, signal);
				Pop(&Sign, &signal);
			}
		}
		else if (expression[index] == '+' || expression[index] == '-') {
			if (StackLen(&Sign)) {
				do {
					Pop(&Sign, &signal);
					if (signal == '(') {
						Push(&Sign, signal);
					}
					else {
						Push(Origin, ' ');
						Push(Origin, signal);
					}
				} while (StackLen(&Sign) && signal == '(');
				Push(Origin, ' ');
				Push(&Sign, expression[index]);
			}
			else {
				Push(Origin, ' ');
				Push(&Sign, expression[index]);
			}
		}
		else if (expression[index] == '*' || expression[index] == '/') {
			Push(Origin, ' ');
			Push(&Sign, expression[index]);
		}
		else {
			continue;
		}
	}

	while (StackLen(&Sign)) {
		Pop(&Sign, &signal);
		Push(Origin, ' ');
		Push(Origin, signal);
	}
	Push(Origin, ' ');

	DestoryStack(&Sign);
	return true;
}


void Print(Stack* Origin) {
	Stack Copy;
	InitStack(&Copy);
	ElemType data;

	Pop(Origin, &data);
	while (StackLen(Origin)) {
		Push(&Copy, data);
		Pop(Origin, &data);
	}
	Push(&Copy, data);

	Pop(&Copy, &data);
	while (StackLen(&Copy)) {
		putchar(data);
		Pop(&Copy, &data);
	}
	putchar(data);
	putchar('#');
}


int main() {

	Stack Origin;
	InitStack(&Origin);

	char expression[100] = "\0";
	Input(expression);

	if (!Transform(&Origin, expression)) {
		DestoryStack(&Origin);
		return 0;
	}

	Print(&Origin);

	DestoryStack(&Origin);
	return 0;
}