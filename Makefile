game: main.o
	g++ main.o -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game -std=c++17

main.o: main.cpp Game.h Asteroid.h Rocket.h Bullet.h Start.h End.h Leaderboard.h AsteroidTest.h RocketTest.h BulletTest.h GameObjectTest.h 
	g++ -c main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -std=c++17

clean:
	rm -f game main.o
