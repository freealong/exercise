/* main test */
#include<iostream>
#include"smart_pointer.h"

using namespace std;
int main()
{
  int *p = new int(1);
  Has_ptr *obj1 = new Has_ptr(p, 1);
  Has_ptr obj2(p, 2);

  cout<<obj2.get_ptr_val()<<endl;
  delete obj1;
  cout<<obj2.get_ptr_val()<<endl;

}
