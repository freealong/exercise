/* c++ primer 4th P421 智能指针 */
#include<cstddef>

class Has_ptr;
/* 计数类 */
class U_Ptr {
  friend class Has_ptr;
  int *ip;
  size_t use;
  U_Ptr(int *p): ip(p), use(1) {}
  ~U_Ptr() {delete ip;}
};

class Has_ptr {
  U_Ptr *ptr;
  int val;

 public:
  Has_ptr(int *p, int i=0): ptr(new U_Ptr(p)), val(i) {}
  Has_ptr(const Has_ptr &orig): ptr(orig.ptr), val(orig.val) {++ptr->use;}
  Has_ptr& operator=(const Has_ptr&);
  ~Has_ptr() {if (--ptr->use == 0) delete ptr;}

  int *get_ptr() const {return ptr->ip;}
  int get_val() const {return val;}
  void set_ptr(int *p) {ptr->ip = p;}
  void set_val(int i) {val = i;}
  int get_ptr_val() const { return *ptr->ip ; }
  void set_ptr_val(int i) { *(ptr->ip) = i; }
};

Has_ptr& Has_ptr::operator=(const Has_ptr &rhs)
{
  ++rhs.ptr->use;
  if(--ptr->use == 0)
    delete ptr;
  ptr = rhs.ptr;
  val = rhs.val;
  return *this;
}
