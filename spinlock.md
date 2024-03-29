# Spinlock (Спин-блокировка)

## Ссылки
https://www.youtube.com/watch?v=yB8sm-pwvZo&t=222s  
https://github.com/ctdk/xv6/blob/master/spinlock.c  
https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/spinlock.c  
[Пример spinlock на портале cppreference.com](https://en.cppreference.com/w/cpp/atomic/atomic_flag)  
[О проблемах spinlock в пользовательском пространстве](https://www.realworldtech.com/forum/?threadid=189711&curpostid=189723)  
[Реализация spinlock в ядре Linux](https://github.com/torvalds/linux/blob/master/kernel/locking/spinlock.c)  
[Измерения spinlock и mutex](https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/)  

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

## Spinlock, который греет CPU
![image](https://user-images.githubusercontent.com/20499566/187440519-942faef3-72be-4b49-b16b-5ccf95dfc6c3.png)
В данной схеме в процедуре acquire поток постоянно выполняет использует процессор для чтения значения из ячейки памяти.
Инструкция [xchg](https://www.felixcloutier.com/x86/xchg) для процессора архитектуры x86_64 позволяет атомарно (за одну операцию) выполнять обмен значений между регистром и ячейкой памяти. Операндами могут быть два регистра общего назначения или регистр и ячейка памяти. При обращении к операнду памяти автоматически реализуется протокол блокировки процессора на время операции обмена, независимо от наличия или отсутствия префикса ```LOCK``` или значения IOPL.  
Префикс LOCK даёт сигнал процессору, что текущий поток имеет монопольный доступ к памяти. Пока выполняется инструкция обмена ```xchg```, другие потоки не могут кэшировать указанную ячейку памяти. Для других потоков будет заблокированы все 64 байта (кэш-линия), в которые входит указаная в инструкции ячейка памяти.  
Инструкция ```xchg```, так как работает не с кэшем, а напрямую с памятью, то работает очень медленно. Нам необходимо уменьшать число вызовов данной инструкции.  
### Ускоряем блокировку
Показаную выше схему блокировки можно сделать быстрее, если мы один раз будем вызывать инструкцию ```xchg``` и если блокировка не установлена, то будем проверять значение общей ячейки памяти с момощью обычной инструкции чтения, которая предусматривает работу с кэшем. Если обнаруживаем, что в ячейке ноль, то ещё раз вызываем ```xchg``` для новой попытки установки блокировки.
![image](https://user-images.githubusercontent.com/20499566/187605258-a0b75dee-20b8-47e7-bd12-b82a6f7c5ced.png)
Spinlock, который постоянно крутится на процессоре можно использовать если известно, что критическая секция кода работает очень быстро. Spinlock обычно используют для увеличения счётчиков.
## Адаптивное активное ожидание блокировки (pause + yield)
pause это подсказка для CPU том, что другой гиперпоток, работающий на том же ядре, должен работать вместо текущего.
[Инструкция pause](https://c9x.me/x86/html/file_module_x86_id_232.html)  
![image](https://user-images.githubusercontent.com/20499566/187611312-32e7f001-7fec-4e33-9e93-a76939cd7eb8.png)  
[Функция yield](https://en.cppreference.com/w/cpp/thread/yield)  
![image](https://user-images.githubusercontent.com/20499566/187611513-a86e73f6-f82e-4fdc-844a-f35d5c9db10b.png)  
На практике нужно сначала крутиться в цикле получения блокировки с использованием инструкции pause. Потом, адаптивно, через некоторое время вызывать функцию yield, уступая процессорное время другим потокам. Так как функция yield делает системный вызов sched_yield (который говорит планировщику, что текущий поток можно не выполнят, а переставить в конец очереди, данный вызов говорит планировщику ОС: я интенсивно использую ЦП, но мне не важна задержка, и я не хочу создавать проблемы для других, может быть, сейчас должно быть обработано более важное событие), то эта функция будет работать медленее инструкции просессора pause.
```cpp
#include <thread>

void acquire(int* locked) {
  SpinWait spin_wait;
  while (xchg(locked, 1) == 1) {
    while (*locked == 1) {
      spin_wait( );
    }
  }
}

class SpinWait {
  static const size_t
    lc_SpinLimit  = 6,
    lc_YieldLimit = 10;

 public:
  void Spin() {
    if (iter_ <= lc_SpinLimit) {
      for (size_t i = 0; i < (1 << iter_); ++i) {
        SpinLockPause();
      }
    } else {
      std::this_thread::yield();
    }
    ++iter_;
  }

  void operator()() {
    Spin();
  }
  
  inline void SpinLockPause() {
    asm volatile("pause\n" : : : "memory");
  }

  // Проверить, что крутимся достаточно долго.
  bool IsEnough() const {
    return iter_ > lc_YieldLimit;
  }

 private:
  size_t iter_{0};
};
```

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
    if (locked_.load(std::memory_order_acquire) == 1 ) {
      return false;
    } else {
      // Пытаемся установить блокировку.
      return locked_.exchange(1) == 0 ? true : false;
    }
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
