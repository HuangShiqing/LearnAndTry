class father {
 public:
  father(/* args */);
  ~father();
  int father_public_param;
  // 类内部成员函数可以访问任意成员
  int father_public_fun() {
    int a = father_public_param;
    int b = father_protected_param;
    int c = father_protected_fun();
    int d = father_private_param;
    int e = father_private_fun();
    return 0;
  }

 protected:
  int father_protected_param;
  int father_protected_fun() { return 0; }

 private:
  int father_private_param;
  int father_private_fun() { return 0; }
};

class son : public father {
 public:
  son(/* args */);
  ~son();
  // 子类任意类型的成员函数都可以访问负类的public和protected成员
  int son_public_fun() {
    int a = father_public_param;
    int b = father_public_fun();
    int c = father_protected_param;
    int d = father_protected_fun();
    return 0;
  }

 protected:
  // 子类任意类型的成员函数都可以访问负类的public和protected成员
  int son_protected_fun() {
    int a = father_public_param;
    int b = father_public_fun();
    int c = father_protected_param;
    int d = father_protected_fun();
    return 0;
  }

 private:
  /* data */
};


