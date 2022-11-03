#ifndef __CHESTNUT_ENGINE_FLAGS_H__
#define __CHESTNUT_ENGINE_FLAGS_H__

#define DECLARE_ENUM_FLAG_OPERATORS(T) \
    CHESTNUT_API T operator|( T lhs, T rhs ); \
    CHESTNUT_API T& operator|=( T& lhs, T rhs ); \
    CHESTNUT_API T operator&( T lhs, T rhs ); \
    CHESTNUT_API T& operator&=( T& lhs, T rhs ); \
    CHESTNUT_API T operator^( T lhs, T rhs ); \
    CHESTNUT_API T& operator^=( T& lhs, T rhs ); \
    CHESTNUT_API T operator~( T rhs ); \
    CHESTNUT_API bool operator==( T lhs, int rhs ); \
    CHESTNUT_API bool operator==( int lhs, T rhs ); \
    CHESTNUT_API bool operator!=( T lhs, int rhs ); \
    CHESTNUT_API bool operator!=( int lhs, T rhs ); \
    CHESTNUT_API bool operator>( T lhs, int rhs ); \
    CHESTNUT_API bool operator>( int lhs, T rhs ); \
    CHESTNUT_API bool operator<( T lhs, int rhs ); \
    CHESTNUT_API bool operator<( int lhs, T rhs ); \

#define DEFINE_ENUM_FLAG_OPERATORS(T) \
    T operator|( T lhs, T rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) | static_cast<int>(rhs) ); \
    } \
    T& operator|=( T& lhs, T rhs ) \
    { \
        T result = lhs | rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator&( T lhs, T rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) & static_cast<int>(rhs) ); \
    } \
    T& operator&=( T& lhs, T rhs ) \
    { \
        T result = lhs & rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator^( T lhs, T rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) ^ static_cast<int>(rhs) ); \
    } \
    T& operator^=( T& lhs, T rhs ) \
    { \
        T result = lhs ^ rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator~( T rhs ) \
    { \
        return static_cast<T>( ~ static_cast<int>(rhs) ); \
    } \
    bool operator==( T lhs, int rhs ) \
    { \
        return static_cast<int>( lhs ) == rhs; \
    } \
    bool operator==( int lhs, T rhs ) \
    { \
        return static_cast<int>( rhs ) == lhs; \
    } \
    bool operator!=( T lhs, int rhs ) \
    { \
        return static_cast<int>( lhs ) != rhs; \
    } \
    bool operator!=( int lhs, T rhs ) \
    { \
        return static_cast<int>( rhs ) != lhs; \
    } \
    bool operator>( T lhs, int rhs ) \
    { \
        return static_cast<int>( lhs ) > rhs; \
    } \
    bool operator>( int lhs, T rhs ) \
    { \
        return lhs > static_cast<int>( rhs ); \
    } \
    bool operator<( T lhs, int rhs ) \
    { \
        return static_cast<int>( lhs ) < rhs; \
    } \
    bool operator<( int lhs, T rhs ) \
    { \
        return lhs < static_cast<int>( rhs ); \
    } \

#endif // __CHESTNUT_ENGINE_FLAGS_H__