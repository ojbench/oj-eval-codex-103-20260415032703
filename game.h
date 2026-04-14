#ifndef GAME_H
#define GAME_H

#include <string>
#include <stdexcept>

struct Node;
struct GameState;
class Card;
class Pile;

enum SkillCardType {
    MULTIPLIER,
    HEAD_BUTT,
};

class Card {
public:
    explicit Card() = default;
    virtual ~Card() = default;
    virtual void play(GameState& game_state) = 0;
};

class ScoreCard: public Card {
private:
    int point_{};
public:
    explicit ScoreCard(int point);
    void play(GameState &game_state) override;
    ~ScoreCard() override = default;
};

class SkillCard: public Card {
private:
    SkillCardType type_{};
public:
    explicit SkillCard(SkillCardType skill_card_type);
    void play(GameState &game_state) override;
    ~SkillCard() override = default;
};

class PowerCard: public Card {
private:
    int plus_{};
public:
    explicit PowerCard(int plus_count);
    void play(GameState &game_state) override;
    ~PowerCard() override = default;
};

struct Node {
    Card* card{nullptr};
    Node* next{nullptr};
    Node* prev{nullptr};
};

class Pile {
private:
    int size_{0};
    Node* head_{nullptr};
    Node* tail_{nullptr};

    void push_back_node(Node* n) {
        n->next = nullptr;
        n->prev = tail_;
        if (tail_) tail_->next = n;
        tail_ = n;
        if (!head_) head_ = n;
        ++size_;
    }
    Node* pop_front_node() {
        if (!head_) return nullptr;
        Node* n = head_;
        head_ = head_->next;
        if (head_) head_->prev = nullptr; else tail_ = nullptr;
        n->next = n->prev = nullptr;
        --size_;
        return n;
    }
    Node* pop_back_node() {
        if (!tail_) return nullptr;
        Node* n = tail_;
        tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr; else head_ = nullptr;
        n->next = n->prev = nullptr;
        --size_;
        return n;
    }
    void append_from(Pile& other) {
        // move all nodes from other's head to this tail
        while (!other.empty()) {
            Node* n = other.pop_front_node();
            push_back_node(n);
        }
    }
    Node* nth_node(int idx) {
        // 1-based from head
        if (idx < 1 || idx > size_) return nullptr;
        Node* cur = head_;
        for (int i = 1; i < idx; ++i) cur = cur->next;
        return cur;
    }
    Node* remove_node(Node* n) {
        if (!n) return nullptr;
        if (n->prev) n->prev->next = n->next; else head_ = n->next;
        if (n->next) n->next->prev = n->prev; else tail_ = n->prev;
        n->next = n->prev = nullptr;
        --size_;
        return n;
    }
public:
    friend void outShuffle(GameState&);
    friend void inShuffle(GameState&);
    friend void oddEvenShuffle(GameState&);
    friend class GameController;
    friend class SkillCard;

    Pile() = default;
    ~Pile();

    int size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void appendCard(Card* card);
};

struct GameState {
    Pile hand_{};
    Pile draw_pile_{};
    Pile discard_pile_{};
    long long total_score{0};
    long long multiplier{1};
    long long power_plus{0};
};

void outShuffle(GameState &game_state);
void inShuffle(GameState &game_state);
void oddEvenShuffle(GameState &game_state);

class GameController {
private:
    GameState game_state_{};
    void (*shuffle_)(GameState&) = nullptr;
public:
    explicit GameController(int mode);
    void draw();
    void play(int card_to_play);
    void finish();
    void shuffle();
    int queryScore();
    int queryDrawPileSize() const { return game_state_.draw_pile_.size(); }
    int queryHandSize() const { return game_state_.hand_.size(); }
    int queryDiscardPileSize() const { return game_state_.discard_pile_.size(); }
    Pile& drawPile() { return game_state_.draw_pile_; }
};

// ================= 洗牌函数实现 ===================
void outShuffle(GameState& game_state) {
    // Move discard head->tail into draw tail
    while (!game_state.discard_pile_.empty()) {
        Node* n = game_state.discard_pile_.pop_front_node();
        game_state.draw_pile_.push_back_node(n);
    }
}

void inShuffle(GameState& game_state) {
    // Move discard tail->head into draw tail (reverse order)
    while (!game_state.discard_pile_.empty()) {
        Node* n = game_state.discard_pile_.pop_back_node();
        game_state.draw_pile_.push_back_node(n);
    }
}

void oddEvenShuffle(GameState& game_state) {
    // Split by index from head: odd group then even group; preserve order within each.
    Pile& d = game_state.discard_pile_;
    Pile& draw = game_state.draw_pile_;
    if (d.empty()) return;
    // Build two temporary piles for odd and even maintaining order
    Pile odd; Pile even;
    int idx = 1;
    while (!d.empty()) {
        Node* n = d.pop_front_node();
        if (idx % 2 == 1) odd.push_back_node(n);
        else even.push_back_node(n);
        ++idx;
    }
    // Append odd then even to draw
    while (!odd.empty()) draw.push_back_node(odd.pop_front_node());
    while (!even.empty()) draw.push_back_node(even.pop_front_node());
}
    
// ================= Card Class Implementation ===========================

ScoreCard::ScoreCard(int point) : point_(point) {}

void ScoreCard::play(GameState &game_state) {
   long long gained = (long long)point_ + game_state.power_plus;
   gained *= game_state.multiplier;
   game_state.total_score += gained;
   game_state.multiplier = 1; // reset after score card
}

SkillCard::SkillCard(SkillCardType skill_card_type) : type_(skill_card_type) {}
void SkillCard::play(GameState &game_state) {
    if (type_ == MULTIPLIER) {
        game_state.multiplier += 1;
    } else if (type_ == HEAD_BUTT) {
        // Move discard tail to draw head
        Node* n = game_state.discard_pile_.pop_back_node();
        if (n) {
            // push to draw head
            n->prev = nullptr;
            n->next = game_state.draw_pile_.head_;
            if (game_state.draw_pile_.head_) game_state.draw_pile_.head_->prev = n;
            game_state.draw_pile_.head_ = n;
            if (!game_state.draw_pile_.tail_) game_state.draw_pile_.tail_ = n;
            game_state.draw_pile_.size_++;
        }
    }
}

PowerCard::PowerCard(int plus_count) : plus_(plus_count) {}
void PowerCard::play(GameState &game_state) {
    game_state.power_plus += plus_;
}

// ================= Pile Class Implementation ===========================
Pile::~Pile() {
    // Delete all nodes and the cards inside (ownership of cards is here)
    Node* cur = head_;
    while (cur) {
        Node* nxt = cur->next;
        delete cur->card;
        delete cur;
        cur = nxt;
    }
    head_ = tail_ = nullptr; size_ = 0;
}

void Pile::appendCard(Card* card) {
    Node* n = new Node();
    n->card = card;
    push_back_node(n);
}

// ================= Game Controller Class Implementation ======================

GameController::GameController(int mode){
    if (mode == 1) shuffle_ = &outShuffle;
    else if (mode == 2) shuffle_ = &inShuffle;
    else if (mode == 3) shuffle_ = &oddEvenShuffle;
    else throw std::runtime_error("Invalid Operation");
}

void GameController::draw() {
    int to_draw = 5;
    while (to_draw-- > 0) {
        if (game_state_.draw_pile_.empty()) {
            // Only trigger shuffle during draw, and only if discard not empty
            if (!game_state_.discard_pile_.empty()) {
                shuffle();
            } else {
                // nothing to draw
            }
        }
        if (game_state_.draw_pile_.empty()) {
            // cannot draw more
            continue;
        }
        Node* n = game_state_.draw_pile_.pop_front_node();
        game_state_.hand_.push_back_node(n);
    }
}

void GameController::play(int card_to_play) {
    if (card_to_play < 1 || card_to_play > game_state_.hand_.size()) return;
    Node* n = game_state_.hand_.nth_node(card_to_play);
    n = game_state_.hand_.remove_node(n);
    Card* c = n->card;
    n->card = nullptr; // detach
    delete n; // remove node; card handled separately
    c->play(game_state_);
    // After effect: if Score or Skill -> move to discard; if Power -> delete
    if (dynamic_cast<PowerCard*>(c) != nullptr) {
        delete c;
    } else {
        game_state_.discard_pile_.appendCard(c);
    }
}

void GameController::shuffle() {
    if (shuffle_) shuffle_(game_state_);
}

void GameController::finish() {
    // move all hand cards to discard preserving order
    while (!game_state_.hand_.empty()) {
        Node* n = game_state_.hand_.pop_front_node();
        game_state_.discard_pile_.push_back_node(n);
    }
}

int GameController::queryScore() {
    return static_cast<int>(game_state_.total_score);
}

#endif //GAME_H
