#include <iostream>

using namespace std;

void swap(int* a, int* b)  //pointer의 두 값을 바꿔주는 swap함수를 따로 구현했다.
{
	int t = *a;
	*a = *b;
	*b = t;
}

void quickSort_Op(int* list, int l, int count) //정렬의 시작점을 나타내는 l은  0으로 시작한다.

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

int main() 
{

    int number;
    cin >> number;
    
    int* people = new int[number];
    
    for(int i = 0; i < number; ++i){
        int waiting_time;
        cin >> waiting_time;
        people[i] = waiting_time;
    }
    
    quickSort_Op(people, 0, number);
    
    int* min_time = new int[number];
    min_time[0] = people[0];
    for (int i = 1; i < number; ++i)
    {
        min_time[i] = min_time[i - 1] + people[i];
    }
    int result = 0;
    for (int i = 0; i < number; ++i)
    {
        result = result + min_time[i];
    }
    delete[] people;
    delete[] min_time;
    cout << result;
    return 0;
}