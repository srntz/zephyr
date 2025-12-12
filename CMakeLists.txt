cmake_minimum_required(VERSION 3.31)
enable_testing()

project(zephyr)

set(
		SPEC_HELPER_FILES
		spec/spec_helpers.c
		spec/spec_helpers.h
)

function(add_test_executable executable_name path_to_dir)
	include(${path_to_dir}/build.cmake)
	add_executable(
			${executable_name}
			${path_to_dir}/spec.c
			${SPEC_HELPER_FILES}
			${SPEC_INCLUDE_SOURCES}
	)
	target_include_directories(${executable_name} PRIVATE src)
	target_include_directories(${executable_name} PRIVATE spec)
	add_test(NAME ${executable_name} COMMAND ${executable_name})
endfunction()

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

add_test_executable("tokenizer_spec" "spec/tokenizer")

target_include_directories(zephyr PRIVATE src)
target_link_libraries(zephyr PRIVATE toolbox)

if (MSVC)
	target_compile_options(zephyr PRIVATE /WX)
else()
	target_compile_options(zephyr PRIVATE -Wall -Wextra -Wpedantic)
endif()