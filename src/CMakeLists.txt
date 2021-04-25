file(GLOB SOURCE_FILES
        *.cpp)

add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main PRIVATE NumberOperationsLib)

