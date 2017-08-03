# Аллокация (распределение) памяти

## Ссылки
http://slideplayer.com/slide/1659576/  
 
- линейный аллокатор  
https://github.com/mtrebi/memory-allocators#time-complexity
- buddy аллокатор  
http://brokenthorn.com/Resources/OSDev26.html  
https://www.kernel.org/doc/gorman/html/understand/understand009.html 
https://habrahabr.ru/post/188010/  
Сложность buddy аллокатора O(log(N)) - бинарный поиск, где N - показетель степени двойки.  
Размер выделяемой памяти = (2^N*Размер страницы) Байт.
- SLAB аллокатор  
http://slideplayer.com/slide/3544296/  
https://www.kernel.org/pub/linux/kernel/people/marcelo/linux-2.4/mm/slab.c
