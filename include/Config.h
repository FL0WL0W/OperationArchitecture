#include "stdint.h"

#ifndef CONFIG_H
#define CONFIG_H

namespace OperationArchitecture
{
    class Config
    {
        public:		
		static void OffsetConfig(const void *&config, unsigned int &totalSize, unsigned int offset);
        
		template<typename T>
		static const T* CastConfigAndOffset(const void *&config, unsigned int &size)
		{
			const T *castedConfig = reinterpret_cast<const T *>(config);
			OffsetConfig(config, size, castedConfig->Size());
			
			return castedConfig;
		}
		
		template<typename T>
		static const T CastAndOffset(const void *&config, unsigned int &size)
		{
			const T casted = *reinterpret_cast<const T *>(config);
			OffsetConfig(config, size, sizeof(T));
			
			return casted;
		}
    };
}

#endif