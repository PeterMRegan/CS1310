#ifndef ENGINE_HPP
#define ENGINE_HPP
class Engine
{
	public :
		enum GameStatus
		{
			STARTUP,
			IDLE,
			NEW_TURN,
			VICTORY,
			DEFEAT
		} gameStatus;
		int fovRadius;
		TCODList<Actor *> actors;
		TCODList<Actor *> monsters;
		Actor *player;
		Actor *stairs;
		Map *map;
		int screenWidth;
		int screenHeight;
		int level;
		Gui *topGui;
		Gui *botGui;
		TCOD_key_t lastKey;

		Engine(int screenWidth, int screenHeight);
		~Engine();
		void sendToBack(Actor *actor);
		void update();
		void render();
		void nextLevel();
		Actor *getClosestMonster(int x, int y, float range) const;

		void init();
		void load();
		void save();

	private :
		bool computeFov;
};

extern Engine engine;
#endif //engine.hpp
