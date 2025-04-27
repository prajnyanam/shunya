#include "standby_state.h"
#include <iostream>
#include "wait_for_command_state.h"
#include "hibernate_state.h"

namespace axillaryNodeManager {

void Standby::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Standby state." << std::endl;
}

void Standby::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "Standby::onUpdate - updating Standby state." << std::endl;
}

void Standby::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eSensorSuiteReady:
      // Transition to WaitForCommand state.
      manager.changeState(std::make_unique<WaitForCommand>());
      break;
    case Event::eSensorSuiteCommLost:
    case Event::eSensorFaulted:
      // Transition to Hibernate state.
      manager.changeState(std::make_unique<Hibernate>());
      break;
    default:
      break;
  }
}

}  // namespace axillaryNodeManager
