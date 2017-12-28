# include <iostream>
#include <vector>
#include <algorithm> 
#include <utility>
using namespace std;

void quickSort(vector<int>& list, vector<int>& list1, vector<int>& list2, int l, int count) //정렬의 시작점을 나타내는 l은  0으로 시작한다.
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
				swap(list[p], list[q]);
				swap(list1[p], list1[q]);
				swap(list2[p], list2[q]);
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
		swap(list[l], list[p - 1]);
		swap(list1[l], list1[p - 1]);
		swap(list2[l], list2[p - 1]);
		quickSort(list, list1, list2, l, p - 1);   // 더욱 작아진 부분들에 대해서 재귀적으로 위의 과정을 반복한다.
		quickSort(list, list1, list2, p, count);
	}
}

int main()
{
	int tmp = 0;
	int com_num;
	cin >> com_num;
	int max_line;
	cin >> max_line;
	vector<int> first_u;
	vector<int> second_u;
	vector<int> cost;
	first_u.reserve(max_line);
	second_u.reserve(max_line);
	cost.reserve(max_line);

	for (int i = 0; i < max_line; ++i)
	{
		int f;
		int s;
		int c;
		cin >> f;
		cin >> s;
		cin >> c;
		first_u.push_back(f);
		second_u.push_back(s);
		cost.push_back(c);
	}

	vector<vector<int>> Set;
	Set.reserve(com_num);
	for (int i = 0; i < com_num; ++i)
	{
		vector<int> temp;
		temp.push_back(i + 1);
		Set.push_back(temp);
		temp.clear();
	}

	quickSort(cost, first_u, second_u, 0, cost.size());
	int answer = 0;

	for (int i = 0; i < max_line; ++i)
	{
		int start = first_u[i];
		int end = second_u[i];
		int start_check;
		int end_check;
		for (int j = 0; j < Set.size(); ++j)
		{
			vector<int> abc = Set[j];
			vector<int> ::iterator it1;
			vector<int> ::iterator it2;
			it1 = find(abc.begin(), abc.end(), start);
			it2 = find(abc.begin(), abc.end(), end);
			if (it1 != abc.end())
				start_check = j;
			if (it2 != abc.end())
				end_check = j;
		}
		if (start_check != end_check)
		{
			answer = answer + cost[i];
			vector<int> for_merge = Set[end_check];
			for (int j = 0; j < for_merge.size(); ++j)
			{
				Set[start_check].push_back(for_merge[j]);
			}
			Set.erase(Set.begin() + end_check);
			//cout << answer << endl;
		}
		
	}
	cout << answer;
	//system("pause");
	return 0;
}