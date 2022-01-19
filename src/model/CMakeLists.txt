# ----------------------------------------------------------------------------
# module scoped variables

set(model_src
    vehicle.cpp
)


# ----------------------------------------------------------------------------
# module library

add_library(model)

target_sources(model
    PRIVATE
        ${model_src}
)

set_target_properties(model PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")


# ----------------------------------------------------------------------------
# consolidated application library

target_sources(app-lib
    PUBLIC
        ${model_src}
)

# redundant (already done in core): a benefit of using target_sources
# target_include_directories(app-lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})