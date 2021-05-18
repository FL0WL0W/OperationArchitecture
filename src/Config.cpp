#include "Config.h"
#include "stdint.h"

#ifdef CONFIG_H
namespace OperationArchitecture
{
	void Config::OffsetConfig(const void *&config, size_t &totalSize, size_t offset) 
	{
		config = reinterpret_cast<const uint8_t *>(config) + offset;
		totalSize += offset;
	}
	void Config::AlignConfig(const void *&config, size_t &totalSize, size_t align)
	{
		OffsetConfig(config, totalSize, reinterpret_cast<size_t>(config) % align);
	}
	void Config::OffsetConfig(void *&config, size_t &totalSize, size_t offset) 
	{
		config = reinterpret_cast<uint8_t *>(config) + offset;
		totalSize += offset;
	}
	void Config::AlignConfig(void *&config, size_t &totalSize, size_t align)
	{
		OffsetConfig(config, totalSize, reinterpret_cast<size_t>(config) % align);
	}
}
#endif
