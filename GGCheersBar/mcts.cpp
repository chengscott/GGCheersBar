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
		return *this;
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

	std::vector<Node*> Node::getChildren() const { return children_; }

	double Node::getUCTscore() const { return UCT_score_; }

	int Node::getVisits() const { return visits_; }

	Position Node::getMove() const { return move_; }

	Node* Node::GetUCTChild() const {
		for (Node* child : children_)
			child->UCT_score_ = double(child->visits_) / double(child->visits_) +
			std::sqrt(2.0 + std::log(double(visits_)) / child->visits_);
		return *std::max_element(children_.begin(), children_.end(),
			[](const Node* lhs, const Node* rhs) {
			return lhs->getUCTscore() < rhs->getUCTscore();
		});
	}

	void Node::Update(const double rhs) {
		++visits_;
		wins_ += rhs;
	}

	Position ComputeMove(const Go& go) {
		auto moves = go.GetMoves();
		if (moves.size() == 1) return moves[0];
		Node root = ComputeTree(go);
		std::map<Position, int> visits;
		std::map<Position, double> wins;
		long long games_played = root.getVisits();
		auto children = root.getChildren;
		for (auto child = children.cbegin(); child != children.cend(); ++child) {
			visits[(*child)->move] += (*child)->visits;
			wins[(*child)->move] += (*child)->wins;
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
			// Move: itr.first
			// visits (%): int(100.0 * v / double(games_played) + 0.5)
			// wins (%): int(100.0 * w / v + 0.5)
		}
		return best_move;
	}

	Node ComputeTree(Go go) {
		auto start_time = std::chrono::high_resolution_clock::now();
		Node node = Node(go);
		while (true) {
			while (!node.hasMoves() && node.hasChildren) {
				node = *node.GetUCTChild();
				go.Move(node.getMove());
			}
			if (node.hasMoves()) {
				auto move = node.getNotMove();
				go.Move(move);
				node = *node.AddChild(move, go);
			}
			// while (go.has_moves) go.random_move
			auto end_time = std::chrono::high_resolution_clock::now();
			double dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
			if (dt > THRESHOLD_TIME) break;
		}
		return node;

	}
}
