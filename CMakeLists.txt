cmake_minimum_required(VERSION 3.16)
project(prack_numbers_system LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(prack_numbers_system main.cpp button.cpp big_int.cpp fraction.cpp
        inoutput_field.cpp
        inoutput_field.h
        rounded_rectangle.cpp
        rounded_rectangle.h
        converter.cpp
        converter.h
        general_data.h
        general_data.cpp
        error_message.cpp
        error_message.h)
target_link_libraries(prack_numbers_system PRIVATE sfml-graphics)
target_compile_features(prack_numbers_system PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
            TARGET prack_numbers_system
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:prack_numbers_system>
            VERBATIM)
endif()

install(TARGETS prack_numbers_system)