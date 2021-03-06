#pragma once
#include "specs.h"

namespace pla
{
	class KSpecs final : public cmm::Specs// Knight Specs
	{
	public:
		float hp;
		float mp;
		float armour;
		float mresistant;
		float velocity;
		float hvelocity;	// half velocity
		float gravity;
		float damage;
		float mdamage;
		float luck;
		float experience;
		int level;

		// other
		float scale;

		KSpecs();
		~KSpecs();
	private:
		void free();
	public:
		void prepare();
		void set(int i, int value);
	};
}