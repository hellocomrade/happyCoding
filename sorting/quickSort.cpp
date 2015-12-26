#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void insertSort(vector<T> &A)
{
	int len = A.size();
	int j, k = 0, tmp = 0;
	for (int i = 1; i < len; ++i)
	{
		k = A[i];
		for (j = i; j > 0 && A[j - 1] > k; --j)
			A[j] = A[j - 1];
		A[j] = k;
	}
}
#define COMBINED
const int SORT_BOUNDARY = 6;
template<typename T>
void quickSort(vector<T> &A, int low, int high)
{
#ifdef COMBINED
	if (high - low <= SORT_BOUNDARY)return;
#else
	if (low >= high)return;
#endif
	srand(time(NULL));
	int r = rand() % (high - low + 1);
	std::swap(A[low], A[low + r]);
	int p = A[low], l = low, h = high + 1;
	while (true)
	{
		do
		{
			++l;
		} while (l <= high && A[l] < p);
		do
		{
			--h;
		} while (A[h] > p);
		if (l > h)
			break;
		std::swap(A[l], A[h]);
	}
	std::swap(A[low], A[h]);
	quickSort(A, low, h - 1);
	quickSort(A, h + 1, high);
}
template<typename T>
void QuickSort(vector<T> &A, int low, int high)
{
	quickSort(A, low, high);
	insertSort(A);
}
void printSortingResult(const vector<int> &A)
{
	for (int i : A)
		cout << i << ',';
	cout << endl;
}
void testCombinedQuickSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6 });
	QuickSort(vec1, 0, vec1.size() - 1);
	printSortingResult(vec1);

	vector<int> vec2({ 1, 2, 3, 4 });
	QuickSort(vec2, 0, vec2.size() - 1);
	printSortingResult(vec2);

	vector<int> vec3({ 4, 3, 2, 1 });
	QuickSort(vec3, 0, vec3.size() - 1);
	printSortingResult(vec3);

	vector<int> vec4({ 2, 1 });
	QuickSort(vec4, 0, vec4.size() - 1);
	printSortingResult(vec4);

	vector<int> vec5({ 1 });
	QuickSort(vec5, 0, vec5.size() - 1);
	printSortingResult(vec5);

	vector<int> vec6({});
	QuickSort(vec6, 0, vec6.size() - 1);
	printSortingResult(vec6);
}
void testQuickSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6 });
	quickSort(vec1, 0, vec1.size() - 1);
	printSortingResult(vec1);

	vector<int> vec2({ 1, 2, 3, 4 });
	quickSort(vec2, 0, vec2.size() - 1);
	printSortingResult(vec2);

	vector<int> vec3({ 4, 3, 2, 1 });
	quickSort(vec3, 0, vec3.size() - 1);
	printSortingResult(vec3);

	vector<int> vec4({ 2, 1 });
	quickSort(vec4, 0, vec4.size() - 1);
	printSortingResult(vec4);

	vector<int> vec5({ 1 });
	quickSort(vec5, 0, vec5.size() - 1);
	printSortingResult(vec5);

	vector<int> vec6({});
	quickSort(vec6, 0, vec6.size() - 1);
	printSortingResult(vec6);
}
void testInsertSort()
{
	vector<int> vec1({ 8, 7, 5, 10, 2, 3, 6 });
	insertSort(vec1);
	printSortingResult(vec1);

	vector<int> vec2({ 1, 2, 3, 4 });
	insertSort(vec2);
	printSortingResult(vec2);

	vector<int> vec3({ 4, 3, 2, 1 });
	insertSort(vec3);
	printSortingResult(vec3);

	vector<int> vec4({ 2, 1 });
	insertSort(vec4);
	printSortingResult(vec4);

	vector<int> vec5({ 1 });
	insertSort(vec5);
	printSortingResult(vec5);

	vector<int> vec6({});
	insertSort(vec6);
	printSortingResult(vec6);
}