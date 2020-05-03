#include "waepon.h"

Waepon::Waepon(float x, float y, int range, int damage)
	: m_range(range)
	, m_damage(damage)
	, m_x(x)
	, m_y(y)
{

}

Bow::Bow(float x, float y, int range = 200, int damage = 25)
	:Waepon(x , y, range, damage)

{

}

Bow::Bow()
	: Waepon(0,0,0,0)
{
	
}

Sword::Sword(float x, float y, int range = 30, int damage = 25)
	: Waepon(x, y, range, damage)
{

}

Sword::Sword()
	: Waepon(0, 0,0,0)
{

}