cmake_minimum_required(VERSION 3.31)

project(zephyr_toolbox)

add_library(toolbox
	string.c
	dynamic_reader/dynamic_reader.c
)