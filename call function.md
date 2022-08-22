# Вызов функций

## ABI
http://www.ucw.cz/~hubicka/papers/abi/  
[System V Application Binary Interface](https://github.com/tpn/pdfs/blob/master/System%20V%20Application%20Binary%20Interface%20(ABI)%20AMD64%20Architecture%20Processor%20Supplement%20-%20v0.99.6%20(October%207%2C%202013).pdf)  
[System V Application Binary Interface](https://webcache.googleusercontent.com/search?q=cache:Fc-8ml3p8QAJ:https://www.intel.com/content/dam/develop/external/us/en/documents/mpx-linux64-abi.pdf&cd=2&hl=ru&ct=clnk&gl=ru)  

## Компиляция
Для компиляции в ассемблерный код синтаксиса Intel с удалением лишних меток и печатью всех опций ассемблера:
```
gcc -S -fno-asynchronous-unwind-tables -masm=intel -fverbose-asm main.c
```
Или просмотр ассемблерного кода 
```
gcc main.c
objdump -d -j .text -M intel a.out
```

## Теория
https://www.cs.cmu.edu/~213/lectures/07-machine-procedures.pdf  
https://cs.brown.edu/courses/csci1310/2020/notes/l08.html  
https://blog.holbertonschool.com/hack-virtual-memory-stack-registers-assembly-code/  
![image](https://user-images.githubusercontent.com/20499566/185850704-b14682a5-8a91-4851-8c6b-2f914a7571ec.png)

Изначально для стека фрейма функции выделяется 128 байт. В стеке фрейма функции всегда находится сохранённое значение регистра ```rbp``` фрейма, вызвавшей функции. По адресу ```-0(%rbp)``` получим значение регистра rbp предыдущей функции:
```c
void func1(void)
{
    long a[14];
    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[13] = 2;
}

int main(void)
{
    func1();
    return (0);
}
```
В асемблерном коде мы видим, что указатель стека (значение в регистре ```rsp``` ) не уменьшается, стек не отодвигается, не увеличивается его размер. Отсутствует директива ```subq $8, %rsp``` (которая появится, если создать массив из 15 элементов по 8 байт).
Добавление локальных переменных двигает (увеличивает) стек на 16 байт через один элемент (для каждого нечётного восьми байтного элемента):
- для 14 элементов: 0 байт к исходным 128 байтам,
- для 15 и 16: 8 байт (128 + 8 = 136),
- для 17 и 18: 24 байта (128 + 24 = 152),
- для 19 и 20: 40 байт (128 + 40 = 168),
- для 21 и 22: 56 байт (128 + 56 = 184).  
```asm
func1:
  pushq %rbp
  movq %rsp, %rbp
  movq $5, -112(%rbp)
  movq $4, -104(%rbp)
  movq $3, -96(%rbp)
  movq $2, -8(%rbp)
  nop
  popq %rbp
  ret
main:
  pushq %rbp
  movq %rsp, %rbp
  call func1
  movl $0, %eax
  popq %rbp
  ret
```
Создаём массив из 16-ти элементов:
```c
void func1(void)
{
    long a[16];
    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[15] = 2;
}

int main(void)
{
    func1();
    return (0);
}
```

```asm
func1:
  pushq %rbp
  movq %rsp, %rbp
  subq $8, %rsp
  movq $5, -128(%rbp)
  movq $4, -120(%rbp)
  movq $3, -112(%rbp)
  movq $2, -8(%rbp)
  nop
  leave
  ret
main:
  pushq %rbp
  movq %rsp, %rbp
  call func1
  movl $0, %eax
  popq %rbp
  ret
```
