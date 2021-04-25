file(GLOB SOURCE_FILES
        *.cpp)

add_executable(Tests ${SOURCE_FILES})

target_link_libraries(Tests PRIVATE doctest_with_main NumberOperationsLib)