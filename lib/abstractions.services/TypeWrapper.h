#pragma once

#include <string>

/**
 * @brief Template class to generate unique type IDs for TypeWrapper instances.
 *
 * @tparam T The type for which to generate the type ID.
 */
template <typename T>
class TypeWrapper
{
public:
    /**
     * @brief Get the mangled type name for the specified type.
     *
     * @return The mangled type name.
     */
    static std::string GetTypeName()
    {
        return typeid(T).name();
    }

    /**
     * @brief Get the unique type ID for the specified type.
     *
     * This method uses the mangled type name as the basis for the type identifier.
     *
     * @return The unique type ID.
     */
    static size_t GetTypeId()
    {
        static const size_t id = std::hash<std::string>{}(GetTypeName());
        return id;
    }
};
