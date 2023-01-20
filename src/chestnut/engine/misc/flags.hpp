#pragma once

#include <initializer_list>
#include <type_traits>

namespace chestnut::engine
{
    // Requires enum type with default values
    template<typename E>
    struct CFlags
    {
        static_assert(std::is_enum_v<E>, "E must be enum");

    public:
        unsigned long m_buffer;

    public:
        CFlags() noexcept
        {
            m_buffer = 0;
        }

        CFlags(E e) noexcept
        {
            m_buffer = static_cast<unsigned long>(1 << static_cast<unsigned long>(e));
        }

        CFlags(std::initializer_list<E> il) noexcept
        {
            m_buffer = 0;
            for(E e : il)
            {
                m_buffer |= static_cast<unsigned long>(1 << static_cast<unsigned long>(e));
            }
        }


        bool empty() const
        {
            return m_buffer == 0;
        }

        operator bool() const
        {
            return m_buffer > 0;
        }


        CFlags<E> operator|(CFlags<E> rhs) const
        {
            return CFlags<E>(m_buffer | rhs.m_buffer);
        }

        CFlags<E>& operator|=(CFlags<E> rhs)
        {
            m_buffer |= rhs.m_buffer;
            return *this;
        }

        CFlags<E> operator&(CFlags<E> rhs) const
        {
            return CFlags<E>(m_buffer & rhs.m_buffer);
        }

        CFlags<E>& operator&=(CFlags<E> rhs)
        {
            m_buffer &= rhs.m_buffer;
            return *this;
        }

        CFlags<E> operator^(CFlags<E> rhs) const
        {
            return CFlags<E>(m_buffer ^ rhs.m_buffer);
        }

        CFlags<E>& operator^=(CFlags<E> rhs)
        {
            m_buffer ^= rhs.m_buffer;
            return *this;
        }

        CFlags<E> operator~() const
        {
            return CFlags<E>(~m_buffer);
        }


        bool operator==(CFlags<E> rhs) const
        {
            return m_buffer == rhs.m_buffer;
        }

        bool operator!=(CFlags<E> rhs) const
        {
            return m_buffer != rhs.m_buffer;
        }

        bool operator<(CFlags<E> rhs) const
        {
            return m_buffer <  rhs.m_buffer;
        }

        bool operator>(CFlags<E> rhs) const
        {
            return m_buffer >  rhs.m_buffer;
        }

    private:
        CFlags(int initBuffer) noexcept 
        : m_buffer(initBuffer) 
        {

        }
    };

} // namespace chestnut::engine
