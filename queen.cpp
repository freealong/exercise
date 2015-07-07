/* 递归解决八皇后问题，8x8的棋盘上要放8个皇后，
   每个皇后不能在同一行、同一列、同一斜线上。 */

#include <iostream>
#include <cstdlib>

using namespace std;

bool conflict(int *state, int nextX, int nextY)
{
  for (int i=0; i<nextY; ++i){
    if(abs(state[i]-nextX)==0 || abs(state[i]-nextX)==(nextY-i))
      return true;
  }
  return false;
};

int queen(int *state, int num, int indexY)
{

  if(indexY==num-1){
    for(int i=0; i<num; ++i){
      if(!conflict(state, i, indexY)){
        state[indexY]=i;
        for(int i=0; i<num; ++i)
          cout<<state[i]<<' ';
        cout<<endl;
      }
    }
    return 0;
  }
  else
    for(int i=0; i<num; ++i){
      if(!conflict(state, i, indexY)){
        state[indexY]=i;
        queen(state, num, indexY+1);
      }
    }
};

int main()
{
  int a[8]={0};

  queen(a,8,0);


  return 0;
}
