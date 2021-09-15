#ifndef __CHESTNUT_RESOURCE_H__
#define __CHESTNUT_RESOURCE_H__

namespace chestnut
{
    class IResource
    {
    public:
        virtual ~IResource() = default;

        virtual bool isValid() const = 0;
    };

} // namespace chestnut

#endif // __CHESTNUT_RESOURCE_H__