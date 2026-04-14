#include <iostream>
#include "game.h"

void loadCards(Pile& draw_pile) {
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string card_type;
        std::cin >> card_type;
        Card *card = nullptr;
        if (card_type == "SCORE") {
            int point;
            std::cin >> point;
            card = new ScoreCard(point);
        } else if (card_type == "SKILL") {
            std::string skill_type;
            std::cin >> skill_type;
            if (skill_type == "Multiplier") {
                card = new SkillCard(SkillCardType::MULTIPLIER);
            } else if (skill_type == "HeadButt") {
                card = new SkillCard(SkillCardType::HEAD_BUTT);
            }
        } else if (card_type == "POWER") {
            int plus_count;
            std::cin >> plus_count;
            card = new PowerCard(plus_count);
        }

        if (card == nullptr) {
            throw std::runtime_error("Invalid Operation");
        }

        draw_pile.appendCard(card);
    }
}

void processCommands(GameController& game) {
    std::string command;
    while (std::cin >> command) {
        if (command == "draw") {
            game.draw();
        } else if (command == "play") {
            int card_index;
            std::cin >> card_index;
            game.play(card_index);
        } else if (command == "finish") {
            game.finish();
        } else if (command == "exit") {
            break;
        } else if (command == "query") {
            std::string query_type;
            std::cin >> query_type;
            if (query_type == "score") {
                std::cout << game.queryScore() << std::endl;
            } else if (query_type == "hand") {
                std::cout << game.queryHandSize() << std::endl;
            } else if (query_type == "draw_pile") {
                std::cout << game.queryDrawPileSize() << std::endl;
            } else if (query_type == "discard_pile") {
                std::cout << game.queryDiscardPileSize() << std::endl;
            } else {
                throw std::runtime_error("Invalid Operation");
            }
        } else {
            throw std::runtime_error("Invalid Operation");
        }
    }
}

int main() {
    int shuffle_mode;
    std::cin >> shuffle_mode;
    auto game_controller = GameController(shuffle_mode);

    // Load cards to the draw pile
    loadCards(game_controller.drawPile());

    // Game controller processes commands
    processCommands(game_controller);
}

