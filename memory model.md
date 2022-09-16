# Модель памяти

## Ссылки
https://www.alibabacloud.com/blog/memory-model-and-synchronization-primitive---part-1-memory-barrier_597460  
[Модель памяти в языке Си](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html#_005f_005fatomic-Builtins)  
https://stackoverflow.com/questions/49107683/why-does-a-stdatomic-store-with-sequential-consistency-use-xchg  
https://preshing.com/20120913/acquire-and-release-semantics/  
https://stackoverflow.com/questions/6935442/x86-spinlock-using-cmpxchg  

# Барьер памяти для x86
https://man7.org/linux/man-pages/man2/membarrier.2.html  
https://habr.com/ru/post/546880/  

Барьер компилятора  
```asm volatile("" ::: "memory");```  

Барьер процессора  
```asm volatile("mfence" ::: "memory");```  
или  
```std::atomic_thread_fence(std::memory_order_seq_cst);```

Полный барьер памяти на Си
```
smp_mb( );
```


# Spinlock
https://en.wikipedia.org/wiki/Spinlock  
https://www.youtube.com/watch?v=yB8sm-pwvZo  

# Примеры генерации кода для разных порядков памяти
Архитектура CPU x86_64
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
    # за один такт процессора (атомарно, другие потоки не имеют доступа к ячейке памяти test).
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
## Запись и чтение (Store and Load)
```cpp
#include <atomic>

std::atomic<long> x(0);
std::atomic<long> y(0);

int r1 = 0;
int r2 = 0;

long a;
void foo( ){
    x.store(1, std::memory_order_release); // Запись в память
    r1 = y.load(std::memory_order_acquire); // Чтение из памяти
}

void bar() {
    y.store(2, std::memory_order_release);
    r2 = x.load(std::memory_order_acquire);
}
```
Код -O2
```asm
# Вариант с std::memory_order_release и std::memory_order_acquire
foo(): x=1; r1=y;
  movq $1, x(%rip)
  movq y(%rip), %rax
  movl %eax, r1(%rip)
  ret

bar(): y=2; r2=x
  movq $2, y(%rip)
  movq x(%rip), %rax
  movl %eax, r2(%rip)
  ret

# Вариант с std::memory_order_seq_cst
foo(): x=1; r1=y;
  movl $1, %eax
  xchgq x(%rip), %rax
  movq y(%rip), %rax
  movl %eax, r1(%rip)
  ret

bar(): y=2; r2=x
  movl $2, %eax
  xchgq y(%rip), %rax
  movq x(%rip), %rax
  movl %eax, r2(%rip)
  ret

r2:
  .zero 4
r1:
  .zero 4
y:
  .zero 8
x:
  .zero 8
```
# Операция xchg
Инструкции метода std::exchange с [порядком памяти](https://en.cppreference.com/w/cpp/atomic/memory_order) std::memory_order_acquire идентичны инструкциям этого метода с порядком std::memory_order_seq_cst
```cpp
#include <atomic>

std::atomic<long> lock(8);

long change_acq( ){
    return lock.exchange(1, std::memory_order_acquire);
}

long change_seq( ){
    return lock.exchange(1, std::memory_order_seq_cst);
}

int main(void) {
    return 0;
}
```
asm с оптимизацией -O2
```asm
change_acq():
  movl $1, %eax
  xchgq lock(%rip), %rax
  ret
change_seq():
  movl $1, %eax
  xchgq lock(%rip), %rax
  ret
main:
  xorl %eax, %eax
  ret
lock:
  .quad 8
```
