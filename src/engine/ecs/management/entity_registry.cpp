#include "entity_registry.hpp"

#include "engine/debug/debug.hpp"
#include "engine/misc/exception.hpp"

namespace chestnut
{    
    bool CEntityRegistry::addEntity( entityid_t id ) 
    {
        if( hasEntity( id ) )
        {
            LOG_CHANNEL( "ENTITY_REGISTRY", "Entity " << id << " is already in the registry!" );
            return false;
        }

        std::pair< entityid_t, SComponentSetSignature > newRecord;
        newRecord.first = id;
        newRecord.second = SComponentSetSignature();

        m_entityRecords.push_back( newRecord );

        return true;
    }

    bool CEntityRegistry::addEntity( entityid_t id, const SComponentSetSignature& signature ) 
    {
        if( hasEntity( id ) )
        {
            LOG_CHANNEL( "ENTITY_REGISTRY", "Entity " << id << " is already in the registry!" );
            return false;
        }

        std::pair< entityid_t, SComponentSetSignature > newRecord;
        newRecord.first = id;
        newRecord.second = signature;

        m_entityRecords.push_back( newRecord );

        return true;
    }

    void CEntityRegistry::updateEntity( entityid_t id, const SComponentSetSignature& newSignature ) 
    {
        bool entityFound;
        entityid_t testId;

        entityFound = false;

        for( auto& record : m_entityRecords )
        {
            testId = record.first;

            if( testId == id )
            {
                entityFound = true;
                record.second = newSignature;
            }
        }

        if( !entityFound )
        {
            addEntity( id, newSignature );
        }
    }

    void CEntityRegistry::removeEntity( entityid_t id ) 
    {
        bool entityFound = false;
        for( auto it = m_entityRecords.begin(); it != m_entityRecords.end(); ++it )
        {
            if( it->first == id )
            {
                entityFound = true;
                m_entityRecords.erase( it );
                break;
            }
        }

        if( !entityFound )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Couldn't remove entity " << id << " as it doesn't exist in the registry." );
        }
    }

    bool CEntityRegistry::hasEntity( entityid_t id ) const
    {
        entityid_t testId;

        for( const auto& record : m_entityRecords )
        {
            testId = record.first;

            if( testId == id )
            {
                return true;
            }
        }

        return false;
    }

    const SComponentSetSignature CEntityRegistry::getEntitySignature( entityid_t id ) const
    {
        entityid_t testId;
        SComponentSetSignature testSignature;

        for( const auto& record : m_entityRecords )
        {
            testId = record.first;
            testSignature = record.second;

            if( testId == id )
            {
                return testSignature;
            }
        }

        // entity was not found in the registry
        throw ChestnutException( "Couldn't find entity " + std::to_string(id) + " in the registry!" );
    }

} // namespace chestnut
