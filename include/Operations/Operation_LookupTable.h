#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_LOOKUPTABLE_H
#define OPERATION_LOOKUPTABLE_H
namespace OperationArchitecture
{
	struct Operation_LookupTableConfig
	{
	private:
		Operation_LookupTableConfig()
		{
			
		}
		
	public:		
		constexpr const size_t Size() const
		{
			return sizeof(Operation_LookupTableConfig) + 
				((sizeof(Operation_LookupTableConfig) % VariableTypeAlignOf(TableType) > 0)? (VariableTypeAlignOf(TableType) - (sizeof(Operation_LookupTableConfig) % VariableTypeAlignOf(TableType))) : 0) + 
				(VariableTypeSizeOf(TableType) * XResolution);
		}

		const void *Table() const { return Config::AlignConfig(this + 1, VariableTypeAlignOf(TableType)); }
		
		float MinXValue;
		float MaxXValue;
		uint8_t XResolution;
		VariableType TableType;
	};

	class Operation_LookupTable : public IOperationBase
	{
	protected:
		const Operation_LookupTableConfig *_config;
	public:		
        Operation_LookupTable(const Operation_LookupTableConfig * const &config);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif