FetchContent_MakeAvailable(googletest)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB_PKG glib-2.0)
if (GLIB_PKG_FOUND)
    message("Found glib-2.0")
    include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()

enable_testing()

add_executable(
        int_stack_demo
        int_stack_demo.c
        int_stack.c)

add_executable(
        int_stack_tests
        int_stack_tests.cc
        int_stack.c
)

target_link_libraries(
        int_stack_tests
        gtest_main
        -lpthread
        ${GLIB_PKG_LIBRARIES}
)
add_library(
    forth_stack_lib
    int_stack.c
)

include(GoogleTest)
gtest_discover_tests(int_stack_tests)
