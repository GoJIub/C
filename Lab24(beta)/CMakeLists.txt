cmake_minimum_required(VERSION 3.15)
project(Lab24 C)

# Стандарт языка
set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Включаем все .c файлы рекурсивно
file(GLOB_RECURSE SOURCES
    "main.c"
    "binaryTree/*.c"
    "queue_lex/*.c"
    "queue_tree/*.c"
    "stack_lex/*.c"
    "stack_tree/*.c"
    "vector_int/*.c"
)

# Указываем папки, где лежат .h-файлы
include_directories(
    .
    binaryTree
    queue_lex
    queue_tree
    stack_lex
    stack_tree
    token
    vector_int
)

# Создаём исполняемый файл
add_executable(main ${SOURCES})
