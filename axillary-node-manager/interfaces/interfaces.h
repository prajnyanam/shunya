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

    struct MasterToManager {
        int heartbeat;

        MasterToManager() :
        heartbeat(0) {};
    };

    struct InputData {
        CameraToManager cameraInput;
        RadarToManager radarInput;
        MasterToManager masterNodeInput;

        InputData() :
            cameraInput(),
            radarInput(),
            masterNodeInput()
            {};
    };
}