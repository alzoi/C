// g++ -std=c++20 hello.cpp

#include <iostream>

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

  return 0;

}
