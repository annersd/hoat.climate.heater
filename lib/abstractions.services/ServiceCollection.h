#pragma once

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
        services[TypeWrapper<T>::GetTypeId()] = []() -> void *
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
    void addServiceWithConstructor(std::function<void *(ServiceCollection *)> constructor)
    {
        constructorMap[TypeWrapper<T>::GetTypeId()] = constructor;
    }

    // Add Service to the collection with a pointer to the service
    template <typename T>
    void addService(T *service)
    {
        services[TypeWrapper<T>::GetTypeId()] = [service]() -> void *
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
        auto it = services.find(TypeWrapper<T>::GetTypeId());
        if (it != services.end())
        {
            void *servicePtr = it->second();
            return reinterpret_cast<T *>(servicePtr);
        }
        return nullptr;
    }

    /**
     * @brief Update a service in the collection using a new constructor.
     *
     * @tparam T The type of the service to update.
     */
    template <typename T>
    void updateServiceWithConstructor()
    {
        auto it = services.find(TypeWrapper<T>::GetTypeId());
        if (it != services.end())
        {
            void *oldService = it->second();
            void *newService = constructorMap[TypeWrapper<T>::GetTypeId()](this);
            delete oldService;
            it->second = [newService]() -> void *
            { return newService; };
        }
    }

private:
    std::map<size_t, std::function<void *()>> services;
    std::map<size_t, std::function<void *(ServiceCollection *)>> constructorMap;
};
