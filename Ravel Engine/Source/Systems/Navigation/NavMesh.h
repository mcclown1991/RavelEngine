#pragma once
#include <array>
#include <bitset>
#include <map>
#include "NavMeshBoundVolume.h"

struct TrapezoidSearchGraphNode;

struct Line2D {
	Line2D() : start(Vector2()), end(Vector2()), normal(Vector2()) {}
	Line2D(Line2D const& r) { start = r.start; end = r.end; normal = r.normal; }
	Line2D& operator=(Line2D const& r) { start = r.start; end = r.end; normal = r.normal; return *this; }
	bool operator<(Line2D const& l)const {
		return this->start.x < l.start.x;
	}
	Vector2 start, end, normal;
};

struct Trapezoid {
public:
	Line2D top, bottom;
	Vector2 left, right;
	std::array<Trapezoid*, 4> _neighbour;
	std::bitset<4> _neighbourUsed;
	int _stateIndex;
	TrapezoidSearchGraphNode* graphState;

#define UPPERLEFT _neighbour[0]
#define LOWERLEFT _neighbour[1]
#define UPPERRIGHT _neighbour[2]
#define LOWERRIGHT _neighbour[3]
};

struct TrapezoidSearchGraphNode {
public:
	enum TSG_TYPE{TSG_XNODE, TSG_YNODE, TSG_LEAF};

	TrapezoidSearchGraphNode* left;
	TrapezoidSearchGraphNode* right;
	TSG_TYPE type;
	Vector2 point;
	Line2D line;
	Trapezoid* trapezoid;
};

class Navigation {
public:
	Navigation();
	void GenerateNavMesh(NavMeshBoundVolume* bounds);
	void CalculateLineNormal();
	void AdjustStartEndPointSegment();
	Trapezoid* TrapezoidSearch(TrapezoidSearchGraphNode const *searchS, Vector2 const &pointS, Vector2 const &pointE);
	void TrapezoidalMap();//compute the trapezoids that form the free space and link them together
	void AdjustRemainingTrapezoids();//IS IMPLEMENTED - It adjusts the top and bottom line segments of every trapezoid
	void RemoveUnusedTrapezoids();//Remove the unused (solid areas) trapezoids
	void PathBuilding();// generates a graph with states and edges

	void StatesBuild(Trapezoid *next, int previousState);//to be used inside PathBuilding() fct - It is a recursive function that builds the states and edges of the graph
	//Trapezoid *TrapezoidSearch(AG_State *searchS,Point2D pointS,Point2D pointE);//IS IMPLEMENTED

	

	//To add any new public member data and member function if needed here
	std::list<Trapezoid* > GetTrapezoids() const;
	TrapezoidSearchGraphNode* searchStructure;
	std::vector<Line2D> segmentList;
private:
	// Math functions
	enum CLASSIFY { CL_ABOVE, CL_UNDER, CL_ON };
	bool AlmostEqual(float x, float y);
	bool PointOnLineSegment(Vector2 const &, Line2D const &);
	CLASSIFY Classify_Point_To_LineSegment(Vector2 const &, Line2D const &);


	TrapezoidSearchGraphNode* GenerateTSGNode(TrapezoidSearchGraphNode::TSG_TYPE type);

	std::list<Trapezoid*> trapezoidalList;
	std::list<Trapezoid*> unusedTrapezoidalList;//this is used only to display the
	int currentState;
	std::map<Line2D, std::bitset<2>> usedPoints;
	std::vector<TrapezoidSearchGraphNode*> stateRef;

	//some byte testing stuff
	const std::bitset<2> NONUSED = 0x0;
	const std::bitset<2> STARTUSED = 0x1;
	const std::bitset<2> ENDUSED = 0x2;
	const std::bitset<2> ALLUSED = 0x3;
	const int STARTPOSITION = 0;
	const int ENDPOSITION = 1;
};

Navigation* Navigator();