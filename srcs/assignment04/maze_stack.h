#ifndef MAZE_STACK
# define MAZE_STACK
# define HEIGHT		7
# define WIDTH		8
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct t_MapPosition
{
	int x;
	int y;
	int dir;
}	MapPosition;

typedef struct StackNodeType
{
	MapPosition pos;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	int currentElementCount;
	StackNode* pTopElement;
} LinkedStack;

LinkedStack* createLinkedStack();
void deleteLinkedStack(LinkedStack* pStack);
void reverseLinkedStack(LinkedStack* pStack);

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack);
int pushLSMapPosition(LinkedStack *pStack, MapPosition data);
StackNode *popLSMapPosition(LinkedStack *pStack);
void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH]);
void printMaze(int mazeArray[HEIGHT][WIDTH]);

char num_to_dir(int i);
char *num_to_str(int i);
void showPath_on_Maze(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH]);

#endif

#ifndef _COMMON_STACK_DEF_
# define _COMMON_STACK_DEF_

# define TRUE		1
# define FALSE		0

#endif