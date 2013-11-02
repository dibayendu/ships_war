// This is where I am putting the calculateObjectPosition method where the ship can move lean forward and backword.

/*
 * Calculates the motion of the ship.
 */
void calculateObjectPosition()
{
	float radians = rotateShip.rotY*PI/RADIANCONSTANT;
	float zPos = sinf(radians) * speed;
	float xPos = cosf(radians) * speed;
	translateShip.posX += xPos * time.calculatedTime;
	// time.elapsedTime/time.timeDivisor;	
	translateShip.posZ -= zPos * time.calculatedTime;
	translateShip.posY = getYAxisValue(translateShip.posX, translateShip.posZ);
	//float dx = 0.0 - translateShip.posX;
	//float dy = 0.0 - translateShip.posY;
	//float degree = atan2(dy,dx) * 180.0 / PI;
	//rotateShip.rotY = degree;
	
	
	float x1 = translateShip.posX;
	float y1 = translateShip.posY;
	
	float normalX = getNormalAxisValue(x1, translateShip.posZ);
	float normalY = normal.normalY;
	float normalZ = getNormalAxisValue(translateShip.posZ, x1);
	float unitLength = getLength(normalX, normalY, normalZ);
	
	// Divides the axis by unit length
	normalX /=unitLength; normalY /=unitLength; normalZ /=unitLength;
	
	// Calculating the x,y,z co-ordinates of the normal
	float distance = getLength((normalX-x1), (normalY-y1), (normalZ-translateShip.posZ));
	float normalLength = normal.normalLength;
	float n = normal.normalLength;
	float m = distance - n;
	
	//Dividing in the ration m:n
	float newX = ((normalX * n) + (x1 * m)) / (m+n);
	float newY = ((normalY * n) + (y1 * m)) / (m+n);
	float newZ= ((normalZ * n) + (translateShip.posZ * m)) / (m+n);
	
	
	
	
	float x2 = newX;
	float y2 = newY;
	
	float xa = (x2-x1)*100;
	float ya = (y2-y1)*100;
	
	float x3 = x1;
	float y3 = y1+0.1f;
	
	float xb = (x3-x1)*100;
	float yb = (y3-y1)*100;
	
	float angle = acos((xa*xb + ya*yb)/ (sqrt(xa*xa + ya*ya) * sqrt(xb*xb + yb*yb)))*180.0/PI;
	rotateShip.rotZ = angle;
	
	printf("[xa = %f] [ya = %f] [xb = %f] [yb = %f] [angle = %f]\n", xa, ya, xb, yb, angle);
	glutPostRedisplay();
}
