#ifndef __CHESTNUT_ENGINE_FLAGS_H__
#define __CHESTNUT_ENGINE_FLAGS_H__

#define DECLARE_ENUM_FLAG_OPERATORS(T) \
    T operator|( const T& lhs, const T& rhs ); \
    T& operator|=( T& lhs, const T& rhs ); \
    T operator&( const T& lhs, const T& rhs ); \
    T& operator&=( T& lhs, const T& rhs ); \
    T operator^( const T& lhs, const T& rhs ); \
    T& operator^=( T& lhs, const T& rhs ); \
    T operator~( const T& rhs );

#define DEFINE_ENUM_FLAG_OPERATORS(T) \
    T operator|( const T& lhs, const T& rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) | static_cast<int>(rhs) ); \
    } \
    T& operator|=( T& lhs, const T& rhs ) \
    { \
        T result = lhs | rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator&( const T& lhs, const T& rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) & static_cast<int>(rhs) ); \
    } \
    T& operator&=( T& lhs, const T& rhs ) \
    { \
        T result = lhs & rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator^( const T& lhs, const T& rhs ) \
    { \
        return static_cast<T>( static_cast<int>(lhs) ^ static_cast<int>(rhs) ); \
    } \
    T& operator^=( T& lhs, const T& rhs ) \
    { \
        T result = lhs ^ rhs; \
        lhs = result; \
        return lhs; \
    } \
    T operator~( const T& rhs ) \
    { \
        return static_cast<T>( ~ static_cast<int>(rhs) ); \
    }

#endif // __CHESTNUT_ENGINE_FLAGS_H__