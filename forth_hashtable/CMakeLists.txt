FetchContent_MakeAvailable(googletest)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB_PKG glib-2.0)
if (GLIB_PKG_FOUND)
    message("Found glib-2.0")
    include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../forth_stack)

add_library(
        forth_hashtable_lib
        forth_hashtable.c
)

target_link_libraries(
        forth_hashtable_lib
        ${GLIB_PKG_LIBRARIES}
)