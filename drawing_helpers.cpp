#include "drawing_helpers.h"

void scale_at_size(float sizeX, float sizeY, float sizeZ, NodePath* node){
    LPoint3f min_point, max_point;
    node->set_scale(1.);
    node->calc_tight_bounds(min_point, max_point);
    float scaleX =  sizeX / (max_point.get_x() - min_point.get_x());
    float scaleY =  sizeY / (max_point.get_y() - min_point.get_y());
    float scaleZ =  sizeZ / (max_point.get_z() - min_point.get_z());
    node->set_scale(scaleX, scaleY, scaleZ);
}

void scale_at_size(float sizeX, float sizeY, NodePath* node){
    LPoint3f min_point, max_point;
    node->set_scale(1.);
    node->calc_tight_bounds(min_point, max_point);
    float scaleX =  sizeX / (max_point.get_x() - min_point.get_x());
    float scaleY =  sizeY / (max_point.get_y() - min_point.get_y());
    node->set_scale(scaleX, scaleY, 1.);
}
