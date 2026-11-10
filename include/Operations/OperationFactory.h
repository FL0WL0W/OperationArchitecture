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

	// Helper to copy entries recursively
	namespace detail {
		template<std::size_t... Sizes>
		struct CombineEntryImpl;
		
		template<>
		struct CombineEntryImpl<> {
			static void copy(std::array<OperationFactoryEntry, 0>&, std::size_t&) {}
		};
		
		template<std::size_t Head, std::size_t... Tail>
		struct CombineEntryImpl<Head, Tail...> {
			static void copy(std::array<OperationFactoryEntry, SumSizes<Head, Tail...>::value>& combined,
							  std::size_t& offset,
							  const std::array<OperationFactoryEntry, Head>& first,
							  const std::array<OperationFactoryEntry, Tail>&... rest) {
				for (std::size_t i = 0; i < Head; ++i) {
					combined[offset++] = first[i];
				}
				CombineEntryImpl<Tail...>::copy(combined, offset, rest...);
			}
		};
	}

	template<std::size_t... Sizes>
	std::array<OperationFactoryEntry, SumSizes<Sizes...>::value> CombineEntries(const std::array<OperationFactoryEntry, Sizes>&... entries)
	{
		std::array<OperationFactoryEntry, SumSizes<Sizes...>::value> combinedEntries = {};
		std::size_t offset = 0;
		detail::CombineEntryImpl<Sizes...>::copy(combinedEntries, offset, entries...);
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