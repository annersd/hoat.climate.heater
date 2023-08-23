#pragma once

#include "IHostedService.h"
#include <string>
#include "ITypeWrapper.h"

/**
 * @brief Template class to generate unique type IDs, type names, and provide access to wrapped types for TypeWrapper instances.
 *
 * @tparam T The type for which to generate the type ID and name.
 */
template <typename T>
class TypeWrapper : public ITypeWrapper
{
public:
    /**
     * @brief Get the mangled type name for the specified type.
     *
     * @return The mangled type name.
     */
    std::string GetTypeName() const override
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
    size_t GetTypeId() const override
    {
        static const size_t id = std::hash<std::string>{}(GetTypeName());
        return id;
    }

    /**
     * @brief Get the name of the wrapped type.
     *
     * @return The name of the wrapped type.
     */
    std::string GetName() const override
    {
        return GetTypeName();
    }

    /**
     * @brief Get the type information of the wrapped type.
     *
     * @return The type information of the wrapped type.
     */
    const std::type_info &GetWrappedType() const override
    {
        return typeid(T);
    }

    bool isHostedService() const override
    {
        return std::is_base_of<cobold::hosting::IHostedService, T>::value;
    }
};
