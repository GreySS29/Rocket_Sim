# Install script for directory: /home/greys/Documents/Doc/C+/mp-units/src/core

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/compat_macros.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/core.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/math.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/overflow_policies.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/format.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ostream.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/bits" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/constexpr_math.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/core_gmf.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/double_width_int.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/fixed_point.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/int_power.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/get_associated_quantity.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/hacks.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/import_std_prelude.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/module_macros.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/quantity_spec_conversion_impl.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/quantity_spec_equation_conversion.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/quantity_spec_hierarchy_conversion.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/quantity_spec_hierarchy.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/ratio.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/sudo_cast.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/text_tools.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/type_list.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/unit_conversion_impl.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/unit_magnitude.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/unsatisfied.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/constexpr_format.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/ostream.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/bits/requires_hosted.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/ext" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/algorithm.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/contracts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/fixed_string.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/inplace_vector.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/prime.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/type_name.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/type_traits.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/ext/format.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/framework" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/compare.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/construction_helpers.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/customization_points.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/dimension.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/dimension_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/point_origin_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_cast.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_character.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_point.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_point_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_spec.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_spec_conversion.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_spec_definitions.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_spec_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/quantity_traits.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/reference.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/reference_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/representation_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/rounding.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/scaling.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/symbol_text.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/symbolic_expression.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_conversion.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_definitions.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_text.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_magnitude.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_magnitude_concepts.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/unit_symbol_formatting.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/value_cast.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/framework/vector_components.h"
    )
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mp-units/utility" TYPE FILE FILES
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/utility/constrained.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/utility/safe_int.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/utility/representation.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/utility/unspecified.h"
    "/home/greys/Documents/Doc/C+/mp-units/src/core/include/mp-units/utility/format.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/greys/Documents/Doc/C+/my_progect/Rocket_Sim/build/mp-units-build/core/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
