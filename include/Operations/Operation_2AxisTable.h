#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_2AXISTABLE_H
#define OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	struct Operation_2AxisTableConfig
	{
	private:
		Operation_2AxisTableConfig()
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
		inline size_t yAxisOffset() const
		{
			size_t s = xAxisOffset();
			s += sizeof(float) * XResolution;
			return s;
		}
		inline size_t tableOffset() const
		{
			const size_t a = VariableTypeAlignOf(TableType);
			size_t s = yAxisOffset();
			s += sizeof(float) * YResolution;
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		size_t Size() const
		{
			size_t s = tableOffset();
			s += VariableTypeSizeOf(TableType) * XResolution * YResolution;
			return s;
		}

		const float *XAxis() const { return reinterpret_cast<const float *>(reinterpret_cast<const uint8_t *>(this) + xAxisOffset()); }
		const float *YAxis() const { return reinterpret_cast<const float *>(reinterpret_cast<const uint8_t *>(this) + yAxisOffset()); }
		template<typename TABLE_TYPE>
		const TABLE_TYPE *Table() const { return reinterpret_cast<const TABLE_TYPE *>(reinterpret_cast<const uint8_t *>(this) + tableOffset()); }
		
		uint8_t XResolution;
		uint8_t YResolution;
		VariableType TableType;
	};

	template<typename TABLE_TYPE>
	class Operation_2AxisTable : public IOperationBase
	{
	protected:
		const Operation_2AxisTableConfig * const _config;
	public:		
        Operation_2AxisTable(const Operation_2AxisTableConfig * const &config) : IOperationBase(1, 2), _config(config) { }

		void AbstractExecute(Variable **variables) override
		{
			variables[0]->Set(Interpolation::InterpolateTable2<TABLE_TYPE>(variables[1]->To<float>(), _config->XAxis(), _config->XResolution, variables[2]->To<float>(), _config->YAxis(), _config->YResolution, _config->Table<TABLE_TYPE>()));
		}
	};
	
	IOperationBase *Operation_2AxisTableCreate(const void *config, size_t &sizeOut);
}
#endif