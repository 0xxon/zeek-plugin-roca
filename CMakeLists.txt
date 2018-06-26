
cmake_minimum_required(VERSION 2.8)

project(BroPluginROCA)

include(BroPlugin)

find_package(GMP)
find_package(OpenSSL)

if (NOT OPENSSL_FOUND)
	message(FATAL_ERROR "OpenSSL not found.")
endif()

if (NOT GMP_FOUND)
	message(FATAL_ERROR "GMP not found.")
endif()

include_directories(BEFORE ${OPENSSL_INCLUDE_DIR})
include_directories(BEFORE ${GMP_INCLUDE_DIR})
include_directories(BEFORE ${GMP_INCLUDE_DIR})
# Workaround because I messed up a few includes :/
include_directories(AFTER "${BRO_PLUGIN_BRO_SRC}/src/file_analysis/analyzer")
include_directories(AFTER "${BRO_PLUGIN_BRO_SRC}/src/file_analysis")

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    endif ()
else ()
    set (CMAKE_C_STANDARD 99)
endif ()

bro_plugin_begin(Johanna ROCA)
bro_plugin_cc(src/Plugin.cc)
bro_plugin_cc(src/roca.c)
bro_plugin_bif(src/roca.bif)
bro_plugin_dist_files(README CHANGES COPYING VERSION)
bro_plugin_link_library(${GMP_LIBRARY})
bro_plugin_link_library(${OPENSSL_CRYPTO_LIBRARY})
bro_plugin_link_library(${OPENSSL_SSL_LIBRARY})
bro_plugin_end()

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" VERSION LIMIT_COUNT 1)

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    # Allows building rpm/deb packages via "make package" in build dir.
    include(ConfigurePackaging)
    ConfigurePackaging(${VERSION})
endif ()
