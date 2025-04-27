#include <iostream>
#include "standby_state.h"
#include "shutdown_state.h"

namespace axillary_node_manager {

void Shutdown::OnEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Shutdown state." << std::endl;
}

void Shutdown::OnUpdate(AxillaryNodeManager& manager) {
  std::cout << "Shutdown::onUpdate - updating Shutdown state." << std::endl;
}

void Shutdown::OnEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eInitialize:
      // Transition to Shutdown state.
      manager.ChangeState(std::make_unique<Standby>());
      break;
    default:
      break;
  }
}

}  // namespace axillary_node_manager
