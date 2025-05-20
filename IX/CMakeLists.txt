cmake_minimum_required(VERSION 3.15)
project(IX C)

# Стандарт языка
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Флаги компиляции
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -g -municode)
endif()

# Явно указываем консольное приложение
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()

# Включаем все .c файлы
file(GLOB SOURCES
    "main.c"
    "tools/*.c"
)

# Указываем папки для .h файлов
include_directories(
    .
    tools
)

# Создаём исполняемый файл
add_executable(main ${SOURCES})