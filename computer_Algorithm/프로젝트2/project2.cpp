#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "stdafx.h" 솔루션파일 만들때 설정때문에 추가되는 것 같습니다.
#include "DGIBox.h"
#define BUCKET_NUM 151552  //DGIBox의 bucket의 총 개수이다.
#define SLOT_NUM 128	//DGIBox에서 각 bucket마다의 index의 수이다.
#define MAX_KEY 16777215	//인풋으로 들어오는 key의 최대값이다.




/*
computer algorithm project2
201511058 김태연

main함수 구현은 project1과 거의 동일한 방법으로 하였습니다.
*/


//dictionary algorithm에 필요한 array들
int ary[MAX_KEY + 1][2] = {0};    //dictionary algorithm에서 사용되는 bucket_id와 index를 저장해주는 array
int count[BUCKET_NUM] = { 0 };	  //dictionary algorithm에서 각 bucket마다의 유의미한 정보의 수를 저장해주는 array
int checker[BUCKET_NUM * SLOT_NUM] = { 0 };	  //dictionary algorithm에서 각 버킷들의 주소에 대응되는 key를 저장해주는 array
//operation 수를 저장해주기 위한 변수들
int set_count = 0;  //Set operation의 횟수를 세어주는 변수  (총 횟수를  세어주는 역할)
int set_count1 = 0;	//Set operation의 횟수를 세어주는 변수  (marker마다 수를 세어주고 다시 0으로 초기화해주는 변수) 
//set_count의 경우는 중간에 전역변수가 이상하게 바뀌는 경우가 생겨서 그 원인을 찾지는 못했고, 중간중간 계속 초기화를 해주었습니다.
int get_count = 0;	//Get operation의 횟수를 세어주는 변수
int empty_count = 0;	//Empty operation의 횟수를 세어주는 변수
int marker = 0;	//main함수에서 count의 수를 print해주기 위한 마커
//ty algorithm에 필요한 array들
char counts[BUCKET_NUM] = { 0 };	//각 bucket에 대해서 몇개가 차있는지 저장해주는 array
char jadress[MAX_KEY + 1] = { 0 };	//각 key값들에 대해서 key값에 해당되는 index를 저장해주는 array

// hash algorithm에서의 cleaning 과정
void cleaning_hash(int i, int j, int v)   //cleaning이 일어나야하는 주소값과, 그 자리에 들어갈 value를 input으로 받는다.
{
	int* temp = new int[SLOT_NUM];  //cleaning을 해주기 전에, 필요한 정보들을 저장해줄 array를 동적할당해준다.
	for (int k = 0; k < SLOT_NUM; ++k)
	{
		temp[k] = -1;	//value의 값이 0이 될 수도 있기 때문에 모두 -1로 초기화를 해준다.
	}
	for (int k = 0; k < SLOT_NUM; ++k)
	{
		int value = Get(i, k);
		get_count++;
		if (value != -1)
		{
			temp[k] = value;	//Get을 한 결과가 -1이 아니면, 즉, 어떠한 정보가 저장이 되어있다면 그 값을 동적할당해준 array의 같은 index 주소에 저장해준다.
		}
	}
	temp[j] = v;	//새로 넣어줘야 하는 값 역시 동적할당해준 array에 마지막으로 업데이트해준다.
	Empty(i);	//bucket을 모두 지워준다.
	empty_count++;
	for (int k = 0; k < SLOT_NUM; ++k)
	{
		if (temp[k] != -1)
		{
			Set(i, k, temp[k]);	//temp의 k값이 버킷에서의 원레의 index 주소와 같았었으므로, k에 대해서 순서대로 다시 Set operation을 해준다.
			set_count1++;
		}
	}
	delete[] temp;	//동적할당해준 메모리를 지워준다.
}

// hash algorithm에서의 write 과정
void w_hash(int k, int v)
{
	int i = k / SLOT_NUM;
	int j = k % SLOT_NUM;
	int check = Set(i, j, v);	//hash function에 맞춰서 value를 Set에 넣어준다.
	set_count1++;
	if (check == 0)  //Set이 정상적으로 되지 않은 경우는 cleaning을 해준다.
	{
		cleaning_hash(i, j, v);
	}
}

//hash algorithm에서의 read 과정
int r_hash(int k)
{
	int i = k / SLOT_NUM;
	int j = k % SLOT_NUM;
	get_count++;
	return Get(i, j);   //key값을 hash function에 대입하여 bucket의 주소값을 구한 후에 Get을 해준다.
}

//dictionary algorithm에서의 cleaning 과정
void cleaning_dic(int bucket, int smallest)	//cleaning을 해줄 bucket과, 그 bucket에서 의미있는 정보의 수를 input으로 받는다.
{
	int* memory = new int[SLOT_NUM];	//cleaning을 해주기 위해 value값을 저장해줄 array를 동적할당해준다.
	int* memory1 = new int[SLOT_NUM];	//cleaning을 해주기 위해 key값을 저장해줄 array를 동적할당해준다.
	int l = 0;
	int z = bucket*SLOT_NUM;	//checker array에서 cleaning을 해줄 key값들을 뽑아주기 위한 index의 시작점을 변수로 선언한다.
	for (int g = 0; g < SLOT_NUM; ++g)
	{
		if (checker[z] != -1)	//cheker를 확인해서, 유의미한 정보가 있을 경우에만 이에 해당되는 value와 key값을 각각 저장해준다.
		{
			int a = checker[z];
			memory[l] = Get(bucket, ary[a][1]);
			memory1[l] = a;
			get_count++;
			ary[a][1] = l;	//dictionary에 새로운 index 주소를 업데이트해준다.
			l++;
		}
		z++;
	}
	z = bucket*SLOT_NUM;
	for (int g = 0; g < SLOT_NUM; ++g)
	{
		checker[z] = -1;	//cleaning을 하기 전에 chekcer의 bucket에 해당되는 부분을 모두 -1로 다시 초기화해준다.
		++z;
	}
	Empty(bucket);	//bucket을 모두 지워준다.
	empty_count++;
	for (int z = 0; z < smallest; ++z)	//다시 순서대로 Set울 해주면서 checker를 업데이트해준다.
	{
		Set(bucket, z, memory[z]);
		int b = bucket*SLOT_NUM + z;
		checker[b] = memory1[z];
		set_count1++;
	}
	delete[] memory;
	delete[] memory1;	//동적할당해준 모든 메모리를 초기화해준다.
}

//dictionary algorithm에서의 write 과정
void w_dic(int k, int v)
{
	static int i = 0;	//dictonary에서 bucket_id를 순서대로 넣어주기 위해 처음에만 0으로 초기화를 해준다.
	static int j = 0;	//dictonary에서 index를 순서대로 넣어주기 위해 처음에만 0으로 초기화를 해준다.
	static int q = 0;	//cleaning이 한 번 된 이후에는 조금 다르게 동작하여야 하기 때문에 이를 위한 marker를 하나 넣어준다.
	if (i == BUCKET_NUM - 1 && j == SLOT_NUM)	//bucket에 순서대로 모두 채워놓고 bucket이 모두 찼을때 cleaning을 해주기 위한 조건문을 실행한다.
	{
		int smallest = count[0];
		int small_index = 0;
		for (int z = 0; z < BUCKET_NUM; ++z)	//cleaning을 할 때, 가장 유의미한 정보가 적은 bucket만을 cleaning해주는 것이 효율적이므로, 유의미한 정보가 가장 적은 bucket을 찾아준다.
		{
			if (count[z] <= smallest)
			{
				smallest = count[z];
				small_index = z;
			}
		}
		cleaning_dic(small_index, smallest);	//cleaning을 해주면, value가 들어갈 bucket에 무의미한 정보를 모두 지워준다.
		i = small_index;
		j = smallest;
		if (ary[k][0] != -1)	//key가 overwrite되는 경우라면 유의미한 정보의 개수에 대한 count와 key값의 주소를 저장해주는 checker를 조정해준다.
		{
			int t = ary[k][0];
			count[t]--;
			int t1 = ary[k][1];
			int ny = t * SLOT_NUM + t1;
			checker[ny] = -1;
		}
		Set(i, j, v);	//cleaning해준 다음 자리에 value를 넣어준다.
		int ny = i * SLOT_NUM + j;
		checker[ny] = k;	//checker에 key값을 저장해준다.
		set_count1++;
		ary[k][0] = i;
		ary[k][1] = j;
		count[i]++;	//유의미한 정도의 수를 추가해준다.
		j++;
		if (j == SLOT_NUM)	//다음 index가 다시 가득찼다면 다시 cleaning을 해준다.
		{
			i = BUCKET_NUM - 1;
			j = SLOT_NUM;
		}
		q++;	//cleaning의 여부를 확인해주기 위해 cleaning의 횟수를 세어준다.
	}
	else	//cleaning을 해주지 않아도 될 때
	{
		if (set_count1 == 0 && set_count == 0)	//가장 처음에 한 번 ary와 checker를 모두 -1로 초기화시켜준다.
		{
			for (int z = 0; z < MAX_KEY + 1; ++z)
			{
				ary[z][0] = -1;
				ary[z][1] = -1;
			}
			for (int z = 0; z < BUCKET_NUM*SLOT_NUM; ++z)
			{
				checker[z] = -1;
			}
		}
		if (ary[k][0] != -1)	//key가 overwrite되는 경우라면 유의미한 정보의 개수에 대한 count와 key값의 주소를 저장해주는 checker를 조정해준다.
		{
			int t = ary[k][0];
			int t1 = ary[k][1];
			count[t]--;
			checker[t*SLOT_NUM + t1] = -1;
		}
		Set(i, j, v);
		set_count1++;
		int ny = i*SLOT_NUM + j;
		checker[ny] = k;	//set을 해준 후, key값의 정보를 저장한다.
		ary[k][0] = i;
		ary[k][1] = j;
		count[i]++;	//set을 해준 후, bucket에서 유의미한 값의 수에 대한 정보를 저장한다.
		j++;
		if ( j == SLOT_NUM && i == BUCKET_NUM - 1)	//bucket이 모두 차면 cleaning을 위한 조건문으로 들어간다.
		{
			j = SLOT_NUM;
		}
		else if (j == SLOT_NUM && q == 0)	//하나의 bucket이 다 차면 다음 bucket으로 넘어간다.
		{
			j = 0;
			i++;
		}
		else if (j == SLOT_NUM && q != 0)	//cleaning을 한 번 한 이후는 bucket이 다 차면 무조건 cleaning을 위한 조건문으로 들어간다.
		{
			i = BUCKET_NUM - 1;
			j = SLOT_NUM ;
		}
	}
}

//dictionary algorithm에서의 read 과정 
int r_dic(int k)
{
	int a = ary[k][0];
	int b = ary[k][1];
	get_count++;
	return Get(a, b);	//key값에 대한 dictionary에 저장되어있는 주소를 통해서 get을 해준다.
}

//ty algorithm에서의 write 과정
void w_ty(int k, int v)
{
	int i = k % BUCKET_NUM;	//hash function으로 key값을 bucket_id로 mapping시켜준다.
	if (set_count == 0 & set_count1 == 0)	//가장 처음으로 실행될 때만 jadress라는 array를 모두 -1로 초기화시켜준다.
	{
		for (int z = 0; z < MAX_KEY + 1; ++z)
		{
			jadress[z] = -1;
		}
	}
	if (counts[i] == SLOT_NUM - 1)	//set을 해줘야 하는 bucket에 대해서 그 bucket이 모두 가득 차있을 때 cleaning의 과정을 해준다.
	{
		int ty = i;	//해당 bucket에 해당되는 key들을 확인해주기 위해서 bucket_id에 해당되는 값을 복사해준다.
		int l = 0;
		counts[i] = 0;
		int* mem = new int[SLOT_NUM];	//cleaning을 하게 위해 임시 메모리를 동적할당해준다.
		while (ty <= MAX_KEY)	//해당 bucket에 대해서 그 안에 어떤 값이 있으면 mem이라는 array에 복사해준다.
		{
			int j1 = jadress[ty];
			if (j1 != -1)
			{
				int h = Get(i, j1);
				get_count++;
				mem[l] = h;
				jadress[ty] = l;	//jadress array를 갱신해준다.
				l++;
			}
			ty = ty + BUCKET_NUM;
		}
		Empty(i);	//bucket을 모두 지워준다.
		empty_count++;
		for (int z = 0; z < l; z++)
		{
			Set(i, z, mem[z]);	//저장된 메모리를 이용해서 다시 순서대로 Set을 해준다.
			set_count1++;
			counts[i]++;
		}
		delete[] mem;	//동적할당시킨 array를 반환해준다.
		int j = counts[i];
		Set(i, j, v);	//cleaning하고 생긴 다음 빈 자리에 set을 해준다.
		set_count1++;
		jadress[k] = j;	//index주소를 저장해준다.
		counts[i]++;
	}
	if (counts[i] != SLOT_NUM - 1)	//cleaning이 필요 없는 경우는 그냥 mapping된 bucket에 대해 순서대로 set을 하고, 그 주소를 저장해준다.
	{
		int j = counts[i];
		Set(i, j, v);
		set_count1++;
		jadress[k] = j;
		counts[i]++;
	}
}

//ty algorithm에서의 read과정
int r_ty(int k)
{
	int i = k % BUCKET_NUM;	//hash function으로 bucket_id를 mapping해준다.
	int j = jadress[k];	//저장된 정보를 통해서 index주소를 불러온다.
	get_count++;
	return Get(i, j);
}

void show_menu()
{
	printf("******************************\n");
	printf("hash_trace_check            1\n");
	printf("dic_trace_check             2\n");
	printf("ty_trace_check              3\n");
	printf("Show_menu                   4\n");
	printf("Exit                        5\n");
	printf("******************************\n");
}

// main함수는 project1과 같은 방식으로 trace파일을 인풋으로 받도록 구현하였습니다.
int main(int argc, char *argv[])
{
	if (argc != 2)  // 입력 형식이 맞지 않은 경우
	{
		fputs("제대로된 입력을 해주세요.\n", stderr);
		return 1;
	}
	if (!fopen(argv[1], "rt"))   // 경로에 해당되는 파일이 없는 경우
	{
		printf("파일이 없습니다.\n");
		return 1;
	}

	int len = -1;   // bin가 아닌 다른 형식의 file을 input으로 받은 경우
	while (argv[1][++len] != 0);
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'b' || argv[1][len - 2] != 'i' || argv[1][len - 1] != 'n')
	{
		printf("규격에 맞는 파일이 아닙니다.\n");
		return 1;
	}

	printf("Input File : %s\n", (argv[1])); //입력 파일명 출력

	int store_set[10];	//hash의 경우는 21억이 넘는 integer의 저장이 필요해서 array로 저장을 해준다.
	int store_get[10];	//hash의 경우는 21억이 넘는 integer의 저장이 필요해서 array로 저장을 해준다.
	int store_empty[10];	//hash의 경우는 21억이 넘는 integer의 저장이 필요해서 array로 저장을 해준다.
	int set_num;
	int get_num;
	int empty_num;
	int wrong;
	int c;
	int x;
	int write_count;
	int read_count;
	char wr;
	int key;
	int value;

	show_menu();

	while (1)
	{
		for (int z = 0; z < 10; ++z)
		{
			store_set[z] = 0;
			store_get[z] = 0;
			store_empty[z] = 0;
		}
		// switch문 이전에 항상 초기화를 해준다.
		set_num = 0;
		get_num = 0;
		empty_num = 0;
		wrong = 0;
		c = 0;
		write_count = 0;
		read_count = 0;
		get_count = 0;
		set_count = 0;
		set_count1 = 0;
		empty_count = 0;
		marker = 0;
		FILE* f = fopen(argv[1], "rb");
		FILE* fi = fopen("hash check.txt", "a");
		FILE* fii = fopen("dic check.txt", "a");
		FILE* ffi = fopen("ty check.txt", "a");
		InitDGIBox();
		checker_init(argv[1]);
		printf("Select : ");
		if (scanf("%d", &x) == 1)
		{
			switch (x)
			{
			case 1:
				printf("############trace hash check start!#############\n");
				//While문이 binary파일을 읽어서 w나 r를 실행시켜주는 역할을 한다.
				while (fread(&wr, 1, 1, f))
				{
					if (wr == 'w')
					{
						fread(&key, 4, 1, f);
						fread(&value, 4, 1, f);
						w_hash(key, value);
						write_count++;
					}
					else
					{
						fread(&key, 4, 1, f);
						r_hash(key);
						read_count++;
					}
					next();

					//1000000번에 한 번씩 check를 해준다.
					if (marker % 1000000 == 0)
					{
						c = check();
						if (c == 0)
						{
							printf("Somthing worng\n");
							wrong++;
						}

					}
					//1000000번에 한 번씩 operation의 수를 print해준다.
					if (marker == 1000000)
					{
						set_count = set_count + set_count1;	//set_count의 경우는 전역변수가 중간에 이상하게 바뀌는 문제땜문에 하나의 과정을 추가해주었다.
						//각각이 2000000000보다 커지면 저장을 해주고 다시 초기화를 하여 0부터 counting을 해준다.
						if (set_count > 2000000000)
						{
							store_set[set_num] = set_count;
							set_count = 0;
							set_num++;
						}
						if (get_count > 2000000000)
						{
							store_get[get_num] = get_count;
							get_count = 0;
							get_num++;
						}
						if (empty_num > 2000000000)
						{
							store_empty[empty_num] = empty_count;
							empty_count = 0;
							empty_num++;
						}
						printf("number of set: %d ", set_count);
						set_count1 = 0;
						printf(" number of get: %d ", get_count);
						printf(" number of empty: %d\n", empty_count);
						marker = 0;
					}
					marker++;
				}
				// text파일에 실행결과를 저장해준다.
				fprintf(fi, argv[1]);
				fprintf(fi, "\n");
				fprintf(fi, "number of set: ");
				fprintf(fi, "%d ", set_count);
				if (store_set[0] != 0)
				{
					for (int z = 0; z < set_num; ++z)
						fprintf(fi, "%d ", store_set[z]);
				}
				fprintf(fi, "\n");
				fprintf(fi, "number of get: ");
				fprintf(fi, "%d ", get_count);
				if (store_get[0] != 0)
				{
					for (int z = 0; z < get_num; ++z)
						fprintf(fi, "%d ", store_get[z]);
				}
				fprintf(fi, "\n");
				fprintf(fi, "number of empty: %d ", empty_count);
				if (store_empty[0] != 0)
				{
					for (int z = 0; empty_num < 10; ++z)
						fprintf(fi, "%d ", store_empty[z]);
				}
				fprintf(fi, "\n");
				fprintf(fi, "number of wrong(per 1000000): %d\n", wrong);
				fprintf(fi, "number of wirte operation: %d\n", write_count);
				fprintf(fi, "number of read operation: %d\n", read_count);
				closeDGIBox();
				fclose(f);
				fclose(fi);
				fclose(fii);
				fclose(ffi);
				break;

			case 2:
			// case1과 모두 같게 동작이 되며, dic에 대한 확인을 해준다.
				printf("############trace dic check start!#############\n");
				while (fread(&wr, 1, 1, f))
				{
					if (wr == 'w')
					{
						fread(&key, 4, 1, f);
						fread(&value, 4, 1, f);
						w_dic(key, value);
						write_count++;
					}
					else
					{
						fread(&key, 4, 1, f);
						r_dic(key);
						read_count++;
					}
					next();

					//check를 해주는 부분이다.
					if (marker % 1000000 == 0)
					{
						c = check();
						if (c == 0)
						{
							printf("Somthing worng\n");
							wrong++;
						}

					}
					if (marker == 1000000)
					{
						set_count = set_count + set_count1;
						if (set_count > 2000000000)
						{
							store_set[set_num] = set_count;
							set_count = 0;
							set_num++;
						}
						if (get_count > 2000000000)
						{
							store_get[get_num] = get_count;
							get_count = 0;
							get_num++;
						}
						if (empty_num > 2000000000)
						{
							store_empty[empty_num] = empty_count;
							empty_count = 0;
							empty_num++;
						}
						printf("number of set: %d ", set_count);
						set_count1 = 0;
						printf(" number of get: %d ", get_count);
						printf(" number of empty: %d\n", empty_count);
						marker = 0;
					}
					marker++;
				}
				fprintf(fii, argv[1]);
				fprintf(fii, "\n");
				fprintf(fii, "number of set: ");
				fprintf(fii, "%d ", set_count);
				if (store_set[0] != 0)
				{
					for (int z = 0; z < set_num; ++z)
						fprintf(fii, "%d ", store_set[z]);
				}
				fprintf(fii, "\n");
				fprintf(fii, "number of get: ");
				fprintf(fii, "%d ", get_count);
				if (store_get[0] != 0)
				{
					for (int z = 0; z < get_num; ++z)
						fprintf(fii, "%d ", store_get[z]);
				}
				fprintf(fii, "\n");
				fprintf(fii, "number of empty: %d ", empty_count);
				if (store_empty[0] != 0)
				{
					for (int z = 0; empty_num < 10; ++z)
						fprintf(fii, "%d ", store_empty[z]);
				}
				fprintf(fii, "\n");
				fprintf(fii, "number of wrong(per 1000000): %d\n", wrong);
				fprintf(fii, "number of wirte operation: %d\n", write_count);
				fprintf(fii, "number of read operation: %d\n", read_count);
				closeDGIBox();
				fclose(f);
				fclose(fi);
				fclose(fii);
				fclose(ffi);
				break;

			case 3:
			//case1과 똑같이 작동하며, ty 알고리즘을 확인해주는 부분이다.
				printf("############trace ty check start!#############\n");
				while (fread(&wr, 1, 1, f))
				{
					if (wr == 'w')
					{
						fread(&key, 4, 1, f);
						fread(&value, 4, 1, f);
						w_ty(key, value);
						write_count++;
					}
					else
					{
						fread(&key, 4, 1, f);
						r_ty(key);
						read_count++;
					}
					next();

					//check를 해주는 부분이다.
					if (marker % 1000000 == 0)
					{
						c = check();
						if (c == 0)
						{
							printf("Somthing worng\n");
							wrong++;
						}

					}
					if (marker == 1000000)
					{
						set_count = set_count + set_count1;
						if (set_count > 2000000000)
						{
							store_set[set_num] = set_count;
							set_count = 0;
							set_num++;
						}
						if (get_count > 2000000000)
						{
							store_get[get_num] = get_count;
							get_count = 0;
							get_num++;
						}
						if (empty_num > 2000000000)
						{
							store_empty[empty_num] = empty_count;
							empty_count = 0;
							empty_num++;
						}
						printf("number of set: %d ", set_count);
						set_count1 = 0;
						printf(" number of get: %d ", get_count);
						printf(" number of empty: %d\n", empty_count);
						marker = 0;
					}
					marker++;
				}
				fprintf(ffi, argv[1]);
				fprintf(ffi, "\n");
				fprintf(ffi, "number of set: ");
				fprintf(ffi, "%d ", set_count);
				if (store_set[0] != 0)
				{
					for (int z = 0; z < set_num; ++z)
						fprintf(ffi, "%d ", store_set[z]);
				}
				fprintf(ffi, "\n");
				fprintf(ffi, "number of get: ");
				fprintf(ffi, "%d ", get_count);
				if (store_get[0] != 0)
				{
					for (int z = 0; z < get_num; ++z)
						fprintf(ffi, "%d ", store_get[z]);
				}
				fprintf(ffi, "\n");
				fprintf(ffi, "number of empty: %d ", empty_count);
				if (store_empty[0] != 0)
				{
					for (int z = 0; empty_num < 10; ++z)
						fprintf(ffi, "%d ", store_empty[z]);
				}
				fprintf(ffi, "\n");
				fprintf(ffi, "number of wrong(per 1000000): %d\n", wrong);
				fprintf(ffi, "number of wirte operation: %d\n", write_count);
				fprintf(ffi, "number of read operation: %d\n", read_count);
				closeDGIBox();
				fclose(f);
				fclose(fi);
				fclose(fii);
				fclose(ffi);
				break;

			case 4:
				show_menu();
				break;

			case 5:
				fclose(f);
				fclose(fi);
				fclose(fii);
				fclose(ffi);
				return 0;

			default:
				printf("해당되는 번호만 입력해주시기 바랍니다.\n");  //1~8외의 다른 숫자를 입력했을 경우
				break;
			}
		}
		else
		{
			while (getchar() != '\n');
			printf("해당되는 번호만 입력해주시기 바랍니다.\n");  //숫자가 아닌 다른 문자를 입력했을 경우
			continue;
		}
	}
	return 0;
}