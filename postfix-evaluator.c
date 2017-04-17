//Orion Guan
//March 7th, 2017

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct stackNode 
{
	int data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int evaluatePostfixExpression(char *expr);
int calculate(int op1, int op2, char operator);
void push(StackNodePtr *topPtr, int value);
int pop(StackNodePtr *topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr topPtr);

int main()
{
	int i = 0;
	printf("Please enter a postfix expression:\n");
	char postfixExpression[80];
	scanf("%s",&postfixExpression[i]);
	postfixExpression[sizeof(postfixExpression)] = '\0';

	printf("%d\n", evaluatePostfixExpression(postfixExpression));
}

//returns the result of the postfix expression
int evaluatePostfixExpression(char *expr)
{
	StackNodePtr stackPtr = NULL;

	int i = 0;
	while (*(expr + i) != '\0')
	{
		char nextChar = *(expr + i);
		int charValue = nextChar - '0';
		if (charValue >= 0 && charValue < 10)
		{
			push(&stackPtr, charValue);
		}
		else if (nextChar == '+' ||
				 nextChar == '-' ||
				 nextChar == '*' ||
				 nextChar == '/' ||
				 nextChar == '^' ||
				 nextChar == '%')
		{
			int x = 0;
			int y = 0;
			if(!isEmpty(stackPtr))
			{
				x = pop(&stackPtr);
			}
			else {printf("No more values to set.");}
			if(!isEmpty(stackPtr))
			{
				y = pop(&stackPtr);
			}
			else {printf("No more values to set.");}
			push(&stackPtr, calculate(y, x, nextChar));
		}
		i++;
	}
	if(!isEmpty(stackPtr))
	{
		return pop(&stackPtr);
	}
	else
	{
		printf("No more values to return.");
		return 0;
	}
}

//calculates the result of a binary operation
int calculate(int op1, int op2, char operator)
{
	if (operator == '+')
	{
		return op1 + op2;
	}
	else if (operator == '-')
	{
		return op1 - op2;
	}
	else if (operator == '*')
	{
		return op1 * op2;
	}
	else if (operator == '/')
	{
		return op1 / op2;
	}
	else if (operator == '^')
	{
		return pow(op1, op2);
	}
	else if (operator == '%')
	{
		return op1 % op2;
	}
	else
	{
		printf("Invalid calculator operator.");
		return 0;
	}
}

//puts an integer on the stack used for this postfix evaluator
void push(StackNodePtr *topPtr, int info)
{
	StackNodePtr newPtr = malloc(sizeof(StackNode));

	if (newPtr != NULL)
	{
		newPtr->data = info;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else
	{
		printf("%d not inserted. No memory available.\n", info);
	}
}

//pops an integer from the stack used for this postfix evaluator
int pop(StackNodePtr *topPtr)
{
	StackNodePtr tempPtr = *topPtr;
	int popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextPtr;
	free(tempPtr);
	return popValue;
}

//returns true if the stack used for this postfix evaluator is empty
int isEmpty(StackNodePtr topPtr)
{
	return (topPtr == NULL);
}

//prints the contents of the stack in order from the value at the given pointer to the bottom of its stack
void printStack(StackNodePtr currentPtr)
{
	if (currentPtr == NULL)
	{
		printf("The stack is empty.\n");
	}
	else
	{
		printf("The stack is:");

		while (currentPtr != NULL)
		{
			printf("%d --> ", currentPtr->data);
			currentPtr = currentPtr->nextPtr;
		}

		printf("NULL\n");
	}
}
