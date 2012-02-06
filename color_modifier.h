#ifndef COLORMODIFIER_H
#define COLORMODIFIER_H
#include "nodePath.h"
enum Color {RED, GREEN, BLUE, NO_COLOR};

void apply_color(NodePath* node_path, Color color);
void apply_color(NodePath* node_path, float red, float green, float blue, float alpha);
#endif