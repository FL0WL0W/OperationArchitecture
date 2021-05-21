#ifndef CREATEWITHPARAMETERS_H
#define CREATEWITHPARAMETERS_H

namespace OperationArchitecture
{
    class ICreateWithParameters
    {
        public:
        virtual IOperationBase* Create(const void *config, size_t &sizeOut) = 0;
    };

    template<typename... PARAMS>
    class CreateWithParameters : public ICreateWithParameters
    {
        protected:
        IOperationBase*(*_factory)(const void *, size_t &, PARAMS...);
		std::tuple<PARAMS...> _params;

        public:
		CreateWithParameters(IOperationBase*(*factory)(const void *, size_t &, PARAMS...), PARAMS... params)
		{
            _factory = factory;
			_params = std::tuple<PARAMS...>(params...);
		}
        IOperationBase* Create(const void *config, size_t &sizeOut) override
        {
            return  _factory(config, sizeOut, std::get<PARAMS>(_params)...);
        }
    };
}

#endif