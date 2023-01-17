#include "Operations/Operation.h"
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
		inline size_t xAxisOffset() const
		{
			const size_t af = alignof(float);
			size_t s = sizeof(uint8_t);
			Config::AlignAndAddSize<uint8_t>(s);
			Config::AlignAndAddSize<VariableType>(s);
			if(s % af > 0)
				s += af - (s % af);
			return s;
		}
		inline size_t tableOffset() const
		{
			const size_t a = VariableTypeAlignOf(TableType);
			size_t s = xAxisOffset();
			s += sizeof(float) * XResolution;
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		size_t Size() const
		{
			size_t s = tableOffset();
			s += VariableTypeSizeOf(TableType) * XResolution;
			return s;
		}

		const float *XAxis() const { return reinterpret_cast<const float *>(reinterpret_cast<const uint8_t *>(this) + xAxisOffset()); }
		template<typename TABLE_TYPE>
		const TABLE_TYPE *Table() const { return reinterpret_cast<const TABLE_TYPE *>(reinterpret_cast<const uint8_t *>(this) + tableOffset()); }
		
		uint8_t XResolution;
		VariableType TableType;
	};

	template<typename TABLE_TYPE>
	class Operation_LookupTable : public AbstractOperation
	{
	protected:
		const Operation_LookupTableConfig *_config;
	public:		
        Operation_LookupTable(const Operation_LookupTableConfig * const &config) : AbstractOperation(1, 1), _config(config) { }

		void AbstractExecute(Variable **variables) override
		{
			variables[0]->Set(Interpolation::InterpolateTable1<TABLE_TYPE>(variables[1]->To<float>(), _config->XAxis(), _config->XResolution, _config->Table<TABLE_TYPE>()));
		}
	};

	AbstractOperation *Operation_LookupTableCreate(const void *config, size_t &sizeOut);
}
#endif