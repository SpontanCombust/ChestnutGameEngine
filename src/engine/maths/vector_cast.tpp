namespace chestnut
{
    template< size_t targetN, typename T, size_t sourceN, typename = typename std::enable_if< ( targetN > sourceN ) >::type >
    Vector<T,targetN> vecCastSizeGreater( const Vector<T,sourceN>& v, T initRemainVals )
    {
        Vector<T,targetN> res( initRemainVals ); // initialize with all ones

        std::memcpy( res.data(), v.data(), sizeof(T) * sourceN );

        return res;
    }

    template< size_t targetN, typename T, size_t sourceN, typename = typename std::enable_if< ( targetN < sourceN ) >::type >
    Vector<T,targetN> vecCastSizeSmaller( const Vector<T,sourceN>& v )
    {
        Vector<T,targetN> res;

        std::memcpy( res.data(), v.data(), sizeof(T) * targetN );

        return res;
    }

    template< size_t targetN, typename T, size_t sourceN >
    Vector<T,targetN> vecCastSize( const Vector<T,sourceN>& v, T initNewVals )
    {
        Vector<T,targetN> res(initNewVals);

        size_t size;
        if( targetN >= sourceN )
        {
            size = sizeof(T) * sourceN;
        }
        else
        {
            size = sizeof(T) * targetN;
        }
        
        std::memcpy( res.data(), v.data(), size );
        
        return res;
    }

    template< typename targetT, typename sourceT, size_t n >
    Vector<targetT,n> vecCastType( const Vector<sourceT,n>& v )
    {
        Vector<targetT,n> res;

        const sourceT *dat = v.data();
        targetT *datRes = res.data();

        for (size_t i = 0; i < n; i++)
        {
            datRes[i] = (targetT)dat[i];   
        }

        return res;
    }

} // namespace chestnut
