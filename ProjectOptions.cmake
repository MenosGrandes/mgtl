
include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(mgtl_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(mgtl_setup_options)
  option(mgtl_ENABLE_HARDENING "Enable hardening" ON)
  option(mgtl_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    mgtl_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    mgtl_ENABLE_HARDENING
    OFF)

  mgtl_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR mgtl_PACKAGING_MAINTAINER_MODE)
    option(mgtl_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(mgtl_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(mgtl_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(mgtl_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(mgtl_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(mgtl_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(mgtl_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(mgtl_ENABLE_PCH "Enable precompiled headers" OFF)
    option(mgtl_ENABLE_CACHE "Enable ccache" OFF)
    option(mgtl_ENABLE_IWYS "Enable IncludeWhatYouSee" OFF)
  else()
    option(mgtl_ENABLE_IPO "Enable IPO/LTO" ON)
    option(mgtl_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(mgtl_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(mgtl_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(mgtl_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(mgtl_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(mgtl_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(mgtl_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(mgtl_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(mgtl_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(mgtl_ENABLE_PCH "Enable precompiled headers" OFF)
    option(mgtl_ENABLE_CACHE "Enable ccache" ON)
    option(mgtl_ENABLE_IWYS "Enable IncludeWhatYouSee" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      mgtl_ENABLE_IPO
      mgtl_WARNINGS_AS_ERRORS
      mgtl_ENABLE_USER_LINKER
      mgtl_ENABLE_SANITIZER_ADDRESS
      mgtl_ENABLE_SANITIZER_LEAK
      mgtl_ENABLE_SANITIZER_UNDEFINED
      mgtl_ENABLE_SANITIZER_THREAD
      mgtl_ENABLE_SANITIZER_MEMORY
      mgtl_ENABLE_UNITY_BUILD
      mgtl_ENABLE_CLANG_TIDY
      mgtl_ENABLE_CPPCHECK
      mgtl_ENABLE_COVERAGE
      mgtl_ENABLE_PCH
      mgtl_ENABLE_IWYS
      mgtl_ENABLE_CACHE)
  endif()

  mgtl_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (mgtl_ENABLE_SANITIZER_ADDRESS OR mgtl_ENABLE_SANITIZER_THREAD OR mgtl_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(mgtl_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(mgtl_global_options)
  if(mgtl_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    mgtl_enable_ipo()
  endif()

  mgtl_supports_sanitizers()

  if(mgtl_ENABLE_HARDENING AND mgtl_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR mgtl_ENABLE_SANITIZER_UNDEFINED
       OR mgtl_ENABLE_SANITIZER_ADDRESS
       OR mgtl_ENABLE_SANITIZER_THREAD
       OR mgtl_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${mgtl_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${mgtl_ENABLE_SANITIZER_UNDEFINED}")
    mgtl_enable_hardening(mgtl_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(mgtl_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(mgtl_warnings INTERFACE)
  add_library(mgtl_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  mgtl_set_project_warnings(
    mgtl_warnings
    ${mgtl_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(mgtl_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(mgtl_options)
  endif()

  include(cmake/Sanitizers.cmake)
  mgtl_enable_sanitizers(
    mgtl_options
    ${mgtl_ENABLE_SANITIZER_ADDRESS}
    ${mgtl_ENABLE_SANITIZER_LEAK}
    ${mgtl_ENABLE_SANITIZER_UNDEFINED}
    ${mgtl_ENABLE_SANITIZER_THREAD}
    ${mgtl_ENABLE_SANITIZER_MEMORY})

  set_target_properties(mgtl_options PROPERTIES UNITY_BUILD ${mgtl_ENABLE_UNITY_BUILD})

  if(mgtl_ENABLE_PCH)
    target_precompile_headers(
      mgtl_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(mgtl_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    mgtl_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(mgtl_ENABLE_CLANG_TIDY)
    mgtl_enable_clang_tidy(mgtl_options ${mgtl_WARNINGS_AS_ERRORS})
  endif()

  if(mgtl_ENABLE_IWYS)
    mgtl_enable_include_what_you_use()
  endif()

  if(mgtl_ENABLE_CPPCHECK)
    mgtl_enable_cppcheck(${mgtl_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(mgtl_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    mgtl_enable_coverage(mgtl_options)
  endif()

  if(mgtl_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(mgtl_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(mgtl_ENABLE_HARDENING AND NOT mgtl_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR mgtl_ENABLE_SANITIZER_UNDEFINED
       OR mgtl_ENABLE_SANITIZER_ADDRESS
       OR mgtl_ENABLE_SANITIZER_THREAD
       OR mgtl_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    mgtl_enable_hardening(mgtl_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
