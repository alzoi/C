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
