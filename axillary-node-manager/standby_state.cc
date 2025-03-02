#include "standby_state.h"
#include <iostream>
#include "wait_for_command_state.h"  
#include "hibernate_state.h"         

namespace axillary_node_manager {

void Standby::onEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Standby state." << std::endl;
}

void Standby::onUpdate(AxillaryNodeManager& manager) {
  std::cout << "Standby::onUpdate - updating standby state." << std::endl;
}

void Standby::onEvent(AxillaryNodeManager& manager, Event event) {
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

}  // namespace axillary_node_manager
