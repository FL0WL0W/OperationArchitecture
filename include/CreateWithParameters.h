#ifndef CREATEWITHPARAMETERS_H
#define CREATEWITHPARAMETERS_H

namespace OperationArchitecture
{
    class ICreateWithParameters
    {
        public:
        virtual IOperationBase* Create(const void *config, unsigned int &sizeOut) = 0;
    };

    template<typename... PARAMS>
    class CreateWithParameters : public ICreateWithParameters
    {
        protected:
        IOperationBase*(*_factory)(const void *, unsigned int &, PARAMS...);
		std::tuple<PARAMS...> _params;

		template<std::size_t... Is>
		IOperationBase* CreateWithTuple(const void *config, unsigned int &sizeOut, const std::tuple<PARAMS...>& tuple, std::index_sequence<Is...>) {
			return _factory(config, sizeOut, std::get<Is>(tuple)...);
		}

        public:
		CreateWithParameters(IOperationBase*(*factory)(const void *, unsigned int &, PARAMS...), PARAMS... params)
		{
            _factory = factory;
			_params = std::tuple<PARAMS...>(params...);
		}
        IOperationBase* Create(const void *config, unsigned int &sizeOut) override
        {
            return CreateWithTuple(config, sizeOut, _params, std::index_sequence_for<PARAMS...>());
        }
    };
}

#endif