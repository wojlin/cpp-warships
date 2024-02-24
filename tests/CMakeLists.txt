set(Tests testGame testGameMechanics)

foreach(Test ${Tests})
    set(Sources ${Test}.cpp)
    add_executable(${Test} ${Sources})
    target_link_libraries(${Test} PUBLIC gtest_main warships_object)
    add_test(NAME ${Test} COMMAND ${Test})
endforeach()

add_custom_target(run_tests DEPENDS ${Tests})

#set(This Tests)
#set(Sources testGameMechanics.cpp)
#add_executable(${This} ${Sources})
#target_link_libraries(${This} PUBLIC gtest_main warships_object)

#add_test(NAME ${This} COMMAND ${This})

