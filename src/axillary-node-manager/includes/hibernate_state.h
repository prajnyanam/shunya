#pragma once

#include "state.h"
#include "axillary_node_manager.h"

namespace axillary_node_manager {

class Hibernate : public State {
 public:
  void OnEnter(AxillaryNodeManager& manager) override;

  void OnUpdate(AxillaryNodeManager& manager) override;

  void OnEvent(AxillaryNodeManager& manager, Event event) override;
};

}  // namespace axillary_node_manager
