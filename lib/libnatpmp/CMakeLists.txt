cmake_minimum_required(VERSION 2.6)

project(natpmp)

add_definitions( -DENABLE_STRNATPMPERR )

add_library(natpmp STATIC
        natpmp.c
        getgateway.c
        natpmp.h
        getgateway.h
        declspec.h
    )


include_directories (${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(natpmp)
