# Spinlock  

## Ссылки
https://www.youtube.com/watch?v=yB8sm-pwvZo&t=222s  
## Теория
Алгоритм взаимной блокировки потоков, в котором инструкции работают не атомарно, и поэтому два потока могут получить доступ к критической секции одновременно.
![image](https://user-images.githubusercontent.com/20499566/187421747-13e75e34-c641-4b60-a9f4-2bef932ec601.png)
При переключении контекста на новый поток, планировщик ОС восстанавливает ([process.md](https://github.com/alzoi/C/blob/master/process.md)) сохранённые при прошлом переключении значения его регистров.
В частности регистр ```rsp``` переводит на адрес вершины стека этого потока и в регистр ```rip``` устанавливает адрес прерванной инструкции.  

Поток может безопасно работать со своими регистрами и стеком. Но для работы с общими ячейками памяти требуется защита от:
* ```data race``` (гонка данных), когда, например, несколько потоков одновременно меняют старое значение счётчика
* ```race condition``` (состояние гонки), когда программа меняет заложенную логику работы из-за недетерминированных состояний гонки между потоками.  

Защита достигается с помощью примитивов синхронизации:
* spinlock
* mutex
* semaphore

## Схема Spinlock
![image](https://user-images.githubusercontent.com/20499566/187440519-942faef3-72be-4b49-b16b-5ccf95dfc6c3.png)
В данной схеме в процедуре acquire поток постоянно выполняет использует процессор для чтения значения из ячейки памяти.

## Примеры
### Устройство Atomic переменных
https://en.cppreference.com/w/cpp/atomic/atomic  
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

long AtomicExchange(long* cell, long new_value) {
    // Обычная функция обмена выполняется за три не атомарных шага.
    // При переключении контекста потока значение общей ячейки памяти может меняться.
    
    long tmp = *cell;
    *cell = new_value;
    return tmp;
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

AtomicExchange():
  # Атомарную функцию обмена значений между ячейкой и регистром можно реализовать только руками на языке ассемблер.
  movq %rsi, %rax
  xchgq (%rdi), %rax
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
### TryLock
Функция TryLock пытается установить блокировку, если блокирову установлена, то возвращает true, иначе false
https://en.cppreference.com/w/cpp/thread/try_lock  
```c
#include <atomic>

std::atomic<long> locked_(0);

bool TryLock() {
    // Пытаемся установить блокировку.
    return locked_.exchange(1) == 0 ? true : false;
}

int main(){
    return 0;
}
```
Сгенерированный для x86_64 ассемблерный код (с флагом компиляции -O2)
```asm
TryLock():
  movl $1, %eax
  xchgq locked_(%rip), %rax
  testq %rax, %rax
  sete %al
  ret
main:
  xorl %eax, %eax
  ret
locked_:
  .zero 8
```
