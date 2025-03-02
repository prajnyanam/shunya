#pragma once 

#include <memory>
#include "state.h"
#include "parameters/parameters.h"
#include "interfaces/interfaces.h"

namespace axillary_node_manager {

class AxillaryNodeManager {
 public:

  AxillaryNodeManager(const Parameters& parameters);

  // Called periodically 
  void update(const InputData& input);

  // Checks if conditions for event emission have occured
  void checkForEvents(const InputData& input);

  // Method to handle external events that come in.
  void handleEvent(Event event);

  // Method used by states to request a state transition.
  void changeState(std::unique_ptr<State> new_state);

 private:
  // Holds the current state object.
  std::unique_ptr<State> m_current_state;
  Parameters m_parameters;
  int m_sensor_miss_counter;
  int m_master_node_miss_counter;

  // Last recorded heartbeat values for sensors.
  int m_last_camera_heartbeat;
  int m_last_radar_heartbeat;
  int m_last_master_node_heartbeat;

  bool isHeartbeatStalled(int currentHeartbeat, int& lastHeartbeat);
};

}  // namespace axillary_node_manager
