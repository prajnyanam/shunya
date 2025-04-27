#include <iostream>
#include "wait_for_command_state.h"
#include "hibernate_state.h"
#include "surveillance_mode_state.h"
#include "chase_mode_state.h"

namespace axillaryNodeManager {

void SurveillanceMode::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering SurveillanceMode state." << std::endl;
}

void SurveillanceMode::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "SurveillanceMode::onUpdate - updating SurveillanceMode state." << std::endl;
}

void SurveillanceMode::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eRunChaseMode:
      // Transition to ChaseMode state.
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
