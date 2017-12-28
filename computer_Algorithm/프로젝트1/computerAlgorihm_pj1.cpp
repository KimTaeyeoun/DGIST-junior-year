#define _CRT_SECURE_NO_WARNINGS 
#include "stdafx.h"  //C++ 프로그래밍 코딩이 처음이라 잘 모르는데, 이 헤더가 없어도 잘 돌아갈 것 이라고 하는데, 제 작업환경에서는 이 헤더를 include해주라는 에러가 떠서 남겨두었습니다. 혹시 이 헤더로 인해 에러가 생기면 지우고 해도 큰 문제는 없을 것 같습니다.
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <cstdlib>

using namespace std;




/*****************************************************************
* 과목명		: Computer Algorithms
* 과목 코드	: SE380
* 담당 교수	: 조성현, 이성진 교수님
* 과제명		: Sorting Algorithms Project
* 제출 기한	: 10월 10일 23시 59분 까지
*
*
* - 과제 상세 -
* Input File Format : *.csv
* csv file ex.)
*
* 50 - List size
* 103,404,832231,32109312,32198312,.....,24 - values
*
* Input File List Size : 1000, 10000, 100000, 500000, 1000000 (학생 테스트용)
* Output File Format : sorted *.csv (Input file과 동일한 Format)
* Data Format : 4byte Integer ( Range 0 ~ 2147483647 )
* OS : Windows
* Tools : Dev C++ or Visual Studio
* Program language : C/C++
* - !과제 상세 -
*
*
* - 구현 목록 -
* Main Function
* Sorting Functions :	Insertion Sort,
*						Merge Sort,
*						Heap Sort,
*						Quick Sort,
*						Optimezed Quick Sort
* File I/O Functions :	Read csv,
*						Write csv
* - !구현 목록 -
*
*
* - 코드 설명 -
* 프로그램을 main 인수와 함께 실행시키면 read_csv() 함수가 main 인수와 동일한 이름의 csv파일을 불러와 *int에 넣어줍니다.
* 파일을 불러올때 먼저 csv파일 처음에 존재하는 values의 size를 읽고 그에 맞는 memory를 *int변수에 동적 할당해줍니다.
* 그 이후 동적 할당된 메모리 영역을 memset() 함수를 통해 -1로 초기화 해줍니다.
* 초기화된 list에 csv파일의 value를 넣어줍니다.
* 사용자는 1~8번까지의 메뉴를 고를수 있습니다.
* 해당 메뉴는 아래 구현된 show_menu() 함수에서 확인 할수있습니다.
* 해당하는 번호를 입력하면 프로그램은 번호에 맞는 작동을 하게 됩니다.
* ex) 3 입력시 Heap Sort 함수가 작동하고 측정 시간 출력 및 정렬된 리스트를 write csv 함수를 통해 csv 파일로 만들어준다.
* 정렬 함수가 작동하는 부분에서는 측정시간이 출력되고 이후 정렬된 데이터를 csv파일로 만들어야 됩니다.
* 작동이 끝나게 되면 프로그램은 다시 번호 입력을 출력하고 사용자가 프로그램 종료 번호인 8번을 입력할때까지 반복한다.
* (1~8 사이의 번호가 아닌 문자열이 입력되면 에러 메세지와 함께 다시 Select 문구가 출력되어야 됩니다.)
*  - !코드 설명 -
*
*
* - 조건 -
* 본 코드는 C언어로 제작되어 있습니다. 가급적이면 c언어로 제작해주셨으면 좋겠습니다.
* 코드 작성시 꼭 주석을 달아주시기 바랍니다. 해당 부분이 어떠한 역활을 하는지 적어주시면 됩니다.
* Input File 이름은 프로그램 실행시 main의 인수로 받아와서 사용하여야 합니다.
* ex ) 정렬프로그램.exe Input.csv
* 없는 파일 이름 혹은 csv 형식이 아닐때 에러 메세지 출력후 프로그램이 종료되도록 해야합니다.
* 인수의 개수가 2개보다 많으면 오류메세지를 출력하여야 합니다.
* (main의 첫번째 인수는 프로그램의 경로가 들어가게 됩니다. 이 점 유의 해주시기 바랍니다.)
* list는 *int를 동적할당하여 활용해주시기 바랍니다.
* 동적할당한 list는 -1로 초기화하여 사용해주시기 바랍니다.
* 불러온 csv 파일 데이터를 동적할당된 list에 담아야합니다.
* 사용자에게 입력받을때 1~8에서 벗어난 숫자 혹은 문자열을 입력 받을시 에러 메세지 출력을 해주어야됩니다.
* 해당 Function의 선언에 맞게 구현해주셔야 됩니다.
* Function의 구현은 main문 밑에 있습니다.
* Output File의 이름은 바꾸지 말아주시기 바랍니다.
* - !조건 -
*
* author: InfoLab 이상현
* email	: sh_lee@dgist.ac.kr
*****************************************************************/
/****************************************************************
* -작성 정보 -
* 작성자		: 김태연
* 학번 		: 201511058
* 사용 Tool	: Visual studio 2017 (Community Version)
* 사용 언어	: C++
*
*
*
*
*****************************************************************/


/* 시간 측정 함수

clock_t t; // ms 단위 시간 측정용 변수
double sec = 0.0;
t = clock(); // clock() - 현재 시간을 받아오는 함수

func(list,count); // 구현된 정렬 함수

t = clock() - t; // 현재시간 - 함수시작전 시간
sec = ((double)t)/CLOCKS_PER_SEC;
//CLOCKS_PER_SEC = 1000

*/
/* File I/O 참고

FILE 구조체
fopen(const char *filename,const char *mode);
fscanf(FILE *stream,const char *format, ...);
fprintf(FILE *stream,const char *format, ...);


*/

/* 동적할당 및 초기화, 복사

malloc(size_t size); // 할당
memset(void *s,int c, size_t n); //초기화
memcpy(const void *to,const void *from,size_t n) //복사

*/

// 구현 해야될 정렬 함수
// int* list : 정렬될 리스트입니다. 함수가 완료되면 정렬된 list가 되어야 합니다.
// int count : 리스트의 사이즈를 나타냅니다.
void insertionSort(int* list, int count);
void mergeSort(int* list, int p, int count);
void heapSort(int* list, int count);
void quickSort(int* list, int l, int count);
void quickSort_Op(int* list, int l, int count);


// 구현해야 될 csv read write
// const char *filename : csv 파일명
// int count : 데이터 개수
// return : list
int* read_csv(const char *filename, int *count);

//int *list : csv 파일로 만들 리스트
//int count : value 개수
//const char *filename : 만들 csv 파일명
void write_csv(int *list, int count, const char *filename);


void show_menu() { // 메뉴판 
	printf("******************************\n");
	printf("Insertion Sort              1\n");
	printf("Merge Sort                  2\n");
	printf("Heap Sort                   3\n");
	printf("Quick Sort                  4\n");
	printf("Quick Sort (Optimizaion)    5\n");
	printf("Show Menu                   6\n");
	printf("Test                        7\n");
	printf("Exit                        8\n");
	printf("******************************\n");
}

//Input 파일명을 main 인수로 받아 사용한다.
int main(int argc, char *argv[])
{
	if (argc != 2)  // 입력 형식이 맞지 않은 경우
	{
		fputs("제대로된 입력을 해주세요.\n", stderr);
		exit(1);
	}
	if (!fopen(argv[1], "rt"))   // 경로에 해당되는 파일이 없는 경우
	{
		printf("파일이 없습니다.\n");
		exit(1);
	}

	int len = -1;   // csv가 아닌 다른 형식의 file을 input으로 받은 경우
	while (argv[1][++len] != 0);
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c' || argv[1][len - 2] != 's' || argv[1][len - 1] != 'v') 
	{
		printf("규격에 맞는 파일이 아닙니다.\n");
		exit(1);
	}
	int a = 0;
	int* count = &a;
	int x;
	clock_t t;
	double sec = 0.0;
	printf("Input File : %s\n", (argv[1])); //입력 파일명 출력

											


	show_menu();

	while (1) {
		int* list = read_csv(argv[1], count);  //측정을 할 때마다 list를 초기화해주기 위해서 while문 안에서 read_csv함수를 호출한다.

		printf("Select : ");
		if (scanf("%d", &x) == 1)
		{
			switch (x) {
			case 1:
				t = clock();
				insertionSort(list, *count);
				t = clock() - t;
				sec = ((double)t) / CLOCKS_PER_SEC;
				printf("%f", sec);
				printf(" sec\n");
				write_csv(list, *count, "insertionSort_output.csv");
				break;
				//시간측정
				//insertionSort 함수를 여기 넣어주세요.
				//시간측정
				//출력 파일 이름 insertionSort_output.csv 
			case 2:
				t = clock();
				mergeSort(list, 0, *count);
				t = clock() - t;
				sec = ((double)t) / CLOCKS_PER_SEC;
				printf("%f", sec);
				printf(" sec\n");
				write_csv(list, *count, "mergeSort_output.csv");
				break;
				//시간측정
				//mergeSort 함수를 여기 넣어주세요.
				//시간측정
				//출력 파일 이름 mergeSort_output.csv
			case 3:
				t = clock();
				heapSort(list, *count);
				t = clock() - t;
				sec = ((double)t) / CLOCKS_PER_SEC;
				printf("%f", sec);
				printf(" sec\n");
				write_csv(list, *count, "heapSort_output.csv");
				break;
				//시간측정
				//heapSort 함수를 여기 넣어주세요.
				//시간측정
				//출력 파일 이름 heapSort_output.csv
			case 4:
				t = clock();
				quickSort(list, 0, *count);
				t = clock() - t;
				sec = ((double)t) / CLOCKS_PER_SEC;
				printf("%f", sec);
				printf(" sec\n");
				write_csv(list, *count, "quickSort_output.csv");
				break;
				//시간측정
				//quickSort 함수를 여기 넣어주세요.
				//시간측정
				//출력 파일 이름 quickSort_output.csv 
			case 5:
				t = clock();
				quickSort_Op(list, 0, *count);
				t = clock() - t;
				sec = ((double)t) / CLOCKS_PER_SEC;
				printf("%f", sec);
				printf(" sec\n");
				write_csv(list, *count, "quickSortOp_output.csv");
				break;
				//시간측정
				//Optimezed quickSort 함수를 넣어주세요.
				//시간측정
				//출력 파일 이름 quickSortOp_output.csv

			case 6:
				show_menu();
				break;
				//메뉴판 출력
			case 7:
				//안채워넣어도 됩니다.
				printf("Hello, world!\n");
				break;
			case 8:
				printf("프로그램 종료 \n");
				exit(0);
				// 8을 입력하면 프로그램이 종료됩니다.

			default:
				printf("해당되는 번호만 입력해주시기 바랍니다.\n");  //1~8외의 다른 숫자를 입력했을 경우
				break;
			} // !switch
		}
		else {
			while (getchar() != '\n');
			printf("해당되는 번호만 입력해주시기 바랍니다.\n");  //숫자가 아닌 다른 문자를 입력했을 경우
			continue;
		}
		free(list);
	} // !while

	return 0;
} // !main

void swap(int* a, int* b)  //pointer의 두 값을 바꿔주는 swap함수를 따로 구현했다.
{
	int t = *a;
	*a = *b;
	*b = t;
}


void insertionSort(int* list, int count)  //삽입정렬
{
	int key;
	for (int j = 1; j < count; j++)
	{
		// 두번째 인덱스부터 key를 잡아주고, 하나씩 늘려가면 key의 왼쪽에는 항상 sorted된 array만 있게 되고, key를 sorted된 array에서 알맞은 위치에 하나씩 swap해주면서 넣준다.
		key = list[j];
		int i = j - 1;
		while (i >= 0 && list[i] > key)
		{
			list[i + 1] = list[i];
			i--;
		}
		list[i + 1] = key;
	}
}

void merge(int* list, int p, int q, int count) //merge sort에서 array들을 merge해주는 부분이다.
{
	int* result;
	result = (int*)malloc(sizeof(int)*(count - p));    //정렬된 결과를 저장해주는 array인 result를 동적할당해준다.
	int left_index = p;
	int right_index = q + 1;
	int i = 0;
	while (left_index <= q && right_index <= count - 1)  //left_index와 right_index중 더 작은 것을 result라는 array에 순서대로 넣어주며 merge를 해준다.
	{
		if (list[left_index] <= list[right_index])
		{
			result[i++] = list[left_index++];
		}
		if (list[left_index] > list[right_index])
		{
			result[i++] = list[right_index++];
		}
	}
	while (left_index <= q)   // left_index에 남은 value들이 있으면 순서대로 result arrray에 추가해준다.
	{
		result[i++] = list[left_index++];
	}
	while (right_index <= count - 1)  // right_index에 남은 value들이 있으면 순서대로 result array에 추가해준다.
	{
		result[i++] = list[right_index++];
	}
	int j = 0;
	while (j < i)
	{
		list[p + j] = result[j];  // 원레의 list가 sorted가 되도록 merge의 시작점부터 순서대로 result의 값을 복사해준다.
		j++;
	}
	free(result);
}

void mergeSort(int* list, int p, int count) //정렬의 시작점을 나타내는 p는 0으로 시작한다.
{
	if (p < count - 1)
	{
		int q = (p + count - 1) / 2;  //시작점과 끝점의 반을 잡아준다음에 재귀적으로 mergeSort를 한다.
		mergeSort(list, p, q + 1);
		mergeSort(list, q + 1, count);
		merge(list, p, q, count);  //stack이 쌓이면서 가장 작게 나눠진 부분부터 merge가 시작된다.
	}
}

void max_heapify(int* list, int i, int count)  //array의 특정 지점을 기준으로 heap을 만들어주는 함수이다.
{
	int l = 2 * i + 1;   // i에 대하여 left쪽의 자손의 숫자이다.
	int r = 2 * i + 2;   // i에 대하여 right쪽의 자손의 숫자이다. 
	int largest = i;
	if (l < count)
	{
		if (list[l] > list[largest])
		{
			largest = l;    // left son이 i보다 크면 largest를 바꿔준다.
		}
	}
	if (r < count)
	{
		if (list[r] > list[largest])   // right son이 largest보다 크면 largest를 바꿔준다.
		{
			largest = r;
		}
	}
	if (largest != i)    // loop를 돈 결과, largest가 바뀌었으면 그 위치를 swap해주고, 바뀐 son에 대해서 같은 과정을 반복해준다.
	{
		swap(&list[i], &list[largest]);
		max_heapify(list, largest, count);
	}
}

void build_max_heap(int* list, int count)   //array전체를 heap으로 만들어주는 함수이다.
{
	for (int i = (count - 1) / 2; i >= 0; i--)  //최초로 자손이 있는 지점부터 시작하여 heap을 만족하는 배열을 만들어준다.
	{
		max_heapify(list, i, count);
	}
}

void heapSort(int* list, int count)    // 가장 첫번째의 최댓값을 맨 뒤의 숫자와 바꿔주며 heap을 재귀적으로 만들어주어 정렬한다.
{
	build_max_heap(list, count);
	for (int i = count - 1; i > 0; i--)
	{
		swap(&list[0], &list[i]);
		count--;
		max_heapify(list, 0, count);
	}
}

void quickSort(int* list, int l, int count) //정렬의 시작점을 나타내는 l은  0으로 시작한다.
{
	if (count > l)
	{
		int pivot = list[l];  //가장 왼쪽의 index를 pivot으로 잡아준다.
		int p = l + 1;
		int q = count - 1;
		while (p <= q)  //partition이라는 함수를 만드는 대신, partition의 역할을 하는 while문을 사용하였다.
		{
			if (list[p] > pivot && list[q] < pivot)  //left side와 right side를 비교하여 위치가 역전되어 있을 경우에 swap을 해준다.
			{
				swap(&list[p], &list[q]);
			}
			else if (list[p] <= pivot)  //left side에 pivot보다 작은 값이 있으면 left side의 pointer를 오른쪽으로 한 칸 이동시킨다.
			{
				++p;
			}
			else if (list[q] >= pivot)  //right side에 pivot보다 큰 값이 있으면 right side의 pointer를 왼쪽으로 한 칸 이동시킨다.
			{
				--q;
			}
		}
		swap(&list[l], &list[p - 1]);  //pivot과 left index, right index의 경계지점을 swap해준다.
		quickSort(list, l, p - 1);   // 더욱 작아진 부분들에 대해서 재귀적으로 위의 과정을 반복한다.
		quickSort(list, p, count);
	}
}

void quickSort_Op(int* list, int l, int count) //정렬의 시작점을 나타내는 l은  0으로 시작한다.
{
{
	if (count - l <= 50)  //array의 크기가 작은 경우에는, 재귀적으로 quicksort를 하지 않고, 삽입정렬으로 정렬을 해준다.
	{
		//기존 알고리즘에 시작점이 추가되어, insertion_sort(list, l, count)의 역할로, 함수로 호출하는 대신 조건문 안에 직접 코드를 작성해주었다.
		int key;
		for (int j = 1 + l; j < count; j++)
		{
			key = list[j];
			int i = j - 1;
			while (i >= 0 && list[i] > key)
			{
				list[i + 1] = list[i];
				i--;
			}
			list[i + 1] = key;
		}
	}
	else
	{
		int c = (l + count) / 2;    //시작점과 끝점, 가운대 지점에 대해서 3개를 크기 순서대로 바꾸어 준다.
		if (list[l] <= list[c])
		{
			if (list[count - 1] <= list[l])
			{
				swap(list+count - 1, list+l);
				swap(list+count - 1, list+c);
			}
			else if (list[count - 1] <= list[c])
			{
				swap(list+count - 1, list+c);
			}
		}
		else if (list[count - 1] >= list[l])
		{
			swap(list+c, list+l);
		}
		else if (list[c] >= list[count - 1])
		{
			swap(list+l, list+count - 1);
		}
		else
		{
			swap(list+l, list+c);
			swap(list+count - 1, list+c);
		
		}
		swap(list+c, list+l + 1);  // 가운데값을 pivot으로 해주기 위해서 정렬된 값에서 첫번째 값과 가운데 값을 swap해준다.
		// 위에서 바꾸어준 세개의 값 중 가운데 값을 pivot으로 써주며, 이 때 첫번째값과 마지막값은 pivot에 대해 정렬이 되어 있으므로 l + 2와 count - 1의 index부터 sorting을 해준다.
		int pivot = list[l + 1];
		int p = l + 2;
		int q = count - 2;
		while (p <= q)
		{
			if (list[p] > pivot && list[q] < pivot)
			{
				swap(list+p, list+q);
			}
			else if (list[p] <= pivot)
			{
				++p;
			}
			else if (list[q] >= pivot)
			{
				--q;
			}
		}
		swap(list+l + 1, list+p - 1);
		if (p > l + 2)  //함수를 한 번 더 재귀적으로 호출하고 멈추는 것 보다는, 조건문으로 함수를 호출할 필요가 없을 때는 호출을 하지 않도록 해 주었다.
		{
			quickSort_Op(list, l, p - 1);
		}
		if (q < count - 2)
		{
			quickSort_Op(list, p, count);
		}
	}
}

// FILE *fp : 불러온 csv 파일 
// int *count : 

int* read_csv(const char *filename, int* count)
{
	FILE* fp = fopen(filename, "rt");
	fscanf(fp, "%d,", count);
	int* list = (int*)malloc(sizeof(int)* (*count));
	memset(list, -1, *count);
	int i = -1;
	int r;
	for (int j = 0; j < (*count); ++j)
	{
		r = fscanf(fp, "%d,", &list[j]);
	}
	fclose(fp);
	return list;
}

void write_csv(int *list, int count, const char *filename) {
	FILE *fp;
	fp = fopen(filename, "wt");
	fprintf(fp, "%d\n", count);
	for (int i = 0; i < count; ++i)
	{
		fprintf(fp, "%d,", list[i]);
	}
	fclose(fp);
}