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
	Node::Node(const Go& go, const Position& pos, Node* parent) {
		move_ = pos;
		moves_ = go.GetMoves();
		chess_ = go.getChess();
		parent_ = parent;
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
		return *this;
	}
	Node::~Node() {
		for (Node* child : children_) delete child;
	}
	std::vector<Node*> Node::getChildren() const { return children_; }
	double Node::getUCTscore() const { return UCT_score_; }
	double Node::getWins() const { return wins_; }
	int Node::getVisits() const { return visits_; }
	Position Node::getMove() const { return move_; }
	Node* Node::getParent() const { return parent_; }
	Node* Node::AddChild(const Position& move, const Go& go) {;
		Node* child = new Node(go, move, this);
		children_.push_back(child);
		auto it = moves_.begin();
		while (it != moves_.end() && *it != move) ++it;
		moves_.erase(it);
		return child;
	}
	bool Node::hasChildren() const { return !children_.empty(); }
	Node* Node::GetUCTChild() const {
		for (Node* child : children_)
			child->UCT_score_ = double(child->wins_) / double(child->visits_) +
			std::sqrt(2.0 + std::log(double(visits_)) / child->visits_);
		return *std::max_element(children_.begin(), children_.end(),
			[](const Node* lhs, const Node* rhs) {
			return lhs->getUCTscore() < rhs->getUCTscore();
		});
	}
	bool Node::hasMoves() const { return !moves_.empty(); }
	Position Node::getExpandedMove() const {
		// HACK: heuristics
		return moves_[0];
	}
	void Node::Update(const double rhs) {
		++visits_;
		wins_ += rhs;
	}

	Position ComputeMove(const Go& go) {
		std::vector<Position> moves = go.GetMoves();
		if (moves.size() == 1) return moves[0];
		Node root = ComputeTree(go);
		long long games_played = root.getVisits();
		std::map<Position, int> visits;
		std::map<Position, double> wins;
		std::vector<Node*> children = root.getChildren();
		for (auto child = children.cbegin(); child != children.cend(); ++child) {
			visits[(*child)->getMove()] += (*child)->getVisits();
			wins[(*child)->getMove()] += (*child)->getWins();
		}
		double best_score = -1;
		Position best_move = Position();
		for (auto itr : visits) {
			Position move = itr.first;
			double v = itr.second;
			double w = wins[move];
			// Expected success rate assuming a uniform prior (Beta(1, 1)).
			// https://en.wikipedia.org/wiki/Beta_distribution
			double expected_success_rate = (w + 1) / (v + 2);
			if (expected_success_rate > best_score) {
				best_move = move;
				best_score = expected_success_rate;
			}
		}
		printf("Expected success rate: %.3f%%", best_score);
		return best_move;
	}

	Node ComputeTree(Go go) {
		auto start_time = high_resolution_clock::now();
		Node* node = new Node(go);
		while (true) {
			// Selection
			while (!node->hasMoves() && node->hasChildren()) {
				node = node->GetUCTChild();
				go.Move(node->getMove());
			}
			// Expansion
			if (node->hasMoves()) {
				Position move = node->getExpandedMove();
				go.Move(move);
				node = node->AddChild(move, go);
			}
			// Simulation
			while (go.Judge() == GGCheersBar::On) go.Simulation();
			// Backpropogation
			Node* node_parent = node->getParent();
			while (node_parent != nullptr) {
				node->Update(go.Judge());
				node = node_parent;
				node_parent = node->getParent();
			}
			// time threshold
			auto end_time = high_resolution_clock::now();
			double dt = 1.e-9*duration_cast<nanoseconds>(end_time - start_time).count();
			if (dt > THRESHOLD_TIME) break;
		}
		return *node;
	}
}