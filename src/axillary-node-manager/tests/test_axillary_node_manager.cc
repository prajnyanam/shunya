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
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);

  // Initially, the state is Standby.
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Standby));

  SECTION("Transition to WaitForCommand on eSensorSuiteReady") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteReady);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::WaitForCommand));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));
  }

  SECTION("Transition to Hibernate on eSensorFaulted") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorFaulted);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));
  }
}

TEST_CASE("WaitForCommand state transitions", "[state]") {
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);
  // Transition to WaitForCommand state directly.
  manager.changeState(std::make_unique<axillaryNodeManager::WaitForCommand>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::WaitForCommand));

  SECTION("Transition to SurveillanceMode on eRunSurveillanceMode") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eRunSurveillanceMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::SurveillanceMode));
  }

  SECTION("Transition to ChaseMode on eRunChaseMode") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eRunChaseMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::ChaseMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));
  }
}

TEST_CASE("SurveillanceMode state transitions", "[state]") {
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillaryNodeManager::SurveillanceMode>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::SurveillanceMode));

  SECTION("Transition to ChaseMode on eRunChaseMode") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eRunChaseMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::ChaseMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));
  }
}

TEST_CASE("ChaseMode state transitions", "[state]") {
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillaryNodeManager::ChaseMode>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::ChaseMode));

  SECTION("Transition to SurveillanceMode on eRunSurveillanceMode") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eRunSurveillanceMode);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::SurveillanceMode));
  }

  SECTION("Transition to Hibernate on eSensorSuiteCommLost") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteCommLost);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));
  }
}

TEST_CASE("Hibernate state transitions", "[state]") {
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillaryNodeManager::Hibernate>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Hibernate));

  SECTION("Transition to Shutdown on eHibernationComplete") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eHibernationComplete);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Shutdown));
  }

  SECTION("Transition to WaitForCommand on eSensorSuiteReady") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eSensorSuiteReady);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::WaitForCommand));
  }
}

TEST_CASE("Shutdown state transitions", "[state]") {
  axillaryNodeManager::Parameters parameters;
  axillaryNodeManager::AxillaryNodeManager manager(parameters);
  manager.changeState(std::make_unique<axillaryNodeManager::Shutdown>());
  REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Shutdown));

  SECTION("Transition to Standby on eInitialize") {
    manager.getCurrentState()->OnEvent(manager, axillaryNodeManager::Event::eInitialize);
    REQUIRE(typeid(*manager.getCurrentState()) == typeid(axillaryNodeManager::Standby));
  }
}
