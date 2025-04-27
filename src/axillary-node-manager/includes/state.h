#pragma once

#include <memory>

namespace axillaryNodeManager {

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
  virtual void OnEnter(AxillaryNodeManager& manager) {}

  // Called on every update cycle.
  virtual void OnUpdate(AxillaryNodeManager& manager) {}

  // Called when an event is triggered.
  virtual void OnEvent(AxillaryNodeManager& manager, Event event) {}

  // Called right before transitioning out of this state.
  virtual void OnExit(AxillaryNodeManager& manager) {}
};

}  // namespace axillaryNodeManager
