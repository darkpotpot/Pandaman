#include "heightfield_displayer.h"
#include "cell.h"
#include "lpoint3.h"
#include "texturePool.h"
#include "global.h"
#include "drawing_helpers.h"

extern int CASE_RATIO;

HeightfieldDisplayer::HeightfieldDisplayer(Grid* grid, NodePath* parentNode):mTerrain(GeoMipTerrain("terrain")){
    mParentNode = parentNode;
    mTerrain.set_heightfield(Filename("resources/map/map.png"));
    mTerrain.set_bruteforce(true);
    mTerrain.generate();
    NodePath terrainRoot = mTerrain.get_root();
    scale_at_size(grid->getWidth() * CASE_RATIO, grid->getHeight() * CASE_RATIO, &terrainRoot);
    PT(TextureStage) groundTextureStage = new TextureStage("ts");
    PT(Texture) groundTexture = TexturePool::load_texture("resources/map/map_grass.jpg");
    terrainRoot.set_tex_scale(groundTextureStage->get_default(), grid->getWidth(), grid->getHeight());
    terrainRoot.set_texture(groundTexture, 1); 
    terrainRoot.reparent_to(*mParentNode);
}
