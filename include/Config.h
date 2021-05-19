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
		static const void *OffsetConfig(const void *config, size_t offset);
		static const void *AlignConfig(const void *config, size_t align);

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
		
		template<typename T>
		static void AssignAndOffset(void *&config, size_t &size, T value)
		{
			AlignConfig(config, size, alignof(const T));
			*reinterpret_cast<T *>(config) = value;
			OffsetConfig(config, size, sizeof(T));
		}
		
		template<typename T>
		static constexpr void AlignAndAddSize(size_t &size)
		{
			if(size % alignof(T) != 0)
				size += alignof(T) - (size % alignof(T));
			size += sizeof(T);
		}
    };
}

#endif