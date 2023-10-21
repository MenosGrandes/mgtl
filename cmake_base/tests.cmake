function (TestBase )

  cmake_minimum_required(VERSION 3.15...3.23)

  project(CmakeConfigPackageTests LANGUAGES CXX)

  # ---- Test as standalone project the exported config package ----

  if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
    enable_testing()

    find_package(mgtl CONFIG REQUIRED) # for intro, project_options, ...

    if(NOT TARGET mgtl_options)
      message(FATAL_ERROR "Requiered config package not found!")
      return() # be strictly paranoid for Template Janitor github action! CK
    endif()
  endif()

  # ---- Dependencies ----

  include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
endfunction()

function(AddTest targetName)
  set(flags)
  set(args)
  set(listArgs SOURCES DEPENDENCIES)

  cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

  if (NOT arg_SOURCES)
    message(FATAL_ERROR "[AddTest]: SOURCES is a required argument")
  endif()
  if (SOURCES IN_LIST arg_KEYWORDS_MISSING_VALUES)
    message(FATAL_ERROR "[AddTest]: SOURCES requires at least one value")
  endif()

  ################
  TestBase()

  add_executable(${targetName} ${arg_SOURCES})
  target_link_libraries(
    ${targetName}
    PRIVATE mgtl::mgtl_warnings
    mgtl::mgtl_options
    mgtl::sample_library
    Catch2::Catch2WithMain)

  if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(
      TARGET ${targetName}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
      COMMAND_EXPAND_LISTS)
  endif()

  # automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
  # to whatever you want, or use different for different binaries
  string( CONCAT TEST_PREFIX_V "UT." ${targetName} ".")
  catch_discover_tests(
    ${targetName}
    TEST_PREFIX ${TEST_PREFIX_V}
    REPORTER XML
    OUTPUT_DIR .
    OUTPUT_PREFIX ${TEST_PREFIX_V}
    OUTPUT_SUFFIX .xml)

endfunction()

function (AddConstexprTests targetName)

  set(flags)
  set(args)
  set(listArgs SOURCES DEPENDENCIES)

  cmake_parse_arguments(arg "${flags}" "${args}" "${listArgs}" ${ARGN})

  if (NOT arg_SOURCES)
    message(FATAL_ERROR "[AddTest]: SOURCES is a required argument")
  endif()
  if (SOURCES IN_LIST arg_KEYWORDS_MISSING_VALUES)
    message(FATAL_ERROR "[AddTest]: SOURCES requires at least one value")
  endif()

  ################
  TestBase()
  # ---- Dependencies ----

  string( CONCAT TEST_PREFIX_V "CONSTEXPR." ${targetName} ".")

  # Add a file containing a set of constexpr tests
  add_executable(${targetName} ${arg_SOURCES})
  target_link_libraries(
    ${targetName}
  PRIVATE mgtl::mgtl_warnings
  mgtl::mgtl_options
  mgtl::sample_library
  Catch2::Catch2WithMain)


catch_discover_tests(
  ${targetName}
  TEST_PREFIX ${TEST_PREFIX_V}
  REPORTER XML
  OUTPUT_DIR .
  OUTPUT_PREFIX ${TEST_PREFIX_V}
  OUTPUT_SUFFIX .xml)


# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing

string( CONCAT TEST_PREFIX_RELAXED_V "CONSTEXPR_RELAXED." ${targetName} ".")
string( CONCAT  RELAXED_TARGET_NAME ${targetName} "-relaxed")
add_executable(${RELAXED_TARGET_NAME} ${arg_SOURCES})
target_link_libraries(
  ${RELAXED_TARGET_NAME}
  PRIVATE mgtl::mgtl_warnings
  mgtl::mgtl_options
  mgtl::sample_library
  Catch2::Catch2WithMain)
target_compile_definitions(${RELAXED_TARGET_NAME} PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(
  ${RELAXED_TARGET_NAME}
  TEST_PREFIX ${TEST_PREFIX_RELAXED_V}
  REPORTER XML
  OUTPUT_DIR .
  OUTPUT_PREFIX ${TEST_PREFIX_RELAXED_V}
  OUTPUT_SUFFIX .xml)


endfunction()
