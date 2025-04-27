#include <iostream>
#include "hibernate_state.h"
#include "chase_mode_state.h"
#include "surveillance_mode_state.h"

namespace axillary_node_manager {

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
      manager.ChangeState(std::make_unique<SurveillanceMode>());
      break;
    case Event::eSensorSuiteCommLost:
      // Transition to Hibernate state.
      manager.ChangeState(std::make_unique<Hibernate>());
      break;
    default:
      break;
  }
}

}  // namespace axillary_node_manager
