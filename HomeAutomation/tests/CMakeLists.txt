set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        main.cpp
        LightSchedulerTests.cpp
        # including the header files here is a hack to get
        # OpenCppCoverage to show the coverage in the headers
        ValidateDevelopmentEnvironment.cpp)
add_executable(home_automation_approval_tests ${SOURCE_FILES} )
target_link_libraries(home_automation_approval_tests production_src Catch2::Catch2 ApprovalTests::ApprovalTests)

# Work around Ninja in-source build error
# See https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md#situation-visual-studio-with-visual-c-compiler-clexe
target_compile_options(home_automation_approval_tests PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/FC>)

add_test(NAME home_automation_approval_tests COMMAND home_automation_approval_tests)
