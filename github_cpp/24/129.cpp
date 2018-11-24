#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "mstree.h"

#define MAXNUM 1000000;

struct Vector                 
{
	int *Id;
	int n;
};

struct Record                 
{
	int left, right;
	float dist;
};


void initVector(struct Vector *v)
{
	for(int i = 0; i < v->n; i++)
		v->Id[i] = i;
}

struct Vector* CreateVector(int count, int init)
{
	struct Vector *v = (struct Vector *)malloc(sizeof(struct Vector) + sizeof(int) * count);

	v->Id = (int *)(v + 1);
	v->n = init;

	return v;
}

void FreeVector(struct Vector *v)
{
	free(v);
}

float** CreateDist(int n)
{
	int m = n - 1;
	float **p = (float **)(malloc(sizeof(float *) * (n - 1)));
	for(int i = 0; i < n - 1; i++)
		p[i] = (float *)malloc(sizeof(float) * (m--));

	return p;
}

void FreeDist(float **p, int n)
{
	for(int i = 0; i < n - 1; i++)
		free(p[i]);

	free(p);
}

void push(struct Vector *v, int value)
{
	v->Id[v->n] = value;
	(v->n)++;
}

void pull(struct Vector *v, int value)
{
	int i;
	for(i = 0; i < v->n; i ++)
		if(v->Id[i] == value) break;

	for(int j = i; j < v->n - 1; j++)
		v->Id[j] = v->Id[j + 1];

	(v->n)--;
}

float Get(float **dist, int x, int y)
{
	if(x > y) return(dist[y][x - y - 1]);
	else return(dist[x][y - x - 1]);
}

//template <typename T>
void ComputeDist(std::vector<FeaturePoints> p, float **dist, int total, int flag)   
{
	switch(flag)
	{
	case 1:
		{
			for(int i = 0; i < total - 1; i++)
			{
				for(int j = i + 1; j < total; j++)
				{
					float x = abs(p[i].x - p[j].x) * abs(p[i].x - p[j].x);
					float y = abs(p[i].y - p[j].y) * abs(p[i].y - p[j].y);

					dist[i][j - i - 1] = x + y;
				}
			}
			break;
		}
		
	case 2:
		{
			for(int i = 0; i < total - 1; i++)
			{
				for(int j = i + 1; j < total; j++)
				{
					float x = abs(p[i].x - p[j].x) * abs(p[i].x - p[j].x);
					float y = abs(p[i].y - p[j].y) * abs(p[i].y - p[j].y);

					dist[i][j - i - 1] = sqrt(x + y);
				}
			}
			break;
		}

	case 3:
		{
			for(int i = 0; i < total - 1; i++)
			{
				for(int j = i + 1; j < total; j++)
				{
					float x = abs(p[i].x - p[j].x);
					float y = abs(p[i].y - p[j].y);

					dist[i][j - i - 1] = x + y;
				}
			}
			break;
		}
	default: printf("flag is wrong!\n"); break;
	}
}

//ѡ�����·��
void ChoseMin(struct Vector *left, struct Vector *right, struct Record *record, float **dist, int n, int max)   
{
	int num;
	float length = MAXNUM;
	if(n == 0)
	{
		num =  max - 1; 
		push(left, num);
		pull(right, num);
	}

	else
	{
		for(int i = 0; i < left->n; i++)
		{
			for(int j = 0; j < right->n; j++)
			{
				float l = Get(dist, right->Id[j], left->Id[i]);
				if(l < length) 
				{
					length = l;
					record[n - 1].left = left->Id[i];
					record[n - 1].right = right->Id[j];
					record[n - 1].dist = length;
				}
			}
		}
		push(left, record[n - 1].right);
		pull(right, record[n - 1].right);
	}
}

//�������·��
void MST(struct Vector *left, struct Vector *right, struct Record *record, float **dist, int max)   
{
	for(int i = 0; i < max; i++)
	{
		ChoseMin(left, right, record, dist, i, max);
	}
}

//�������·���õ�lambda
float ComputeLambda(struct Record *record, float alpha, int max)    
{
	float sum = 0, avg;
	for(int i = 0; i < max - 1; i++)
		sum += record[i].dist;
	
	avg = alpha * sum / (max - 1);

	return avg;
	
}

//template <typename T>
float min_span_tree(std::vector<FeaturePoints> points, float alpha) 
{
	int count = points.size();                              
	if(count == 0)
	{
		printf("points is null\n");
		exit(0);
	}
	float **dist = CreateDist(count);

	struct Vector *left = CreateVector(count, 0);
	struct Vector *right = CreateVector(count, count);
	initVector(right);

	struct Record* record = (struct Record *)malloc(sizeof(struct Record) * (count - 1));

	ComputeDist(points, dist, count, 2);
	MST(left, right, record, dist, count);	

	float lambda = ComputeLambda(record, alpha, count); 
//	printf("MST compute over and Get the lambda is %f\n", lambda);

	FreeVector(left);
	FreeVector(right);
	FreeDist(dist, count);
	free(record);

	return lambda;
}