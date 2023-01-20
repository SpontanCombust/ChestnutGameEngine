namespace chestnut::engine
{
    template<typename E>
    void to_json(nlohmann::json& j, const CFlags<E>& p)
    {
        size_t flagBits = sizeof(decltype(p.m_buffer)) * 8;

        std::vector<E> vecEnumVals;

        // go over each bit of the flags buffer
        for(size_t i = 0; i < flagBits; i++)
        {
            // check if a bit is set in the flags buffer
            if((p.m_buffer & (1 << i)) > 0)
            {
                // if the bit is set, cast ordinal to enum value
                vecEnumVals.push_back(static_cast<E>(i));
            }
        }

        j = vecEnumVals;
    }

    template<typename E>
    void from_json(const nlohmann::json& j, CFlags<E>& p)
    {
        std::vector<E> vecEnumVals;
        j.get_to(vecEnumVals);

        p = CFlags<E>();
        for(E e : vecEnumVals)
        {
            p |= e;
        }
    }
    
} // namespace chestnut::engine