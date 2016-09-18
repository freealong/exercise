#ifndef EXERCISE_ALGORITHMS_SORT_H_
#define EXERCISE_ALGORITHMS_SORT_H_

#include<stdio.h>

/* print array */
void print_array(int* Nums, const int len)
{
  for (int i = 0; i < len; ++i)
    printf("%d ", Nums[i]);
}

/* 以下为插入排序部分 */
/* insertion sort
   Input: Nums to be sorted;
          len of Nums;
   Output: Nums
   Time complexity: O(n^2) */

void insert_sort(int* Nums, const int len)
{
    for (int i, j = 1, key; j <  len; ++j) {
    key = Nums[j];
    i = j - 1;
    while (i >= 0 && Nums[i] > key) {
      Nums[i+1] = Nums[i];
      --i;
    }
    Nums[i+1] = key;
  }
}
/* 插入排序部分结束 */

/* 以下为合并排序部分 */
/* merge sort
   Input: Nums to be sorted;
          begin of Nums;
          end of Nums;
   Output: Nums
   Time complexity: O(nlogn) */
void merge_sort(int* Nums, int begin, int end)
{
    int middle = (begin + end) / 2;
    if (begin < end) {
        merge_sort(Nums, begin, middle);
        merge_sort(Nums, middle + 1, end);
        // merge, input: Nums, begin, middle, end
        int n1 = middle - begin + 1, n2 = end -middle;
        int L[n1], R[n2];
        int i,j;
        for (i = 0; i < n1; ++i)
            L[i] = Nums[begin + i];
        for (j = 0; j < n2; ++j)
            R[j] = Nums[middle + 1 +j];
        i = 0;
        j = 0;
        for (int k = begin; k <= end; ++k)
            if ( i < n1 && j < n2)
                if (L[i] <= R[j])
                    Nums[k] = L[i++];
                else
                    Nums[k] = R[j++];
            else if (i == n1)
                Nums[k] = R[j++];
            else
                Nums[k] = L[i++];
    }
}

/* count sum of inversion(逆序对) in array
   Input: Nums of array;
          begin of Nums;
          end of Nums;
   Output: Nums
   Time complexity: O(nlogn) */
void count_inversion(int* Nums, int begin, int end, int* sum_inversion)
{
    int middle = (begin + end) / 2;
    if (begin < end) {
        count_inversion(Nums, begin, middle, sum_inversion);
        count_inversion(Nums, middle + 1, end, sum_inversion);
        // merge, input: Nums, begin, middle, end
        int n1 = middle - begin + 1, n2 = end -middle;
        int L[n1], R[n2];
        int i,j;
        for (i = 0; i < n1; ++i)
            L[i] = Nums[begin + i];
        for (j = 0; j < n2; ++j)
            R[j] = Nums[middle + 1 +j];
        i = 0;
        j = 0;
        for (int k = begin; k <= end; ++k)
            if ( i < n1 && j < n2)
                if (L[i] <= R[j]) {
                    (*sum_inversion)++;
                    Nums[k] = L[i++];
                }
                else
                    Nums[k] = R[j++];
            else if (i == n1)
                Nums[k] = R[j++];
            else
                Nums[k] = L[i++];
    }
}
/* 合并排序部分结束 */

/* 以下为堆排序部分 */
#define PARENT(i) (i-1)/2
#define LEFT(i)  2*(i)+1
#define RIGHT(i)  2*(i)+2
void exchange(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
/* max_heapify
   使以 pos 为根的子树成为最大堆
   Input: @Nums Numbers to be sorted;
          @len_heap length of heap;
          @pos position;
   Output: @Nums */
void max_heapify(int* Nums, int len_heap, int pos)
{
    int l = LEFT(pos), r = RIGHT(pos), largest = 0;
    if (l < len_heap && Nums[l] > Nums[pos])
        largest = l;
    else
        largest = pos;
    if (r < len_heap && Nums[r] > Nums[largest])
        largest = r;
    if (largest != pos)
    {
        exchange(&Nums[pos], &Nums[largest]);
        max_heapify(Nums, len_heap, largest);
    }
}

/* heap sort
   Input: @Nums Numbers to be sorted;
          @len length of Numbers;
   Output: @Nums
   Time complexity: O(nlogn) */
void heap_sort(int* Nums, int len)
{
    /* build max heap */
    int len_heap = len;
    for (int i = len/2-1; i >= 0; --i)
        max_heapify(Nums, len_heap, i);
    /* begin to sort */

    for (int i = len - 1; i >= 1; --i)
    {
        exchange(&Nums[0], &Nums[i]);
        len_heap--;
        max_heapify(Nums, len_heap, 0);
    }
}
/* 堆排序部分结束 */

/* 以下为快速排序部分 */
/* partition
   对子数组进行就地重排
   Input: @Nums
          @p 子数组起始位置
          @r 子数组结束位置
   Output: @Nums
           @i 较大元素子数组的起始位置 */
int partition(int* Nums, int p, int r)
{
    int last_number = Nums[r];
    int i = p;
    for (int j = p; j < r; ++j)
    {
        if (Nums[j] < last_number)
            exchange(&Nums[i++], &Nums[j]);
    }
    exchange(&Nums[i], &Nums[r]);
    return i;
}

/* quick_sort */
void quick_sort(int* Nums, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(Nums, p, r);
        quick_sort(Nums, p, q-1);
        quick_sort(Nums, q+1, r);
    }
}
/* 快速排序部分结束 */

/* 以下为线性时间排序 */
/* counting_sort
   计数排序，假设排序的元素是介于0到k之间的整数
   Input: @A array to be sorted
          @len_A
          @k max number in A
   Output: @B array to store sorted numbers
*/
void counting_sort(int* A, int len_A, int k, int *B)
{
    int C[k+1];
    for (int i = 0; i <= k; ++i)
        C[i] = 0;
    for (int i = 0; i < len_A; ++i)
        C[A[i]]++;
    for (int i = 1; i <= k; ++i)
        C[i] += C[i-1];
    for (int i = len_A - 1; i >= 0; --i)
    {
        C[A[i]]--;
        B[C[A[i]]] = A[i];
    }
}
/* 线性时间排序结束 */

#endif
