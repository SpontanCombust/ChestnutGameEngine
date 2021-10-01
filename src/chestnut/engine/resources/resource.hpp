#ifndef __CHESTNUT_ENGINE_RESOURCE_H__
#define __CHESTNUT_ENGINE_RESOURCE_H__

namespace chestnut::engine
{
    class IResource
    {
    public:
        virtual ~IResource() = default;

        virtual bool isValid() const = 0;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_RESOURCE_H__