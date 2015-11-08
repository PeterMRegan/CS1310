#ifndef PICKABLE_HPP
#define PICKABLE_HPP
class Pickable : public Persistent
{
	public :
		bool pick(Actor *owner, Actor *wearer);
		virtual bool use(Actor *owner, Actor *wearer);
		void drop(Actor *owner, Actor *wearer);
		static Pickable *create (TCODZip &zip);

	protected :
		enum PickableType
		{
			HEALER,LIGHTNING_BOLT
		};
};
#endif
