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
		constexpr const size_t size() const
		{
			const size_t a = VariableTypeAlignOf(TableType);
			size_t s = sizeof(float);
			Config::AlignAndAddSize<float>(s);
			Config::AlignAndAddSize<float>(s);
			Config::AlignAndAddSize<float>(s);
			Config::AlignAndAddSize<uint8_t>(s);
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
			s += VariableTypeSizeOf(TableType) * XResolution * YResolution;
			return s;
		}

		const void *Table() const { return reinterpret_cast<const uint8_t *>(this) + size(); }
		
		float MinXValue;
		float MaxXValue;
		float MinYValue;
		float MaxYValue;
		uint8_t XResolution;
		uint8_t YResolution;
		VariableType TableType;
	};

	class Operation_2AxisTable : public IOperationBase
	{
	protected:
		const Operation_2AxisTableConfig *_config;
	public:		
        Operation_2AxisTable(const Operation_2AxisTableConfig * const &config);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif