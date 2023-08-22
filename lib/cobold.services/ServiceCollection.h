#pragma once

#include "cobold.hpp"
#include <map>
#include <functional>
#include <typeinfo>

#include "TypeWrapper.h"

/**
 * @brief Class for managing a collection of services using dependency injection.
 */
class ServiceCollection
{
public:
    /**
     * @brief Add a service to the collection without a constructor.
     *
     * The service can be later retrieved using the getService method.
     *
     * @tparam T The type of the service to add.
     */
    template <typename T>
    void addService()
    {
        services[new TypeWrapper<T>()] = []() -> void *
        { return new T(); };
    }

    /**
     * @brief Add a service to the collection with a constructor.
     *
     * The service can be later retrieved using the getService method.
     *
     * @tparam T The type of the service to add.
     * @param constructor A constructor function for the service.
     */
    template <typename T>
    void addService(std::function<void *(ServiceCollection *)> constructor)
    {
        constructorMap[new TypeWrapper<T>()] = constructor;
    }

    /**
     * @brief Add a service to the collection with a pointer to the service.
     *
     * The service can be later retrieved using the getService method.
     *
     * @tparam T The type of the service to add.
     * @param service A pointer to the service.
     */
    template <typename T>
    void addService(T *service)
    {
        services[new TypeWrapper<T>()] = [service]() -> void *
        { return service; };
    }

    /**
     * @brief Get a service from the collection.
     *
     * @tparam T The type of the service to retrieve.
     * @return A pointer to the retrieved service, or nullptr if not found.
     */
    template <typename T>
    T *getService()
    {
        ITypeWrapper *typeWrapper = new TypeWrapper<T>();
        auto it = services.find(typeWrapper);
        if (it != services.end())
        {
            void *servicePtr = it->second();
            return reinterpret_cast<T *>(servicePtr);
        }
        return nullptr;
    }

    // Helper function to check if a type is derived from IHosedService
    template <typename Derived, typename Base>
    struct is_derived
    {
        static constexpr bool value = std::is_base_of<Base, Derived>::value;
    };

    // get a list of services that inherit from the specified interface IHosedService*
template <typename T >
std::vector<T> getServicesInheritingFromInterface()
{
    std::vector<T> servicesList;
    // for (auto it = services.begin(); it != services.end(); ++it)
    // {
    //     ITypeWrapper *typeWrapper = it->first;
    //     if (is_derived<T, TInterface>::value && typeid(*typeWrapper) == typeid(TypeWrapper<T>))
    //     {
    //         void *servicePtr = it->second();
    //         T service = dynamic_cast<T>(reinterpret_cast<TInterface>(servicePtr));
    //         if (service)
    //         {
    //             servicesList.push_back(service);
    //         }
    //     }
    // }
    return servicesList;
}
    /**
     * @brief Update a service in the collection using a new constructor.
     *
     * @tparam T The type of the service to update.
     */
    template <typename T>
    void updateService()
    {
        ITypeWrapper *typeWrapper = new TypeWrapper<T>();
        auto it = services.find(typeWrapper);
        if (it != services.end())
        {
            void *oldService = it->second();
            void *newService = constructorMap[TypeWrapper<T>()](this);
            delete oldService;
            it->second = [newService]() -> void *
            { return newService; };
        }
    }

private:
    std::map<ITypeWrapper *, std::function<void *()>> services;
    std::map<ITypeWrapper *, std::function<void *(ServiceCollection *)>> constructorMap;
};
