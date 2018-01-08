#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

//https://leetcode.com/problems/longest-increasing-subsequence/
/*
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

Observation:
Length of Longest Increasing Subsequence is a classic DP problem. It can be solved in O(N^2) using DP.
The max LIS length at index i is stored at memo[i], when index k is reached, every elements with index j in memo satisfis:
j < k && nums[j] < nums[k],
has to be examined so we can find the max LIS length at index i.
During this process, we will keep tracking maxLen in a separate variable due to the fact that the max LIS is not always
in memo[len - 1].

There is actually a weird algorithm that can solve this problem in O(NlogN) using O(1) space!
It takes advantage of binary search. The amazing thing is that the sequence BS is applied on is built
on the fly and in place of nums! What's more interesting is that the elements stored in nums for BS purpose
doesn't have any meaning other than maintaining the position of tail.

OK, finally, I came with my version that takes O(1) space and run in O(N) time and keep tracking the LIS in place
nums[0 -- maxLen - 1]
We use nums as the place to keep tracking the clue, which is:

nums[i] represents the smallest largest element in a LIS with size of i. So nums[2] means the LIS is 2, if
we have [1,10] and [1,3], nums[2] = 3. By doing so, we leave the most generous (greedy) option for the further down
elements in nums[j], given j >= maxLen. Say nums[3] = 4, by searching nums[2], we will get a new LIS with size of 3, which is
not possible if we leave nums[2] = 10.

Since nums[i], given i in [0, maxLen - 1], is a monotonic sequence (increasing). We can find the element just smaller than nums[k] using
binary search. There should not be any duplicated value in this mono seq, any binary search shold work. I
use lower_bound here to get the element that is no less than nums[k]:
1. If all elements in nums[i], given i in [0, maxLen - 1], are smaller than nums[k], we get a longer LIS,
so, maxLen++;

2. If returned index j from BS is from 0 to maxLen - 1 and nums[k] < nums[j], we know for LIS with size of j,
we have a smaller ending element nums[k]. Then we update the nums[j] = nums[k];
*/
class SolutionLongestIncreasingSubsequence {
public:
	//O(NlogN) with O(1) space
	int lengthOfLIS(vector<int>& nums) {
		int ans = 0;
		for (int i : nums) {
			auto itor = std::lower_bound(nums.begin(), nums.begin() + ans, i);
			*itor = i;
			ans = std::max(ans, (int)(itor - nums.begin()) + 1);
		}
		return ans;
	}
	//O(NlogN) with O(N) space. This is useful if input vector is const
	int lengthOfLIS4(vector<int>& nums) {
		vector<int> vec;
		for (int i : nums) {
			auto itor = std::lower_bound(vec.begin(), vec.end(), i);
			if (itor == vec.end())vec.push_back(i);
			else *itor = i;
		}
		return static_cast<int>(vec.size());
	}
	//O(NlogN) with O(1) space
	int lengthOfLIS3(vector<int>& nums) {
		int len = nums.size();
		if (0 == len)return 0;
		int maxLen = 1;
		auto begin = nums.begin();
		for (int i = 1; i < len; ++i)
		{
			auto ret = std::lower_bound(begin, begin + maxLen, nums[i]);
			if (ret == begin + maxLen)//maxLen + 1
				*(begin + maxLen++) = nums[i];
			else if (nums[i] < *ret)
				*ret = nums[i];
		}
		return maxLen;
	}
	//O(NlogN) with O(1) space
	int lengthOfLIS2(vector<int>& nums) {
		int len = nums.size();
		auto begin = nums.begin();
		//tail is used to track the end of the work array, which is nums
		//(tail - begin) is the length of the longest increase subsequence
		auto tail = begin;
		auto end = nums.end();
		std::vector<int>::iterator low;
		for (int i = 0; i < len; ++i)
		{
			//lower_bound returns the position that is no less than the given value
			//It's a built in function in STL based upon binary search
			low = std::lower_bound(begin, tail, nums[i]);
			*low = nums[i];
			//when low == tail, the last elemnt is inserted at position tail.
			//it is the time to extend tail to possibly fit the next element
			//This is the trick to maintain the length of longest increase subsequence
			if (low == tail)
				++tail;
		}
		return tail - nums.begin();
	}
	//O(N^2) with O(N) space
	int lengthOfLIS1(vector<int>& nums) {
		int len = nums.size();
		vector<int> memo(len, 1);
		int tmp = 0, maxLen = 0;
		for (int i = 0; i < len; ++i)
		{
			tmp = nums[i];
			for (int j = i - 1; j > -1; --j)
			{
				if (nums[j] < tmp)
					memo[i] = std::max(memo[j] + 1, memo[i]);
			}
			maxLen = std::max(maxLen, memo[i]);
		}
		return maxLen;
	}
};
void TestlengthOfLIS()
{
	SolutionLongestIncreasingSubsequence lenLIS;
	vector<int> vec1{ 10, 9, 2, 5, 3, 7, 101, 18 };
	assert(4 == lenLIS.lengthOfLIS(vec1));
	vector<int> vec2{};
	assert(0 == lenLIS.lengthOfLIS(vec2));
	vector<int> vec3{ 0 };
	assert(1 == lenLIS.lengthOfLIS(vec3));
	vector<int> vec4{ 2, 1 };
	assert(1 == lenLIS.lengthOfLIS(vec4));
	vector<int> vec5{ 1, 2 };
	assert(2 == lenLIS.lengthOfLIS(vec5));
	vector<int> vec6{ 1, -1, 2, -3, 4, -5, 6, -7 };
	assert(4 == lenLIS.lengthOfLIS(vec6));
	vector<int> vec7{ 10, 9, 2, 5, 3, 4 };
	assert(3 == lenLIS.lengthOfLIS(vec7));
}