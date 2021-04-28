file(GLOB SOURCE_FILES
        *.cpp)

add_executable(MyMain ${SOURCE_FILES})

target_link_libraries(MyMain PRIVATE MatrixOperationsLib)