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

struct Node
{
	wchar_t* data;
	Node* next;
};

Node* startNode;
wchar_t* testInput = L"¿ÓÀ¬a¥‹Åt³ª³ª³ª»Ÿ·cÄm³ª³ª¹ÅŸ³ª³ª³ª¾¿Àø³ª2³ªO¢NÀø³ª³ª";

void input();
void search();
void remove();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	input();

	DWORD StartTime;
	DWORD EndTime;

	StartTime = GetTickCount();

	for(int i = 0 ; i < 100000; i++)
		search();

	EndTime = GetTickCount();

	printf("%f sec\n", (float)(EndTime - StartTime) / 1000.0f);

	remove();

	return 0;
}

void input()
{
	setlocale(LC_ALL, "");
	Node* currentNode;

	wchar_t temp[256];
	memset(temp, 0, 256);
	FILE* fp;
	fp = fopen("input.txt", "r");
	startNode = (Node*)malloc(sizeof(Node));
	currentNode = startNode;

	while (fgetws(temp, 256, fp) != NULL)
	{
		currentNode->data = (wchar_t*)malloc(sizeof(wchar_t) * 256);
		wcscpy(currentNode->data, temp);
		currentNode->next = (Node*)malloc(sizeof(Node));
		currentNode = currentNode->next;
		currentNode->data = NULL;
		currentNode->next = NULL;
		memset(temp, 0, 256);
	}

	fclose(fp);
}

void search()
{
	int tis = wcslen(testInput) - 1;

	wchar_t* ttt = (wchar_t*)malloc(sizeof(wchar_t) * 256);
	wcscpy(ttt, testInput);

	Node* currentNode = startNode;

	while (currentNode->data != NULL)
	{
		int ss = wcslen(currentNode->data) - 1;
		for (int i = 0; i < tis; i++)
		{
			bool s = true;
			for (int j = 0; j < ss; j++)
			{
				if (currentNode->data[j] != ttt[i + j])
				{
					s = false;
					break;
				}
			}
			if (s == true)
			{
				for (int j = 0; j < ss; j++)
				{
					ttt[i + j] = '*';
				}
			}
		}
		currentNode = currentNode->next;
	}
	free(ttt);
}

void remove()
{
	Node* tempNode;
	Node* removeNode = startNode;
	while (removeNode != NULL)
	{
		tempNode = removeNode->next;
		free(removeNode->data);
		free(removeNode);
		removeNode = tempNode;
	}
}