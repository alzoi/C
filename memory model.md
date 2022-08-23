# Модель памяти

## Ссылки
https://www.alibabacloud.com/blog/memory-model-and-synchronization-primitive---part-1-memory-barrier_597460  
[Модель памяти в языке Си](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html#_005f_005fatomic-Builtins)  

# Барьер памяти для x86
Барьер компилятора  
```asm volatile("" ::: "memory");```  
Барьер процессора  
```asm volatile("mfence" ::: "memory");```  

# Spinlock
https://en.wikipedia.org/wiki/Spinlock  

# Примеры генерации кода для разных порядков памяти
```c
#include <atomic>

long foo(void) {

    long x = 8;
    std::atomic<long> bar (2);
    
    bar.store(x, std::memory_order_seq_cst);

    return x;
}
int main(void) {

    return 0;
}
```
```asm
// memory_order_seq_cst
foo():
  movq $2, -8(%rsp)
  movl $8, %eax
  xchgq -8(%rsp), %rax // Обмен значений в регистре rax и в ячейке памяти -8(rsp) за один такт процессора
  movl $8, %eax
  ret
main:
  xorl %eax, %eax
  ret

// memory_order_release
foo():
  movq $2, -8(%rsp)
  movl $8, %eax
  movq $8, -8(%rsp)
  ret
main:
  xorl %eax, %eax
  ret

// memory_order_relaxed
foo():
  movq $8, -8(%rsp)
  movl $8, %eax
  ret
main:
  xorl %eax, %eax
  ret
```
