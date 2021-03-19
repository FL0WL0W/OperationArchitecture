#include "Operations/IOperation.h"
#include "Packed.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_2AXISTABLE_H
#define OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	PACK(
	struct Operation_2AxisTableConfig
	{
	private:
		Operation_2AxisTableConfig()
		{
			
		}
		
	public:		
		constexpr const unsigned int Size() const
		{
			return sizeof(Operation_2AxisTableConfig) +
				(VariableTypeSizeOf(TableType) * XResolution * YResolution);
		}

		const void *Table() const { return this + 1; }
		
		float MinXValue;
		float MaxXValue;
		uint8_t XResolution;
		float MinYValue;
		float MaxYValue;
		uint8_t YResolution;
		VariableType TableType;
	});

	class Operation_2AxisTable : public IOperationBase
	{
	protected:
		const Operation_2AxisTableConfig *_config;
	public:		
        Operation_2AxisTable(const Operation_2AxisTableConfig * const &config);

		void AbstractExecute(Variable &ret, Variable *params) override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif