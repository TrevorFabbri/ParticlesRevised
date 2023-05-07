#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Default);
	srand(time(0));
}


void Engine::run()
{
	// Timing 	
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		float dtAsSeconds = dt.asSeconds();
		input();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}
		}

		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{		
			// Create a loop to construct 5 particles
			for (int i = 0; i < 5; i++)
			{
				int numPoints = rand() % (50 - 25 + 1) + 25;
				Vector2i temp;
				temp.x = event.mouseButton.x;
				temp.y = event.mouseButton.y;
				Particle P(m_Window, numPoints, temp);
				m_particles.push_back(P);
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for(int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles.at(i).getTTL() > 0.0)
		{
			m_particles.at(i).update(dtAsSeconds);
		}
		else
		{
			m_particles.erase(m_particles.begin());
		}
	}
}

void Engine::draw()
{

	m_Window.clear();

	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();
}