file(GLOB_RECURSE HEADER_FILES
        *.hpp
        )

file(GLOB_RECURSE SOURCE_FILES
        *.cpp
        *.inl
        )

add_library(NumberOperationsLib STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(NumberOperationsLib PUBLIC Number Operations)
