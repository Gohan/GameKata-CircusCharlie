#include <gtest/gtest.h>
#include "framework/game/BaseGame.h"
#include "framework/game/GameObject.h"

namespace {
    class Game : public BaseGame {
    };

    class Object1 : public GameObject {
    public:
        explicit Object1(BaseGame* game) : GameObject(game) {
        }

        void Update(double deltaTime) override {
            updateCalledTimes++;
        }

        void Render() override {
            renderCalledTimes++;
        }

        int updateCalledTimes = 0;
        int renderCalledTimes = 0;
    };
}

class BaseGameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>();
    }

    void TearDown() override {
        game = nullptr;
    }

    void TickUpdate() {
        SDL_Event e;
        game->RunLoopOnce(e);
    }

    // Game game;
    std::unique_ptr<Game> game;
};

TEST_F(BaseGameTest, test1) {
    printf_s("start test1:\n");
    fprintf_s(stderr, "test1 message \n");
    ASSERT_TRUE(true);
    auto obj1 = std::make_shared<Object1>(game.get());
    auto obj2 = std::make_shared<Object1>(game.get());
    game->AddGameObject(obj1);
    game->AddGameObject(obj2);
    game->Init("TEST", 100, 100);
    game->RemoveGameObject(obj2);
    TickUpdate();
    ASSERT_GE(obj1->updateCalledTimes, 1);
    ASSERT_EQ(obj1->renderCalledTimes, 1);
    ASSERT_EQ(obj2->updateCalledTimes, 0);
    ASSERT_EQ(obj2->renderCalledTimes, 0);
    printf_s("end test1\n");
}