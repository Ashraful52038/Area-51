#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;

vector < pair<double, double>>bullet;
vector < pair<double, double>>bullet2;


int main()
{
	int HealthTank1 = 100, HealthTank2 = 100;
	bool collisionOccurred1 = false;
	bool collisionOccurred2 = false;


	sf::RenderWindow window(sf::VideoMode(1000, 600), "Area-51");
	
	
	
	
	sf::Texture backgroundtexture;                  //Background

	if (!backgroundtexture.loadFromFile("wA.jpg"))
	{
		cout << "Background loading error!\n";
	}
	sf::Sprite backgroundsprite(backgroundtexture);



	sf::Texture maintexture;                        //Maincharacter1
	if (!maintexture.loadFromFile("bmw420.png"))
	{
		cout << "Main loading error!\n";
	}
	sf::Sprite mainsprite(maintexture);
	mainsprite.setPosition(sf::Vector2f(480, 480));
    

	sf::Texture tanktexture;                        //Maincharacter2
	if (!tanktexture.loadFromFile("tank.png"))
	{
		cout << "Jet loading error!\n";
	}
	sf::Sprite tanksprite(tanktexture);
	tanksprite.setPosition(sf::Vector2f(480, 20));


	sf::Texture bullettexture;                        //bullet
	if (!bullettexture.loadFromFile("bullet.png"))
	{
		cout << "Bullet loading error!\n";
	}
	sf::Sprite bulletsprite(bullettexture);
	
	sf::Texture bullettexture2; 
	                                                           //bullet
	if (!bullettexture2.loadFromFile("bullet.png"))
	{
		cout << "Bullet2 loading error!\n";
	}
	sf::Sprite bulletsprite2(bullettexture2);
	



	sf::SoundBuffer bulletsoundbuffer;                 //bullet sound
	if (!bulletsoundbuffer.loadFromFile("Tanks.bin"))
	{
		cout << "Tanks sound load error" << endl;
	}
	sf::Sound bulletsound;
	bulletsound.setBuffer(bulletsoundbuffer);
	                                     //Background Sound
	sf::SoundBuffer bgmsoundbuffer;                 
	if (!bgmsoundbuffer.loadFromFile("bgm.wav"))
	{
		cout << "bgm sound load error" << endl;
	}
	sf::Sound bgmsound;
	bgmsound.setBuffer(bgmsoundbuffer);


	bgmsound.play();
	bgmsound.setLoop(true);
	bgmsound.setVolume(50);

	

	while (window.isOpen())
	{
		//eventloop

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				cout << "Space key  has been released!" << endl;    //bullet relase
				bulletsound.play();
				bullet.push_back(make_pair(mainsprite.getPosition().x-5, mainsprite.getPosition().y));
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F)
			{
				cout << "X key  has been released!" << endl;    //bullet2 relase
				bulletsound.play();
				bullet2.push_back(make_pair(tanksprite.getPosition().x+2, tanksprite.getPosition().y-20));
			}
		}


		


			//MOVE
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cout << "Left has been pressed" << endl;
				if (mainsprite.getPosition().x > -10)
					
				mainsprite.move(sf::Vector2f(-1, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				cout << "Right has been pressed" << endl;
				if (mainsprite.getPosition().x < 920)
					mainsprite.move(sf::Vector2f(1, 0));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				cout << "Up has been pressed" << endl;
				if (mainsprite.getPosition().y > -10)
					mainsprite.move(sf::Vector2f(0, -1));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				cout << "Down has been pressed" << endl;
				if (mainsprite.getPosition().y < 450)
					mainsprite.move(sf::Vector2f(0, 1));
			}
		


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  //movetank//left
		{
			cout << "A has been pressed" << endl;
			if (tanksprite.getPosition().x > -10)
				tanksprite.move(sf::Vector2f(-1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  //right
		{
			cout << "D has been pressed" << endl;
			if (tanksprite.getPosition().x < 920)
				tanksprite.move(sf::Vector2f(1, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  //up
		{
			cout << "W has been pressed" << endl;
			if (tanksprite.getPosition().y > -10)
				tanksprite.move(sf::Vector2f(0, -1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  //down
		{
			cout << "S has been pressed" << endl;
			if (tanksprite.getPosition().y < 450)
				tanksprite.move(sf::Vector2f(0, 1));
		}

		//Collision & Health Decreasing//
	   //tank1 is fired

		if (mainsprite.getGlobalBounds().intersects(bulletsprite2.getGlobalBounds()))
		{
			if (!collisionOccurred1) // check if collision has already occurred
			{
				cout << "Main is fired" << endl;
				HealthTank1 -= 20;
				cout << "Health1 " << HealthTank1 << endl;
				//if (HealthTank1 <= 0) cout << Main is destroyed   Tank is win << endl;
				collisionOccurred1 = true; // set collision flag to true
			}
		}
		else
		{
			collisionOccurred1 = false; // reset collision flag if no collision occurred
		}


		//tank2 is fired

		if (tanksprite.getGlobalBounds().intersects(bulletsprite.getGlobalBounds()))
		{
			if (!collisionOccurred2) // check if collision has already occurred
			{
				cout << "Tank is fired" << endl;
				HealthTank2 -= 20;
				cout << "Health2 " << HealthTank2 << endl;
				//if (HealthTank2 <= 0) cout << Tank is destroyed    Main is win << endl;
				collisionOccurred2 = true; // set collision flag to true
			}
		}
		else
		{
			collisionOccurred2 = false;
		}



		window.clear();

		window.draw(backgroundsprite);
		window.draw(mainsprite);
		window.draw(tanksprite);
		//tank1 life draw
		if (HealthTank1 > 0) {
			sf::RectangleShape healthBar(sf::Vector2f(HealthTank1, 10));

			if (HealthTank1 >= 60)
				healthBar.setFillColor(sf::Color::Green);
			if (HealthTank1 >= 40 && HealthTank1 < 60)
				healthBar.setFillColor(sf::Color::Blue);
			if (HealthTank1 > 0 && HealthTank1 < 40)
				healthBar.setFillColor(sf::Color::Red);
			healthBar.setPosition(mainsprite.getPosition().x, mainsprite.getPosition().y - 10);
			window.draw(healthBar);
		}
		//Tank2 life draw

		if (HealthTank2 > 0) {
			sf::RectangleShape healthBar2(sf::Vector2f(HealthTank2, 10));

			if (HealthTank2 >= 60)
				healthBar2.setFillColor(sf::Color::Green);
			if (HealthTank2 >= 40 && HealthTank2 < 60)
				healthBar2.setFillColor(sf::Color::Blue);
			if (HealthTank2 > 0 && HealthTank2 < 40)
				healthBar2.setFillColor(sf::Color::Red);
			healthBar2.setPosition(tanksprite.getPosition().x, tanksprite.getPosition().y - 10);
			window.draw(healthBar2);
		}
		

		if (!bullet.empty())         //bullet1(down)
		{

			for (int i = 0; i < bullet.size(); i++)
			{
				bullet[i].second -= 0.5;

				if (bullet[i].second <= -10)
				{
					continue;
				}
				bulletsprite.setPosition(sf::Vector2f(bullet[i].first+35, bullet[i].second));

				bulletsprite.move(sf::Vector2f(0, -2));

				window.draw(bulletsprite);
			}
		}

		if (!bullet2.empty())       //bullet2(up)
		{

			for (int i = 0; i < bullet2.size(); i++)
			{
				bullet2[i].second += 0.5;

				if (bullet2[i].second <= -10)
				{
					continue;
				}
				bulletsprite2.setPosition(sf::Vector2f(bullet2[i].first+40 , bullet2[i].second+100));
				
				bulletsprite2.move(sf::Vector2f(0, 2));

				window.draw(bulletsprite2);
			}
		}

		window.display();

	}
		
	



	return 0;

}