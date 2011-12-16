#include "grid_display.h"
#include "cell.h"
#include "lpoint3.h"
#include "texturePool.h"
#include "global.h"
#include "drawing_helpers.h"

extern int CASE_RATIO;

GridDisplayer::GridDisplayer(NodePath* parentNode){
    mParentNode = parentNode;
    mTerrain = new GeoMipTerrain("mySimpleTerrain");
    mTerrain->set_heightfield(Filename("resources/map/map.png"));
    mTerrain->set_bruteforce(true);
    mTerrain->generate();
}

void GridDisplayer::display_grid(Grid* grid){
    NodePath terrainRoot = mTerrain->get_root();
    terrainRoot.reparent_to(*mParentNode);
    scale_at_size(grid->mWidth * CASE_RATIO, grid->mHeight * CASE_RATIO, &terrainRoot); // 256 is the size of the heightfield
    PT(TextureStage) groundTextureStage = new TextureStage("ts");
    PT(Texture) groundTexture = TexturePool::load_texture("resources/map/map_grass.jpg");
    terrainRoot.set_tex_scale(groundTextureStage->get_default(), CASE_RATIO, CASE_RATIO);
    terrainRoot.set_texture(groundTexture, 1); 
}
