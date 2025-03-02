#include <iostream>
#include "hibernate_state.h"         
#include "wait_for_command_state.h"
#include "shutdown_state.h"

namespace axillary_node_manager {

void Hibernate::onEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Hibernate state." << std::endl;
}

void Hibernate::onUpdate(AxillaryNodeManager& manager) {
  std::cout << "Hibernate::onUpdate - updating Hibernate state." << std::endl;
}

void Hibernate::onEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eHibernationComplete:
      // Transition to Hibernate state.
      manager.changeState(std::make_unique<Shutdown>());
      break;
    case Event::eSensorSuiteReady:
      // Transition to Hibernate state.
      manager.changeState(std::make_unique<WaitForCommand>());
      break;
    default:
      break;
  }
}

}  // namespace axillary_node_manager
