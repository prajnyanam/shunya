
#--------------------------------------------------------------------------------------------------
# Configure source code formatting tools
# Apply auto-formatting by calling add_clang_format() on target
# The provided script formats all specified files during the initial build. 
# Once a file has been formatted, it will only reformat files that are touched or modified in subsequent builds.
#--------------------------------------------------------------------------------------------------
option(ENABLE_CLANG_FORMAT "Enable automatic source file formatting with clang-format" ON)

if(ENABLE_CLANG_FORMAT)
  find_program(CLANG_FORMAT_BIN NAMES clang-format QUIET)
  if(NOT CLANG_FORMAT_BIN)
    message(WARNING "clang-format requested but not found")
  endif()
endif()

# print summary
message(STATUS "Auto-format code (ENABLE_CLANG_FORMAT): ${ENABLE_CLANG_FORMAT} ${CLANG_FORMAT_BIN}")

# Target to run clang-format on all files without having to compile them
add_custom_target(format)


function(add_clang_format _targetname)
  if (CLANG_FORMAT_BIN AND ENABLE_CLANG_FORMAT)
    # Ensure the target exists
    if (NOT TARGET ${_targetname})
      message(FATAL_ERROR "add_clang_format should only be called on targets (got " ${_targetname} ")")
    endif()

    # Supported file extensions for clang-format
    set(_supported_file_types ".c" ".cc" ".cpp" ".h" ".hpp" ".inl")

    # Construct GLOB patterns dynamically
    set(_patterns "")
    foreach (_ext ${_supported_file_types})
      list(APPEND _patterns "${CMAKE_SOURCE_DIR}/*${_ext}")
    endforeach()

    # Automatically detect all source files in the current project directory
    file(GLOB_RECURSE _clang_sources ${_patterns})

    if (NOT _clang_sources)
      message(WARNING "No source files found for clang-format in ${CMAKE_SOURCE_DIR}")
      return()
    endif()

    set(_sources "")
    foreach (_source ${_clang_sources})
      get_filename_component(_ext_type ${_source} EXT)
      if (${_ext_type} IN_LIST _supported_file_types)
        get_filename_component(_source_file ${_source} NAME)
        MATH(EXPR counter "${counter}+1")
        set(_format_file .${CMAKE_FILES_DIRECTORY}/${_targetname}_${counter}_${_source_file}.format)

        # Add custom command to format files
        add_custom_command(
          OUTPUT ${_format_file}
          DEPENDS ${_source}
          COMMAND ${CLANG_FORMAT_BIN} -style=file -i ${_source}
          COMMAND ${CMAKE_COMMAND} -E touch ${_format_file}
          COMMENT "Formatting ${_source}"
        )

        list(APPEND _sources ${_format_file})
      endif()
    endforeach()

    if (_sources)
      add_custom_target(${_targetname}_clangformat
        SOURCES ${_sources}
        COMMENT "Clang-Format for target ${_targetname}"
      )
      add_dependencies(${_targetname} ${_targetname}_clangformat)
      add_dependencies(format ${_targetname}_clangformat)
    endif()
  endif() # CLANG_FORMAT_BIN found
endfunction()