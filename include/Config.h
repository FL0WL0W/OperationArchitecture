#include "stddef.h"

#ifndef CONFIG_H
#define CONFIG_H

namespace OperationArchitecture
{
    class Config
    {
        public:		
		static void OffsetConfig(const void *&config, size_t &totalSize, size_t offset);
		static void AlignConfig(const void *&config, size_t &totalSize, size_t align);
		static void OffsetConfig(void *&config, size_t &totalSize, size_t offset);
		static void AlignConfig(void *&config, size_t &totalSize, size_t align);

		template<typename T>
		static const T* CastConfigAndOffset(const void *&config, size_t &size)
		{
			AlignConfig(config, size, alignof(const T));
			const T *castedConfig = reinterpret_cast<const T *>(config);
			OffsetConfig(config, size, castedConfig->Size());
			
			return castedConfig;
		}
		
		template<typename T>
		static const T CastAndOffset(const void *&config, size_t &size)
		{
			AlignConfig(config, size, alignof(const T));
			const T casted = *reinterpret_cast<const T *>(config);
			OffsetConfig(config, size, sizeof(T));
			
			return casted;
		}
    };
}

#endif