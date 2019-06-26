

//update position
velocity.x = 0;

if (movingLeft)
velocity.x -= 0.5f;
if (movingRight)
velocity.x += 0.5f;

velocity.y += GRAVITY;

if (pos.y >= 708 && velocity.y > 0) 
{
	velocity.y = 0;
}

pos += velocity;

playerSprite.setPosition(pos);