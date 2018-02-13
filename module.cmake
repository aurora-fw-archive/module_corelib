# ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
# ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
# ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
# A Powerful General Purpose Framework
# More information in: https://aurora-fw.github.io/
#
# Copyright (C) 2017 Aurora Framework, All rights reserved.
#
# This file is part of the Aurora Framework. This framework is free
# software; you can redistribute it and/or modify it under the terms of
# the GNU Lesser General Public License version 3 as published by the
# Free Software Foundation and appearing in the file LICENSE included in
# the packaging of this file. Please review the following information to
# ensure the GNU Lesser General Public License version 3 requirements
# will be met: https://www.gnu.org/licenses/lgpl-3.0.html.

message(STATUS "Loading corelib module...")

if (NOT CONFIGURED_ONCE)
	set(AURORAFW_MODULE_CORELIB_SOURCE_DIR ${AURORAFW_MODULE_CORELIB_DIR}/src)
endif()

include_directories(${AURORAFW_MODULE_CORELIB_DIR}/include)

file(GLOB_RECURSE AURORAFW_MODULE_CORELIB_HEADERS ${AURORAFW_MODULE_CORELIB_DIR}/include/*.*)
file(GLOB_RECURSE AURORAFW_MODULE_CORELIB_SOURCE ${AURORAFW_MODULE_CORELIB_SOURCE_DIR}/*.*)

add_library (aurorafw-corelib SHARED ${AURORAFW_MODULE_CORELIB_SOURCE})
aurora_add_library_target(aurorafw-corelib SHARED)

if(AURORA_PCH)
	add_precompiled_header(aurorafw-corelib "${AURORAFW_MODULE_CORELIB_HEADERS}")
endif()

target_link_libraries(aurorafw-corelib aurorafw-stdl-cc)

set_target_properties(aurorafw-corelib PROPERTIES OUTPUT_NAME "aurorafw-corelib_${AURORA_PLATFORM_PREFIX}_${AURORA_CPUARCH_PREFIX}")

install(TARGETS aurorafw-corelib DESTINATION lib)

file(GLOB AURORAFW_MODULE_CORELIB_HEADERS_AURORAFW ${AURORAFW_MODULE_CORELIB_DIR}/include/AuroraFW/*.*)
file(GLOB AURORAFW_MODULE_CORELIB_HEADERS_CORELIB ${AURORAFW_MODULE_CORELIB_DIR}/include/AuroraFW/CoreLib/*.*)

install(FILES ${AURORAFW_MODULE_CORELIB_HEADERS_AURORAFW} DESTINATION include/AuroraFW/)
install(FILES ${AURORAFW_MODULE_CORELIB_HEADERS_CORELIB} DESTINATION include/AuroraFW/CoreLib)