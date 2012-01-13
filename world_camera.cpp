
#include <math.h>
#include "world_camera.h"
#include "global.h"
#include "camera.h"

int DISTANCE_OFFSET = 100;
float FOLLOW_DISTANCE = 200.f;

void switch_camera(const Event * theEvent, void * data)
{ (static_cast<WorldCamera*>(data))->switchCamera(); }

WorldCamera::WorldCamera(WindowFramework* window, KeyboardManager* km):m_level(NULL){
    mCamera = window->get_camera_group();
	m_CamType = 0;
	m_pKeyboardManager = km;
}

void WorldCamera::displayLevel(Level* level)
{
	m_pKeyboardManager->register_key(SWITCH_CAMERA_KEY, switch_camera, this);
	assert(m_level == NULL);
	m_level = level;
	resetCamera();
}

void WorldCamera::undisplayLevel()
{
	m_pKeyboardManager->unregister_key(SWITCH_CAMERA_KEY);
	assert(m_level != NULL);
	m_level = NULL;
}

void WorldCamera::switchCamera()
{
	m_CamType = (m_CamType + 1) % 2;
	resetCamera();
}

void WorldCamera::resetCamera()
{
	switch (m_CamType){
		case 0:
			seeAll();
			break;
		case 1:
			followDisplayable();
			break;
		default:
			seeAll();
			break;
	}
}

void WorldCamera::seeAll(){
	Grid* grid = m_level->get_grid();
    float centerX = grid->getWidth() * CASE_RATIO / 2.;
    float centerY = grid->getHeight() * CASE_RATIO / 2.;
    float distance = max(centerX, centerY) / tan(0.35) * 4/3.; //todo, 0.35 is radians(20) cause 40 is the default fov, 4/3 is the default ratio
    mCamera.reparent_to(*m_level->get_root_node());
	mCamera.set_pos(centerX, centerY, distance);
    mCamera.set_hpr(0,-90.,0);
    DCAST(Camera, mCamera.get_child(0).node())->get_lens()->set_far(distance + DISTANCE_OFFSET);
}

void WorldCamera::followDisplayable()
{
	EntityDisplayer* character = dynamic_cast<EntityDisplayer*>(m_level->get_character()->getDisplayer());
	mCamera.reparent_to(character->getDrawing());
	mCamera.set_pos(0.f, 0.f, FOLLOW_DISTANCE);
	mCamera.set_hpr(0,-90.,0);
	DCAST(Camera, mCamera.get_child(0).node())->get_lens()->set_far(FOLLOW_DISTANCE + DISTANCE_OFFSET);
	mCamera.set_compass(*m_level->get_root_node());
}