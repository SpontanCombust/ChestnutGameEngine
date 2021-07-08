#ifndef __CHESTNUT_COMPONENT_STORAGE_H__
#define __CHESTNUT_COMPONENT_STORAGE_H__

#include "component_storage_segment.hpp"
#include "../component.hpp"

#include <deque>
#include <unordered_map>

namespace chestnut
{
    class IComponentStorage
    {
    protected:
        size_t m_segmentSize;

        unsigned int m_segmentIDCounter;
        std::unordered_map< entityid_t, unsigned int > m_mapEntityIDToSegmentID;

    public:
        IComponentStorage( size_t segmentSize );
        virtual ~IComponentStorage() = default;

        // Number of components fitting in single segment
        size_t getSegmentSize() const;

        virtual IComponent *createComponent( entityid_t entityID ) = 0;
        virtual IComponent *getComponent( entityid_t entityID ) const = 0;
        virtual bool hasComponent( entityid_t entityID ) const = 0;
        virtual void eraseComponent( entityid_t entityID ) = 0;
        virtual void clearComponents() = 0;
        // Makes it so the storage can store specified amount of components
        // The end result is equal or greater than totalSize depending on storage's segment size
        virtual void reserveComponents( size_t totalSize ) = 0;
        // Allocates additional memory for specified amount of compoenents
        // The end result is equal or greater than additionalSize depending on storage's segment size
        virtual void reserveMoreComponents( size_t additionalSize ) = 0;
        virtual size_t getComponentCount() const = 0;
        virtual size_t getComponentCapacity() const = 0;
        // Returns the amount of segments which store components
        virtual unsigned int getSegmentCount() const = 0;
        // Returns the amount of segments with all free slots for components
        virtual unsigned int getEmptySegmentCount() const = 0;
        // Reduces the capacity by deleting all segments that don't store any active components at the moment
        virtual void removeEmptySegments() = 0;
    };


    template< typename C >
    class CComponentStorage : public IComponentStorage
    {
    private:
        std::unordered_map< unsigned int, CComponentStorageSegment<C> * > m_mapSegmentIDToSegmentPtr;
        std::deque< CComponentStorageSegment<C> * > m_dequeAvailableSegments;

    public:
        CComponentStorage( size_t segmentSize );
        ~CComponentStorage();

        IComponent *createComponent( entityid_t entityID ) override;
        bool hasComponent( entityid_t entityID ) const override;
        IComponent *getComponent( entityid_t entityID ) const override;
        void eraseComponent( entityid_t entityID ) override;
        void clearComponents() override;
        void reserveComponents( size_t totalSize ) override;
        void reserveMoreComponents( size_t additionalSize ) override;
        size_t getComponentCount() const override;
        size_t getComponentCapacity() const override;
        unsigned int getSegmentCount() const override;
        unsigned int getEmptySegmentCount() const override;
        void removeEmptySegments() override;

    private:
        CComponentStorageSegment<C> *createNewSegment();
    };

} // namespace chestnut


#include "component_storage.tpp"


#endif // __CHESTNUT_COMPONENT_STORAGE_H__