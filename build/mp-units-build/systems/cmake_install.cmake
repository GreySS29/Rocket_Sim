# Install script for directory: /home/greys/Documents/Doc/C+/mp-units/src/systems

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/angular.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/astronomy.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/cgs.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/hep.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iau.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec80000.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/imperial.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/international.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq_angle.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/natural.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/typographic.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/usc.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/yard_pound.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/angular" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/angular/units.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/angular/math.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/codata" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/adopted_values.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2014.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2014_essential.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2018.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2018_essential.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2022.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/codata2022_essential.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/codata/math_constants.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/hep" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/hep/constants.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/hep/quantities.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/hep/units.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/iec" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec/binary_prefixes.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec/quantities.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec/unit_symbols.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/iec/units.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/isq" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/atomic_and_nuclear_physics.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/base_quantities.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/electromagnetism.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/information_science_and_technology.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/light_and_radiation.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/mechanics.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/si_quantities.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/space_and_time.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/isq/thermodynamics.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/systems/si" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/constants.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/core.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/prefixes.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/unit_symbols.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/unit_symbols_essential.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/units.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/math.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/chrono.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/systems/include/mp-units/systems/si/prefix_utils.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/greys/Documents/Doc/C+/my_progect/Rocket_Sim/build/mp-units-build/systems/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
