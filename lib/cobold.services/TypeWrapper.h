#pragma once

#include <string>

/**
 * @brief Interface for generating unique type IDs and type names.
 */
class ITypeWrapper
{
public:
    /**
     * @brief Get the mangled type name for the specified type.
     *
     * @return The mangled type name.
     */
    virtual std::string GetTypeName() const = 0;

    /**
     * @brief Get the unique type ID for the specified type.
     *
     * This method uses the mangled type name as the basis for the type identifier.
     *
     * @return The unique type ID.
     */
    virtual size_t GetTypeId() const = 0;

    /**
     * @brief Get the name of the wrapped type.
     *
     * @return The name of the wrapped type.
     */
    virtual std::string GetName() const = 0;

    virtual ~ITypeWrapper() {}
};

/**
 * @brief Template class to generate unique type IDs and type names for TypeWrapper instances.
 *
 * @tparam T The type for which to generate the type ID and name.
 */
template <typename T>
class TypeWrapper : public ITypeWrapper
{
public:
    std::string GetTypeName() const override
    {
        return typeid(T).name();
    }

    size_t GetTypeId() const override
    {
        static const size_t id = std::hash<std::string>{}(GetTypeName());
        return id;
    }

    std::string GetName() const override
    {
        return GetTypeName();
    }
};
