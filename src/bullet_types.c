#include "bullet_types.h"
#include <math.h>
#include <stddef.h>

void normal_bullet_move(bullet* current_bullet, int bullet_damage, float bullet_speed)
{	
	if(current_bullet->target==NULL)
	{
		current_bullet->active=false;
		return;
	}

        float currentX=current_bullet->position.x;
        float currentY=current_bullet->position.y;
        float targetX=current_bullet->target->position.x+current_bullet->target->type.texture.width/2;
        float targetY=current_bullet->target->position.y+current_bullet->target->type.texture.height/2;
        float frame_time=GetFrameTime();
        float speed=bullet_speed*frame_time;

        float directionX = targetX - currentX;
        float directionY = targetY - currentY;

        float distance = sqrt(directionX * directionX + directionY * directionY);
    
        if (distance < speed) 
		{
                current_bullet->active=false;
		current_bullet->target->type.hit_points-=bullet_damage;
        }
        else {
                directionX /= distance;
                directionY /= distance;

                directionX *= speed;
                directionY *= speed;

                current_bullet->position.x += directionX;
                current_bullet->position.y += directionY;

        }


}
void no_bullet_move(bullet* current_bullet, int damage, float speed)
{
	current_bullet->active=false;
}

bullet normal_bullet_get(){
	bullet new_bullet;
	new_bullet.active=true;
	new_bullet.texture=LoadTexture("assets/tower_textures/bullet.png");
	new_bullet.bullet_move=normal_bullet_move;
	return new_bullet;
}

bullet no_bullet_get(){
	bullet new_bullet;
	new_bullet.active=false;
	new_bullet.texture=LoadTexture("assets/tower_textures/bullet.png");
	new_bullet.bullet_move=no_bullet_move;
	return new_bullet;
}

bullet get_bullet(int type)
{
	switch (type)
	{
		case 1:
		return normal_bullet_get();
		break;
		default:
		return no_bullet_get();
		break;

	}

}
