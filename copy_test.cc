/* main test function */

#include"copy_test.h"

int main()
{
  Message mes1(std::string("msg1")), mes2(std::string("msg2"));
  Folder fld1, fld2;
  mes1.save(fld1);
  mes1.save(fld2);
  mes2.save(fld2);

  mes1.show();
  mes2.show();

  fld1.show();
  fld2.show();

}
