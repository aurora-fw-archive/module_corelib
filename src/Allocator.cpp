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

#include <AuroraFW/CoreLib/Allocator.h>
#include <AuroraFW/STDL/LibC/Assert.h>
#include <AuroraFW/STDL/LibC/String.h>
#include <AuroraFW/Core/DebugManager.h>

namespace AuroraFW {
	MemoryAllocator::MemoryAllocator()
		: _stats({0,0,0,0})
	{}

	MemoryAllocator::MemoryAllocator(MemoryStats stats)
		: _stats(stats)
	{}

	MemoryAllocator::~MemoryAllocator()
	{}

	void* MemoryAllocator::allocate(size_t size, MemoryStats &stats)
	{
		assert(size < 1024 * 1024 * 1024);
		stats.add(size);
		size_t asize = size + sizeof(size_t);
		byte_t* ret = (byte_t*)AFW_ALIGNED_ALLOC(asize, 16);
		memset(ret, 0, asize);
		memcpy(ret, &size, sizeof(size_t));
		ret += sizeof(size_t);
		return ret;
	}

	void* MemoryAllocator::allocate(size_t size, MemoryStats &stats, const char* file, uint line)
	{
		assert(size < 1024 * 1024 * 1024);
		if(size > 1024 * 1024)
			DebugManager::Log("Large allocation (>1MB) at ", file, ":", line);

		return allocate(size, stats);
	}

	void MemoryAllocator::free(void* block, MemoryStats &stats)
	{
		byte_t *mem = (byte_t *)block - sizeof(size_t);
		size_t size = *(size_t *)mem;
		stats.remove(size);
		AFW_ALIGNED_FREE(mem);
	}

	void MemoryAllocator::free(void* block, size_t size, MemoryStats &stats)
	{
		stats.remove(size);
		AFW_ALIGNED_FREE((byte_t *)block - sizeof(size_t));
	}
}
