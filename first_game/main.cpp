#include <iostream>
#include "Game.h"

int main()
{


    // init srand
    std::srand(static_cast<unsigned>(time(NULL)));
    // window initializations
    Game game;




    // Game Loop
    while (game.running() && !game.getEndGame()) {

        // Update
        game.update();
        // Render
        game.render();

    }


    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);



    //// game loop
    //while (window.isOpen())
    //{

    //    
    // 

    //    // Event Polling
    //    while (window.pollEvent(event))
    //    {

    //        switch (event.type) {
    //        case sf::Event::Closed:
    //            window.close();
    //            break;

    //        case sf::Event::KeyPressed:
    //            if (event.key.code == sf::Keyboard::Escape) {
    //                shape.setFillColor(sf::Color::Red);

    //            }
    //            break;

    //        }
    //      
    //    }

    //    // Update

    //    // Render

    //    window.clear(); // Clear old frame

    //    // Draw game
    //    window.draw(shape); 

    //    window.display(); // Tell app window is done drawing and ready to render new frame
    //}


    return 0;
}