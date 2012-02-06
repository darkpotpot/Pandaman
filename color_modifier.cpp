#include "color_modifier.h"

void apply_color(NodePath* node_path, Color color)
{
    switch(color)
    {
    case RED:
        apply_color(node_path, 1.,0.5,0.5,1.);
        break;
    case GREEN:
        apply_color(node_path, 0.5,1.,0.5,1.);
        break;
    case BLUE:
        apply_color(node_path, 0.5,0.5,1.0,1.);
        break;
    case NO_COLOR:
        node_path->clear_color();
        node_path->clear_color_scale();
        break;

    }
}

void apply_color(NodePath* node_path, float red, float green, float blue, float alpha)
{
node_path->set_color_scale( red,  green,  blue,  alpha);
}