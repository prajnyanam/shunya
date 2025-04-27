#pragma once

namespace axillary_node_manager {

struct CameraToManager {
  int heartbeat;

  CameraToManager() : heartbeat(0) {}
};

struct RadarToManager {
  int heartbeat;

  RadarToManager() : heartbeat(0) {}
};

struct MasterToManager {
  int heartbeat;

  MasterToManager() : heartbeat(0) {}
};

struct InputData {
  CameraToManager camera_input;
  RadarToManager radar_input;
  MasterToManager master_node_input;

  InputData() : camera_input(), radar_input(), master_node_input() {}
};

}  // namespace axillary_node_manager
