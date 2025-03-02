#pragma once

namespace axillary_node_manager {
    
    struct CameraToManager {
        int heartbeat;

        CameraToManager() :
        heartbeat(0) {};
    };

    struct RadarToManager {
        int heartbeat;

        RadarToManager() :
        heartbeat(0) {};
    };

    struct InputData {
        int sensorHeartbeatCounterThresh;
        int masterNodeHeartbeatCounterThresh;
        CameraToManager cameraInput;
        RadarToManager radarInput;

        InputData(int sensorHeartbeatCounterThresh = 100,
            int masterNodeHeartbeatCounterThresh = 100) :
            sensorHeartbeatCounterThresh(sensorHeartbeatCounterThresh), 
            masterNodeHeartbeatCounterThresh(masterNodeHeartbeatCounterThresh),
            cameraInput(),
            radarInput()
            {};
    };
}