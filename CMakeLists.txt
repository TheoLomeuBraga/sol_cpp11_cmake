add_subdirectory("lua")



include_directories(src lua/src)

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


    #test lib

    set_target_properties(lua_static PROPERTIES POSITION_INDEPENDENT_CODE ON)

    if(WIN32)
        add_definitions(-DLUA_BUILD_AS_DLL)
        add_library(examplelib SHARED examples/example_lib.cpp)
        set_target_properties(examplelib PROPERTIES
            PREFIX ""
            SUFFIX ".dll")

    else()
        add_library(examplelib SHARED examples/example_lib.cpp)
        set_target_properties(examplelib PROPERTIES
            PREFIX "lib"
            SUFFIX ".so"
            COMPILE_FLAGS "-fPIC")

    endif()

    target_link_libraries(examplelib lua_static)


    if(UNIX AND NOT APPLE)
        target_link_options(examplelib PRIVATE "-Wl,--no-as-needed")
        target_compile_options(examplelib PRIVATE "-fPIC")
    endif()


    configure_file(examples/use_example_lib.lua ${CMAKE_CURRENT_BINARY_DIR}/use_example_lib.lua COPYONLY)



    
    

endif(SOL_EXAMPLES)
