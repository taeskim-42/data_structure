#include "maze_stack.h"

char num_to_dir(int i)
{
	if (i == 0)
		return ('^');
	else if (i == 1)
		return ('>');
	else if (i == 2)
		return ('v');
	else if (i == 3)
		return ('<');
	else
		return ('S');
}

char *num_to_str(int i)
{
	if (i == 0)
		return ("UP");
	else if (i == 1)
		return ("RIGHT");
	else if (i == 2)
		return ("DOWN");
	else if (i == 3)
		return ("LEFT");
	else
		return ("START");
}

void showPath_on_Maze(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
	StackNode *tmp_node;
	char map[HEIGHT][WIDTH] = {0, };

	reverseLinkedStack(pStack);
	tmp_node = pStack->pTopElement;
	printf("PATH ON MAZE========\n");
	for (int i = 0; i < pStack->currentElementCount; i++)	
	{
		if (tmp_node->pLink == NULL)
			map[tmp_node->pos.y][tmp_node->pos.x] = 'E';
		else
			map[tmp_node->pos.y][tmp_node->pos.x] = num_to_dir(tmp_node->pLink->pos.dir);
		tmp_node = tmp_node->pLink;
	}
	for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            printf("%c ", map[i][j] == 0 ? '.' : map[i][j]);
        printf("\n");
    }
	printf("====================\n");
	reverseLinkedStack(pStack);
}