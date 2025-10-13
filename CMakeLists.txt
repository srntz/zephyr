cmake_minimum_required(VERSION 3.31)

project(zephyr)

add_subdirectory(toolbox)
add_executable(zephyr
	zephyr.c 
	token.c 
	tokenizer.c
)
target_link_libraries(zephyr PRIVATE toolbox)

if (MSVC)
	target_compile_options(zephyr PRIVATE /WX)
else()
	target_compile_options(zephyr PRIVATE -Wall -Wextra -Wpedantic)
endif()