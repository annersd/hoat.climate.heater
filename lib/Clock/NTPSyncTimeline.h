#ifndef NTPSYNCTIMELINE_H
#define NTPSYNCTIMELINE_H

#include "ITimeline.h"
#include <NTPClient.h>
#include <Ethernet.h>

class NTPSyncTimeline : public ITimeline
{
private:
    NTPClient ntpClient;
    unsigned long long cachedUnixTime;
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

    unsigned long long now() override
    {
        unsigned long elapsedSeconds = (millis() - lastSyncMillis) / 1000;
        return cachedUnixTime + elapsedSeconds;
    }
};

#endif // NTPSYNCTIMELINE_H
