file(GLOB SOURCE_FILES
        *.cpp)

add_executable(MyTests ${SOURCE_FILES})

target_link_libraries(MyTests PRIVATE doctest_with_main MatrixOperationsLib)