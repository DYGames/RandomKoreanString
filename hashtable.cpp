#include <stdio.h>
#include <malloc.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <Windows.h>

#include <crtdbg.h>

#ifndef _DEBUG

#define new new(_CLIENT_BLOCK,__FILE__,__LINE)

#endif

const int START_KOREAN = 44032;

struct Node
{
	bool isRoot;
	bool isEnd;
	Node** next;
};

FILE* fp;
Node** roots;
wchar_t* testInput = L"¿ÓÀ¬a¥‹Åt³ª³ª³ªž»Ÿž·cÄm³ª³ª¹ÅŸ³ª³ª³ª¾¿Àø³ª2³ªO¢NÀø³ª³ª";

wchar_t temp[256];

void input(Node** node, wchar_t* str, int idx)
{
	if (node[str[idx] - START_KOREAN]->next == NULL)
	{
		node[str[idx] - START_KOREAN]->next = (Node**)malloc(sizeof(Node) * (55203 - 44032));
		for (int i = 0; i < (55203 - 44032); i++)
		{
			node[str[idx] - START_KOREAN]->next[i] = NULL;
		}
	}
	node[str[idx] - START_KOREAN]->next[str[idx + 1] - START_KOREAN] = (Node*)malloc(sizeof(Node));
	node[str[idx] - START_KOREAN]->next[str[idx + 1] - START_KOREAN]->isRoot = false;
	node[str[idx] - START_KOREAN]->next[str[idx + 1] - START_KOREAN]->isEnd = false;
	node[str[idx] - START_KOREAN]->next[str[idx + 1] - START_KOREAN]->next = NULL;
	if (idx + 1 == wcslen(str) - 2)
	{
		node[str[idx] - START_KOREAN]->next[str[idx + 1] - START_KOREAN]->isEnd = true;
		return;
	}
	input(node[str[idx] - START_KOREAN]->next, str, idx + 1);
}

void print(Node** node, int depth)
{
	if (node == NULL)
		return;
	for (int i = 0; i < (55203 - 44032); i++)
	{
		if (node[i] != NULL)
		{
			wprintf(L"%d : %c\n", depth, i + START_KOREAN);
			if (node[i]->next != NULL)
				print(node[i]->next, depth + 1);
		}
	}
}

bool searchrecv(Node** node, wchar_t* str, int idx, int offset)
{
	if (node == NULL)
		return false;

	if (str[idx + offset] > 55203 || str[idx + offset] < 44032)
		return false;

	int i = str[idx + offset] - START_KOREAN;
	if (node[i] != NULL)
	{
		if (node[i]->isEnd)
		{
			str[idx + offset] = '*';
			return true;
		}
		else
		{
			bool t = searchrecv(node[i]->next, str, idx, offset + 1);
			if (t)
			{
				str[idx + offset] = '*';
			}
			return t;
		}
	}
	return false;
}

void search(wchar_t* str)
{
	int tis = wcslen(str) - 1;
	for (int i = 0; i < tis; i++)
	{
		if (str[i] == '*')
			continue;

		if (str[i] > 55203 || str[i] < 44032)
			continue;

		if (searchrecv(roots[str[i] - START_KOREAN]->next, str, i, 1))
		{
			str[i] = '*';
		}
	}
}

void remove(Node** node)
{
	if (node == NULL)
		return;

	for (int i = 0; i < (55203 - 44032); i++)
	{
		if (node[i] != NULL)
		{
			if (node[i]->next != NULL)
				remove(node[i]->next);
			free(node[i]);
		}
	}
	free(node);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	memset(temp, 0, sizeof temp / sizeof(wchar_t));
	setlocale(LC_ALL, "");

	fp = fopen("input.txt", "r");

	roots = (Node**)malloc(sizeof(Node) * (55203 - 44032));
	for (int i = 0; i < 55203 - 44032; i++)
	{
		roots[i] = (Node*)malloc(sizeof(Node));
		roots[i]->isRoot = true;
		roots[i]->isEnd = false;
		roots[i]->next = NULL;
	}

	while (fgetws(temp, 256, fp) != NULL)
	{
		input(roots, temp, 0);
		memset(temp, 0, sizeof temp / sizeof(wchar_t));
	}

	fclose(fp);

	//print(roots, 0);

	DWORD StartTime;
	DWORD EndTime;

	wchar_t* ttt = (wchar_t*)malloc(sizeof(wchar_t) * 256);

	StartTime = GetTickCount();
	for (int i = 0; i < 1000000; i++)
	{
		memset(ttt, 0, sizeof ttt / sizeof(wchar_t));
		wcscpy(ttt, testInput);
		search(ttt);
	}
	EndTime = GetTickCount();

	wprintf(L"%s\n", ttt);
	free(ttt);

	printf("%f sec\n", (float)(EndTime - StartTime) / 1000.0f);

	remove(roots);

	return 0;
}
