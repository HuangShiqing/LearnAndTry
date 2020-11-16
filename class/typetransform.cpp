// 只有子类转换成父类，父类不可能转换成子类，因为子类是从父类继承而来，
// 子类中包含父类中所有成员。而如果父类可以转换成子类，意味着将子类中将有一部分是未知的成员，会出现不合法的内存访问
// 在子类转换成父类的时候，也需要注意，只能是指针或者引用，不能是对象，除非当子类B以public方式继承父类A后，或者有重写构造函数和赋值函数。

class father {
 private:
  /* data */
 public:
  father(/* args */);
  ~father();
};

father::father(/* args */) {}

father::~father() {}

class son : public father {
 private:
  /* data */
 public:
  son(/* args */);
  ~son();
};

son::son(/* args */) {}

son::~son() {}

int main() {
    // 子类的对象可以隐含的转换为父类的对象
    // 子类对象可以初始化积累的引用
    // 子类的指针可以隐含的转换为父类的指针
    son son;
    father*  p_father = &son;
    
    return  0;

}