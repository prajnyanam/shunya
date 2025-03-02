#pragma once

namespace axillary_node_manager {
    struct Parameters {
        int sensorHeartbeatCounterThresh;
        int masterNodeHeartbeatCounterThresh;

        Parameters(int sensorHeartbeatCounterThresh = 100,
        int masterNodeHeartbeatCounterThresh = 100) :
        sensorHeartbeatCounterThresh(sensorHeartbeatCounterThresh), 
        masterNodeHeartbeatCounterThresh(masterNodeHeartbeatCounterThresh)
        {};
    };
}