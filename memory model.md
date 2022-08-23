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

std::atomic<long> test(38);

void SeqCst(void) {
    test.store(52, std::memory_order_seq_cst);
}

void Release(void) {
    test.store(17, std::memory_order_release);
}

void Relaxed(void) {
    test.store(9, std::memory_order_relaxed);
}

int main(void) {

    return 0;
}
```
```asm
# memory_order_seq_cst
SeqCst():
    movl    $52, %eax
    # Обмен значений в регистре rax и в ячейке памяти -8(rsp) за один такт процессора (атомарно, без переключений).
    xchgq   %rax, test(%rip)
    retq

# memory_order_release
Release():
    movq    $17, test(%rip)
    retq

# memory_order_relaxed
Relaxed():
    movq    $9, test(%rip)
    retq

main:
    xorl    %eax, %eax
    retq
test:
    .quad   38
```
