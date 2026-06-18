#include "View.h"

View::View(ViewManager* vm, sf::RenderWindow* rw, std::string tileset, const std::vector<std::string>& id_view, const std::vector<std::shared_ptr<View>>& views, unsigned int seed) :m_context{
	.time = 0,
	.dt = 0,
	.offsetX = 0,
	.offsetY = 0,
	.window = rw,
	.rm = std::make_unique<ResourceManager>(tileset),
	.rand = std::make_unique<std::mt19937>(seed),
},m_manager(vm), m_gui(*rw), m_gui_textures(), m_gui_widget(), m_navigator(),m_ordered_id_views(id_view)
{
	for (int i = 0; i < id_view.size(); i++)
		m_navigator[id_view[i]] = views[i];
	int it = -m_navigator.size() / 2;
	for (const auto& [i, ev] : m_navigator)
	{
		m_gui_textures[i + "1"] = sf::Texture("resources/" + i + "1.png");
		m_gui_textures[i + "2"] = sf::Texture("resources/" + i + "2.png");
		m_gui_widget[i] = std::make_shared<tgui::Button>();
		m_gui_widget[i]->getRenderer()->setTexture(m_gui_textures[i + "1"]);
		m_gui_widget[i]->getRenderer()->getTexture().setDefaultSmooth(false);
		m_gui_widget[i]->getRenderer()->setTextureDown(m_gui_textures[i + "2"]);
		m_gui_widget[i]->getRenderer()->getTextureDown().setDefaultSmooth(false);
		m_gui_widget[i]->getRenderer()->setBorderColor(tgui::Color::Transparent);
		m_gui_widget[i]->getRenderer()->setBorders(tgui::Borders());
		m_gui_widget[i]->setPosition(rw->getSize().x / 2, rw->getSize().y / 2 + 100 * it);
		m_gui_widget[i]->setVisible(true);
		m_gui_widget[i]->setSize(117 * 2, 32 * 2);
		m_gui_widget[i]->setOrigin(.5, .5);
		m_gui_widget[i]->onClick([&]
			{
				if (ev)m_manager->changeView(ev);
				else m_manager->backView();
			});
		m_gui.add(m_gui_widget[i]);
		it++;
	}
}

void View::handle(const std::optional<sf::Event>& ev)
{
	if (const auto* resized = ev->getIf<sf::Event::Resized>())
	{
		int it = -m_gui_widget.size() / 2;
		for (auto w : m_ordered_id_views)
		{
			m_gui_widget[w]->setPosition(m_context.window->getSize().x / 2, m_context.window->getSize().y / 2 + 100 * it);
			it++;
		}
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
