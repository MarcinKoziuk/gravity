/*
 * client/cmain.cpp
 *
 * Defines the entry point for the client module.
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <Rocket/Core.h>
#include <Rocket/Debugger.h>

#include <gravity/client/options.hpp>
#include <gravity/client/render/renderer.hpp>
#include <gravity/client/bounding_camera.hpp>
#include <gravity/client/ui/rocket_renderer_interface_impl.hpp>
#include <gravity/client/ui/rocket_system_interface_impl.hpp>
#include <gravity/client/ui/rocket_shell_interface_impl.hpp>

#include <gravity/game/math/vec2f.hpp>
#include <gravity/game/entity.hpp>
#include <gravity/game/game.hpp>
#include <gravity/game/logging.hpp>

using namespace Gravity;
using namespace Gravity::Client;
using namespace Gravity::Game;



int main(int argc, char *argv[])
{
	InitializeLogging();
    Options& options = Options::GetInstance();
    options.LoadFromCommandLine(argc, argv);

    GRAVITY_LOG(info, "Client started.");

    sf::ContextSettings settings;
	settings.DepthBits = 0;
	settings.StencilBits = 8;
	settings.AntialiasingLevel = 2;

    sf::RenderWindow window(sf::VideoMode(options.hres, options.vres, options.bitdepth), "Gravity", sf::Style::Default, settings);
    ::Gravity::Game::Game game;
	
    game.Start();
    
	BoundingCamera camera(Vec2f(400, 300), Vec2f());


    // ROCKET

    RocketRendererInterfaceImpl rendererInterface;
    RocketSystemInterfaceImpl systemInterface;
    RocketShellInterfaceImpl shellInterface("../data/gui/");

    rendererInterface.target =  &window;
    rendererInterface.states = (sf::RenderStates *) &sf::RenderStates::Default;

    Rocket::Core::SetFileInterface(&shellInterface);
    Rocket::Core::SetRenderInterface(&rendererInterface);
    Rocket::Core::SetSystemInterface(&systemInterface);

    if(!Rocket::Core::Initialise())
        return 0;

    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");
    Rocket::Core::FontDatabase::LoadFontFace("DejaVuSans-Bold.ttf");
    Rocket::Core::FontDatabase::LoadFontFace("DejaVuSans-BoldOblique.ttf");
    Rocket::Core::FontDatabase::LoadFontFace("DejaVuSans-Oblique.ttf");
    Rocket::Core::FontDatabase::LoadFontFace("DejaVuSans.ttf");

    Rocket::Core::Context *Context = Rocket::Core::CreateContext("default",
        Rocket::Core::Vector2i(window.GetSize().x, window.GetSize().y));
    
    Rocket::Debugger::Initialise(Context);
    
    Rocket::Core::ElementDocument *document = Context->LoadDocument("my.rml");

    if(document)
    {
        document->Show();
        document->RemoveReference();
    };

    // END ROCKET


    //Rocket::Core::ElementDocument* document;

    while(window.IsOpen()) {
    	sf::Event event;
        Entity* ship = game.GetWorld().GetEntities()[0];

		while (window.PollEvent(event)) {
        //window.PollEvent(event);
			if (event.Type == sf::Event::Closed)
				window.Close();

			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Escape))
				return 0;

			if ((event.Type == sf::Event::MouseWheelMoved)) {
				options.renderscale += event.MouseWheel.Delta*.1f;
			}

			if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Keyboard::Space)) {
                Shape* bombShape = Shape::CreateBombShape();
				Entity* bomb = new Entity(game.GetWorld(), *bombShape, ship->GetPos() + Vec2f(1, 1));
                bomb->SetVel(ship->GetVel());
                bomb->SetMass(0.01f);
                game.GetWorld().AddEntity(*bomb);
                
			}
            
            switch(event.Type)
            {
                case sf::Event::Resized:
                    //rendererInterface.Resize();
                    break;
                case sf::Event::MouseMoved:
                    Context->ProcessMouseMove(event.MouseMove.X, event.MouseMove.Y,
                                              systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::MouseButtonPressed:
                    Context->ProcessMouseButtonDown(event.MouseButton.Button,
                            systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::MouseButtonReleased:
                    Context->ProcessMouseButtonUp(event.MouseButton.Button,
                            systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::MouseWheelMoved:
                    Context->ProcessMouseWheel(event.MouseWheel.Delta,
                                               systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::TextEntered:
                    if (event.Text.Unicode > 32)
                        Context->ProcessTextInput(event.Text.Unicode);
                    break;
                case sf::Event::KeyPressed:
                    Context->ProcessKeyDown(systemInterface.TranslateKey(event.Key.Code),
                                            systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::KeyReleased:
                    if(event.Key.Code == sf::Keyboard::F8)
                    {
                        Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
                    };

                    Context->ProcessKeyUp(systemInterface.TranslateKey(event.Key.Code),
                                          systemInterface.GetKeyModifiers(&window));
                    break;
                case sf::Event::Closed:
                    return 1;
                    break;
            };
		}       
        
        int rotate = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right) - sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
		bool forward = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);



		sf::View nView(Vec2f(options.hres, options.vres), Vec2f(options.hres, options.vres));
		camera.Update(ship->GetPos() * options.renderscale);
		nView.Move(camera.GetPos() - Vec2f(options.hres, options.vres));

        ship->Rotate(rotate*2);
		if (forward)
			ship->ApplyForce(Vec2f(0.f, 2.f).Rotate(ship->GetAngle()));

        window.Clear();
        window.SetView(nView);
        DrawWorld(window, game.GetWorld(), 0.f);

        sf::View viewEmpty = window.GetDefaultView();
        window.SetView(viewEmpty);
        Context->Update();
        Context->Render();
        window.SetFramerateLimit(60);
        window.Display();

        
        game.Step();

    }

    game.Stop();
    return 0;
}
