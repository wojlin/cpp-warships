set(This Tests)
set(Sources test_gameplay.cpp)
add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC gtest_main warhsips_object)

add_test(NAME ${This} COMMAND ${This})

