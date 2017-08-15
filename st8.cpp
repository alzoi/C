// stepik.org/lesson/44339/step/4?course=Операционные-системы&unit=22145

#include <iostream>
#include <string>
#include <atomic>

std::atomic_int a(0), b(0), c(0), d(0), k1(0), k2(0);

// Поток 0 (раскладывается на атомарны операции: op1, op2, op3)
//void TH0(){
//   atomic_store(&c, 1);
//   atomic_store(&a, atomic_load(&d));   
//}
void op1(void){
   atomic_store(&c, 1);                  // 1
}
void op2(void){
   atomic_store(&k1, atomic_load(&d));   // 2
}
void op3(void){
   atomic_store(&a, atomic_load(&k1));   // 3
}

// Поток 1 (раскладывается на атомарные операции: op3, op4, op5)
//void TH1(void){
//    atomic_store(&d, 1);
//    atomic_store(&b, atomic_load(&c));
//}
void op4(void){
   atomic_store(&d, 1);                  // 4
}
void op5(void){
   atomic_store(&k2, atomic_load(&c));   // 5
}
void op6(void){
   atomic_store(&b, atomic_load(&k2));   // 6
}

void print(void){
   std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << std::endl;
   atomic_store(&a, 0); atomic_store(&b,  0); atomic_store(&c,  0); atomic_store(&d,  0); atomic_store(&k1, 0); atomic_store(&k2, 0);
}

int main(void) {
   // Возможные перестановки атомарных операций потоков.
   // Поток 0 начинает.
   op1();	op2();	op3();	op4();	op5();	op6();	print();
   op1();	op2();	op4();	op3();	op5();	op6();	print();
   op1();	op2();	op4();	op5();	op3();	op6();	print();
   op1();	op2();	op4();	op5();	op6();	op3();	print();   
   op1();	op4();	op2();	op3();	op5();	op6();	print();
   op1();	op4();	op2();	op5();	op3();	op6();	print();
   op1();	op4();	op2();	op5();	op6();	op3();	print();   
   op1();	op4();	op5();	op2();	op3();	op6();	print();
   op1();	op4();	op5();	op2();	op6();	op3();	print();
   op1();	op4();	op5();	op6();	op2();	op3();	print();

   // Поток 1 начинает.
   op4();	op1();	op2();	op3();	op5();	op6();	print();
   op4();	op1();	op2();	op5();	op3();	op6();	print();
   op4();	op1();	op2();	op5();	op6();	op3();	print();
   op4();	op1();	op5();	op2();	op3();	op6();	print();
   op4();	op1();	op5();	op2();	op6();	op3();	print();
   op4();	op1();	op5();	op6();	op2();	op3();	print();
   op4();	op5();	op1();	op2();	op3();	op6();	print();
   op4();	op5();	op1();	op2();	op6();	op3();	print();
   op4();	op5();	op1();	op6();	op2();	op3();	print();
   op4();	op5();	op6();	op1();	op2();	op3();	print();
   return 0;
}

/* Результат:

a = 0 b = 1 c = 1 d = 1
a = 0 b = 1 c = 1 d = 1
a = 0 b = 1 c = 1 d = 1
a = 0 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 1 c = 1 d = 1
a = 1 b = 0 c = 1 d = 1
a = 1 b = 0 c = 1 d = 1
a = 1 b = 0 c = 1 d = 1
a = 1 b = 0 c = 1 d = 1

*/
