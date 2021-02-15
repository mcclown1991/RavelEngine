#include "NavMesh.h"
#include "CollisionManager.h"

#include <queue>

#undef min

Navigation * Navigator()
{
	static Navigation s;
	return(&s);
}


Navigation::Navigation()
{
}

bool Navigation::AlmostEqual(float x, float y) {
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place), 
	// which is 1 in this case
	return std::abs(x - y) < std::numeric_limits<float>::epsilon() * std::abs(x + y)
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<float>::min();
}

bool Navigation::PointOnLineSegment(Vector2 const &pnt, Line2D const &lns) {
	float res1 = lns.end.y - lns.start.y;
	float res2 = lns.end.x - lns.start.x;
	float res3 = pnt.x - lns.start.x;
	float res4 = pnt.y - lns.start.y;
	float t;

	if (AlmostEqual(res3*res1, res4*res2)) //the point is on the line of the segment
	{
		if (res1 != 0.0f)
			t = res4 / res1;
		else //if(res2 != 0)
			t = res3 / res2;
		if ((t >= 0.0f) && (t <= 1.0f))
			return true;
	}
	return false;
}

Navigation::CLASSIFY Navigation::Classify_Point_To_LineSegment(Vector2 const &pnt, Line2D const &lns) {
	Vector2 v1(pnt.x - lns.start.x, pnt.y - lns.start.y);
	Vector2 v2(lns.end.x - lns.start.x, lns.end.y - lns.start.y);
	if (AlmostEqual(v1.x*v2.y, v1.y*v2.x))
		return CL_ON;
	if (v1.x*v2.y - v1.y*v2.x > 0.0f)
		return CL_UNDER;
	else
		return CL_ABOVE;
}

TrapezoidSearchGraphNode* Navigation::GenerateTSGNode(TrapezoidSearchGraphNode::TSG_TYPE type) {
	TrapezoidSearchGraphNode* node = Memory()->alloc<TrapezoidSearchGraphNode>();
	node->type = type;
	stateRef.push_back(node);
	return node;
}

void Navigation::CalculateLineNormal() {
	for (Line2D& lines : segmentList) {
		lines.normal = Vector2(-(lines.end.y - lines.start.y), lines.end.x - lines.start.x);
		float dominator = sqrt((lines.normal.x * lines.normal.x) + (lines.normal.y * lines.normal.y));
		lines.normal.x = lines.normal.x / dominator;
		lines.normal.y = lines.normal.y / dominator;
	}
}

void Navigation::AdjustStartEndPointSegment() {
	std::for_each(segmentList.begin(), segmentList.end(), [](Line2D& line) {
		if (line.end.x < line.start.x)
			std::swap(line.start, line.end);
	});
}

Trapezoid *Navigation::TrapezoidSearch(TrapezoidSearchGraphNode const *searchS, Vector2 const &pointS, Vector2 const &pointE) {
	TrapezoidSearchGraphNode const *temp = searchS;
	while (temp) {
		switch (temp->type) {
		case TrapezoidSearchGraphNode::TSG_XNODE:
			//NOTES
			//because of the line segments general positions strategy
			//the points should not have the same x.

			if (pointS.x < temp->point.x)
				temp = temp->left;
			else
				temp = temp->right;
			break;
		case TrapezoidSearchGraphNode::TSG_YNODE:
			//NOTES
			//if p lies on the current segment (this can only happen if both segments
			//share their left end point)
			//so we only compare their slopes to classify the point

			switch (Classify_Point_To_LineSegment(pointS, temp->line)) {
			case CL_ABOVE:
				temp = temp->left;
				break;
			case CL_UNDER:
				temp = temp->right;
				break;
			case CL_ON:
				if (Classify_Point_To_LineSegment(pointE, temp->line) == CL_ABOVE)
					temp = temp->left;
				else
					temp = temp->right;
				break;
			}
			break;
		case TrapezoidSearchGraphNode::TSG_LEAF:
			return temp->trapezoid;
			break;
		}
	}
	return nullptr;
}

void Navigation::TrapezoidalMap() {
	searchStructure = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
	//Initialization of the search structure for the trapezoidal map
	//searchStructure : root of the directed acyclic binary search tree - (one single root for all)
	//searchStructure->type = AG_LEAF;
	std::list<Trapezoid*>::iterator temptr1;
	temptr1 = trapezoidalList.begin();
	searchStructure->trapezoid = *temptr1;
	(*temptr1)->graphState = searchStructure;

	std::queue<Trapezoid *> interceptTraps;

	//continue here
	std::for_each(segmentList.begin(), segmentList.end(), [&](Line2D& line) {

		std::bitset<2> result;
		for (std::pair<Line2D const, std::bitset<2>>& testline : usedPoints) {

			//test start point 
			if (line.start == testline.first.start || line.start == testline.first.end) {
				//start point shares
				result |= STARTUSED;
			}

			if (line.end == testline.first.start || line.end == testline.first.end) {
				//end point shares
				result |= ENDUSED;
			}
		}

		usedPoints[line] = result;
		Trapezoid* trap = TrapezoidSearch(searchStructure, line.start, line.end);
		if (trap != nullptr) {
			interceptTraps.push(trap);
			bool findingTraps = true;

			// finding intercepted trapizoids
			while (findingTraps) {
				//is above
				if (trap->right.y > line.start.y) {
					Trapezoid* upper = trap->UPPERRIGHT;
					Trapezoid* lower = trap->LOWERRIGHT;
					if (lower && lower->right.x < line.end.x) {
						trap = lower;
						interceptTraps.push(trap);
					}
					else if (upper && upper->right.x < line.end.x) {
						trap = upper;
						interceptTraps.push(trap);
					}
					else {
						findingTraps = false;
					}
					continue;
				}
				findingTraps = false;
			}

			// building new traps
			//test if points is in used... 
			if (usedPoints.count(line) > 0) {
				if (interceptTraps.size() == 1) {//1 interception

					Trapezoid* t = interceptTraps.front();
					if (result == ALLUSED) {
						//all points are used
						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();

						trapA->left = line.start;
						trapA->right = line.end;
						trapA->top = t->top;
						trapA->bottom = line;
						trapB->left = line.start;
						trapB->right = line.end;
						trapB->top = line;
						trapB->bottom = t->bottom;

						bool startOnTop = PointOnLineSegment(line.start, t->top);
						bool startOnBottom = PointOnLineSegment(line.start, t->bottom);
						bool endOnTop = PointOnLineSegment(line.end, t->top);
						bool endOnBottom = PointOnLineSegment(line.end, t->bottom);

						if (startOnBottom && endOnTop) { //case 1
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						else if (startOnTop && endOnBottom) { //case 2
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
						}

						else if (startOnTop) { //case 3
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						else if (startOnBottom) { //case 4
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						else if (endOnTop) { // case 5
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						else if (endOnBottom) { // case 6
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
						}

						else { // case 7
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						// add traps to list
						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);

						TrapezoidSearchGraphNode* Node = t->graphState;
						Node->type = TrapezoidSearchGraphNode::TSG_YNODE;
						Node->line = line;

						TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						left->trapezoid = trapA;
						trapA->graphState = left;
						Node->left = left;

						TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						right->trapezoid = trapB;
						trapB->graphState = right;
						Node->right = right;
					}
					if (result == STARTUSED) {
						//start point used only
						Trapezoid* trapA = Memory()->alloc<Trapezoid>();
						Trapezoid* trapB = Memory()->alloc<Trapezoid>();
						Trapezoid* trapC = Memory()->alloc<Trapezoid>();
						trapA->left = line.end;
						trapA->right = t->right;
						trapA->top = t->top;
						trapA->bottom = t->bottom;
						trapB->left = line.start;
						trapB->right = line.end;
						trapB->top = t->top;
						trapB->bottom = line;
						trapC->left = line.start;
						trapC->right = line.end;
						trapC->top = line;
						trapC->bottom = t->bottom;

						trapA->UPPERLEFT = trapB;
						trapA->LOWERLEFT = trapC;
						trapA->UPPERRIGHT = t->UPPERRIGHT;
						trapA->LOWERRIGHT = t->LOWERRIGHT;
						if (trapA->UPPERRIGHT)
							trapA->UPPERRIGHT->UPPERLEFT = trapA;
						if (trapA->LOWERRIGHT)
							trapA->LOWERRIGHT->LOWERLEFT = trapA;

						if (PointOnLineSegment(line.start,
							t->top)) { //case 1
							trapB->UPPERRIGHT = trapA;
							trapC->LOWERLEFT = t->LOWERLEFT;
							trapC->LOWERRIGHT = trapA;
							if (trapC->LOWERLEFT)
								trapC->LOWERLEFT->LOWERRIGHT = trapC;
						}

						else if (PointOnLineSegment(line.start,
							t->bottom)) { //case 2
							trapB->UPPERLEFT = t->UPPERLEFT;
							trapB->UPPERRIGHT = trapA;
							if (trapB->UPPERLEFT)
								trapB->UPPERLEFT->UPPERRIGHT = trapB;
							trapC->LOWERRIGHT = trapA;
						}

						else { //case 3
							trapB->UPPERRIGHT = trapA;
							trapB->UPPERLEFT = t->UPPERLEFT;
							if (trapB->UPPERLEFT)
								trapB->UPPERLEFT->UPPERRIGHT = trapB;
							trapC->LOWERRIGHT = trapA;
							trapC->LOWERLEFT = t->LOWERLEFT;
							if (trapC->LOWERLEFT)
								trapC->LOWERLEFT->LOWERRIGHT = trapC;
						}

						// add traps to list
						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);
						trapezoidalList.push_back(trapC);

						//update search stucture
						TrapezoidSearchGraphNode* A = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						A->trapezoid = trapA;
						trapA->graphState = A;

						TrapezoidSearchGraphNode* B = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						B->trapezoid = trapB;
						trapB->graphState = B;

						TrapezoidSearchGraphNode* C = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						C->trapezoid = trapC;
						trapC->graphState = C;

						TrapezoidSearchGraphNode* state = t->graphState;

						state->type = TrapezoidSearchGraphNode::TSG_XNODE;
						state->point = line.end;
						state->right = A;

						TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
						left->line = line;
						left->left = B;
						left->right = C;

					}
					if (result == ENDUSED) {
						//end point used only
						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();
						Trapezoid* trapC = new Trapezoid();

						trapA->left = t->left;
						trapA->right = line.start;
						trapA->top = t->top;
						trapA->bottom = t->bottom;
						trapB->left = line.start;
						trapB->right = line.end;
						trapB->top = t->top;
						trapB->bottom = line;
						trapC->left = line.start;
						trapC->right = line.end;
						trapC->top = line;
						trapC->bottom = t->bottom;

						trapA->UPPERLEFT = t->UPPERLEFT;
						trapA->LOWERLEFT = t->LOWERLEFT;
						if (trapA->UPPERLEFT)
							trapA->UPPERLEFT->UPPERRIGHT = trapA;
						if (trapA->LOWERLEFT)
							trapA->LOWERLEFT->LOWERRIGHT = trapA;
						trapA->UPPERRIGHT = trapB;
						trapA->LOWERRIGHT = trapC;

						if (PointOnLineSegment(line.end,
							t->top)) { //case 1
							trapB->UPPERLEFT = trapA;
							trapC->LOWERLEFT = trapA;
							trapC->LOWERRIGHT = t->LOWERRIGHT;
							if (trapC->LOWERRIGHT)
								trapC->LOWERRIGHT->LOWERLEFT = trapC;
						}

						else if (PointOnLineSegment(line.end,
							t->bottom)) {//case 2
							trapB->UPPERLEFT = trapA;
							trapB->UPPERRIGHT = t->UPPERRIGHT;
							if (trapB->UPPERRIGHT)
								trapB->UPPERRIGHT->UPPERLEFT = trapB;
							trapC->LOWERLEFT = trapA;
						}

						else { //case 3
							trapB->UPPERLEFT = trapA;
							trapB->UPPERRIGHT = t->UPPERRIGHT;
							if (trapB->UPPERRIGHT)
								trapB->UPPERRIGHT->UPPERLEFT = trapB;
							trapC->LOWERLEFT = trapA;
							trapC->LOWERRIGHT = t->LOWERRIGHT;
							if (trapC->LOWERRIGHT)
								trapC->LOWERRIGHT->LOWERLEFT = trapC;
						}

						// add traps to list
						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);
						trapezoidalList.push_back(trapC);

						//update search stucture
						TrapezoidSearchGraphNode* A = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						A->trapezoid = trapA;
						trapA->graphState = A;

						TrapezoidSearchGraphNode* B = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						B->trapezoid = trapB;
						trapB->graphState = B;

						TrapezoidSearchGraphNode* C = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						C->trapezoid = trapC;
						trapC->graphState = C;

						TrapezoidSearchGraphNode* state = t->graphState;

						state->type = TrapezoidSearchGraphNode::TSG_XNODE;
						state->point = line.start;
						state->left = A;

						TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
						right->line = line;
						right->left = B;
						right->right = C;

					}
					if (result == NONUSED) {
						//all free points

						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();
						Trapezoid* trapC = new Trapezoid();
						Trapezoid* trapD = new Trapezoid();
						trapA->left = t->left;
						trapA->right = line.start;
						trapA->top = t->top;
						trapA->bottom = t->bottom;

						trapB->left = line.end;
						trapB->right = t->right;
						trapB->top = t->top;
						trapB->bottom = t->bottom;

						trapC->left = line.start;
						trapC->right = line.end;
						trapC->top = t->top;
						trapC->bottom = line;

						trapD->left = line.start;
						trapD->right = line.end;
						trapD->top = line;
						trapD->bottom = t->bottom;

						//neighbour linking
						trapA->UPPERLEFT = t->UPPERLEFT;
						trapA->LOWERLEFT = t->LOWERLEFT;
						trapA->UPPERRIGHT = trapC;
						trapA->LOWERRIGHT = trapD;

						if (trapA->UPPERLEFT)
							trapA->UPPERLEFT->UPPERRIGHT = trapA;
						if (trapA->LOWERLEFT)
							trapA->LOWERLEFT->LOWERRIGHT = trapA;
						trapB->UPPERLEFT = trapC;
						trapB->LOWERLEFT = trapD;
						trapB->UPPERRIGHT = t->UPPERRIGHT;
						trapB->LOWERRIGHT = t->LOWERRIGHT;
						if (trapB->UPPERRIGHT)
							trapB->UPPERRIGHT->UPPERLEFT = trapB;
						if (trapB->LOWERRIGHT)
							trapB->LOWERRIGHT->LOWERLEFT = trapB;
						trapC->UPPERLEFT = trapA;
						trapC->UPPERRIGHT = trapB;
						trapD->LOWERLEFT = trapA;
						trapD->LOWERRIGHT = trapB;

						// add traps to list
						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);
						trapezoidalList.push_back(trapC);
						trapezoidalList.push_back(trapD);

						//update search stucture
						TrapezoidSearchGraphNode* A = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						A->trapezoid = trapA;
						trapA->graphState = A;

						TrapezoidSearchGraphNode* B = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						B->trapezoid = trapB;
						trapB->graphState = B;

						TrapezoidSearchGraphNode* C = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						C->trapezoid = trapC;
						trapC->graphState = C;

						TrapezoidSearchGraphNode* D = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						D->trapezoid = trapD;
						trapD->graphState = D;

						TrapezoidSearchGraphNode* state = t->graphState;

						state->type = TrapezoidSearchGraphNode::TSG_XNODE;
						state->point = line.start;
						state->left = A;

						TrapezoidSearchGraphNode* _right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_XNODE);
						_right->point = line.end;
						state->right = _right;
						_right->right = B;

						TrapezoidSearchGraphNode* _left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
						_left->line = line;
						_left->left = C;
						_left->right = D;
						_right->left = _left;
					}
					interceptTraps.pop();
					trapezoidalList.remove(t);
					delete t;
				}
				else { //more then 1 intersection
					Trapezoid* t = interceptTraps.front();
					Trapezoid* _previousb = t;
					Trapezoid* _previoust = t;

					if (result.test(STARTPOSITION)) {

						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();

						trapA->left = line.start;
						trapA->right = t->right;
						trapA->top = t->top;
						trapA->bottom = line;
						trapB->left = line.start;
						trapB->right = t->right;
						trapB->top = line;
						trapB->bottom = t->bottom;
						//add trapA and trapB to "trapezoidalList"

						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);

						//for later use
						_previoust = trapA;
						//Save the previous top trapezoid pointer (trapA) from the trapezoidalList.
						_previousb = trapB;
						//Save the previous bottom trapezoid pointer (trapB) from the trapezoidalList.

						//if the rightPoint of the original trapezoid is above
						//the new line segment
						if (t->right.y > line.end.y) {
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
						}

						else {
							//the rightPoint of the original trapezoid is below
							//the new line segment
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;
						}

						//replace search structure
						TrapezoidSearchGraphNode* Node = t->graphState;
						Node->type = TrapezoidSearchGraphNode::TSG_YNODE;
						Node->line = line;

						TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						left->trapezoid = trapA;
						trapA->graphState = left;
						Node->left = left;

						TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						right->trapezoid = trapB;
						trapB->graphState = right;
						Node->right = right;
					}
					if (!result.test(STARTPOSITION)) {

						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();
						Trapezoid* trapC = new Trapezoid();

						trapA->left = t->left;
						trapA->right = line.start;
						trapA->top = t->top;
						trapA->bottom = t->bottom;
						trapB->left = line.start;
						trapB->right = t->right;
						trapB->top = t->top;
						trapB->bottom = line;
						trapC->left = line.start;
						trapC->right = t->right;
						trapC->top = line;
						trapC->bottom = t->bottom;
						//add trapA,trapB and trapC to "trapezoidalList"
						trapezoidalList.push_back(trapA);
						trapezoidalList.push_back(trapB);
						trapezoidalList.push_back(trapC);

						//for later use
						_previoust = trapB;
						//Save the previous top trapezoid pointer (trapB) from the
						//trapezoidalList.
						_previousb = trapC;
						//Save the previous bottom trapezoid pointer (trapC) from
						//the trapezoidalList.

						trapA->UPPERLEFT = t->UPPERLEFT;
						trapA->LOWERLEFT = t->LOWERLEFT;
						if (trapA->UPPERLEFT)
							trapA->UPPERLEFT->UPPERRIGHT = trapA;
						if (trapA->LOWERLEFT)
							trapA->LOWERLEFT->LOWERRIGHT = trapA;
						trapA->UPPERRIGHT = trapB;
						trapA->LOWERRIGHT = trapC;

						//if the rightPoint of the original trapezoid is above
						//the new line segment
						if (t->right.y > line.end.y) {
							trapB->UPPERLEFT = trapA;
							trapB->UPPERRIGHT = t->UPPERRIGHT;
							if (trapB->UPPERRIGHT)
								trapB->UPPERRIGHT->UPPERLEFT = trapB;
							trapC->LOWERLEFT = trapA;
						}

						else {
							//the rightPoint of the original trapezoid is below
							//the new line segment
							trapB->UPPERLEFT = trapA;
							trapC->LOWERLEFT = trapA;
							trapC->LOWERRIGHT = t->LOWERRIGHT;
							if (trapC->LOWERRIGHT)
								trapC->LOWERRIGHT->LOWERLEFT = trapC;
						}

						//replace search structure
						TrapezoidSearchGraphNode* Node = t->graphState;
						Node->type = TrapezoidSearchGraphNode::TSG_XNODE;
						Node->point = line.start;

						TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						left->trapezoid = trapA;
						trapA->graphState = left;
						Node->left = left;

						TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
						right->line = line;
						Node->right = right;

						TrapezoidSearchGraphNode* right_left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						right_left->trapezoid = trapB;
						trapB->graphState = right_left;
						right->left = right_left;

						TrapezoidSearchGraphNode* right_right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
						right_right->trapezoid = trapC;
						trapB->graphState = right_right;
						right->right = right_right;
					}

					interceptTraps.pop();
					trapezoidalList.remove(t);
					delete t;

					while (interceptTraps.size() > 1) {
						t = interceptTraps.front();
						Trapezoid* trapA = new Trapezoid();
						Trapezoid* trapB = new Trapezoid();

						if (t->left.y > line.end.y) { // is above line segment
							trapA->left = t->left;
							trapA->right = t->right;
							trapA->top = t->top;
							trapA->bottom = line;
							//add trapA to "trapezoidalList・
							trapezoidalList.push_back(trapA);

							delete trapB;

							trapB = _previousb;//previous bottom partition (to be merged)
							trapB->right = t->right;

							trapA->LOWERLEFT = _previoust;
							if (trapA->LOWERLEFT)
								trapA->LOWERLEFT->LOWERRIGHT = trapA;
							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;

							_previoust = trapA;

							//update search structure
							TrapezoidSearchGraphNode* state = t->graphState;

							state->type = TrapezoidSearchGraphNode::TSG_YNODE;
							state->line = line;

							TrapezoidSearchGraphNode* A = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							A->trapezoid = trapA;
							state->left = A;
							trapA->graphState = A;

							state->right = _previousb->graphState;
						}
						else { //is below line segment
							Memory()->dealloc(trapA);
							trapA = _previoust;//previous top partition (to be	linked)
							trapA->right = t->right;
							trapB->left = t->left;
							trapB->right = t->right;
							trapB->top = line;
							trapB->bottom = t->bottom;
							//add trapB to "trapezoidalList"
							trapezoidalList.push_back(trapB);

							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->UPPERLEFT = _previousb;//previous bottom partition
							if (trapB->UPPERLEFT)
								trapB->UPPERLEFT->UPPERRIGHT = trapB;
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;

							_previousb = trapB;

							//update search structure
							TrapezoidSearchGraphNode* state = t->graphState;

							state->type = TrapezoidSearchGraphNode::TSG_YNODE;
							state->line = line;

							TrapezoidSearchGraphNode* B = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							B->trapezoid = trapB;
							state->left = B;
							trapA->graphState = B;

							state->left = _previoust->graphState;
						}

						interceptTraps.pop();
						trapezoidalList.remove(t);
						Memory()->dealloc(t);
					}

					t = interceptTraps.front();
					if (result.test(ENDPOSITION)) {
						//if the leftPoint of the original trapezoid is above
						//the new line segment
						if (t->left.y > line.end.y) {
							Trapezoid* trapA = new Trapezoid();
							Trapezoid* trapB = new Trapezoid();

							trapA->left = t->left;
							trapA->right = t->right;
							trapA->top = t->top;
							trapA->bottom = line;
							//add trapA to "trapezoidalList・
							trapezoidalList.push_back(trapA);

							delete trapB;

							trapB = _previousb;//previous bottom partition.
														   //(to be linked)
							trapB->right = t->right;

							trapA->UPPERLEFT = t->UPPERLEFT;
							if (trapA->UPPERLEFT)
								trapA->UPPERLEFT->UPPERRIGHT = trapA;
							trapA->LOWERLEFT = _previoust;//previous top partition
							if (trapA->LOWERLEFT)
								trapA->LOWERLEFT->LOWERRIGHT = trapA;
							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;

							//replace search structure
							TrapezoidSearchGraphNode* Node = t->graphState;
							Node->type = TrapezoidSearchGraphNode::TSG_YNODE;
							Node->line = line;
							Node->right = _previousb->graphState;

							TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							left->trapezoid = trapA;
							trapA->graphState = left;

							Node->left = left;
						}
						else { //if the leftPoint of the original trapezoid is below
							 //the new line segment
							Trapezoid* trapB = Memory()->alloc<Trapezoid>();

							Trapezoid* trapA = _previoust; //previous top partition. (to be linked)
							trapA->right = t->right;
							trapB->left = t->left;
							trapB->right = t->right;
							trapB->top = line;
							trapB->bottom = t->bottom;
							//add trapB to "trapezoidalList"
							trapezoidalList.push_back(trapB);

							trapA->UPPERRIGHT = t->UPPERRIGHT;
							if (trapA->UPPERRIGHT)
								trapA->UPPERRIGHT->UPPERLEFT = trapA;
							trapB->UPPERLEFT = _previousb;//previous bottom
																		//partition
							trapB->LOWERLEFT = t->LOWERLEFT;
							if (trapB->UPPERLEFT)
								trapB->UPPERLEFT->UPPERRIGHT = trapB;
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->LOWERRIGHT = t->LOWERRIGHT;
							if (trapB->LOWERRIGHT)
								trapB->LOWERRIGHT->LOWERLEFT = trapB;

							//replace search structure
							TrapezoidSearchGraphNode* Node = t->graphState;
							Node->type = TrapezoidSearchGraphNode::TSG_YNODE;
							Node->line = line;
							Node->left = _previoust->graphState;

							TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							right->trapezoid = trapB;
							trapB->graphState = right;

							Node->right = right;
						}
					}

					if (!result.test(ENDPOSITION)) {
						Trapezoid* trapA = new Trapezoid();
						trapA->left = line.end;
						trapA->right = t->right;
						trapA->top = t->top;
						trapA->bottom = t->bottom;
						//add trapA to "trapezoidalList"
						trapezoidalList.push_back(trapA);

						trapA->UPPERRIGHT = t->UPPERRIGHT;
						trapA->LOWERRIGHT = t->LOWERRIGHT;
						if (trapA->UPPERRIGHT)
							trapA->UPPERRIGHT->UPPERLEFT = trapA;
						if (trapA->LOWERRIGHT)
							trapA->LOWERRIGHT->LOWERLEFT = trapA;

						if (t->left.y > line.end.y) {
							//above
							Trapezoid* trapB = Memory()->alloc<Trapezoid>();
							trapB->left = t->left;
							trapB->right = line.end;
							trapB->top = t->top;
							trapB->bottom = line;
							//add trapB to "trapezoidalList"
							trapezoidalList.push_back(trapB);

							Trapezoid* trapC = _previousb; //previous bottom partition.
							//(to be linked)
							trapC->right = line.end;

							trapA->UPPERLEFT = trapB;
							trapA->LOWERLEFT = trapC;
							trapB->UPPERLEFT = t->UPPERLEFT;
							if (trapB->UPPERLEFT)
								trapB->UPPERLEFT->UPPERRIGHT = trapB;
							trapB->LOWERLEFT = _previoust;//previous top partition
							if (trapB->LOWERLEFT)
								trapB->LOWERLEFT->LOWERRIGHT = trapB;
							trapB->UPPERRIGHT = trapA;
							trapC->LOWERRIGHT = trapA;

							//replace search structure
							TrapezoidSearchGraphNode* leaf = t->graphState;
							leaf->type = TrapezoidSearchGraphNode::TSG_XNODE;
							leaf->point = line.end;

							TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							right->trapezoid = trapA;
							trapA->graphState = right;
							leaf->right = right;

							TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
							left->line = line;

							TrapezoidSearchGraphNode* left_left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							left_left->trapezoid = trapB;
							trapB->graphState = left_left;
							left->left = left_left;
							left->right = _previousb->graphState;
						}
						else {
							//bellow
							Trapezoid* trapB = _previoust;//previous top partition. (to be
							//linked)
							trapB->right = line.end;
							Trapezoid* trapC = new Trapezoid();
							trapC->left = t->left;
							trapC->right = line.end;
							trapC->top = line;
							trapC->bottom = t->bottom;
							//add trapC to "trapezoidalList"
							trapezoidalList.push_back(trapC);

							trapA->UPPERLEFT = trapB;
							trapA->LOWERLEFT = trapC;
							trapB->UPPERRIGHT = trapA;
							trapC->UPPERLEFT = _previousb; //previous bottom partition
							if (trapC->UPPERLEFT)
								trapC->UPPERLEFT->UPPERRIGHT = trapC;
							trapC->LOWERRIGHT = trapA;
							trapC->LOWERLEFT = t->LOWERLEFT;

							//replace search structure
							TrapezoidSearchGraphNode* leaf = t->graphState;
							leaf->type = TrapezoidSearchGraphNode::TSG_XNODE;
							leaf->point = line.end;

							TrapezoidSearchGraphNode* right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							right->trapezoid = trapA;
							trapA->graphState = right;
							leaf->right = right;

							TrapezoidSearchGraphNode* left = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_YNODE);
							left->line = line;

							TrapezoidSearchGraphNode* left_right = GenerateTSGNode(TrapezoidSearchGraphNode::TSG_LEAF);
							left_right->trapezoid = trapC;
							trapC->graphState = left_right;
							left->right = left_right;
							left->right = _previoust->graphState;
						}
					}
					interceptTraps.pop();
					trapezoidalList.remove(t);
					Memory()->dealloc(t);
				}
			}
		}
	});
}

void Navigation::RemoveUnusedTrapezoids() {
	for (auto& trap : trapezoidalList) {
		if (trap->top.normal.y > 0 && trap->bottom.normal.y < 0) {
			//solid trap
			unusedTrapezoidalList.push_back(trap);
		}
	}
	for (auto& trap : unusedTrapezoidalList) {
		trapezoidalList.remove(trap);
		trap->UPPERLEFT = trap->LOWERLEFT = trap->UPPERRIGHT = trap->LOWERRIGHT = nullptr;
		trap->graphState = nullptr;
	}
}

void Navigation::AdjustRemainingTrapezoids() {
	//Adjust the end points of all of the trapezoid's top-bottom line segments.	
	for (auto& tr : trapezoidalList) {
		float starty, endy, topslope;
		//set the end-points of the top segment
		topslope = (tr->top.end.y - tr->top.start.y) / (tr->top.end.x - tr->top.start.x);//different x(s)
		starty = topslope * (tr->left.x - tr->top.start.x) + tr->top.start.y;
		endy = topslope * (tr->right.x - tr->top.start.x) + tr->top.start.y;

		tr->top.start.x = tr->left.x;
		tr->top.start.y = starty;
		tr->top.end.x = tr->right.x;
		tr->top.end.y = endy;

		//set the end-points of the bottom segment
		topslope = (tr->bottom.end.y - tr->bottom.start.y) / (tr->bottom.end.x - tr->bottom.start.x);//different x(s)
		starty = topslope * (tr->left.x - tr->bottom.start.x) + tr->bottom.start.y;
		endy = topslope * (tr->right.x - tr->bottom.start.x) + tr->bottom.start.y;

		tr->bottom.start.x = tr->left.x;
		tr->bottom.start.y = starty;
		tr->bottom.end.x = tr->right.x;
		tr->bottom.end.y = endy;
	}
}

std::list<Trapezoid*> Navigation::GetTrapezoids() const {
	return trapezoidalList;
}

void Navigation::GenerateNavMesh(NavMeshBoundVolume * bounds)
{
	// generate first trapezoid which is the bounding box
	std::vector<Collider2D*>& obj = GetCollision()->GetCollisionObjects();
	std::vector<size_t> bounded;
	for (Collider2D* col : obj) {
		// hack to include all objects
		// should check if object is bounded
		Line2D line;
		line.start = col->rect.BottomLeft();
		line.end = col->rect.BottomRight();
		segmentList.push_back(line);
		line.start = col->rect.BottomRight();
		line.end = col->rect.TopRight();
		segmentList.push_back(line);
		line.start = col->rect.TopRight();
		line.end = col->rect.TopLeft();
		segmentList.push_back(line);
		line.start = col->rect.TopLeft();
		line.end = col->rect.BottomLeft();
		segmentList.push_back(line);
	}

	// create first trapezoid from navmeshboundvolume
	Trapezoid* boundingVol = Memory()->alloc<Trapezoid>();
	boundingVol->left = bounds->transform->position;
	boundingVol->right = Vector2(boundingVol->left.x + bounds->GetWidth(), boundingVol->left.y + bounds->GetHeight());
	boundingVol->top.start = Vector2(boundingVol->left.x, boundingVol->right.y);
	boundingVol->top.end = Vector2(boundingVol->right);
	boundingVol->bottom.start = Vector2(boundingVol->left);
	boundingVol->bottom.end = Vector2(boundingVol->right.x, boundingVol->left.y);

	for (auto& it : boundingVol->_neighbour) {
		it = nullptr;
	}

	boundingVol->top.normal = Vector2(-(boundingVol->top.end.y - boundingVol->top.start.y), boundingVol->top.end.x - boundingVol->top.start.x);
	float dominator = sqrt((boundingVol->top.normal.x * boundingVol->top.normal.x) + (boundingVol->top.normal.y * boundingVol->top.normal.y));
	boundingVol->top.normal.x = boundingVol->top.normal.x / dominator;
	boundingVol->top.normal.y = boundingVol->top.normal.y / dominator;

	boundingVol->bottom.normal = Vector2(-(boundingVol->bottom.end.y - boundingVol->bottom.start.y), boundingVol->bottom.end.x - boundingVol->bottom.start.x);
	dominator = sqrt((boundingVol->bottom.normal.x * boundingVol->bottom.normal.x) + (boundingVol->bottom.normal.y * boundingVol->bottom.normal.y));
	boundingVol->bottom.normal.x = boundingVol->bottom.normal.x / dominator;
	boundingVol->bottom.normal.y = boundingVol->bottom.normal.y / dominator;
}

