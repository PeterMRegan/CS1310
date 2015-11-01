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
		Actor *player;
		Map *map;
		int screenWidth;
		int screenHeight;
		TCOD_key_t lastKey;

		Engine(int screenWidth, int screenHeight);
		~Engine();
		void sendToBack(Actor *actor);
		void update();
		void render();

	private :
		bool computeFov;
};

extern Engine engine;
