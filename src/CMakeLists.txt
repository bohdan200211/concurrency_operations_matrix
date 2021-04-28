add_executable(MyMain main.cpp)
add_executable(MyTable CreateTimeTable.cpp)

target_link_libraries(MyMain PRIVATE MatrixOperationsLib)
target_link_libraries(MyTable PRIVATE MatrixOperationsLib)