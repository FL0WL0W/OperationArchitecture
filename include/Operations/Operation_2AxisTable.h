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
		
	public:		
		constexpr const size_t Size() const
		{
			return sizeof(Operation_2AxisTableConfig) + 
				((sizeof(Operation_2AxisTableConfig) % VariableTypeAlignOf(TableType) > 0)? (VariableTypeAlignOf(TableType) - (sizeof(Operation_2AxisTableConfig) % VariableTypeAlignOf(TableType))) : 0) + 
				(VariableTypeSizeOf(TableType) * XResolution * YResolution);
		}

		const void *Table() const { return Config::AlignConfig(this + 1, VariableTypeAlignOf(TableType)); }
		
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