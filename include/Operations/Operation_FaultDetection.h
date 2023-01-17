#include "Operations/Operation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_FAULTDETECTION_H
#define OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	template<typename compare_t>
	struct Operation_FaultDetectionConfig
	{
	public:
		size_t Size() const
		{
			size_t s = sizeof(compare_t);
			Config::AlignAndAddSize<compare_t>(s);
			Config::AlignAndAddSize<compare_t>(s);
			return s;
		}
		
		compare_t MinValue;
		compare_t MaxValue;
		compare_t DefaultValue;
	};

	template<typename compare_t>
	class Operation_FaultDetection : public AbstractOperation
	{
	protected:
		const Operation_FaultDetectionConfig<compare_t> * const _config;
	public:		
        Operation_FaultDetection(const Operation_FaultDetectionConfig<compare_t> * const &config) : AbstractOperation(1, 1), _config(config) {}

		void AbstractExecute(Variable **variables) override
		{
			compare_t test = variables[1]->To<compare_t>();
			if(test < _config->MinValue || test > _config->MaxValue)
			{
				switch(variables[1]->Type)
				{
					case UINT8:
						variables[0]->Set<uint8_t>(_config->DefaultValue);
						break;
					case UINT16:
						variables[0]->Set<uint16_t>(_config->DefaultValue);
						break;
					case UINT32:
						variables[0]->Set<uint32_t>(_config->DefaultValue);
						break;
					case UINT64:
						variables[0]->Set<uint64_t>(_config->DefaultValue);
						break;
					case INT8:
						variables[0]->Set<int8_t>(_config->DefaultValue);
						break;
					case INT16:
						variables[0]->Set<int16_t>(_config->DefaultValue);
						break;
					case INT32:
						variables[0]->Set<int32_t>(_config->DefaultValue);
						break;
					case INT64:
						variables[0]->Set<int64_t>(_config->DefaultValue);
						break;
					case FLOAT:
						variables[0]->Set<float>(_config->DefaultValue);
						break;
					case DOUBLE:
						variables[0]->Set<double>(_config->DefaultValue);
						break;
					case BOOLEAN:
						variables[0]->Set<bool>(_config->DefaultValue);
						break;
					default:
						//should throw here
						break;
				}
			}
			else
			{
				variables[0]->Set(*variables[1]);
			}
		}

		static AbstractOperation *Create(const void *config, size_t &sizeOut)
		{
			const Operation_FaultDetectionConfig<compare_t> *faultConfig = Config::CastConfigAndOffset<Operation_FaultDetectionConfig<compare_t>>(config, sizeOut);
			return new Operation_FaultDetection(faultConfig);
		}
	};
}
#endif