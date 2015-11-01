class Gui
{
	public :
		int yOffset;
		Gui(int yOffset);
		~Gui();
		void render();
		void message(const TCODColor &col, const char *text, ...);

	protected :
		TCODConsole *con;
		struct Message
		{
			char *text;
			TCODColor col;
			Message(const char *text, const TCODColor &col);
			~Message();
		};
		TCODList<Message *> log;
};
