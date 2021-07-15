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

        std::pair< entityid_t, CEntitySignature > newRecord;
        newRecord.first = id;
        newRecord.second = CEntitySignature();

        m_entityRecords.push_back( newRecord );

        return true;
    }

    bool CEntityRegistry::addEntity( entityid_t id, const CEntitySignature& signature ) 
    {
        if( hasEntity( id ) )
        {
            LOG_CHANNEL( "ENTITY_REGISTRY", "Entity " << id << " is already in the registry!" );
            return false;
        }

        std::pair< entityid_t, CEntitySignature > newRecord;
        newRecord.first = id;
        newRecord.second = signature;

        m_entityRecords.push_back( newRecord );

        return true;
    }

    void CEntityRegistry::updateEntity( entityid_t id, const CEntitySignature& newSignature ) 
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

    void CEntityRegistry::removeAllEntities() 
    {
        m_entityRecords.clear();
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

    const CEntitySignature CEntityRegistry::getEntitySignature( entityid_t id ) const
    {
        entityid_t testId;
        CEntitySignature testSignature;

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


    const std::string CEntityRegistry::toString() const
    {
        std::string str;

        for( const auto& pair : m_entityRecords )
        {
            str += "( ";
            str += std::to_string( pair.first ) + ", ";
            str += pair.second.toString();
            str += " )";
            str += "\n";
        }

        return str;
    }

} // namespace chestnut
