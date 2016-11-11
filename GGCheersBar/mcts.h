#ifndef MCTS_Def
#define MCTS_Def
#include "go.h"
#include "util.h"
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

namespace MCTS {
	typedef typename GGCheersBar::Go Go;
	typedef typename GGCheersBar::Position Position;
	typedef typename GGCheersBar::Chess Chess;
	static const double THRESHOLD_TIME = 9.2;

	class Node {
	public:
		Node() { }
		Node(const Node&);
		Node(const Go&, const Position& = GGCheersBar::NotFound, Node* = nullptr);
		Node& operator=(const Node&);
		~Node();
		std::vector<Node*> getChildren() const;
		double getUCTscore() const;
		double getWins() const;
		int getVisits() const;
		Position getMove() const;
		Node* getParent() const;
		Node* AddChild(const Position&, const Go&);
		bool hasChildren() const;
		Node* GetUCTChild() const;
		bool hasMoves() const;
		Position getNotMove() const;
		void Update(const double);
	private:
		std::vector<Node*> children_;
		std::vector<Position> moves_;
		double UCT_score_ = 0;
		double wins_ = 0;
		int visits_ = 0;
		Position move_;
		Node* parent_;
		Chess chess_;
	};

	Position ComputeMove(const Go&);
	Node ComputeTree(Go);
}
#endif