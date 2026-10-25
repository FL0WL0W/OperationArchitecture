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

	template<std::size_t... Sizes>
	constexpr std::array<OperationFactoryEntry, (Sizes + ...)> CombineEntries(const std::array<OperationFactoryEntry, Sizes>&... entries)
	{
		std::array<OperationFactoryEntry, (Sizes + ...)> combinedEntries;
		std::size_t offset = 0;

		// A simple fold expression to copy each array into combinedEntries
		auto copy_elements = [&combinedEntries, &offset](const auto& arr) {
			for (std::size_t i = 0; i < arr.size(); ++i) {
				combinedEntries[offset++] = arr[i];
			}
		};
		(copy_elements(entries), ...);

		return combinedEntries;
	}

	class OperationFactory
	{
	protected:
		std::map<uint32_t, AbstractOperation*> _staticOperations;
		const OperationFactoryEntry *_factories;
		size_t _numberOfFactories;
	public:
		void Delete();
		void Register(const OperationFactoryEntry *factories, size_t numberOfFactories);
		void Register(const uint32_t id, AbstractOperation* operation);
		void Unregister(const uint32_t id);

		//This creates an operation that is owned by the caller and must be deleted by the caller
		AbstractOperation *Create(const void *config, size_t &sizeOut);
	};
}
#endif