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
int* T = NULL, *V_W = NULL, *E = NULL;
int r_c, next_vertex, connect = 0, edge_count = 0;
char g, v;

int main()
{
	int e = 0, sum = 0;
	/*========read num and init array========*/
	puts("========================");
	printf("Now have three grapth.\nPlease choose graph:");
	scanf("%d", &g);
	r_c = readnum(g);//read vertex number
	printf("vertex number=%d\n", r_c);
	puts("========================");
	T = (int *)malloc(sizeof(int)*r_c*r_c); //declare check data table
	E = (int *)malloc(sizeof(int)*r_c); //declare Edge_array
	V_W = (int *)malloc(sizeof(int)*r_c); //declare vertex-weight table
	para = (SORT*)malloc(sizeof(SORT)*r_c); //declare sortarray 
	/*=======================================*/

	/*========init para and vertex_weight table========*/
	for (int i = 0; i < r_c*r_c; i++) //init T
		T[i] = 0;
	for (int i = 0; i < r_c; i++) //init T
	{
		V_W[i] = 999;
		para[i].sortarray = 999;
		para[i].vernum = i + 1;
	}
	T = readfile(T, g); //input data
	/*================================================*/

	/*===================start MST====================*/
	int EDGE;
	printf("Choose the start vertex:");
	scanf("%d", &v);
	puts("========================");
	puts("-------------------------------------");
	printf("v%d set 0\n", v);
	para[v - 1].sortarray = V_W[v - 1] = 0;//choosen vertex set 0
	EDGE = checktable(v, para); //start form v1
	printf("The smallest weighted edge is %d (v%d,v%d).\nChoose edge (v%d,v%d).\n", EDGE, v, next_vertex, v, next_vertex);
	printf("Next vertex %d\n", next_vertex);
	puts("-------------------------------------");
	v = next_vertex;

	while (1)
	{
		printf("v%d set 0\n", next_vertex);
		E[e] = V_W[next_vertex - 1];
		para[next_vertex - 1].sortarray = V_W[next_vertex - 1] = 0;
		EDGE = checktable(next_vertex, para);
		if (EDGE == 0)
		{
			printf("all vertex already visited\n");
			puts("-------------------------------------");
			printf("output all edge:\n");
			for (int i = 0; i < r_c - 1; i++)//count total weigth
			{
				sum += E[i];
				printf("E[%d]=%d\t", i, E[i]);
			}
			printf("\ntotal weight =%d\n", sum);
			puts("-------------------------------------");
			break;
		}
		printf("The smallest weighted edge is %d (v%d,v%d).\nChoose edge (v%d,v%d).\n", EDGE, connect, next_vertex, connect, next_vertex);
		printf("Next vertex %d\n", next_vertex);
		puts("-------------------------------------");
		e++;
		v = next_vertex;
	}

	/*===================end MST====================*/
	system("pause");
	return 0;
}

int checktable(int arg, SORT* para)
{
	int temp = 0, vtemp = 0, flag;
	//======refresh vertex_weigth table======//
	for (int j = 0; j < r_c; j++) //存放weigth進V_W 與 sortarray
		if (V_W[j] > T[(arg - 1)* r_c + j] && T[(arg - 1)* r_c + j] != 0) //使用上0為已拜訪 資料0為未連接
			V_W[j] = T[(arg - 1) * r_c + j];
	//=======================================//

	//=============refresh para==============//
	for (int j = 0; j < r_c; j++) 
	{
		para[j].sortarray = V_W[j];
		para[j].vernum = j + 1;
	}
	//=======================================//

	/*==============bubble sort==============*/
	for (int c = r_c - 1; c >= 0; c--) 
	{
		flag = 1;
		for (int i = 0; i < c; i++)
		{
			if (para[i].sortarray>para[i + 1].sortarray)
			{
				temp = para[i].sortarray;
				vtemp = para[i].vernum;
				para[i].sortarray = para[i + 1].sortarray;
				para[i].vernum = para[i + 1].vernum;
				para[i + 1].sortarray = temp;
				para[i + 1].vernum = vtemp;
				flag = 0;
			}
		}
		if (flag == 1)
			break;
	}
	/*=======================================*/

	/*=======fetch smallest one edge=========*/
	vtemp = 0;
	for (int f = 0; f < r_c; f++) 
	{
		if (para[f].sortarray > 0)
		{
			temp = para[f].sortarray;
			vtemp = next_vertex = para[f].vernum;
			break;
		}
	}
	/*=======================================*/

	/*check T position fetch vertex number*/
	for (int i = 0; i < r_c; i++)
	{
		if (T[(vtemp - 1)*r_c + i] == temp)
		{
			connect = i + 1;
		}
	}
	/*====================================*/
	return temp;
}