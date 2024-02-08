#pragma once

#include "GameServiceContainer.h"
#include "absl/strings/str_join.h"

namespace {
    constexpr bool DEBUG = true;
}

namespace {
    class ControllerState {
    public:
        ControllerState(int32_t which, SDL_GameController* controller) :
                which(which), controller(controller) {
            axes.resize(SDL_CONTROLLER_AXIS_MAX, 0);
        }

        int32_t which;
        SDL_GameController* controller;
        std::bitset<SDL_CONTROLLER_BUTTON_MAX> buttons;
        std::vector<int16_t> axes;
    };
}

class ControllerGameService : public IService<BaseGame>, public ISDLEventProcessor {
public:
    explicit ControllerGameService(BaseGame* game) {
        this->game = game;
    }

    ~ControllerGameService() override {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService destroyed");
    };

    bool OnProcessEvent(SDL_Event& e) override {
        switch (e.type) {
            case SDL_CONTROLLERDEVICEADDED: {
                SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                             "ControllerGameService::OnProcessEvent: SDL_CONTROLLERDEVICEADDED");
                auto controller = SDL_GameControllerOpen(e.cdevice.which);
                auto state = ControllerState{e.cdevice.which, controller};
                gameControllers.emplace_back(state);
                break;
            }
            case SDL_CONTROLLERDEVICEREMOVED: {
                SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                             "ControllerGameService::OnProcessEvent: SDL_CONTROLLERDEVICEREMOVED");
                auto removed = std::remove_if(gameControllers.begin(), gameControllers.end(), [&](const auto& item) {
                    return item.which == e.cdevice.which;
                });
                if (removed != gameControllers.end()) {
                    SDL_GameControllerClose(removed->controller);
                    gameControllers.erase(removed);
                } else {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ControllerGameService::OnProcessEvent: not found");
                }
                break;
            }
            case SDL_CONTROLLERBUTTONUP:
            case SDL_CONTROLLERBUTTONDOWN: {
                auto it = std::find_if(gameControllers.begin(), gameControllers.end(), [&](const auto& item) {
                    return item.which == e.cbutton.which;
                });
                if (it == gameControllers.end()) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                                 "ControllerGameService::OnProcessEvent(SDL_CONTROLLERBUTTON): not found controller");
                    return false;
                }
                if (e.cbutton.state == SDL_PRESSED) {
                    it->buttons.set(e.cbutton.button);
                } else {
                    it->buttons.reset(e.cbutton.button);
                }
                if (DEBUG) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                                 "ControllerGameService::OnProcessEvent: SDL_CONTROLLERBUTTON: %s",
                                 it->buttons.to_string().c_str());
                }
                break;
            }
            case SDL_CONTROLLERAXISMOTION: {
                auto it = std::find_if(gameControllers.begin(), gameControllers.end(), [&](const auto& item) {
                    return item.which == e.caxis.which;
                });
                if (it == gameControllers.end()) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                                 "ControllerGameService::OnProcessEvent(SDL_CONTROLLERAXISMOTION): not found controller");
                    return false;
                }
                it->axes[e.caxis.axis] = e.caxis.value;
                if (DEBUG) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                                 "ControllerGameService::OnProcessEvent: SDL_CONTROLLERAXISMOTION: %s",
                                 absl::StrJoin(it->axes, ", ").c_str());
                }
                break;
            }
        }
        return false;
    }

private:
    std::deque<ControllerState> gameControllers;
};
