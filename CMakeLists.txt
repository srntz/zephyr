cmake_minimum_required(VERSION 3.31)

project(zephyr)

add_subdirectory(toolbox)

add_executable(
		zephyr
		zephyr.c
		src/tokenizer/tokenizer.c
		src/token/token.h
		src/token/token_list.c
		src/token/token_list.h
		src/error/error.h
		src/error/error.c
		src/tokenizer/tokenizer.h
		src/tokenizer/tokenizer.c
)

target_include_directories(zephyr PRIVATE src)
target_link_libraries(zephyr PRIVATE toolbox)

if (MSVC)
	target_compile_options(zephyr PRIVATE /WX)
else()
	target_compile_options(zephyr PRIVATE -Wall -Wextra -Wpedantic)
endif()