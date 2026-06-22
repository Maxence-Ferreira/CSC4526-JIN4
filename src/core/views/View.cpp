#include "View.h"

View::View(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, const std::vector<std::string>& id_view, const std::vector<std::shared_ptr<View>>& views, unsigned int seed) :m_context{
	.time = 0,
	.dt = 0,
	.offsetX = 0,
	.offsetY = 0,
	.mouseX = 0,
	.mouseY = 0,
	.window = rw,
	.rm = std::make_unique<ResourceManager>(tileset),
	.rand = std::make_unique<std::mt19937>(seed),
},m_manager(vm), m_gui(*rw), m_gui_textures(), m_gui_widget(), m_navigator(),m_ordered_id_views(id_view)
{
	int it = -(id_view.size() / 2.f);
	for (int i_ = 0; i_ < id_view.size(); i_++)
	{
		m_navigator[id_view[i_]] = views[i_];
		const auto& i = id_view[i_];
		const auto& ev = m_navigator[i];;
		m_gui_textures[i + "1"] = sf::Texture("resources/" + i + "1.png");
		m_gui_textures[i + "2"] = sf::Texture("resources/" + i + "2.png");
		m_gui_widget[i] = std::make_shared<tgui::Button>();
		m_gui_widget[i]->getRenderer()->setTexture(m_gui_textures[i + "1"]);
		m_gui_widget[i]->getRenderer()->getTexture().setDefaultSmooth(false);
		m_gui_widget[i]->getRenderer()->setTextureDown(m_gui_textures[i + "2"]);
		m_gui_widget[i]->getRenderer()->getTextureDown().setDefaultSmooth(false);
		m_gui_widget[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_gui_widget[i]->getRenderer()->setBorders(tgui::Borders());
		auto ypos = (std::to_string(50 + 10 * it) + "%");
		m_gui_widget[i]->setPosition("50%", ypos.c_str());
		m_gui_widget[i]->setVisible(true);
		sf::Vector2u v = m_gui_textures[i + "1"].getSize();
		m_gui_widget[i]->setSize((float)v.x/v.y*64.f, 64);
		m_gui_widget[i]->setOrigin(.5, .5);
		m_gui_widget[i]->onClick([this,i , &ev]
			{
				if (ev)m_manager->changeView(ev);
				else if(!behavior(i))m_manager->backView();
				m_manager->playSound("resources/click.wav");
			});
		m_gui.add(m_gui_widget[i]);
		it++;
	}	
}

void View::handle(const std::optional<sf::Event>& ev)
{
	if (const auto* resized = ev->getIf<sf::Event::Resized>())
	{
		for (const auto& [_, view] : m_navigator)if (view)view->handle(ev);
	}
	m_gui.handleEvent(*ev);
}

void View::update()
{
}

void View::draw()
{
	m_gui.draw();
}

void View::onEnter()
{
}

void View::onExit()
{
}


View::~View()=default;
