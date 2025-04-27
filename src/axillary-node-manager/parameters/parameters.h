#pragma once

namespace axillary_node_manager {

struct Parameters {
  int sensor_heartbeat_counter_thresh;
  int master_node_heartbeat_counter_thresh;

  Parameters(int sensor_heartbeat_counter_thresh = 100,
             int master_node_heartbeat_counter_thresh = 100)
      : sensor_heartbeat_counter_thresh(sensor_heartbeat_counter_thresh),
        master_node_heartbeat_counter_thresh(master_node_heartbeat_counter_thresh) {}
};

}  // namespace axillary_node_manager
