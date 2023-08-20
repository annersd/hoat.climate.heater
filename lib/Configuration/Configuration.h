#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
// #include <ArduinoJson.h>
#include <abstractions.hpp>

class Configuration : public abstractions::configuration::IConfiguration
{
private:
    std::map<std::string, std::string> configMap;

public:
    Configuration()
    {
        // Initialize or load configuration data here
        configMap["name"] = "John";
        configMap["location.city"] = "New York";
        configMap["location.country"] = "USA";
        configMap["email"] = "john@example.com";
        configMap["contact.phone"] = "123-456-7890";
    }

    std::string getValue(const std::string &key)
    {
        auto it = configMap.find(key);
        if (it != configMap.end())
        {
            return it->second;
        }
        else
        {
            return "";
        }
    }

    void setValue(const std::string &key, const std::string &value)
    {
        configMap[key] = value;
    }

    void deleteKey(const std::string &key)
    {
        configMap.erase(key);
    }

    bool keyExists(const std::string &key)
    {
        return configMap.find(key) != configMap.end();
    }

    std::string findKeyStartingWith(const std::string &prefix)
    {
        for (const auto &pair : configMap)
        {
            if (pair.first.find(prefix) == 0)
            {
                return pair.first;
            }
        }
        return "";
    }

    std::vector<std::string> findKeysByRegex(const std::string &regexPattern)
    {
        std::vector<std::string> matchingKeys;
        std::regex pattern(regexPattern);

        for (const auto &pair : configMap)
        {
            if (std::regex_match(pair.first, pattern))
            {
                matchingKeys.push_back(pair.first);
            }
        }

        return matchingKeys;
    }

    abstractions::configuration::IConfiguration *getSection(const std::string &path) override
    {
        abstractions::configuration::IConfiguration *sectionConfig = new Configuration();

        std::string regexPattern = path + "\\..*";
        std::regex pattern(regexPattern);

        std::string prefix = path + ".";
        size_t prefixLength = prefix.length();

        for (const auto &pair : configMap)
        {
            if (std::regex_match(pair.first, pattern))
            {
                std::string shortenedKey = pair.first.substr(prefixLength);
                sectionConfig->setValue(shortenedKey, pair.second);
            }
        }

        return sectionConfig;
    }

    void loadFromJson(const char *jsonString)
    {
        // StaticJsonDocument<256> jsonDoc;
        // deserializeJson(jsonDoc, jsonString);

        // for (const JsonPair &kvp : jsonDoc.as<JsonObject>())
        // {

        //     configMap[std::string(kvp.key().c_str())] = kvp.value().as<std::string>();
        // }
    }
};

int main()
{
    abstractions::configuration::IConfiguration *config = new Configuration();

    // Access and print values from the configuration
    std::cout << "Name: " << config->getValue("name") << std::endl;
    std::cout << "City: " << config->getValue("location.city") << std::endl;
    std::cout << "Country: " << config->getValue("location.country") << std::endl;

    abstractions::configuration::IConfiguration *section = config->getSection("location");
    std::cout << "City: " << section->getValue("city") << std::endl;
    std::cout << "Country: " << section->getValue("country") << std::endl;

    // Add new key-value pair
    config->setValue("email", "john@example.com");

    // Delete a key
    config->deleteKey("location.city");

    // Find a key starting with a prefix
    std::string foundKey = config->findKeyStartingWith("loc");
    if (!foundKey.empty())
    {
        std::cout << "Key starting with 'loc': " << foundKey << std::endl;
    }
    else
    {
        std::cout << "No key found with the specified prefix." << std::endl;
    }

    // Find keys using regex
    std::vector<std::string> regexKeys = config->findKeysByRegex("contact\\..*");
    std::cout << "Keys matching regex 'contact\\..*':" << std::endl;
    for (const std::string &key : regexKeys)
    {
        std::cout << key << std::endl;
    }

    delete config;
    delete section;

    return 0;
}
