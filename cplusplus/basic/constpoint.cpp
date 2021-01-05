float a = 5;

const float* p1 = &a;//常量指针，指向常量，不允许修改值

float* const p2 = &a;//指针常量，不允许修改指针