#include "grid_display.h"
#include "cell.h"
#include "lpoint3.h"
#include "texturePool.h"
#include "global.h"

GridDisplayer::GridDisplayer(WindowFramework* window){
    mWindow = window;
    mTerrain = new GeoMipTerrain("mySimpleTerrain");
    mTerrain->set_heightfield(Filename("resources/map/map.png"));
    mTerrain->set_bruteforce(true);
    mTerrain->set_focal_point(mWindow->get_camera_group());
    mTerrain->generate();
}

void GridDisplayer::display_grid(Grid& grid){
    NodePath terrainRoot = mTerrain->get_root();
    terrainRoot.reparent_to(mWindow->get_render()); 
    terrainRoot.set_scale(grid.mWidth * CASE_RATIO / 256., grid.mHeight * CASE_RATIO / 256., 1.); // 256 is the size of the heightfield
    PT(TextureStage) groundTextureStage = new TextureStage("ts");
    PT(Texture) groundTexture = TexturePool::load_texture("resources/map/map_grass.jpg");
    terrainRoot.set_tex_scale(groundTextureStage->get_default(), CASE_RATIO, CASE_RATIO);
    terrainRoot.set_texture(groundTexture, 1); 

}
