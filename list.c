#include <stdio.h>
#include <stdlib.h>

// https://www.ibm.com/developerworks/ru/library/l-linux_kernel_65/index.html
struct list_head{
	struct list_head
		*prev,
		*next;
};

void list_init(struct list_head *list){
// Инициализация двусвязного списка.
	list->next = list->prev = list;
}
static void list_insert(struct list_head *node, struct list_head *prev, struct list_head *next){
// Вставка узла node между узлами prev и next.
	node->prev = prev;
	node->next = next;
	prev->next = node;
	next->prev = node;
}
void list_add_tail(struct list_head *node, struct list_head *list){
// Вставка узла node перед элементом list.
	list_insert(node, list->prev, list);
}
void list_add(struct list_head *node, struct list_head *list){
// Вставка узла node после элемента list.
	list_insert(node, list, list->next);
}
void list_del(struct list_head *node){
// Удаление узла node из списка.
	struct list_head *prev = node->prev;
	struct list_head *next = node->next;
	prev->next = next;
	next->prev = prev;
}
int list_empty(const struct list_head *list){
// Возвращает ненулевое значение (1 - true), если данный список пуст, то есть если следующий элемент = текущему.
	return list->next == list;
}
struct list{
	struct list_head head;
	unsigned int k;
};

void test(void){   
// Заполнение двусвязного списка.
	struct list *p1, *p2, *p3;
	p1 = (struct list *)malloc(1*sizeof(struct list *));
	p1->k = 5;
	list_init(&p1->head);
	//
	p2 = (struct list *)malloc(1*sizeof(struct list *));   
	p2->k = 6;
	list_add_tail(&p2->head, &p1->head);
	//
	p3 = (struct list *)malloc(1*sizeof(struct list *));   
	p3->k = 7;
	list_add_tail(&p3->head, &p2->head);
	//
	printf("p1=%u, p2=%u, p3=%u\n", p1->k, p2->k, p3->k);
	// Проходим по списку.
	struct list_head *head = &p1->head;
	struct list_head *ptr = head;
	do{
		struct list *tmp = (struct list *)ptr;
		printf("p=%u\n", tmp->k);
		ptr = ptr->next;
	}while(ptr != head);
}
int main(void){
	test();
	return 0;
}
