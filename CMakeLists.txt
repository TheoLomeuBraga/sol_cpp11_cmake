add_subdirectory("lua-5.2.4")



include_directories(src lua-5.2.4/src)

option(SOL_EXAMPLES "add sol examples" ON)

if(SOL_EXAMPLES)

    SET(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")

    add_executable(basic examples/basic.cpp)
    target_link_libraries(basic lua_static)

    add_executable(config examples/config.cpp)
    target_link_libraries(config lua_static)

    add_executable(functions examples/functions.cpp)
    target_link_libraries(functions lua_static)

    add_executable(tables examples/tables.cpp)
    target_link_libraries(tables lua_static)

    add_executable(userdata examples/userdata.cpp)
    target_link_libraries(userdata lua_static)

    add_executable(variables examples/variables.cpp)
    target_link_libraries(variables lua_static)

    add_executable(class_variable examples/class_variable.cpp)
    target_link_libraries(class_variable lua_static)

endif(SOL_EXAMPLES)
