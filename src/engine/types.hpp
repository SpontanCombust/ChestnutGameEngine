#ifndef __CHESTNUT_TYPES_H__
#define __CHESTNUT_TYPES_H__

#include <cstdint>
#include <typeindex>

namespace chestnut
{
    typedef uint64_t entityid_t;

    typedef unsigned int listenerid_t;
    
    typedef void event_function;

    typedef unsigned int timerid_t;

    typedef std::type_index componenttindex_t;

    typedef std::type_index eventtindex_t;

} // namespace chestnut


#endif // __CHESTNUT_TYPES_H__