#pragma once

#include "GameServiceContainer.h"

class ControllerGameService : public IService<BaseGame>, public ISDLEventProcessor {
public:
    explicit ControllerGameService(BaseGame* game) {
        this->game = game;
    }

    ~ControllerGameService() override = default;

    bool OnProcessEvent(SDL_Event& e) override {
        switch (e.type) {
            case SDL_CONTROLLERDEVICEADDED: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLERDEVICEADDED");
                auto controller = SDL_GameControllerOpen(e.cdevice.which);
                auto name = SDL_GameControllerName(controller);
                SDL_GameControllerSetPlayerIndex(controller, gameControllers.size());
                auto mapping = SDL_GameControllerMappingForDeviceIndex(e.cdevice.which);
                gameControllers.push_back(controller);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: %s", name);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent mapping: ", mapping);
                break;
            }
            case SDL_CONTROLLERDEVICEREMOVED: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLERDEVICEREMOVED");
                auto removed = std::remove_if(gameControllers.begin(), gameControllers.end(), [&](const auto& item) {
                    return SDL_GameControllerGetJoystick(item) == SDL_JoystickFromInstanceID(e.cdevice.which);
                });
                if (removed != gameControllers.end()) {
                    SDL_GameControllerClose(*removed);
                    gameControllers.erase(removed);
                } else {
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: not found");
                }
                break;
            }
            case SDL_CONTROLLERBUTTONDOWN: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLERBUTTONDOWN");
                auto controllerButtonEvent = reinterpret_cast<SDL_ControllerButtonEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: button %d, %d",
                            controllerButtonEvent->button, controllerButtonEvent->state);
                switch (e.cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_A");
                        break;
                    case SDL_CONTROLLER_BUTTON_B:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_B");
                        break;
                    case SDL_CONTROLLER_BUTTON_X:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_X");
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_Y");
                        break;
                    case SDL_CONTROLLER_BUTTON_BACK:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_BACK");
                        break;
                    case SDL_CONTROLLER_BUTTON_GUIDE:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_GUIDE");
                        break;
                    case SDL_CONTROLLER_BUTTON_START:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_START");
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_LEFTSTICK");
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_RIGHTSTICK");
                        break;
                    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_LEFTSHOULDER");
                        break;
                    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_RIGHTSHOULDER");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_DPAD_UP");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_DPAD_DOWN");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_DPAD_LEFT");
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLER_BUTTON_DPAD_RIGHT");
                        break;

                    default:
                        break;
                }
                break;
            }
            case SDL_CONTROLLERBUTTONUP: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_CONTROLLERBUTTONUP");
                auto controllerButtonUpEvent = reinterpret_cast<SDL_ControllerButtonEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: button %d, %d",
                            controllerButtonUpEvent->button, controllerButtonUpEvent->state);
                break;
            }
            case SDL_JOYDEVICEADDED: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYDEVICEADDED");
                auto joystick = SDL_JoystickOpen(e.jdevice.which);
                joysticks.push_back(joystick);
                break;
            }
            case SDL_JOYDEVICEREMOVED: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                            "ControllerGameService::OnProcessEvent: SDL_JOYDEVICEREMOVED");
                auto removed = std::remove_if(joysticks.begin(), joysticks.end(), [&](const auto& item) {
                    return SDL_JoystickInstanceID(item) == e.jdevice.which;
                });
                if (removed != joysticks.end()) {
                    SDL_JoystickClose(*removed);
                    joysticks.erase(removed);
                }
                break;
            }
            case SDL_JOYBUTTONDOWN: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYBUTTONDOWN");
                auto joyButtonEvent = reinterpret_cast<SDL_JoyButtonEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: button %d, %d",
                            joyButtonEvent->button, joyButtonEvent->state);
                break;
            }
            case SDL_JOYBUTTONUP: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYBUTTONUP");
                auto joyButtonUpEvent = reinterpret_cast<SDL_JoyButtonEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: button %d, %d",
                            joyButtonUpEvent->button, joyButtonUpEvent->state);
                break;
            }
            case SDL_JOYBALLMOTION: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYBALLMOTION");
                auto joyBallEvent = reinterpret_cast<SDL_JoyBallEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: ball %d, %d, %d",
                            joyBallEvent->ball, joyBallEvent->xrel, joyBallEvent->yrel);
                break;
            }
            case SDL_JOYHATMOTION: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYHATMOTION");
                auto joyHatEvent = reinterpret_cast<SDL_JoyHatEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: hat %d, %d",
                            joyHatEvent->hat, joyHatEvent->value);
                break;
            }
            case SDL_JOYAXISMOTION: {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: SDL_JOYAXISMOTION");
                auto joyAxisEvent = reinterpret_cast<SDL_JoyAxisEvent*>(&e);
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: axis %d, %d",
                            joyAxisEvent->axis, joyAxisEvent->value);
                break;
            }
            default:
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: %d", e.type);
                break;
        }
        return false;
    }

    void GetJoystickKeys() {
        for (auto joystick: joysticks) {
            for (int i = 0; i < SDL_JoystickNumButtons(joystick); i++) {
                if (SDL_JoystickGetButton(joystick, i)) {
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::GetJoystickKeys: button %d", i);
                }
            }
        }
    }

private:
    std::deque<SDL_Joystick*> joysticks;
    std::deque<SDL_GameController*> gameControllers;
};
