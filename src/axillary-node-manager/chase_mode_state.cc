#include <iostream>
#include "hibernate_state.h"
#include "chase_mode_state.h"
#include "surveillance_mode_state.h"

namespace axillaryNodeManager {

void ChaseMode::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering ChaseMode state." << std::endl;
}

void ChaseMode::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "ChaseMode::onUpdate - updating ChaseMode state." << std::endl;
}

void ChaseMode::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eRunSurveillanceMode:
      // Transition to Surveillance state.
      manager.changeState(std::make_unique<SurveillanceMode>());
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
