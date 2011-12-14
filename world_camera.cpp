
#include <math.h>
#include "world_camera.h"
#include "global.h"

WorldCamera::WorldCamera(WindowFramework* window){
    mCamera = window->get_camera_group();
}

void WorldCamera::seeAll(Grid& grid){
    float centerX = grid.mWidth * CASE_RATIO / 2.;
    float centerY = grid.mHeight * CASE_RATIO / 2.;
    float distance = max(centerX, centerY) / tan(0.35) *4/3.; //todo, 0.35 is radians(20) cause 40 is the default fov, 4/3 is the default ratio
    mCamera.set_pos(50.,50., distance);
    mCamera.set_hpr(0,-90.,0);
}
