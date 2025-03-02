#pragma once

#include <memory>

namespace axillary_node_manager {

class AxillaryNodeManager;  // Forward declaration


enum class Event {
  eSensorSuiteReady,
  eRunSurveillanceMode,
  eRunChaseMode,
  eMasterNodeCommLost,
  eSensorFaulted,
  eSensorSuiteCommLost,
  eHibernationComplete,
  eInitialize,
};

// Abstract base class for states.
class State {
 public:
  virtual ~State() = default;

  // Called once when the state is entered.
  virtual void onEnter(AxillaryNodeManager& manager) {}

  // Called on every update cycle."
  virtual void onUpdate(AxillaryNodeManager& manager) {}

  // Called when an event is triggered.
  virtual void onEvent(AxillaryNodeManager& manager, Event event) {}

  // Called right before transitioning out of this state.
  virtual void onExit(AxillaryNodeManager& manager) {}
};

}  // namespace axillary_node_manager

