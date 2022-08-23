# Модель памяти

## Ссылки
https://www.alibabacloud.com/blog/memory-model-and-synchronization-primitive---part-1-memory-barrier_597460  
[Модель памяти в языке Си](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html#_005f_005fatomic-Builtins)  

# Барьер памяти для x86
Барьер компилятора  
```asm volatile("" ::: "memory");```  
Барьер процессора  
```asm volatile("mfence" ::: "memory");```  
или  
```std::atomic_thread_fence(std::memory_order_seq_cst);```

# Spinlock
https://en.wikipedia.org/wiki/Spinlock  

# Примеры генерации кода для разных порядков памяти
Архитектура CPU x86-64
## Store
```c
// gcc -S -O2 -std=c++20 main.cpp

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
    # Обмен значений между регистром %rax и ячейкой памяти test(%rip)
    # за один такт процессора (атомарно, без переключений на другие потоки).
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
## Load
```c
#include <atomic>

std::atomic<long> test(38);
long a;

void LoadSeqCst(void) {
    a = test.load(std::memory_order_seq_cst);
}

void LoadAcquire(void) {
    a = test.load(std::memory_order_acquire);
}

void LoadRelaxed(void) {
    a = test.load(std::memory_order_relaxed);
}
```
```asm
LoadSeqCst():
        movq    test(%rip), %rax
        movq    %rax, a(%rip)
        ret
LoadAcquire():
        movq    test(%rip), %rax
        movq    %rax, a(%rip)
        ret
LoadRelaxed():
        movq    test(%rip), %rax
        movq    %rax, a(%rip)
        ret
main:
        xorl    %eax, %eax
        ret
a:
        .zero   8
test:
        .quad   38
```
