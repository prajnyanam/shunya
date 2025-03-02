#include "axillary_node_manager.h"
#include "standby_state.h"
#include "wait_for_command_state.h"
#include "surveillance_mode_state.h"
#include "chase_mode_state.h"
#include "shutdown_state.h"

namespace axillary_node_manager {

AxillaryNodeManager::AxillaryNodeManager(const Parameters& parameters)
    : m_current_state(std::make_unique<Standby>()), 
    m_parameters(parameters),
    m_sensor_miss_counter(0),
    m_master_node_miss_counter(0),
    m_last_camera_heartbeat(0),
    m_last_radar_heartbeat(0),
    m_last_master_node_heartbeat(0)
    {

  // Call OnEnter for the initial state
  m_current_state->onEnter(*this);
}

void AxillaryNodeManager::update(const InputData& input) {
  if (m_current_state) {
    m_current_state->onUpdate(*this);
  }
}

void AxillaryNodeManager::handleEvent(Event event) {
  if (m_current_state) {
    m_current_state->onEvent(*this, event);
  }
}

void AxillaryNodeManager::changeState(std::unique_ptr<State> new_state) {
  if (m_current_state) {
    m_current_state->onExit(*this);
  }

  m_current_state = std::move(new_state);

  if (m_current_state) {
    m_current_state->onEnter(*this);
  }
}

bool AxillaryNodeManager::isHeartbeatStalled(int currentHeartbeat, int& lastHeartbeat) {
  bool isStalled = (currentHeartbeat == lastHeartbeat);
  // Update the stored heartbeat value for the next check.
  lastHeartbeat = currentHeartbeat;
  return isStalled;
}

void AxillaryNodeManager::checkForEvents(const InputData& input) {
     // Check if the camera and radar heartbeats have stalled.
  bool hasCameraStalled = isHeartbeatStalled(input.cameraInput.heartbeat, m_last_camera_heartbeat);
  bool hasRadarStalled  = isHeartbeatStalled(input.radarInput.heartbeat, m_last_radar_heartbeat);

  // If either sensors have stalled, increment the miss counter.
  // we might want to have sensor specific in the future
  if (hasCameraStalled || hasRadarStalled) {
    m_sensor_miss_counter++;
    if (m_sensor_miss_counter > m_parameters.sensorHeartbeatCounterThresh) {
      // Emit the event if the threshold is exceeded.
      handleEvent(Event::eSensorSuiteCommLost);
    }
  } else {
    // If at least one sensor has updated, reset the counter.
    m_sensor_miss_counter = 0;
  }

  bool hasMasterNodeStalled = isHeartbeatStalled(input.masterNodeInput.heartbeat, m_last_master_node_heartbeat);
  if (hasMasterNodeStalled) {
    m_master_node_miss_counter++;
    if (m_master_node_miss_counter > m_parameters.masterNodeHeartbeatCounterThresh) {
      handleEvent(Event::eMasterNodeCommLost);
    }
  } else {
    m_master_node_miss_counter = 0;
  }
}

State* AxillaryNodeManager::getCurrentState() const {
    return m_current_state.get();
  }

}  // namespace axillary_node_manager
