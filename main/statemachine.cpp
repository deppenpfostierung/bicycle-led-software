#include "statemachine.h"

constexpr const char *const TAG = "STATEMACHINE";

// esp-idf includes
#include <esp_log.h>

namespace bicycle
{

void StateMachine::start()
{
    m_currentState = {};
}

void StateMachine::update()
{
    if (m_currentState.lights.blinkerState != State::Lights::OFF)
    {
        if (m_currentState.lights.lastBlinkerChange == std::nullopt ||
            espchrono::ago(*m_currentState.lights.lastBlinkerChange) > timings.BLINKER_INTERVAL)
        {
            m_currentState.lights.blinkVisible = !m_currentState.lights.blinkVisible;
            m_currentState.lights.lastBlinkerChange = espchrono::millis_clock::now();
        }
    }
    else
    {
        m_currentState.lights.blinkVisible = false;
    }
}

void StateMachine::stop()
{
}

void StateMachine::handleAction(const Action action)
{
    switch (action)
    {
    case BLINKER_OFF:
        m_currentState.lights.blinkerState = State::Lights::OFF;
        return;
    case BLINKER_TOGGLE_LEFT: {
        switch (m_currentState.lights.blinkerState)
        {
        case State::Lights::LEFT:
        case State::Lights::HAZARD:
            m_currentState.lights.blinkerState = State::Lights::OFF;
            break;
        case State::Lights::RIGHT:
            m_currentState.lights.blinkerState = State::Lights::HAZARD;
            break;
        case State::Lights::OFF:
            m_currentState.lights.blinkerState = State::Lights::LEFT;
            break;
        default:
            ESP_LOGW(TAG, "Unknown blinker state %d", m_currentState.lights.blinkerState);
            break;
        }
        return;
    }
    case BLINKER_TOGGLE_RIGHT: {
        switch (m_currentState.lights.blinkerState)
        {
        case State::Lights::RIGHT:
        case State::Lights::HAZARD:
            m_currentState.lights.blinkerState = State::Lights::OFF;
            break;
        case State::Lights::LEFT:
            m_currentState.lights.blinkerState = State::Lights::HAZARD;
            break;
        case State::Lights::OFF:
            m_currentState.lights.blinkerState = State::Lights::RIGHT;
            break;
        default:
            ESP_LOGW(TAG, "Unknown blinker state %d", m_currentState.lights.blinkerState);
            break;
        }
        return;
    }
    case BLINKER_TOGGLE_HAZARD:
        m_currentState.lights.blinkerState = m_currentState.lights.blinkerState == State::Lights::HAZARD ? State::Lights::OFF : State::Lights::HAZARD;
        return;
    case HIGH_BEAM_TOGGLE:
        m_currentState.lights.highBeam = !m_currentState.lights.highBeam;
        return;
    case HIGH_BEAM_ON:
        m_currentState.lights.highBeam = true;
        return;
    case HIGH_BEAM_OFF:
        m_currentState.lights.highBeam = false;
        return;
    case LOW_BEAM_TOGGLE:
        m_currentState.lights.lowBeam = !m_currentState.lights.lowBeam;
        return;
    case LOW_BEAM_ON:
        m_currentState.lights.lowBeam = true;
        return;
    case LOW_BEAM_OFF:
        m_currentState.lights.lowBeam = false;
        return;
    case BRAKE_LIGHT_TOGGLE:
        m_currentState.lights.brakeLight = !m_currentState.lights.brakeLight;
        return;
    case BRAKE_LIGHT_ON:
        m_currentState.lights.brakeLight = true;
        return;
    case BRAKE_LIGHT_OFF:
        m_currentState.lights.brakeLight = false;
        return;
    case REAR_FOG_LIGHT_TOGGLE:
        m_currentState.lights.rearFogLight = !m_currentState.lights.rearFogLight;
        return;
    case REAR_FOG_LIGHT_ON:
        m_currentState.lights.rearFogLight = true;
        return;
    case REAR_FOG_LIGHT_OFF:
        m_currentState.lights.rearFogLight = false;
        return;
    default:
        ESP_LOGW(TAG, "Unknown action %d", action);
    }
}

StateMachine stateMachine;

void init_statemachine()
{
    stateMachine.start();
}

void update_statemachine()
{
    stateMachine.update();
}

} // namespace bicycle