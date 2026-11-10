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

	// Helper to copy entries recursively - constexpr compatible
	namespace detail {
		// Base case: no more arrays to copy
		template<std::size_t Total>
		constexpr void copy_array_impl(std::array<OperationFactoryEntry, Total>&, std::size_t) {}
		
		// Recursive case: copy one array and then the rest
		template<std::size_t Total, std::size_t Head, std::size_t... Tail>
		constexpr void copy_array_impl(std::array<OperationFactoryEntry, Total>& combined,
									   std::size_t offset,
									   const std::array<OperationFactoryEntry, Head>& first,
									   const std::array<OperationFactoryEntry, Tail>&... rest)
		{
			// Copy the first array element by element
			for (std::size_t i = 0; i < Head; ++i) {
				combined[offset + i] = first[i];
			}
			// Recursively copy the rest
			copy_array_impl(combined, offset + Head, rest...);
		}
	}

	template<std::size_t... Sizes>
	constexpr std::array<OperationFactoryEntry, SumSizes<Sizes...>::value> CombineEntries(const std::array<OperationFactoryEntry, Sizes>&... entries)
	{
		std::array<OperationFactoryEntry, SumSizes<Sizes...>::value> combinedEntries = {};
		detail::copy_array_impl(combinedEntries, 0, entries...);
		return combinedEntries;
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