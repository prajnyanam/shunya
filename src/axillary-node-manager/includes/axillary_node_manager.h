#pragma once 

#include <memory>
#include "state.h"
#include "../parameters/parameters.h"
#include "../interfaces/interfaces.h"

namespace axillary_node_manager {

class AxillaryNodeManager {
 public:

  AxillaryNodeManager(const Parameters& parameters);

  // Called periodically 
  void Update(const InputData& input);

  // Checks if conditions for event emission have occurred
  void CheckForEvents(const InputData& input);

  // Method to handle external events that come in.
  void HandleEvent(Event event);

  // Method used by states to request a state transition.
  void ChangeState(std::unique_ptr<State> new_state);

  // Get new state
  State* GetCurrentState() const;

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

  bool IsHeartbeatStalled(int currentHeartbeat, int& lastHeartbeat);
};

}  // namespace axillary_node_manager
