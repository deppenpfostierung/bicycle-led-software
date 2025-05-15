#pragma once

// system includes
#include <cppmacros.h>

namespace bicycle
{

enum Action
{
    // BLINKER
    BLINKER_OFF,
    BLINKER_LEFT,
    BLINKER_RIGHT,
    BLINKER_HAZARD,

    // HIGH BEAM
    HIGH_BEAM_TOGGLE,
    HIGH_BEAM_ON,
    HIGH_BEAM_OFF,

    // LOW BEAM
    LOW_BEAM_TOGGLE,
    LOW_BEAM_ON,
    LOW_BEAM_OFF,

    // BRAKE LIGHT
    BRAKE_LIGHT_TOGGLE,
    BRAKE_LIGHT_ON,
    BRAKE_LIGHT_OFF,

    // REAR FOG LIGHT
    REAR_FOG_LIGHT_TOGGLE,
    REAR_FOG_LIGHT_ON,
    REAR_FOG_LIGHT_OFF,
};

struct State
{
    struct Lights
    {
        enum BlinkerState
        {
            OFF,
            LEFT,
            RIGHT,
            HAZARD
        } blinkerState = OFF;

        bool highBeam { false };
        bool lowBeam { false };

        bool brakeLight { false };

        bool rearFogLight { false };
    } lights;

    struct Battery
    {
        enum BatteryState
        {
            BATTERY_OK,
            BATTERY_LOW,
            BATTERY_CRITICAL
        } batteryState = BATTERY_OK;
    } battery;
};

class StateMachine final
{
public:
    StateMachine() = default;

    ~StateMachine() = default;

    CPP_DISABLE_COPY_MOVE(StateMachine)

    void start();
    void update();
    void stop();

    void handleAction(Action action);

    const State &getCurrentState() const
    {
        return m_currentState;
    }

private:
    State m_currentState;
};

extern StateMachine stateMachine;

void init_statemachine();

void update_statemachine();

} // namespace bicycle