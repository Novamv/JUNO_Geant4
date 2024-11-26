#----------------------------------------------------------------------------
set(useROOT true)
# Setup the project
cmake_minimum_required(VERSION 3.16...3.27)
project(JunoG4)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
#
find_package(Geant4 REQUIRED ui_all vis_all)
# find_package(Geant4 11.1.0 REQUIRED)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
#if(useROOT)
#        EXECUTE_PROCESS(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")
#endif(useROOT)
find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${ROOT_INCLUDE_DIR}
    ${Geant4_INCLUDE_DIR}
)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(juno juno.cc ${sources} ${headers})
target_link_libraries(juno ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory
#
set(Juno_SCRIPTS
    runDebug.mac
    run.mac
)

foreach(_script ${Juno_SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${PROJECT_BINARY_DIR}/${_script}
    )
endforeach(_script ${Juno_scripts})

