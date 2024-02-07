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
        }

        void Render() override {
        }
    };
}

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        game = std::make_unique<Game>();
    }

    void TearDown() override {
        game = nullptr;
    }

    // Game game;
    std::unique_ptr<Game> game;
};

TEST_F(GameTest, test1) {
    printf_s("start test1:\n");
    fprintf_s(stderr, "test1 message \n");
    ASSERT_TRUE(true);
    auto obj1 = std::make_shared<Object1>(game.get());
    game->AddGameObject(obj1);
    game->AddGameObject(obj1);
    game->RemoveGameObject(obj1);
    game->RemoveGameObject(obj1);
    printf_s("end test1\n");
}