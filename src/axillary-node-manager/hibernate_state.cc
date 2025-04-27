#include <iostream>
#include "hibernate_state.h"
#include "wait_for_command_state.h"
#include "shutdown_state.h"

namespace axillaryNodeManager {

void Hibernate::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Hibernate state." << std::endl;
}

void Hibernate::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "Hibernate::onUpdate - updating Hibernate state." << std::endl;
}

void Hibernate::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eHibernationComplete:
      // Transition to Shutdown state.
      manager.changeState(std::make_unique<Shutdown>());
      break;
    case Event::eSensorSuiteReady:
      // Transition to WaitForCommand state.
      manager.changeState(std::make_unique<WaitForCommand>());
      break;
    default:
      break;
  }
}

}  // namespace axillaryNodeManager
