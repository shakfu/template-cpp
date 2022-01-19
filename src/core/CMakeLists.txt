# ----------------------------------------------------------------------------
# module scoped variables

set(core_src
    process.cpp
)

# ----------------------------------------------------------------------------
# module library

add_library(core)

target_sources(core
    PRIVATE
        ${core_src}
)

set_target_properties(core PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")


# ----------------------------------------------------------------------------
# consolidated application library

target_sources(app-lib
    PUBLIC
        ${core_src}
)

target_include_directories(app-lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})