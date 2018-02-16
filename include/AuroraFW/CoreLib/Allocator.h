/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#ifndef AURORAFW_CORELIB_ALLOCATOR_H
#define AURORAFW_CORELIB_ALLOCATOR_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/CoreLib/MemoryManager.h>

namespace AuroraFW {
	class AFW_API MemoryAllocator {
	public:
		MemoryAllocator();
		MemoryAllocator(MemoryStats );
		~MemoryAllocator();

		inline void* allocate(size_t size) { return allocate(size, _stats); }
		inline void* allocate(size_t size, const char* file, uint line) { return allocate(size, _stats, file, line); }
		static void* allocate(size_t , MemoryStats& );
		static void* allocate(size_t , MemoryStats& , const char* , uint );

		inline void free(void* block) { free(block, _stats); }
		inline void free(void* block, size_t size) { free(block, size, _stats); }
		static void free(void* , MemoryStats& );
		static void free(void* , size_t , MemoryStats& );

		inline MemoryStats getMemoryStats() const { return _stats; }

	private:
		MemoryStats _stats;
	};
}

#ifdef AFW__DEBUG
#define AFW_NEW new(__FILE__, __LINE__)
#else
#define AFW_NEW new
#endif
#define AFW_DELETE delete

inline void* operator new(size_t size)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats());
}

inline void* operator new(size_t size, const char* file, uint line)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats(), file, line);
}

inline void* operator new[](size_t size)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats());
}

inline void* operator new[](size_t size, const char* file, uint line)
{
	return AuroraFW::MemoryAllocator::allocate(size, AuroraFW::MemoryManager::getMemoryStats(), file, line);
}

inline void operator delete(void* block) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete[](void* block) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete(void* block, size_t size) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, size, AuroraFW::MemoryManager::getMemoryStats());
}

inline void operator delete[](void* block, size_t size) AFW_NOEXCEPT
{
	AuroraFW::MemoryAllocator::free(block, size, AuroraFW::MemoryManager::getMemoryStats());
}

#endif // AURORAFW_CORELIB_ALLOCATOR_H
