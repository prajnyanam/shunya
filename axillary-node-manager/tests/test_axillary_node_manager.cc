#include <catch2/catch_test_macros.hpp>

#include "axillary_node_manager.h"
#include "standby_state.h"
#include "wait_for_command_state.h"
#include "surveillance_mode_state.h"
#include "chase_mode_state.h"
#include "hibernate_state.h"
#include "shutdown_state.h"
#include "state.h" 
#include <typeinfo>


TEST_CASE("Standby state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);

  // Initially, the state is Standby.
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Standby));

  SECTION("Transition to WaitForCommand on eSensorSuiteReady") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteReady);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::WaitForCommand));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));
  }

  SECTION("Transition to Hibernate on eSensorFaulted") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorFaulted);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));
  }
}

TEST_CASE("WaitForCommand state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);
  // Transition to WaitForCommand state directly.
  manager.changeState(std::make_unique<axillary_node_manager::WaitForCommand>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::WaitForCommand));

  SECTION("Transition to SurveillanceMode on eRunSurveillanceMode") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eRunSurveillanceMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::SurveillanceMode));
  }

  SECTION("Transition to ChaseMode on eRunChaseMode") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eRunChaseMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::ChaseMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));
  }
}

TEST_CASE("SurveillanceMode state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillary_node_manager::SurveillanceMode>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::SurveillanceMode));

  SECTION("Transition to ChaseMode on eRunChaseMode") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eRunChaseMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::ChaseMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));
  }
}

TEST_CASE("ChaseMode state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillary_node_manager::ChaseMode>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::ChaseMode));

  SECTION("Transition to SurveillanceMode on eRunSurveillanceMode") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eRunSurveillanceMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::SurveillanceMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));
  }
}

TEST_CASE("Hibernate state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillary_node_manager::Hibernate>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Hibernate));

  SECTION("Transition to Shutdown on eHibernationComplete") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eHibernationComplete);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Shutdown));
  }

  SECTION("Transition to WaitForCommand on eSensorSuiteReady") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eSensorSuiteReady);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::WaitForCommand));
  }
}

TEST_CASE("Shutdown state transitions", "[state]") {
  axillary_node_manager::Parameters parameters;
  axillary_node_manager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillary_node_manager::Shutdown>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Shutdown));

  SECTION("Transition to Standby on eInitialize") {
    manager.getCurrentState()->onEvent(manager, axillary_node_manager::Event::eInitialize);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillary_node_manager::Standby));
  }
}
