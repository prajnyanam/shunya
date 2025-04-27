#include "axillary_node_manager.h"
#include "standby_state.h"
#include "wait_for_command_state.h"
#include "surveillance_mode_state.h"
#include "chase_mode_state.h"
#include "shutdown_state.h"

namespace axillaryNodeManager {

AxillaryNodeManager::AxillaryNodeManager(const Parameters& parameters)
    : current_state_(std::make_unique<Standby>()), 
      parameters_(parameters),
      sensor_miss_counter_(0),
      master_node_miss_counter_(0),
      last_camera_heartbeat_(0),
      last_radar_heartbeat_(0),
      last_master_node_heartbeat_(0) {

  // Call OnEnter for the initial state
  current_state_->OnEnter(*this);
}

void AxillaryNodeManager::update(const InputData& input) {
  if (current_state_) {
    current_state_->OnUpdate(*this);
  }
}

void AxillaryNodeManager::handleEvent(Event event) {
  if (current_state_) {
    current_state_->OnEvent(*this, event);
  }
}

void AxillaryNodeManager::changeState(std::unique_ptr<State> new_state) {
  if (current_state_) {
    current_state_->OnExit(*this);
  }

  current_state_ = std::move(new_state);

  if (current_state_) {
    current_state_->OnEnter(*this);
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
  bool hasCameraStalled = isHeartbeatStalled(input.camera_input.heartbeat, last_camera_heartbeat_);
  bool hasRadarStalled  = isHeartbeatStalled(input.radar_input.heartbeat, last_radar_heartbeat_);

  // If either sensors have stalled, increment the miss counter.
  // we might want to have sensor specific in the future
  if (hasCameraStalled || hasRadarStalled) {
    sensor_miss_counter_++;
    if (sensor_miss_counter_ > parameters_.sensor_heartbeat_counter_thresh) {
      // Emit the event if the threshold is exceeded.
      handleEvent(Event::eSensorSuiteCommLost);
    }
  } else {
    // If at least one sensor has updated, reset the counter.
    sensor_miss_counter_ = 0;
  }

  bool hasMasterNodeStalled = isHeartbeatStalled(input.master_node_input.heartbeat, last_master_node_heartbeat_);
  if (hasMasterNodeStalled) {
    master_node_miss_counter_++;
    if (master_node_miss_counter_ > parameters_.master_node_heartbeat_counter_thresh) {
      handleEvent(Event::eMasterNodeCommLost);
    }
  } else {
    master_node_miss_counter_ = 0;
  }
}

State* AxillaryNodeManager::getCurrentState() const {
  return current_state_.get();
}

}  // namespace axillaryNodeManager
