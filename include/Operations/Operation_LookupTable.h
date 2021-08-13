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
		constexpr const size_t size() const
		{
			const size_t a = VariableTypeAlignOf(TableType);
			size_t s = sizeof(float);
			Config::AlignAndAddSize<float>(s);
			Config::AlignAndAddSize<uint8_t>(s);
			Config::AlignAndAddSize<VariableType>(s);
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		constexpr const size_t Size() const
		{
			size_t s = size();
			s += VariableTypeSizeOf(TableType) * XResolution;
			return s;
		}

		template<typename TABLE_TYPE>
		const TABLE_TYPE *Table() const { return reinterpret_cast<const TABLE_TYPE *>(reinterpret_cast<const uint8_t *>(this) + size()); }
		
		float MinXValue;
		float MaxXValue;
		uint8_t XResolution;
		VariableType TableType;
	};

	template<typename TABLE_TYPE>
	class Operation_LookupTable : public IOperationBase
	{
	protected:
		const Operation_LookupTableConfig *_config;
	public:		
        Operation_LookupTable(const Operation_LookupTableConfig * const &config) : IOperationBase(1, 1), _config(config) { }

		void AbstractExecute(Variable **variables) override
		{
			variables[0]->Set(Interpolation::InterpolateTable1<TABLE_TYPE>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, _config->Table<TABLE_TYPE>()));
		}
	};

	IOperationBase *Operation_LookupTableCreate(const void *config, size_t &sizeOut);
}
#endif