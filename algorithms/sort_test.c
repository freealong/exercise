#include <stdio.h>
#include <math.h>
#include "sort.h"

int main()
{
  int ArrayNums[5]={4,2,3,2,1};
  int length_of_nums = sizeof(ArrayNums)/sizeof(ArrayNums[0]);

  // test insertion sort
  // insert_sort(ArrayNums, length_of_nums);

  // test merge sort
  //merge_sort(ArrayNums, 0, length_of_nums - 1);

  // test count insersion
  //int sum = 0;
  //int* pointor_sum = &sum;
  //count_inversion(ArrayNums, 0, length_of_nums - 1, pointor_sum);
  //printf("%d\n", sum);

  // test heap sort
  //heap_sort(ArrayNums, length_of_nums);

  // test quick sort
  //quick_sort(ArrayNums, 0, length_of_nums-1);

  //test counting sort
  int OutputArray[5];
  int k = 4;
  counting_sort(ArrayNums, length_of_nums, k, OutputArray);

  // print sorted array
  print_array(OutputArray, length_of_nums);
  return 0;
}
