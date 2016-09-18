/* Horner's rule, 霍纳法则, 求多项式值的一个快速算法，算法复杂度O(n)。
   原理：F(x) = a0+a1*x^1+...+an*x^n = ((an*x+a{n-1})*x+a{n-2}...)x+a0 */

#include<stdio.h>

int horner(const int A[], int N, int x)
{
  int fx = 0;
  int i;
  for(i=N-1;i>=0;--i)
    fx = A[i] + fx * x;
  return fx;
}

int main()
{
  int A[4]={1,2,3,4},N=4,x=2;
  printf("when x=%d,1+2*x+3*x^2+4*x^3=%d\n", x, horner(A, N, x));
  return 0;
}
