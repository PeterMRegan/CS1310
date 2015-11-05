class Pickable
{
	public :
		bool pick(Actor *owner, Actor *wearer);
		virtual bool use(Actor *owner, Actor *wearer);
		void drop(Actor *owner, Actor *wearer);
};
