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
	int depth;
	wchar_t* data;
	Node* left;
	Node* right;
};

FILE* fp;
Node* startNode;
wchar_t* testInput = L"¿ÓÀ¬¥‹Åt³ª³ª³ªž»Ÿž·cÄm³ª³ª¹ÅŸ³ª³ª³ª¾¿Àø³ª2³ªO¢NÀø³ª³ª";

wchar_t temp[256];

void input(Node** node, wchar_t* str, int depth)
{
	if ((*node) == NULL)
	{
		(*node) = (Node*)malloc(sizeof(Node));
		(*node)->data = (wchar_t*)malloc(sizeof(wchar_t) * 256);
		(*node)->depth = depth;
		wcscpy((*node)->data, str);
		(*node)->left = NULL;
		(*node)->right = NULL;
	}
	else if ((*node)->data[0] < str[0])
	{
		input(&(*node)->left, str, depth + 1);
	}
	else if ((*node)->data[0] >= str[0])
	{
		input(&(*node)->right, str, depth + 1);
	}

}

void print(Node* node)
{
	static int c = 0;
	if (node == NULL)
		return;
	wprintf(L"%d %d : %s", c, node->depth, node->data);
	c++;
	print(node->left);
	print(node->right);
}

void searchrecv(Node* node, wchar_t* str, int c)
{
	int ss = wcslen(node->data) - 1;
	bool s = true;

	for (int j = 0; j < ss; j++)
	{
		if (node->data[j] != str[c + j])
		{
			s = false;
			break;
		}
	}
	if (s == true)
	{
		for (int j = 0; j < ss; j++)
		{
			str[c + j] = '*';
		}
	}

	if (node->left != NULL && str[c] > node->data[0])
		searchrecv(node->left, str, c);
	else if (node->right != NULL && str[c] < node->data[0])
		searchrecv(node->right, str, c);
}

void search(Node* node, wchar_t* str)
{
	int tis = wcslen(str) - 1;
	for (int i = 0; i < tis; i++)
	{
		if (str[i] == '*')
			continue;
		searchrecv(node, str, i);
	}
}

void remove(Node* node)
{
	if (node == NULL)
		return;

	remove(node->left);
	remove(node->right);

	free(node->data);
	free(node);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	memset(temp, 0, sizeof temp / sizeof(wchar_t));
	setlocale(LC_ALL, "");

	fp = fopen("input.txt", "r");

	while (fgetws(temp, 256, fp) != NULL)
	{
		input(&startNode, temp, 0);
		memset(temp, 0, sizeof temp / sizeof(wchar_t));
	}

	fclose(fp);

	//print(startNode);

	DWORD StartTime;
	DWORD EndTime;

	StartTime = GetTickCount();


	wchar_t* ttt = (wchar_t*)malloc(sizeof(wchar_t) * 256);
	//for (int i = 0; i < 10000; i++)
	{
		memset(ttt, 0, sizeof ttt / sizeof(wchar_t));
		wcscpy(ttt, testInput);
		search(startNode, ttt);
	}
	wprintf(L"%s\n", ttt);
	free(ttt);

	EndTime = GetTickCount();

	printf("%f sec\n", (float)(EndTime - StartTime) / 1000.0f);

	remove(startNode);

	return 0;
}
