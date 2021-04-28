file(GLOB_RECURSE HEADER_FILES
        *.hpp
        )



add_library(MatrixOperationsLib STATIC ${HEADER_FILES})

target_link_libraries(MatrixOperationsLib PUBLIC libfort::fort)

target_include_directories(MatrixOperationsLib PUBLIC MatrixOperationsLib)
set_target_properties(MatrixOperationsLib PROPERTIES LINKER_LANGUAGE CXX)
