#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int readnum(int G)
{
	FILE *fp, *fp2, *fp3;
	int ch;
	switch (G)
	{
	case 1:
		fp = fopen("graph1.txt", "rb");
		ch = getc(fp);
		break;
	case 2:
		fp2 = fopen("graph2.txt", "rb");
		ch = getc(fp2);
		break;
	case 3:
		fp3 = fopen("graph3.txt", "rb");
		ch = getc(fp3);
		break;
	default:
		puts("========================");
		printf("did't have this graph\n");
		system("pause");
		exit (1);
		break;
	}
	ch -= 48;
	return ch;
}

int* readfile(int* T, int G)
{
	FILE *fp, *fp2, *fp3;
	int temp, i = 0;
	switch (G)
	{
	case 1:
		fp = fopen("graph1.txt", "rb");
		temp = getc(fp); //read useless information on grapgh.txt
		temp = getc(fp);
		temp = getc(fp);
		while (!feof(fp))
		{
			//printf("i=%d\n",i);
			temp = getc(fp);
			if (temp > 47 && temp <58)
			{
				//printf("temp=%d ", temp);
				T[i] = temp - 48;
				//printf("T=%d\n", T[i]);
				i++;
			}
			else if (temp == -1)
				break;
			else
				continue;
		}
		break;
	case 2:
		fp2 = fopen("graph2.txt", "rb");
		temp = getc(fp2); //read useless information on grapgh.txt
		temp = getc(fp2);
		temp = getc(fp2);
		while (!feof(fp2))
		{
			//printf("i=%d\n",i);
			temp = getc(fp2);
			if (temp > 47 && temp <58)
			{
				//printf("temp=%d ", temp);
				T[i] = temp - 48;
				//printf("T=%d\n", T[i]);
				i++;
			}
			else if (temp == -1)
				break;
			else
				continue;
		}
		break;
	case 3:
		fp3 = fopen("graph3.txt", "rb");
		temp = getc(fp3); //read useless information on grapgh.txt
		temp = getc(fp3);
		temp = getc(fp3);
		while (!feof(fp3))
		{
			//printf("i=%d\n",i);
			temp = getc(fp3);
			if (temp > 47 && temp <58)
			{
				//printf("temp=%d ", temp);
				T[i] = temp - 48;
				//printf("T=%d\n", T[i]);
				i++;
			}
			else if (temp == -1)
				break;
			else
				continue;
		}
		break;
	default:
		printf("did't have this graph\n");
		system("pause");
		exit (1);
		break;
	}
	return T;
}
