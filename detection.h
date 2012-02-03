#ifndef DETECTION_H
#define DETECTION_H
#include "grid.h"
#include "point2d.h"

void get_panda_pos_ifp(Grid* grid, int x, int y, bool& panda_detected, int& panda_x, int& panda_y, int dist);
void get_traversed_cases(int x1,int y1,int x2, int y2, list<Point2d>& traversed_cases);
void display_traversed_cases(int x1,int y1,int x2, int y2);
#endif