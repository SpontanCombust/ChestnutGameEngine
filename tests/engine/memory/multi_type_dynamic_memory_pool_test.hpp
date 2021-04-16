#include "engine/memory/multi_type_dynamic_memory_pool.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
namespace test
{
    void multiTypeDynamicMemoryPoolTest()
    {
        struct Foo
        {
            int foo;
            virtual ~Foo() = default;
        };

        struct Bar : Foo
        {
            float bar;
        };

        CMultiTypeDynamicMemoryPool mempool;

        LOG_CHANNEL( "TEST", "<<Memory pool test>>" );
        {
            int *tmp1 = mempool.create<int>();
            Foo *tmp2 = (Foo *)mempool.create<Bar>();
            
            mempool.remove( tmp1 );
            int *tmp3 = mempool.create<int>();

            mempool.remove( tmp2 );
            Bar *tmp4 = mempool.create<Bar>();

            mempool.remove( tmp3 );
            mempool.remove( tmp4 );
        }
        LOG_CHANNEL( "TEST", "" );
    }

} // namespace test

} // namespace chestnut
