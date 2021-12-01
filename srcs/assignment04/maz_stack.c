#include "./maz_stack.h"

// [0]North [1]East [2]South [3]West
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int find_ans;

char *num_to_dir(int i)
{
	if (i == 0)
		return ("NORTH");
	else if (i == 1)
		return ("EAST");
	else if (i == 2)
		return ("SOUTH");
	else if (i == 3)
		return ("WEST");
	else
		return ("START");
}

void findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack)
{
	if (startPos.x == endPos.x && startPos.y == endPos.y)
	{
		showPath(pStack, mazeArray);
		find_ans = 1;
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		MapPosition tmp;
		
		int nx = startPos.x + dx[i];
		int ny = startPos.y + dy[i];
		if (nx >= WIDTH || nx < 0 || ny >= HEIGHT || ny < 0)
			continue;
		if (mazeArray[ny][nx] != 0)
			continue;
		mazeArray[ny][nx] = 2;
		tmp.x = nx;
		tmp.y = ny;
		tmp.dir = i;
		pushLSMapPosition(pStack, tmp);
		findPath(mazeArray, tmp, endPos, pStack);
		free(popLSMapPosition(pStack));
		mazeArray[ny][nx] = 0;
	}
}

void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
	StackNode *tmp_node;

	reverseLinkedStack(pStack);
	tmp_node = pStack->pTopElement;
	printf("====================\n");
	for (int i = 0; i < pStack->currentElementCount; i++)	
	{
		printf("(%d, %d) %s\n", tmp_node->pos.x, tmp_node->pos.y, num_to_dir(tmp_node->pos.dir));
		tmp_node = tmp_node->pLink;
	}
	printf("====================\n");
	reverseLinkedStack(pStack);
}

void printMaze(int mazeArray[HEIGHT][WIDTH])
{
	printf("===========================================\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			printf("%d ", mazeArray[i][j]);
		printf("\n");
	}
	printf("===========================================\n");
}

int main()
{
	MapPosition startPos;
	MapPosition endPos;
	LinkedStack *pStack = createLinkedStack();
	
	startPos.x = 0;
	startPos.y = 0;
	startPos.dir = -1;
	endPos.x = WIDTH - 1;
	endPos.y = HEIGHT - 1;
	endPos.dir = 0;

	int mazeArray[HEIGHT][WIDTH] = {    
        {0, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 0, 1},
		{1, 1, 1, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0}
    };

	printMaze(mazeArray);
	pushLSMapPosition(pStack, startPos);
	findPath(mazeArray, startPos, endPos, pStack);
	if (find_ans == 0)
		printf("there's no answer\n");
	deleteLinkedStack(pStack);
	return 0;
}