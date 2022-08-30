# Spinlock
```c
#include <atomic>

long atm = 7;
std::atomic<long> test(38);

long AtomicLoad(long* cell) {
    return *cell;
}

void AtomicStore(long* cell, long value ) {
    *cell = value;
}

void StoreRelease(void) {
    test.store(17, std::memory_order_release);
}

void StoreSC(void) {
    test.store(17);
}

int main(void) {

    AtomicStore(&atm, 9);
    int x;
    x = AtomicLoad(&atm);

    return x;
}
```
Сгенерированный на x86_64 ассемблерный код  
```asm
AtomicLoad(long*):
  movq (%rdi), %rax
  ret
AtomicStore(long*, long):
  movq %rsi, (%rdi)
  ret
StoreRelease():
  movq $17, test(%rip)
  ret
StoreSC():
  movl $17, %eax
  xchgq test(%rip), %rax
  ret
main:
  movq $9, atm(%rip)
  movl $9, %eax
  ret
test:
  .quad 38
atm:
  .quad 7
```
