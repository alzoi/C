#include <iostream>
#include <vector>
#include <algorithm>
// http://ideone.com/8Mvk3u
void print(std::vector <unsigned int> a) {
// Вывод вектора.
   unsigned int sp = 0, st=0;
   double k;
   for (auto now : a) {
      std::cout << now << " ";
      // Считаем среднее время ожидания завершения задачи.
      sp = sp + now;
      st = st + sp + now;
   }
   std::cout << " | " << st << " ";
   std::cout << std::endl;
}
int main(void) {
   int k, f;
	std::cin >> k;
	std::vector <unsigned int> v;
	for (int i = 0; i < k; i++) {
		std::cin >> f;
		v.push_back(f);
	}
   print(v);
   // Выполняем перестановку с вектором.
   while(std::next_permutation(v.begin(), v.end())) {
      print(v);
   }   
   //do {
   //     res.push_back(num);
   //} while (std::next_permutation(num.begin(), num.end()));   
   return 0;
}
