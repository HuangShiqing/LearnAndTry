# README
## Target
目的是实现一个管理大量Op的Conver(推理也同理)代码的注册机制. 这类代码的特点是一个Op的种类量大, 另外一个是不定期会增加Op

## Implementation
1. 首先实现一个基础OpConverter作为父类, 包含一个virtual函数run作为默认Convert处理. 每种具体的Op都继承于该父类实现一个子类, 比如PoolConverter, 重点是需要重新实现自己的run.
2. 然后再实现一个OpConverterSuit作为管理者, 包含一个静态成员变量OpConverterSuit* global, 以及一个静态成员函数get用于获得这个global. 另外还包含了一个成员变量std::map<std::string, OpConverter*> mTests用于记录Op的字符名和具体的OpConverter(这里用父类指针)的映射关系. 当然还包含操作这个map的insert和search方法
3. 每种具体的Op都需要调用insert. 这里利用一个OpConverterRegister类的构造函数和全局变量的自动初始化实现了一个不需要逐个手动显式调用insert的自动过程.
4. 使用时直接通过静态成员函数get获得global, 然后去search即可根据字符名获得对应的子类(都是用父类指针)方法run

## Quick Start
```bash
bash mk.sh
./main
```