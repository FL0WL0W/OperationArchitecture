#include <map>

#ifndef GENERATORMAP_H
#define GENERATORMAP_H
namespace OperationArchitecture
{
    template<typename VALUE>
	class GeneratorMap : public std::map<uint32_t, VALUE*>
	{
	public:		
    	VALUE *GenerateValue(uint32_t id)
        {
            VALUE *ret;
            typename GeneratorMap::iterator it = this->find(id);
            if (it == this->end())
            {
                ret = new VALUE();
                this->insert(std::pair<uint32_t, VALUE *>(id, ret));
            }
            else
            {
                ret = it->second;
            }

            return ret;
        }
	};
}
#endif