#pragma once 

#include <memory>
#include "state.h"
#include "../parameters/parameters.h"
#include "../interfaces/interfaces.h"

namespace axillaryNodeManager {

class AxillaryNodeManager {
 public:

  AxillaryNodeManager(const Parameters& parameters);

  // Called periodically 
  void update(const InputData& input);

  // Checks if conditions for event emission have occurred
  void checkForEvents(const InputData& input);

  // Method to handle external events that come in.
  void handleEvent(Event event);

  // Method used by states to request a state transition.
  void changeState(std::unique_ptr<State> new_state);

  // Get new state
  State* getCurrentState() const;

 private:
  // Holds the current state object.
  std::unique_ptr<State> current_state_;
  Parameters parameters_;
  int sensor_miss_counter_;
  int master_node_miss_counter_;

  // Last recorded heartbeat values for sensors.
  int last_camera_heartbeat_;
  int last_radar_heartbeat_;
  int last_master_node_heartbeat_;

  bool isHeartbeatStalled(int currentHeartbeat, int& lastHeartbeat);
};

}  // namespace axillaryNodeManager
