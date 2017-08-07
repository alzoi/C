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
http://elixir.free-electrons.com/linux/v2.6.11/source/mm/slab.c  

Кэш SLAB аллокатора состоит из связного списка SLAB-ов.
SLAB - это некоторая область в физической памяти, которая состоит из:
1) заголовка
2) последовательного списка объектов равного размера, указатели на которые возвращаются пользователям.

При освобождении памяти, занятой под объект пользователя в память, которая была отведена для объекта записыается адрес предыдущего свободного объекта. Получается, что для x64 битных процессоров размер объекта должен быть не менеее 8 байтов.

| Заголовок SLAB0 | Объект0 (Занят) | Объект1 (Занят) | Объект2 (Свободен) |
