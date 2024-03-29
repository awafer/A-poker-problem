/*
www.aiexp.info
Kai Sun
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
���� 0
�ݻ� 1
���� 2
��Ƭ 3 
*/
int DEPTH;
typedef struct
{
	char x, y;
} CARD;
CARD lisA[18+1] = {{4, 0}, {'A', 2}, {'A', 3}, {'J', 2}, {'J', 3}};
CARD lisB[18+1] =
{
	{18, 0},
	{'2', 1},
	{'K', 0}, {'K', 1}, {'K', 3}, 
	{'Q', 1}, {'Q', 2}, {'Q', 3},
	{'9', 1}, {'9', 2},
	{'7', 2}, {'7', 3},
	{'6', 0}, {'6', 2},
	{'5', 0}, {'5', 3},
	{'4', 1}, {'4', 3},
	{'3', 1}
};
int cmp[128];
void init()
{
	cmp['3'] = 1;
	cmp['4'] = 2;
	cmp['5'] = 3;
	cmp['6'] = 4;
	cmp['7'] = 5;
	cmp['8'] = 6;
	cmp['9'] = 7;
	cmp['0'] = 8;
	cmp['J'] = 9;
	cmp['Q'] = 10;
	cmp['K'] = 11;
	cmp['A'] = 12;
	cmp['2'] = 13;
};
int movelis[64][512];
int genall(int *move, CARD *lis)
{
	int i, j, k, l;
	int num = 0;
	if(lis->x >= 5)
	{
		if((lis[10].x || lis[11].x) && (lis[12].x || lis[13].x) &&
			(lis[14].x || lis[15].x) && (lis[16].x || lis[17].x) && lis[18].x)
		{
			for(i=10; i<=11; i++)
			{
				if(lis[i].x == 0) continue;
				for(j=12; j<=13; j++)
				{
					if(lis[j].x == 0) continue;
					for(k=14; k<=15; k++)
					{
						if(lis[k].x == 0) continue;
						for(l=16; l<=17; l++)
						{
							if(lis[l].x == 0) continue;
							move[num ++] = (1<<i)|(1<<j)|(1<<k)|(1<<l)|(1<<18);
						}
					}
				}
			}
		}
		if(lis[2].x && lis[3].x && lis[4].x)
		{
			for(i=1; i<=18; i++)
			{
				if(i >= 2 && i <= 4) continue;
				if(lis[i].x == 0) continue;
				for(j=i+1; j<=18; j++)
				{
					if(i >= 2 && i <= 4) continue;
					if(lis[j].x == 0) continue;
					if(lis[i].x != lis[j].x) break;
					move[num ++] = (1<<i)|(1<<j)|(1<<2)|(1<<3)|(1<<4);
				}
			}
		}
		if(lis[5].x && lis[6].x && lis[7].x)
		{
			for(i=1; i<=18; i++)
			{
				if(i >= 5 && i <= 7) continue;
				if(lis[i].x == 0) continue;
				for(j=i+1; j<=18; j++)
				{
					if(i >= 5 && i <= 7) continue;
					if(lis[j].x == 0) continue;
					if(lis[i].x != lis[j].x) break;
					move[num ++] = (1<<i)|(1<<j)|(1<<5)|(1<<6)|(1<<7);
				}
			}
		}
		if(lis[4].x && lis[7].x && lis[11].x && lis[15].x && lis[17].x)
		{
			move[num ++] = (1<<4)|(1<<7)|(1<<11)|(1<<15)|(1<<17);
		}
		if(lis[1].x && lis[3].x && lis[5].x && lis[8].x && lis[16].x)
		{
			move[num ++] = (1<<1)|(1<<3)|(1<<5)|(1<<8)|(1<<16);
		}
		if(lis[1].x && lis[3].x && lis[5].x && lis[8].x && lis[18].x)
		{
			move[num ++] = (1<<1)|(1<<3)|(1<<5)|(1<<8)|(1<<18);
		}
		if(lis[1].x && lis[3].x && lis[5].x && lis[16].x && lis[18].x)
		{
			move[num ++] = (1<<1)|(1<<3)|(1<<5)|(1<<16)|(1<<18);
		}
		if(lis[1].x && lis[3].x && lis[8].x && lis[16].x && lis[18].x)
		{
			move[num ++] = (1<<1)|(1<<3)|(1<<8)|(1<<16)|(1<<18);
		}
		if(lis[1].x && lis[5].x && lis[8].x && lis[16].x && lis[18].x)
		{
			move[num ++] = (1<<1)|(1<<5)|(1<<8)|(1<<16)|(1<<18);
		}
		if(lis[3].x && lis[5].x && lis[8].x && lis[16].x && lis[18].x)
		{
			move[num ++] = (1<<3)|(1<<5)|(1<<8)|(1<<16)|(1<<18);
		}
	}
	for(i=1; i<18; i++)
	{
		if(lis[i].x == 0) continue;
		for(j=i+1; j<=18; j++)
		{
			if(lis[j].x != lis[i].x) break;
			move[num ++] = (1<<i)|(1<<j);
		}
	}
	for(i=1; i<=18; i++)
	{
		if(lis[i].x) move[num ++] = 1<<i;
	}
	if(num > 512) printf("ERROR: 1\n");
	return num;
}
int genpart(int *move, CARD *lis, int flag, int card)
{
	int i, j;
	int num = 0;
	if(flag == 2)
	{
		for(i=1; i<18; i++)
		{
			if(lis[i].x == 0) continue;
			if(cmp[lis[i].x] <= cmp[card]) continue;
			for(j=i+1; j<=18; j++)
			{
				if(lis[j].x != lis[i].x) break;
				move[num ++] = (1<<i)|(1<<j);
			}
		}
	}
	else
	{
		for(i=1; i<=18; i++)
		{
			if(lis[i].x == 0) continue;
			if(cmp[lis[i].x] > cmp[card]) move[num ++] = 1<<i;
		}
	}
	return num;
}
int dmax = 1000;
int maxmin(CARD *A, CARD *B, int depth, int flag, int card)
{
	int i, j, k, v, best = -1;
	int num = 0, *move;
	int tmp[5];
	move = movelis[depth];
	if(depth < dmax)
	{
		dmax=depth;
	}
	if(depth == -1) printf("ERROR: 2\n");
	//if(depth == -1) return 0;
	if(B->x == 0) return -1;
	switch(flag)
	{
		case 0:
			num = genall(move, A);
			break;
		case 1:
		case 2:
			num = genpart(move, A, flag, card);
			break;
		case 5:
			num = 0;
			break;
	}
	for(i=0; i<num; i++)
	{
		k = 0;
		for(j=1; j<=18; j++)
		{
			if((1<<j) & move[i])
			{
				tmp[k ++] = A[j].x;
				A[j].x = 0;
			}
		}
		A[0].x -= k;
		v = -maxmin(B, A, depth-1, k, tmp[0]);
		A[0].x += k;
		k = 0;
		for(j=1; j<=18; j++)
		{
			if((1<<j) & move[i])
			{
				A[j].x = tmp[k ++];
			}
		}
		if(v == 1)
		{
			if(depth == DEPTH)
			{
				for(j=1; j<=18; j++)
				{
					if((1<<j) & move[i])
					{
						printf("[%c %d]\t", A[j].x, A[j].y);
					}
				}
				puts("");
			}
			return v;
		}
		if(v == 0) best = 0;
	}
	if(flag && DEPTH != depth)
	{
		v = -maxmin(B, A, depth-1, 0, 0);
		if(v == 1)
		{
			if(depth == DEPTH)
			{
				for(j=1; j<=18; j++)
				{
					if((1<<j) & move[i])
					{
						printf("[%c %d]\t", A[j].x, A[j].y);
					}
				}
				puts("");
			}
			return v;
		}
		if(v == 0) best = 0;
	}
	return best;
}
int main(void)
{
	int i;
	int v;
	init();
	//for(DEPTH=63; DEPTH<64; DEPTH++)
	DEPTH = 63;
	{
		v = maxmin(lisB, lisA, DEPTH, 0, 0);
		for(i=1; i<=18; i++)
		{
			printf("%d ", lisB[i].x);
		}
		puts("");
		printf("depth:%d v=%d\n", 63-dmax, v);
		//if(v) break;
	}
	system("pause");
	return 0;
}
