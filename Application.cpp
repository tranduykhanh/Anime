﻿//   Code by Harding Adonis
//   E - mail: hardingadonis@gmail.com

#include "Application.hpp"
#include "StateScreen/Intro.hpp"
#include "StateScreen/GameOver.hpp"

namespace Goku
{
    Application::Application() :
        m_window(sf::VideoMode(SCREEN_WITDH, SCREEN_HEIGHT), L"Thợ Săn Rồng Son Goku", sf::Style::Close)
    {


        this->m_window.setFramerateLimit(60);


        sf::Image Icon;
        Icon.loadFromFile(Path_Texture + "Icon.png");
        this->m_window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());

        State temp = new Intro(&this->m_window);
        this->m_all_state.push(temp);


    }

    Application::~Application()
    {
        
    }


    void Application::run()
    {
        sf::Clock clock;
        sf::Time  timeSinceLastUpdate = sf::Time::Zero;

        while (this->m_window.isOpen())
        {
            this->m_all_state.top()->handleEvent();
            timeSinceLastUpdate += clock.restart();

            this->m_window.clear();

            while (timeSinceLastUpdate > this->m_time_per_second)
            {
                timeSinceLastUpdate -= m_time_per_second;
                this->m_all_state.top()->handleEvent();
                this->m_all_state.top()->update();
            }
            this->m_all_state.top()->draw();

            this->m_window.display();

            if (!this->m_all_state.top()->checkLive() && this->m_all_state.top()->m_type == BaseStateScreeen::Intro)
            {
                this->m_all_state.pop();
                State temp = new GameState(&this->m_window);
                this->m_all_state.push(temp);
            }

            if (!this->m_all_state.top()->checkLive() && this->m_all_state.top()->m_type == BaseStateScreeen::GamePlay)
            {
                this->m_all_state.pop();
                State temp = new GameOver(&this->m_window);
                this->m_all_state.push(temp);
            }
        }
    }
}