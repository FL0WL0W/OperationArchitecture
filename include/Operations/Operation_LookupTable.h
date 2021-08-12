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

		const void *Table() const { return reinterpret_cast<const uint8_t *>(this) + size(); }
		
		float MinXValue;
		float MaxXValue;
		uint8_t XResolution;
		VariableType TableType;
	};

	class Operation_LookupTable
	{
	public:		
		static Operation *Construct(const Operation_LookupTableConfig * const &tableConfig);
		static Operation *Create(const void *config, size_t &sizeOut);
	};
}
#endif