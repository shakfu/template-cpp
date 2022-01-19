cmake_minimum_required(VERSION 3.14)

project(app
	VERSION 0.0.1
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_CURRENT_SOURCE_DIR}/build            )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug/bin  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# for thirdparty libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib)

# main code directories
add_subdirectory(src)
add_subdirectory(tests)


configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/config.toml"
            	"${CMAKE_BINARY_DIR}/bin/config.toml" )

