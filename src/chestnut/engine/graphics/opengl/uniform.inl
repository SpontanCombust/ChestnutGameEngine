namespace chestnut::engine
{
    template<typename T>
    CUniform<T>::CUniform(const std::string& name, GLint location)
    {
        static_assert(sizeof(T) == 0, "Template type not supported for the uniform!");
    }

    template<typename T>
    void CUniform<T>::set(T&& value)
    {

    }

} // namespace chestnut::engine
