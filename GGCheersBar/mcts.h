#ifndef MCTS_Def
#define MCTS_Def
#include "go.h"
#include "util.h"
#include <vector>
#include <algorithm>

namespace MCTS {
	typedef typename GGCheersBar::Go Go;
	typedef typename GGCheersBar::Position Position;
	typedef typename GGCheersBar::Chess Chess;

	class Node {
	public:
		Node() { }
		Node(const Node&);
		Node(const Go&, const Position& = GGCheersBar::NotFound, Node* = nullptr);
		~Node();
		Node& operator=(const Node&);
		Node* AddChild(const Position&, const Go&);
		bool hasChildren() const;
		Node* GetUCTChild() const;
		bool hasMoves() const;
		// getUnMoves() const
		double getUCTscore() const;
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

	Position ComputeMove(const Go);
}
#endif