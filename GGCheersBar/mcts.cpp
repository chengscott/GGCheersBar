#include "mcts.h"

namespace MCTS {
	Node::Node(const Node& rhs) {
		children_ = rhs.children_;
		moves_ = rhs.moves_;
		UCT_score_ = rhs.UCT_score_;
		wins_ = rhs.wins_;
		visits_ = rhs.visits_;
		move_ = rhs.move_;
		parent_ = rhs.parent_;
		chess_ = rhs.chess_;
	}

	Node::Node(const Go& go, const Position& pos = GGCheersBar::NotFound,
		Node* parent = nullptr) {
		moves_ = go.GetMoves();
		chess_ = go.getChess();
		parent_ = parent;
	}

	Node::~Node() {
		for (Node* child : children_) delete child;
	}

	Node& Node::operator=(const Node& rhs) {
		children_ = rhs.children_;
		moves_ = rhs.moves_;
		UCT_score_ = rhs.UCT_score_;
		wins_ = rhs.wins_;
		visits_ = rhs.visits_;
		move_ = rhs.move_;
		parent_ = rhs.parent_;
		chess_ = rhs.chess_;
	}

	Node* Node::AddChild(const Position& move, const Go& go) {;
		Node* child = new Node(go, move, this);
		children_.push_back(child);
		auto it = moves_.begin();
		while (it != moves_.end() && *it != move) ++it;
		moves_.erase(it);
		return child;
	}

	bool Node::hasChildren() const { return !children_.empty(); }

	bool Node::hasMoves() const { return !moves_.empty();  }

	double Node::getUCTscore() const { return UCT_score_; }

	Node* Node::GetUCTChild() const {
		for (Node* child : children_)
			child->UCT_score_ = double(child->visits_) / double(child->visits_) +
			std::sqrt(2.0 + std::log(double(visits_)) / child->visits_);
		return *std::max_element(children_.begin(), children_.end(),
			[](const Node& lhs, const Node& rhs) {
			return lhs.getUCTscore() < rhs.getUCTscore();
		});
	}

	void Node::Update(const double rhs) {
		++visits_;
		wins_ += rhs;
	}
}
