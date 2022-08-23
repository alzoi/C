# Модель памяти

## Ссылки
https://www.alibabacloud.com/blog/memory-model-and-synchronization-primitive---part-1-memory-barrier_597460  

# Барьер памяти для x86
Барьер компилятора  
```asm volatile("" ::: "memory");```  
Барьер процессора  
```asm volatile("mfence" ::: "memory");```  
