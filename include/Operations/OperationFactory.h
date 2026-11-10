#include <map>
#include <list>
#include "Operations/AbstractOperation.h"

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	typedef AbstractOperation* (*OperationFactoryCreate)(const void *, size_t &);
	struct OperationFactoryEntry
	{
		uint32_t ID;
		OperationFactoryCreate Create;
	};

	// Helper to compute the sum of template parameters (C++11 compatible)
	template<std::size_t... Sizes>
	struct SumSizes;
	
	template<>
	struct SumSizes<> {
		static constexpr std::size_t value = 0;
	};
	
	template<std::size_t Head, std::size_t... Tail>
	struct SumSizes<Head, Tail...> {
		static constexpr std::size_t value = Head + SumSizes<Tail...>::value;
	};

	// Helper to copy entries - uses recursion  on template parameters
	namespace detail {
		// Base case: no arrays to combine
		template<std::size_t Total>
		inline std::array<OperationFactoryEntry, Total> combine_arrays(std::array<OperationFactoryEntry, Total> result)
		{
			return result;
		}
		
		// Recursive case: combine first array with rest
		template<std::size_t Head, std::size_t... Tail>
		inline std::array<OperationFactoryEntry, Head + SumSizes<Tail...>::value> 
		combine_arrays(const std::array<OperationFactoryEntry, Head>& first,
					   const std::array<OperationFactoryEntry, Tail>&... rest)
		{
			// Create the result array
			std::array<OperationFactoryEntry, Head + SumSizes<Tail...>::value> result = {};
			
			// Copy the first array
			for (std::size_t i = 0; i < Head; ++i) {
				result[i] = first[i];
			}
			
			// Recursively combine the rest
			auto rest_combined = combine_arrays(rest...);
			for (std::size_t i = 0; i < SumSizes<Tail...>::value; ++i) {
				result[Head + i] = rest_combined[i];
			}
			
			return result;
		}
	}

	// Combine multiple arrays into a single array
	template<std::size_t... Sizes>
	inline std::array<OperationFactoryEntry, SumSizes<Sizes...>::value> CombineEntries(const std::array<OperationFactoryEntry, Sizes>&... entries)
	{
		return detail::combine_arrays(entries...);
	}

	class OperationFactory
	{
	protected:
		std::map<uint32_t, AbstractOperation*> _staticOperations;
		const OperationFactoryEntry *_factories;
		size_t _numberOfFactories;
	public:
		void Clear();
		void Register(const OperationFactoryEntry *factories, size_t numberOfFactories);
		void Register(const uint32_t id, AbstractOperation* operation);
		void Unregister(const uint32_t id);

		//This creates an operation that is owned by the caller and must be deleted by the caller
		AbstractOperation *Create(const void *config, size_t &sizeOut);
	};
}
#endif