#include "framework/game/BaseGame.h"
#include "framework/services/GameServiceContainer.h"

class ControllerGameService;

class Game : public BaseGame {
public:
    Game();
    virtual ~Game();
    void OnInitialize() override;

    template<class T>
    void AddService(std::shared_ptr<T> service) {
        container->AddService<T>(service);
    }

    template<class T>
    void RemoveService() {
        container->RemoveService<T>();
    }

    template<class T>
    std::shared_ptr<T> GetService() {
        return container->GetService<T>();
    }

private:
    std::shared_ptr<ControllerGameService> controllerGameService;
};