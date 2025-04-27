#pragma once

#include "state.h"
#include "axillary_node_manager.h"

namespace axillaryNodeManager {

class Standby : public State {
 public:
  void OnEnter(AxillaryNodeManager& manager) override;

  void OnUpdate(AxillaryNodeManager& manager) override;

  void OnEvent(AxillaryNodeManager& manager, Event event) override;
};

}  // namespace axillaryNodeManager
