
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
����ṹ��
direction�������£�
6
^
5     |    7
4----------|---------------->0
3     |    1
2
�ң�0���£�2����4����6��
���8������ˮƽ���ҷ���Ϊ0����ʱ��ת��
*/
struct B_POINT
{
	double x;
	double y;
	int direction;
};
typedef int(*DirectionSearchFunc)(struct B_POINT*, int, int, int*);
/*
���������
*/
void GenerateData(struct B_POINT*pPoints, int nCounts, int maxx, int maxy, int num)
{
	int x, y,i;
	for (i = 0; i < num; i++)
	{
		x = rand() % maxx;
		y = rand() % maxy;
		pPoints[i].x = x;
		pPoints[i].y = y;
		pPoints[i].direction = -1;
	}
}
void PrintData(struct B_POINT*pPoints, int nCounts)
{
	int i;
	for (i = 0; i < nCounts; i++)
	{
		printf("(%lf,%lf)\n", pPoints[i].x, pPoints[i].y);
	}
}
/*
�������е��е���ʼ���㣨Yֵ���
*/
int FindFirstPoint(struct B_POINT*pPoints, int nCounts)
{
	int index = 0;
	int i = 0;
	for (i = 1; i < nCounts; i++)
	{
		if (pPoints[index].y < pPoints[i].y)
		{
			index = i;
		}
		else if (pPoints[index].y == pPoints[i].y&&pPoints[index].x > pPoints[i].x)
		{
			index = i;
		}
	}
	return index;
}
/*
����б��
*/
double CalcSlope(struct B_POINT first, struct B_POINT second)
{
	double slope;
	slope = fabs(second.y - first.y) / fabs(second.x - first.x);
	return slope;
}

/*
����0�����ڵĵ㣬ˮƽ����
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaZero(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double maxx = 0;
	int i = 0;
	struct B_POINT currentPoint;
	struct	B_POINT lastPoint;
	for (i = 0; i < nCounts; i++)
	{
		//0�����ڵĵ�
		currentPoint = pPoints[i];
		lastPoint = pPoints[lastIndex];
		if (currentPoint.x > lastPoint.x
			&& currentPoint.y == lastPoint.y
			&&i != lastIndex)
		{
			if (!find)
			{
				find = 1;
				pointIndex = i;
				maxx = currentPoint.x;
			}
			else if (currentPoint.x > maxx)
			{
				pointIndex = i;
				maxx = currentPoint.x;
			}

		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 0;//4
	return find;
}

/*
����1������б����С�ĵ㣬��������
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaOne(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double slope = 0;
	int i = 0;
	struct B_POINT currentPoint;
	struct B_POINT lastPoint;
	for (i = 0; i < nCounts; i++)
	{
		//1�����ڵĵ�
		currentPoint = pPoints[i];
		lastPoint = pPoints[lastIndex];
		if (currentPoint.x > lastPoint.x
			&& currentPoint.y < lastPoint.y
			&&i != lastIndex)
		{
			double tmp = CalcSlope(lastPoint, currentPoint);
			if (!find)
			{
				find = 1;
				pointIndex = i;
				slope = tmp;
			}
			else if (tmp < slope)
			{
				pointIndex = i;
				slope = tmp;
			}
		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 1;//0
	return find;
}

/*
����2�����ڵĵ㣬��ֱ����
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaTwo(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double miny = 0;
	int i = 0;
	struct B_POINT currentPoint;
	struct B_POINT lastPoint;
	for (i = 0; i < nCounts; i++)
	{
		//2�����ڵĵ�
		currentPoint = pPoints[i];
		lastPoint = pPoints[lastIndex];
		if (currentPoint.x == lastPoint.x
			&& currentPoint.y < lastPoint.y
			&&i != lastIndex)
		{
			if (!find)
			{
				find = 1;
				pointIndex = i;
				miny = currentPoint.y;
			}
			else if (currentPoint.y < miny)
			{
				pointIndex = i;
				miny = currentPoint.y;
			}

		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 2;//5
	return find;
}

/*
����3������б�����ĵ㣬��������
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaThree(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double slope = 0;
	int i = 0;
	for (i = 0; i < nCounts; i++)
	{
		//3�����ڵĵ�
		struct B_POINT currentPoint = pPoints[i];
		struct B_POINT lastPoint = pPoints[lastIndex];
		if (currentPoint.x < lastPoint.x
			&& currentPoint.y < lastPoint.y
			&&i != lastIndex)
		{
			double tmp = CalcSlope(lastPoint, currentPoint);
			if (!find)
			{
				find = 1;
				pointIndex = i;
				slope = tmp;
			}
			else if (tmp > slope)
			{
				pointIndex = i;
				slope = tmp;
			}
		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 3;//1
	return find;
}

/*
����4�����ڵĵ㣬ˮƽ����
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaFour(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double minx = 0;
	int i;
	for ( i = 0; i < nCounts; i++)
	{
		//4�����ڵĵ�
		struct B_POINT currentPoint = pPoints[i];
		struct B_POINT lastPoint = pPoints[lastIndex];
		if (currentPoint.x < lastPoint.x
			&& currentPoint.y == lastPoint.y
			&&i != lastIndex)
		{
			if (!find)
			{
				find = 1;
				pointIndex = i;
				minx = currentPoint.x;
			}
			else if (currentPoint.x < minx)
			{
				pointIndex = i;
				minx = currentPoint.x;
			}

		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 4;//6
	return find;
}

/*
����5������б����С�ĵ㣬��������
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaFive(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double slope = 0;
	int i = 0;
	for (i = 0; i < nCounts; i++)
	{
		//5�����ڵĵ�
		struct B_POINT currentPoint = pPoints[i];
		struct B_POINT lastPoint = pPoints[lastIndex];
		if (currentPoint.x < lastPoint.x
			&& currentPoint.y > lastPoint.y
			&&i != lastIndex)
		{
			double tmp = CalcSlope(lastPoint, currentPoint);
			if (!find)
			{
				find = 1;
				pointIndex = i;
				slope = tmp;
			}
			else if (tmp < slope)
			{
				pointIndex = i;
				slope = tmp;
			}
		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 5;//2
	return find;
}
/*
����6�����ڵĵ㣬��ֱ����
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextPointIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaSix(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextPointIndex)
{
	int find = 0;
	int pointIndex = 0;
	double maxy = 0;
	int i = 0;
	for (i = 0; i < nCounts; i++)
	{
		//6�����ڵĵ�
		struct B_POINT currentPoint = pPoints[i];
		struct B_POINT lastPoint = pPoints[lastIndex];
		if (currentPoint.x == lastPoint.x
			&& currentPoint.y > lastPoint.y
			&&i != lastIndex)
		{
			if (!find)
			{
				find = 1;
				pointIndex = i;
				maxy = currentPoint.y;
			}
			else if (currentPoint.y > maxy)
			{
				pointIndex = i;
				maxy = currentPoint.y;
			}

		}
	}
	*nextPointIndex = pointIndex;
	if (find)
		pPoints[*nextPointIndex].direction = 6;//7
	return find;
}
/*
����7������б�����ĵ�,���Ϸ���
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindPointFromAreaSeven(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextIndex)
{
	int find = 0;
	int pointIndex = 0;
	double slope = 0;
	int i = 0;
	for (i = 0; i < nCounts; i++)
	{
		//7�����ڵĵ�
		struct B_POINT currentPoint = pPoints[i];
		struct B_POINT lastPoint = pPoints[lastIndex];
		if (currentPoint.x > lastPoint.x
			&& currentPoint.y > lastPoint.y
			&&i != lastIndex)
		{
			double tmp = CalcSlope(lastPoint, currentPoint);
			if (!find)
			{
				find = 1;
				pointIndex = i;
				slope = tmp;
			}
			else if (tmp > slope)
			{
				pointIndex = i;
				slope = tmp;
			}
		}
	}
	*nextIndex = pointIndex;
	if (find)
		pPoints[*nextIndex].direction = 7;//3
	return find;
}
/*
������һ������
nDirections ����Ѱ�ķ������
direction ��������
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindNextPointClockwise(int nDirections, int*direction, struct B_POINT*pPoints, int nCounts, int lastIndex, int *nextIndex)
{
	int bFind = 0;
	DirectionSearchFunc funcs[8];
	int dir, ret;
	int i = 0;
	funcs[0] = FindPointFromAreaZero;
	funcs[1] = FindPointFromAreaOne;
	funcs[2] = FindPointFromAreaTwo;
	funcs[3] = FindPointFromAreaThree;
	funcs[4] = FindPointFromAreaFour;
	funcs[5] = FindPointFromAreaFive;
	funcs[6] = FindPointFromAreaSix;
	funcs[7] = FindPointFromAreaSeven;
	for (i = 0; i < nDirections; i++)
	{
		 dir = direction[i];
		 ret = funcs[dir](pPoints, nCounts, lastIndex, nextIndex);
		if (ret)
		{
			bFind = 1;
			break;
		}
	}
	return bFind;
}
/*
������һ������
pPoints �㼯��
nCounts ���ϵ����
lastIndex ��һ���Ѿ��ҵ��Ķ����index
nextIndex ��һ����Ҫ�ҵ��Ķ����index
*/
int FindNextPoint(struct B_POINT*pPoints, int nCounts, int lastIndex, int*nextIndex)
{
	
	int lastDirection = 0;
	int directionCount = 0;
	int directionArray[8];
	if (nCounts < 3)
		return 0;
	lastDirection = pPoints[lastIndex].direction;
	switch (lastDirection)
	{
	case 0:
		//0 1 2 3
		directionCount = 4;
		directionArray[0] = 0;
		directionArray[1] = 1;
		directionArray[2] = 2;
		directionArray[3] = 3;
		break;
	case 1:
		//1 2 3 4 5
		directionCount = 5;
		directionArray[0] = 1;
		directionArray[1] = 2;
		directionArray[2] = 3;
		directionArray[3] = 4;
		directionArray[4] = 5;
		break;
	case 2:
		//2 3 4 5
		directionCount = 4;
		directionArray[0] = 2;
		directionArray[1] = 3;
		directionArray[2] = 4;
		directionArray[3] = 5;
		break;
	case 3:
		//3 4 5 6 7
		directionCount = 5;
		directionArray[0] = 3;
		directionArray[1] = 4;
		directionArray[2] = 5;
		directionArray[3] = 6;
		directionArray[4] = 7;
		break;
	case 4:
		//4 5 6 7
		directionCount = 4;
		directionArray[0] = 4;
		directionArray[1] = 5;
		directionArray[2] = 6;
		directionArray[3] = 7;
		break;
	case 5:
		//5 6  7 0 1
		directionCount = 5;
		directionArray[0] = 5;
		directionArray[1] = 6;
		directionArray[2] = 7;
		directionArray[3] = 0;
		directionArray[4] = 1;
		break;
	case 6:
		// 6 7 0 1
		directionCount = 4;
		directionArray[0] = 6;
		directionArray[1] = 7;
		directionArray[2] = 0;
		directionArray[3] = 1;
		break;
	case 7:
		//7 0 1 2 3
		directionCount = 5;
		directionArray[0] = 7;
		directionArray[1] = 0;
		directionArray[2] = 1;
		directionArray[3] = 2;
		directionArray[4] = 3;
		break;
	default:
		break;
	}
	int ret = FindNextPointClockwise(directionCount, directionArray, pPoints, nCounts, lastIndex, nextIndex);
	return ret;
}
/*
�жϵ��Ƿ��ڶ������
pPoints �㼯��
nCounts ���ϵ����
bp ���жϵ�
*/
int IsPointInPolygon(struct B_POINT*pPoints, int nCounts, struct B_POINT bp)
{


	int nvert;
	double testX;
	double testY;

	int i, j;
	int c;
	c= 0;
	if (nCounts < 3)
		return 0;
	nvert = nCounts;
	testX = bp.x;
	testY = bp.y;

	for (i = 0, j = nvert - 1; i < nvert; j = i++)
	{
		if (((pPoints[i].y > testY) != (pPoints[j].y > testY)) &&
			(testX < (pPoints[j].x - pPoints[i].x) * (testY - pPoints[i].y) / (pPoints[j].y - pPoints[i].y) + pPoints[i].x))
			c = !c;

		//����
		if ((testX == pPoints[i].x&&testY == pPoints[i].y)
			|| (testX == pPoints[j].x&&testY == pPoints[j].y))
		{
			c = 0;
			break;
		}
		//��ֱֱ��
		else if ((pPoints[i].x == pPoints[j].x))
		{
			if ((pPoints[j].x == testX) &&
				((pPoints[i].y > testY) != (pPoints[j].y > testY)))
			{
				c = 0;
				break;
			}
		}
		//ˮƽֱ��
		else if (pPoints[i].y == pPoints[j].y)
		{
			if ((pPoints[i].y == testY) &&
				((pPoints[i].x > testX) != (pPoints[j].x > testX))
				)
			{
				c = 0;
				break;
			}
		}
		//����бֱ����
		else if (
			((pPoints[i].y >= testY&&pPoints[j].y <= testY) || (pPoints[i].y <= testY&&pPoints[j].y >= testY))
			&& ((pPoints[i].x >= testX&&pPoints[j].x <= testX) || (pPoints[i].x <= testX&&pPoints[j].x >= testX))
			)
		{
			if (testX == (pPoints[j].x - pPoints[i].x) * (testY - pPoints[i].y) / (pPoints[j].y - pPoints[i].y) + pPoints[i].x)
			{
				c = 0;
				break;
			}
		}

	}

	return c;
}
/*
�����¶���ζ���
pPoints �㼯��
nCounts ���ϵ����
pIndexArray ����
pArrayCount �����
*/
int FindAllPoints(struct B_POINT* pPoints, int nCount, int**pIndexArray, int*pArrayCount)
{
	int fristPointIndex;
	int capacity = 20;
	int arrayIndex = 0;
	int bFound = 0;
	int nextPointIndex = 0;
	int lastPointIndex = 0;
	int ret;
	int *tmpIndexArray;
	if (nCount < 3)
		return 0;
	fristPointIndex = FindFirstPoint(pPoints, nCount);
	pPoints[fristPointIndex].direction = 0;
	*pIndexArray = (int*)malloc(sizeof(int)*capacity);
	(*pIndexArray)[arrayIndex++] = fristPointIndex;

	while (1)
	{
		lastPointIndex = (*pIndexArray)[arrayIndex - 1];
		ret = FindNextPoint(pPoints,nCount, lastPointIndex, &nextPointIndex);
		if (!ret)
		{
			bFound = 0;
			break;
		}
		if (arrayIndex == capacity)
		{
			capacity *= 2;
			tmpIndexArray = (int*)malloc(sizeof(int)*capacity);
			memcpy(tmpIndexArray, *pIndexArray, arrayIndex * sizeof(int));
			free(*pIndexArray);
			*pIndexArray = tmpIndexArray;
		}
		(*pIndexArray)[arrayIndex++] = nextPointIndex;
		if (nextPointIndex == fristPointIndex)
		{
			bFound = 1;
			break;
		}
	}
	*pArrayCount = arrayIndex;
	return bFound;
}
long ReadData(struct B_POINT* pPoints, int *nCount,char* fn)
{
	FILE* fp;
	char strLine[64];
	double x=0, y=0;
	int index = 0;
	memset(strLine, 0, 64);
	fp = fopen(fn, "r");
	while (!feof(fp))
	{
		fgets(strLine, 64, fp);
		if (strlen(strLine) < 3)
			break;
		sscanf(strLine, "%lf %lf", &x, &y);
		pPoints[index].x = x;
		pPoints[index].y = y;
		pPoints[index].direction = -1;
		index++;
	}
	fclose(fp);
	*nCount= index;
	return index;
}



int main(int argc,char **argv)
{
	struct B_POINT *pAllPoints,*pVPoints,testPoints[6];
	int i, x, y;
	int pointCount ;
	int firstIndex;
	int *pIndexArray=0;
	int arryIndex;
	int indexArrayCount;
	int bFound = 0;
	int testCount;
	int ret;
	

	// srand(time(NULL));//�������
	pAllPoints = (struct B_POINT*)malloc(pointCount * sizeof(struct B_POINT));
	//GenerateData(pAllPoints, pointCount, 800,  900, pointCount);//
	ReadData(pAllPoints, &pointCount,argv[1]);//�߽��ļ�
	//�������ж���
	bFound = FindAllPoints(pAllPoints, pointCount, &pIndexArray, &indexArrayCount);
	if (bFound)
	{
		printf("Got %d points\n", indexArrayCount);
		for ( i = 0; i < indexArrayCount; i++)
		{
			printf("(%lf,%lf)\tIndex:%d\n", pAllPoints[pIndexArray[i]].x, pAllPoints[pIndexArray[i]].y, pIndexArray[i]+1);
		}
		pVPoints = (struct B_POINT*)malloc(sizeof(struct B_POINT)*indexArrayCount);
		for (i = 0; i < indexArrayCount; i++)
		{
			pVPoints[i] = pAllPoints[pIndexArray[i]];
		}
		//GenerateData(testPoints, 6, 1000, 1200, 6);
		ReadData(testPoints, &testCount, argv[2]);//�ж��ļ�
		char *substr=NULL;
		for ( i = 0; i < testCount; i++)
		{

			//�жϵ���ͼ����
			ret = IsPointInPolygon(pVPoints, indexArrayCount, testPoints[i]);
			if (ret)
			{
				substr=strtok(argv[1],"/");
				system("pwd");
				//sleep(1);
				printf("(%lf,%lf)\tIN\n", testPoints[i].x, testPoints[i].y);
				
				break;
			}
			else
				printf("(%lf,%lf)\tOUT\n", testPoints[i].x, testPoints[i].y);
		}
		free(pVPoints);
	}
	free(pAllPoints);
	free(pIndexArray);
	return 0;
}

