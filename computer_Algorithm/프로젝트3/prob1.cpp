#include <iostream>
using namespace std;

int main()
{
	int max_weight;
	cin >> max_weight;
	int max_num;
	cin >> max_num;
	int* weight = new int[max_num];
	int* value = new int[max_num];
	for (int i = 0; i < max_num; ++i)
	{
		int w;
		int b;
		cin >> w;
		cin >> b;
		weight[i] = w;
		value[i] = b;
	}
	int B[1001][1001] = { 0 };

	for (int w = 1; w <= max_weight; ++w)
	{
		for (int i = 0; i < max_num; ++i)
		{
			if (weight[i] <= w)
			{
				int a = w - weight[i];
				if (value[i] + B[a][i] > B[w][i])
				{
					B[w][i + 1] = value[i] + B[a][i];
				}
				else
				{
					B[w][i + 1] = B[w][i];
				}
			}
			else
			{
				B[w][i + 1] = B[w][i];
			}
		}
	}
	int result = B[max_weight][max_num];
	cout << result;
	delete[] weight;
	delete[] value;
	return 0;
}