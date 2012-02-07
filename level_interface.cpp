#include <sstream>

#include "level_interface.h"
#include "cardMaker.h"
#include "texture.h"
#include "texturePool.h"

LevelInterface::LevelInterface(WindowFramework* window):
m_interface(NodePath("LevelInterface")),
m_lifes(new TextNode("lifes"))
{
	m_interface.reparent_to(window->get_render_2d());
	hide();
	//
	PT(Texture) tex;
	tex = TexturePool::load_texture( "resources/gui/lifes.png"); 
	CardMaker cm("cardMaker");
	cm.set_frame_fullscreen_quad();
	PT(PandaNode) readyCard = cm.generate(); 
	NodePath lifes(readyCard);
	lifes.set_texture( tex ); 
	lifes.reparent_to(m_interface);
	lifes.set_scale(0.1, 0.1, 0.05);
	lifes.set_pos(0.9, 0.8, 0.9);
	//
	m_lifes->set_text_color(0.f, 0.f, 1.f, 1.f);
	m_lifes->set_text("0");
	NodePath lifeText = m_interface.attach_new_node(m_lifes);
	lifeText.set_scale(0.1);
	lifeText.set_pos(0.91, 0.9, 0.875);
}

void LevelInterface::hide()
{
	m_interface.hide();
}

void LevelInterface::show()
{
	m_interface.show();
}

void LevelInterface::set_lifes(int dLifes)
{
    std::ostringstream oss;
    oss << dLifes;
	m_lifes->set_text(oss.str());
}