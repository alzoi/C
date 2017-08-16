// Работа с параллельными потоками в С++
// Компиляция: g++ -lpthread main.cpp

#include <iostream>
#include <unistd.h>
#include <thread>
#include <atomic>

std::atomic_int a, b, c, d, k1, k2;
void thread0(void){
   std::cout << "Идентификатор потока " << std::this_thread::get_id() << std::endl;
   std::atomic_store(&c, 1);
   std::atomic_store(&a, std::atomic_load(&d));
}

void thread1(void){
   std::cout << "Идентификатор потока " << std::this_thread::get_id() << std::endl;
   std::atomic_store(&d, 1);
   std::atomic_store(&b, std::atomic_load(&c));
}
void print(void) {
   std::cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << std::endl;
   std::atomic_store(&a,  0); std::atomic_store(&b,  0); std::atomic_store(&c, 0); std::atomic_store(&d, 0);
   std::atomic_store(&k1, 0); std::atomic_store(&k2, 0);
}
int main(void){
   std::atomic_store(&a,  0); std::atomic_store(&b,  0); std::atomic_store(&c, 0); std::atomic_store(&d, 0);
   std::atomic_store(&k1, 0); std::atomic_store(&k2, 0);
   std::thread t0, t1;
   for(int i = 0; i < 10; i++){
      // Создаём потоки.
      if(i % 2){
         t0 = std::thread(thread0);   
         t1 = std::thread(thread1);      
      } else {
         t1 = std::thread(thread1);      
         t0 = std::thread(thread0);
      }
      // Ждём завершение работы потоков.
      t0.join();
      t1.join();
      print();
   }
   return 0;
}
