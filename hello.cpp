// g++ -Wall -std=c++11 -O2 hello.cpp

#include <iostream>
#include <vector>

void print() {
  // "using-директива" сообщает компилятору, что мы используем все объекты из пространства имен std, действует локально в данной функции.
  using namespace std;
  cout << "Hello";
}

int main() { 

  // "using-объявление" сообщает компилятору, что cout следует обрабатывать, как std::cout.
  using std::cout;
  
  print();
  cout << "\nWorld!" << std::endl;

  std::vector<int> v1 = {1, 2, 3, 4};

  cout << "Vector: ";
  for(auto i : v1) {
    cout << i << " ";
  }  
  
  return 0;

}
