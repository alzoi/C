// Образец программы элементарного командного интерпретатора (командной оболочки).
// Программа в цикле обрабатывает указанные пользователем команды, парсит строку команды и запускает на исполнение в новом процессе.

// gcc main.c

// Перевод режима отладки для отладки родительского или дочернего процесса: 
// (gdb) set follow-fork-mode <mode>
// <mode>: parent | child

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static char **parse_cmd(const char *str) {
// Разбор строки str, подготовка массива указателей на отдельные слова команды.
    // Создаём массив из 128 указателей на char.
    char **args = malloc(128 * sizeof (*args));
    //printf("%s\n", *args);
    size_t size = 0;
    size_t cap = 127;
    for (size_t i = 0; str[i];) {
        // Продвигаемся по строке пока текущий символ является символом разделителем слов.
        while (str[i] && isspace(str[i])){
            ++i;
        }            
        // Выходим из цикла если нашли в строке символ 0 (конец строки).
        if (!str[i]) {
            break;
        }
        // Если у команды более cap параметров.
        if (size == cap) {
            // Увеличиваем массив параметров в 2 раза.
            cap = 2 * (cap + 1) - 1;
            args = realloc(args, sizeof (*args) * (cap + 1));
        }
        const size_t p = i;
        // Продвигаемся по строке пока не встретим символ разделитель слов.
        while (str[i] && !isspace(str[i])) {
            ++i;
        }
        // Выделяем память под найденный параметр команды.
        args[size] = malloc((i - p + 1) * sizeof(char));
        // Копируем в выделенный буфер байты параметра.
        strncpy(args[size], &str[p], i - p);
        // Ограничитель строки параметра.
        args[size][i - p] = '\0';
        // Последний параметр = NULL.
        args[++size] = NULL;
    }
    return args;
}

static void run_cmd(const char *cmd) {
// Запуск на исполнение команды, указанной в строке cmd.

    // Создаём дочерний процесс.
    const pid_t pid = fork();
    // Если ошибка.
    if (pid < 0) {
        printf("fork failed\n");
        return;
    }
    // Родитель ждёт завершение дочернего процесса.
    if (pid) {
        int k,waitstatus;
        waitpid(pid, &waitstatus, 0);
        k = WEXITSTATUS(waitstatus);
        // Если дочерний процесс завершился с ошибкой.
        if(k != 0) {
            printf("exec failed\n");            
        }
        return;
    }
    // В дочернем процессе разбираем строку команды.
    char **args = parse_cmd(cmd);
    printf("%s\n", cmd);
    // Запускаем программу (данные текущего процесса заменяются новыми данными, данными новой программы).
    execvp(args[0], args);
    // Если мы тут, то произошла ошибка при попытке запуска внешней программы.
    exit(1);
}

int main(int argc, char **argv) {
    int k;
    k = k + 1;
    k = 5;
    // Основной цикл (запускаем команды в цикле).
    while (1) {
        size_t size = 0;
        char *cmd = 0;
        // Читаем строку со стандартного ввода в буфер cmd.
        const ssize_t read = getline(&cmd, &size, stdin);
        // 
        if (read < 0) {
            // Освобождаем память выделенную буферу cmd.
            free(cmd);
            // Выходим из цикла.
            break;
        }
        // В конце строки ставим символ 0 для идентификации окончания строки.
        if (cmd[read - 1] == '\n') {
            cmd[read - 1] = '\0';
        }
        // Если ввели команду для выхода из интерпретатора.
        if (!strcmp(cmd, "exit")) {
            free(cmd);
            break;
        }
        // Запускаем команду.
        run_cmd(cmd);
        free(cmd);
    }
    return 0;
}
