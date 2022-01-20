# ----------------------------------------------------------------------------
# consolidated static library

add_library(app-lib)
set_target_properties(app-lib PROPERTIES OUTPUT_NAME app)
set_target_properties(app-lib PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/obj")

# ----------------------------------------------------------------------------
# directory dependencies

add_subdirectory(core)
add_subdirectory(model)
add_subdirectory(db)

# ----------------------------------------------------------------------------
# program executable

add_executable(app-exe program.cpp)

set_target_properties(app-exe PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(app-exe
    PRIVATE
        core
        model
        db

    PUBLIC
    # sqlite3
        SQLiteCpp
        sqlite3

    # sol2
        pthread
        dl
        lua
        m

    # cpp-terminal
        cpp-terminal

    # openssl
        ssl
        crypto

    # webview
        "-framework WebKit"

    # spdlog
        spdlog

    # zmq
        zmq

    # pqxx
        pqxx
        pgcommon
        pgport
        pq

    # cpr
        cpr
        curl-d
        z
        ssh2
        "-framework CoreFoundation"
        "-framework Security"
        "-framework SystemConfiguration"

    # xlsxwriter (requires z)
        xlsxwriter

)


# rename the cmake name of the exec to the project name
set_target_properties(app-exe PROPERTIES OUTPUT_NAME app)


# ----------------------------------------------------------------------------
# python scripting plugin

find_package(pybind11 REQUIRED)
pybind11_add_module(app scripting_py.cpp)
target_link_libraries(app
    PRIVATE
    core
    model
)

set_target_properties(app PROPERTIES 
   LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# ----------------------------------------------------------------------------
# lua scripting plugin

add_library(lua_app MODULE scripting_lua.cpp)
target_compile_options(lua_app PRIVATE
    -fPIC)
target_link_libraries(lua_app
    PRIVATE
    core
    model
    PUBLIC
    lua
    m
)


set_target_properties(lua_app PROPERTIES 
   LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set_target_properties(lua_app PROPERTIES 
   LIBRARY_OUTPUT_NAME app)

set_target_properties(lua_app PROPERTIES
    PREFIX "")

