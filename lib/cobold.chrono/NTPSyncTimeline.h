#pragma once

#include <cobold.hpp>
#include <NTPClient.h>
#include <Ethernet.h>
#include <stdint.h>

class NTPSyncTimeline : public cobold::time::ITimeline
{
private:
    NTPClient ntpClient;
    uint64_t cachedUnixTime;
    unsigned long lastSyncMillis;
    const unsigned long syncInterval = 86400000; // Sync every 24 hours

public:
    NTPSyncTimeline(EthernetUDP udp)
        : ntpClient(udp), cachedUnixTime(0), lastSyncMillis(0)
    {
        ntpClient.begin();
    }

    void update() override
    {
        unsigned long currentMillis = millis();
        if (currentMillis - lastSyncMillis >= syncInterval)
        {
            ntpClient.update();
            cachedUnixTime = ntpClient.getEpochTime();
            lastSyncMillis = currentMillis;
        }
    }

    uint64_t now() override
    {
        unsigned long elapsedSeconds = (millis() - lastSyncMillis) / 1000;
        return cachedUnixTime + elapsedSeconds;
    }
};
