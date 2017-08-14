# Поток исполнения

Поток исполнения это код и некоторое состояние потока (контекст).
Код это набор инструкций в памяти и указатель на следующую инструкцию (значение регистра %rip).
Контекст потока это данные, над которыми работает поток, это значение регистров общего назначения и регистра флагов и содержимое памяти.

Процессу операционная система (ОС) выделяет ресурсу (процессорное время и память).
Поток работает внутри процесса и пользуется той памятью, которая предоставлена процессу.
При создании процесса создаётся один поток и начинает исполнять код, использовать и модифицировать память процесса.
Если в процессе создать несколько потоков, то они будут исполняться одновременно (параллельно) и использовать одно логическое адресное пространство (использовать общую память).

Если потоки живут в разных процессах, то они будут использовать разную память.

Процесс это сущность, которой ОС выделяет ресурсы, поток это сущность, которая потребляет выделенные процессу ресурсы.

## Поток

У каждого потока свой стек, так как стек хранит адреса возвратов из функций и локальные переменные.
Для каждого потока ОС должна выделить память под стек. Регистр %rsp указывает на вершину стека.
При переключении на исполнение кода Потока-i система перезаписывает значение регистра %rsp.

Если в машине имеет один процессор с двумя ядрами, то два созданных потока будут выполняться физически одновременно, каждый на своём ядре.
Если имеется один процессор с одним ядром, то потоки будут выполняться поочередно, получая от ОС некий квант времени исполнения на ядре процессора. Полный код потока будет выполняться кусочками.

## Переключение потоков

Перед переключением с Потока-0 (исполняемый поток) на Поток-1 необходимо сохранить, где-то в памяти контекст Потока-0 (значение регистров rip, rsp, регистров общего назначения и другие данные относящиеся к контексту). Выбрать из памяти сохранённые данные контекста Потока-1 и восстановить их на процессоре (загрузить новые значеняе регистров процессора).

```c
// Объявление функции switch_threads прототип:
// **prev = %rdi - указатель на указатель, это адрес (указатель) памяти по которому необходимо
//сохранить адрес (указатель) вершины стека текущего потока; после выполнения функции адрес *prev будет указывать
// на вершину стека текущего потока с которого выполняется переключение, то есть можно получить значение для %rsp.
// *next = %rsi - указатель в котором хранится адрес вершины стека для нового потока.

void switch_threads(void **prev, void *next);
```

```asm
.text

# Подпрограмма для переключения на новый поток.
switch_threads:
	## Сохранение контекста текущего потока.
	# Сохраняем на стеке значения регистров общего назначения.
	pushq %rbx
	pushq %rbp
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	# Сохраняем на стеке значение регистра флагов.
	pushfq
	# Сохраняем в памяти (по адресу (%rdi) первый параметр функции) текущее значение указателя на стек.
	movq %rsp, (%rdi)

	## Восстановление контекста нового потока (получение нового стека с новым содержимым).
	# Загружаем в регистр %rsp значение для стека нового процесса,
	#значение выбирается из второго параметра функции.
	movq %rsi, %rsp
	# Новое значение регистра флагов.
	popfq
	# Новые значения регистров общего назначения.
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbp
	popq %rbx

	# Выход из подпрограммы (инструкция retq выполняет чтение значения следующей команды %rip с вершины стека
	# после выхода из подпрограммы в качестве следующей инструкции будет выполняться инструкция нового потока.
	retq
  ```
  
Если Потоку-0 дополнительно требуются данные регистров rax, rbx и т.д., то Поток-0 перед вызовом подпрограммы switch_threads() должен сохранить значения необходимых регистров на своём стеке.

Схема переключения потоков  

![alt переключение потоков](https://hsto.org/getpro/habr/post_images/c2e/655/3a6/c2e6553a6d05d801375f45a34019f6ef.png)
```c
Поток-0()
	// Полезный код.
	useful_code0();
	// Сохранение данных.
	save_context0();
	// Системный вызов для переключения на новый поток.
	switch_th(
		call switch_threads
		retq
	);
	Поток-1()
		// Полезный код.
		useful_code1();
		// Сохранение данных.
		save_context1();
		// Системный вызов для переключения на новый поток.
		switch_th(
			call switch_threads
			retq
		);
Поток-0()	
	// Полезный код.
	useful_code0();
```