class Pickable;

class LightningBolt: public Pickable
{
	public :
		float range,damage;
		LightningBolt(float range, float damage);
		bool use(Actor *owner, Actor *wearer);
};


