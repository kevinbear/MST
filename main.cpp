#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "define.h"
using namespace std;
typedef struct sort
{
	int sortarray;
	int vernum;
}SORT;
SORT *para = NULL;
int checktable(int, SORT*);
int* T = NULL;
int* V_W = NULL;
int* E = NULL;
int r_c, next_vertex,connect=0, edge_count = 0;
char g, v;

int main()
{
	int e = 0, sum = 0;
	/*read num to create a array*/
	printf("Please choose graph:");
	scanf("%d", &g);
	r_c = readnum(g);
	printf("r_c=%d\n", r_c);
	T = (int *)malloc(sizeof(int)*r_c*r_c); //check table
	E = (int *)malloc(sizeof(int)*r_c);//Edge_array
	V_W = (int *)malloc(sizeof(int)*r_c); //vertex-weight table
	para = (SORT*)malloc(sizeof(SORT)*r_c);//sortarray 
	for (int i = 0; i < r_c*r_c; i++) //init T
		T[i] = 0;
	for (int i = 0; i < r_c; i++) //init T
	{
		V_W[i] = 999;
		para[i].sortarray = 999;
		para[i].vernum = i + 1;
	}
	T = readfile(T, g); //input data
	/*for (int i = 0; i < r_c*r_c; i++) //output array condition
	{
	if (i % (r_c) == 0)
	printf("\n");
	printf("%d\t", T[i]);
	}*/

	int EDGE;
	puts("/***********************************************/");
	printf("Choose the start vertex:");
	scanf("%d", &v);
	printf("Choose edge v%d\nv%d set 0\n", v, v);
	para[v - 1].sortarray = V_W[v - 1] = 0;//choosen vertex set 0
	EDGE = checktable(v, para); //start form v1
	printf("The smallest weighted edge of subtree is %d (v%d,v%d).Choose edge (v%d,v%d)\n", EDGE, v, next_vertex, v, next_vertex);
	puts("/***********************************************/");
	v = next_vertex;
	//system("pause");
	while (1)
	{
		if (edge_count <r_c - 1)
		{
			puts("/***********************************************/");
			printf("Next vertex %d\n", next_vertex);
			printf("v%d set 0\n", next_vertex);
			E[e] = V_W[next_vertex - 1];
			para[next_vertex - 1].sortarray = V_W[next_vertex - 1] = 0;
			EDGE = checktable(next_vertex, para);
			if (EDGE == 0) break;
			printf("The smallest weighted edge of subtree is %d (v%d,v%d).Choose edge (v%d,v%d)\n\n", EDGE, connect, next_vertex, connect, next_vertex);
			puts("/***********************************************/");
			edge_count++;
			e++;
			v = next_vertex;
			//system("pause");
		}
		else break;
	}
	for (int i = 0; i < r_c - 1; i++)
	{
		sum += E[i];
		printf("E[%d]=%d\n", i, E[i]);
	}
	printf("total weight =%d\n", sum);
	system("pause");
	return 0;
}


int checktable(int arg, SORT* para)
{
	int temp = 0, vtemp = 0, flag;
	printf("vertex-weight table refresh\n");
	for (int j = 0; j < r_c; j++) //存放weigth進V_W 與 sortarray
	{
		if (V_W[j] > T[(arg - 1)* r_c + j] && T[(arg - 1)* r_c + j] != 0) //使用上0為已拜訪 資料0為未連接
		{
			V_W[j] = T[(arg - 1) * r_c + j];
			//para[j].sortarray = T[(arg - 1) * r_c + j];
			//printf("V_W[%d]=%d T[%d]=%d para[%d].sortarray=%d\n", j + 1, V_W[j], (arg - 1) * r_c + j + 1, T[(arg - 1) * r_c + j],j+1,para[j].sortarray);
		}
	}
	for (int j = 0; j < r_c; j++) //更新para
	{
		para[j].sortarray = V_W[j];
		para[j].vernum = j + 1;
	}
	//================================= output V_W current value
	//puts("============================================================================");
	//for (int i = 0; i < r_c; i++)
	//{
	//	printf("V_W[%d]=%d \t", i + 1, V_W[i]);
	//}
	//puts("\n============================================================================");
	/*puts("============================================================================");
	for (int i = 0; i < r_c; i++)
	{
	printf("para[%d].a=%d para[%d].v=%d\n", i + 1, para[i].sortarray, i + 1, para[i].vernum);
	}
	puts("\n============================================================================");*/
	//=================================
	for (int c = r_c - 1; c >= 0; c--) //sort
	{
		flag = 1;
		for (int i = 0; i < c; i++)
		{
			if (para[i].sortarray>para[i + 1].sortarray)
			{
				//printf("sortarray[%d]=%d vernum=%d sortarray[%d]=%d vernum=%d\n ", i + 1, para[i].sortarray, para[i].vernum, i + 2, para[i + 1].sortarray,para[i+1].vernum);
				temp = para[i].sortarray;
				vtemp = para[i].vernum;
				para[i].sortarray = para[i + 1].sortarray;
				para[i].vernum = para[i + 1].vernum;
				para[i + 1].sortarray = temp;
				para[i + 1].vernum = vtemp;
				//printf("C:sortarray[%d]=%d vernum=%d sortarray[%d]=%d vernum=%d\n ", i + 1, para[i].sortarray, para[i].vernum, i + 2, para[i + 1].sortarray, para[i + 1].vernum);
				flag = 0;
			}
		}
		if (flag == 1)
			break;
	}
	/*puts("===========================================");
	for (int i = 0; i < r_c; i++)
	{
		printf("para[%d].a=%d para[%d].v=%d\n", i + 1, para[i].sortarray, i + 1, para[i].vernum);
	}
	puts("===========================================");*/
	vtemp=0;
	for (int f = 0; f < r_c; f++) //fetch smallest one edge
	{
		if (para[f].sortarray > 0)
		{
			temp = para[f].sortarray;
			vtemp=next_vertex = para[f].vernum;
			break;
		}
	}
	//check T position fetch vertex number
	//check T position fetch vertex number
	for (int i = 0; i < r_c; i++)
	{
		if (T[(vtemp - 1)*r_c + i] == temp)
		{
			connect = i + 1;
		}
	}
	return temp;
}

