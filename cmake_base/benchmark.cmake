
function(AddBenchmark targetName)
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
    #PRIVATE mgtl::mgtl_warnings
    #mgtl::mgtl_options
    mgtl::sample_library
    nanobench)
  #[[
  if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(
      TARGET ${targetName}
      PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:nemchmarks> $<TARGET_FILE_DIR:benchmarks>
      COMMAND_EXPAND_LISTS)
  endif()

  #]]
endfunction()

