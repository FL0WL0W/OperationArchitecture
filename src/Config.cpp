#include "Config.h"

#ifdef CONFIG_H
namespace OperationArchitecture
{
	void Config::OffsetConfig(const void *&config, unsigned int &totalSize, unsigned int offset) 
	{
		config = reinterpret_cast<const void *>(reinterpret_cast<const uint8_t *>(config) + offset);
		totalSize += offset;
	}
}
#endif
