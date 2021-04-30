#ifndef __CHESTNUT_SHADER_PROGRAM_H__
#define __CHESTNUT_SHADER_PROGRAM_H__

#include <string>
#include <unordered_map>

namespace chestnut
{
    class CShaderProgram
    {
    private:
        unsigned int m_programID;

        std::unordered_map< std::string, int > m_mapVarLocations;

    public:
        CShaderProgram();
        CShaderProgram( unsigned int programID );
        ~CShaderProgram() = default;

        unsigned int getID() const;
        bool isValid() const;
        
        void bind();
        void unbind();

        // Returns -1 if doesn't find one
        int getAttributeLocation( std::string attrName );
        // Returns -1 if doesn't find one
        int getUniformLocation( std::string uniformName );
    };
    
} // namespace chestnut


#endif // __CHESTNUT_SHADER_PROGRAM_H__