project(apps)

# Resolves issue with unable to debug with CLion, reverts back to g++9
if(NOT MSVC)
add_compile_options(-gdwarf-4)
endif()

# Create the exectuable
add_executable(examplePlot examplePlot.cpp)
add_executable(movingTimeframe movingTimeframe.cpp)

if(MSVC)
target_compile_options(examplePlot PRIVATE /wd4244 /wd4464 /wd5045)
target_compile_options(movingTimeframe PRIVATE /wd4244 /wd4464 /wd5045)
target_link_options(examplePlot PRIVATE /NODEFAULTLIB:library)
target_link_options(movingTimeframe PRIVATE /NODEFAULTLIB:library)
endif()

# Link the static library from subproject 1
target_link_libraries(examplePlot PRIVATE openGLPlotLive ${LIBS})
target_link_libraries(movingTimeframe PRIVATE openGLPlotLive ${LIBS})

# Copy Shader files to build directory
add_custom_command(TARGET examplePlot PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../Shaders $<TARGET_FILE_DIR:examplePlot>/Shaders)

# Copy Texture files to build directory
add_custom_command(TARGET examplePlot PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../textures $<TARGET_FILE_DIR:examplePlot>/textures)