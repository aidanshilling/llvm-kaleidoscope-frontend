cmake_minimum_required(VERSION 3.23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Kaleidoscope)

add_executable(Kaleidoscope)
target_sources(Kaleidoscope
	PRIVATE
		cmd/Driver/driver.cpp

	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			include
		FILES
			include/Driver/driver.h
)

add_library(Lexer)
target_sources(Lexer
	PRIVATE
		lib/Lexer/lexer.cpp
	
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			include
		FILES
			include/Lexer/lexer.h
)
