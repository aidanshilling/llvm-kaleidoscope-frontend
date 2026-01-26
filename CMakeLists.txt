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

add_library(Parser)
target_sources(Parser
	PRIVATE
		lib/Parser/parser.cpp
	
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			include
		FILES
			include/Parser/parser.h
)
