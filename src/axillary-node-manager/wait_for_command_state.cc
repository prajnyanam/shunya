#include <iostream>
#include "wait_for_command_state.h"  
#include "hibernate_state.h"         
#include "surveillance_mode_state.h"
#include "chase_mode_state.h"

namespace axillaryNodeManager {

void WaitForCommand::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering WaitForCommand state." << std::endl;
}

void WaitForCommand::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "WaitForCommand::onUpdate - updating WaitForCommand state." << std::endl;
}

void WaitForCommand::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eRunSurveillanceMode:
      // Transition to WaitForCommand state.
      manager.changeState(std::make_unique<SurveillanceMode>());
      break;
    case Event::eRunChaseMode:
      // Transition to WaitForCommand state.
      manager.changeState(std::make_unique<ChaseMode>());
      break;
    case Event::eSensorSuiteCommLost:
      // Transition to Hibernate state.
      manager.changeState(std::make_unique<Hibernate>());
      break;
    default:
      break;
  }
}

}  // namespace axillaryNodeManager
