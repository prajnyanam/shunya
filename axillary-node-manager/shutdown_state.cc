#include <iostream>
#include "standby_state.h"
#include "shutdown_state.h"

namespace axillary_node_manager {

void Shutdown::onEnter(AxillaryNodeManager& manager) {
  std::cout << "Entering Shutdown state." << std::endl;
}

void Shutdown::onUpdate(AxillaryNodeManager& manager) {
  std::cout << "Shutdown::onUpdate - updating Shutdown state." << std::endl;
}

void Shutdown::onEvent(AxillaryNodeManager& manager, Event event) {
  switch (event) {
    case Event::eInitialize:
      // Transition to Shutdown state.
      manager.changeState(std::make_unique<Standby>());
      break;
    default:
      break;
  }
}

}  // namespace axillary_node_manager
