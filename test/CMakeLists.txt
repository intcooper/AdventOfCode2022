find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if (Boost_FOUND)
    add_executable (
        ${PROJECT_NAME}Tests 
        "TestModule.cpp"
        "GridTests.cpp"
        "PointTests.cpp"
    )

    target_include_directories(${PROJECT_NAME}Tests PRIVATE ${Boost_INCLUDE_DIR})
    target_include_directories(${PROJECT_NAME}Tests PRIVATE ../include)

    target_compile_definitions(${PROJECT_NAME}Tests PRIVATE BOOST_ALL_DYN_LINK)

    target_link_libraries(${PROJECT_NAME}Tests PRIVATE Boost::unit_test_framework)

    if (MSVC)
        target_compile_options(${PROJECT_NAME}Tests PRIVATE /W4)
    else()
        target_compile_options(${PROJECT_NAME}Tests PRIVATE -Wall -Wextra)
    endif()

    if (CMAKE_VERSION VERSION_GREATER 3.12)
        set_property(TARGET ${PROJECT_NAME}Tests PROPERTY CXX_STANDARD 20)
    endif()

endif()
