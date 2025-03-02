#pragma once

#include "state.h"
#include "axillary_node_manager.h" 

namespace axillary_node_manager {

class ChaseMode : public State {
 public:
  void onEnter(AxillaryNodeManager& manager) override;

  void onUpdate(AxillaryNodeManager& manager) override;

  void onEvent(AxillaryNodeManager& manager, Event event) override;
};

}  // namespace axillary_node_manager

