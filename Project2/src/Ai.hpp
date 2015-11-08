#ifndef AI_HPP
#define AI_HPP

class Ai : public Persistent
{
	public :
		virtual void update(Actor *owner)=0;
		static Ai *create (TCODZip &zip);

	protected :
		enum AiType
		{
			MONSTER,PLAYER
		};
};

class PlayerAi : public Ai
{
	public :
		void update(Actor *owner);
		void handleActionKey(Actor *owner, int ascii);
		void load(TCODZip &zip);
		void save(TCODZip &zip);

	protected :
		bool moveOrAttack(Actor *owner, int targetx, int targety);
		Actor *choseFromInventory(Actor *owner);
};

class MonsterAi : public Ai
{
	public :
		void update(Actor *owner);
		void load(TCODZip &zip);
		void save(TCODZip &zip);

	protected :
		int moveCount;
		void moveOrAttack(Actor *owner, int targetx, int targety);
};
#endif //ai.hpp
