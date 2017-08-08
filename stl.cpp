// Сортировка и перестановка вектора структуры данных.

#include <iostream>
#include <vector>
#include <algorithm>

// http://ideone.com/8Mvk3u

unsigned int min = 0;
struct gs_th{
   unsigned int time;
   unsigned int index;
};
std::vector <struct gs_th> v_min;

// Функция сравнения.
bool cmp(struct gs_th a, struct gs_th b) {
    return a.time < b.time;
}
void print(std::vector <struct gs_th> *a) {
// Вывод вектора.
   unsigned int s1 = 0, s2 = 0;
   //for(std::vector<struct gs_th>::iterator it = a->begin(); it!=a->end(); it++){
   for (auto now : *a) {
      std::cout << now.time << " ";
      // Считаем среднее время ожидания завершения задачи.
      s1 = s1 + now.time;
      s2 = s2 + s1;
   }
   std::cout << " | " << s2 << std::endl;
   // Минимальное значение.
   if(min == 0) {
      min = s2;
      v_min = *a;
   } else if(s2 < min) {
      min = s2;
      v_min = *a;
   }   
}

int main(void) {
   unsigned int k, f;
   struct gs_th ls_th;
	std::cin >> k;
   std::cout << "число задач " << k << std::endl;
   std::vector <struct gs_th> v;   
	for (unsigned int i = 0; i < k; i++) {
		std::cin >> f;
		v.push_back({f, i});
	}
   // Сортировка (после сортировки вектор будет в порядке, дающем минимальное среднее время ожидания завершения задачи).
   std::sort(v.begin(), v.end(), cmp);
   
   // (!)
   std::cout << "перестановки:" << std::endl;
   print(&v);
   // После сортировки Перестановку делать не нужно, приведена для демонстрации.
   // Выполняем перестановку с вектором.
   while(std::next_permutation(v.begin(), v.end(), cmp)) {
      print(&v);
   }   
   std::cout << "min среднее время=" << min << std::endl;
   // Вывод номера задачи.
   for (auto now : v_min) {  
      std::cout << now.time << "(" << now.index << ")" << " ";
      //std::cout << now.index << " ";
   }
   std::cout << std::endl;
   return 0;
}
