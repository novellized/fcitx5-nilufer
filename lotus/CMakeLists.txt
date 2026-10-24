# SPDX-FileCopyrightText: 2026 Nilüfer Team
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
# Turkish Telex input engine for Nilüfer.
set(CMAKE_UNITY_BUILD_BATCH_SIZE 8)
if(NOT DEFINED CMAKE_UNITY_BUILD)
    set(CMAKE_UNITY_BUILD OFF)
endif()
add_library(lotus_engine STATIC
    case_map.cpp
    dictionary.cpp
    encoder.cpp
    input_method.cpp
    key_processor.cpp
    macro_table.cpp
    utf8.cpp
)
set_target_properties(lotus_engine PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
target_compile_options(lotus_engine PRIVATE -Wall -Wextra)
target_include_directories(lotus_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(Lotus::Engine ALIAS lotus_engine)
