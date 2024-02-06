module;

export module GameService:ControllerGameService;

import :IService;

class Game;

export class ControllerGameService : public IService {
public:
    explicit ControllerGameService(Game* game);

    virtual ~ControllerGameService() override {
    };
};
