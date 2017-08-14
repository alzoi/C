#include <iostream>
#include <queue>

int rwreg;
int val1, val2, val3, val4;

void op1(void){
    val1 = rwreg; // 1
}
void op2(void){
    rwreg = 1;    // 2
}
void op3(void){
    val2 = rwreg; // 3
}
void op4(void){
    val3 = rwreg; // 4
}
void op5(void){
    rwreg = 2;    // 5
}
void op6(void){
    val4 = rwreg; // 6
}
void print(void){
   std::cerr << val1 << " " << val2 << " " << val3 << " " << val4 << std::endl;
}

int main(void) {
   rwreg = 0;
   op1();op4();op2();op3();op5();op6();print(); // *
   rwreg = 0;
   op4();op1();op2();op3();op5();op6();print(); // *
   rwreg = 0;
   op1();op4();op2();op5();op3();op6();print(); //
   rwreg = 0;
   op1();op2();op3();op4();op5();op6();print(); //
   rwreg = 0;
   op1();op2();op4();op3();op5();op6();print(); //
   rwreg = 0;
   op4();op1();op5();op6();op2();op3();print(); // * 
   return 0;
}
