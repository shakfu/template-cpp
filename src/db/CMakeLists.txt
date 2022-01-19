# ----------------------------------------------------------------------------
# module scoped variables

set(db_src
    store.cpp
)


# ----------------------------------------------------------------------------
# module library

add_library(db)

target_sources(db
    PRIVATE
        ${db_src}
)

set_target_properties(db PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")


# ----------------------------------------------------------------------------
# consolidated application library

target_sources(app-lib
    PUBLIC
        ${db_src}
)

