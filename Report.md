Name: Abdulrehman Mahmoud Suliman  <br  />
id:1180140  <br  />

# Details about implementations

In this assignment I have made the implementation of a full body robot <br   />
Made all the required movements <br  />

##  keyboard movements

S-s Controls the shoulder of both hands <br  />
E-e Controls the elbows of both hands<br  />
L-l Controls the upper part of the left leg <br  />
D-d Controls the lower part of the left leg  <br  />
K-k Controls the left leg in rotating to open and close the leg <br  />
Y-y Controls the upper part of the right leg<br  />
R-r Controls the lower part of the right leg <br  />
Q-q Controls the right leg in rotating to open and close the leg <br  />
f   moves forward <br  />
b   moves backword <br  />

used the arrows to move right, left, up, and down. However mouse can be used also. <br  />

Ex: <br  />

	case 'k':
		if(LegUpLeft<=50)
			LegUpLeft = (LegUpLeft + 5) % 360;
		glutPostRedisplay();
		break;
	case 'K':
		if (LegUpLeft > 0)
			LegUpLeft = (LegUpLeft - 5) % 360;
		glutPostRedisplay();
		break;
	case 'q':
		if (LegUpLLeft >= -50)
			LegUpLLeft = (LegUpLLeft - 5) % 360;
		glutPostRedisplay();
		break;
	case 'Q':
		if (LegUpLLeft < 0)
			LegUpLLeft = (LegUpLLeft + 5) % 360;
		glutPostRedisplay();
		break;

<br />
for Example the implementation of the first leg: <br  />

//Leg1
	
	glPushMatrix();
	glTranslatef(0.375, -1.3, 0.0);
	glRotatef((GLfloat)LegUp, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)LegUpLeft, 0.0, 0.0, 1.0);
	glTranslatef(0.375, -1.2, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)LegDown, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 0.0);

	glPushMatrix();
	glScalef(0.5, 2.0, 0.75);
	glutWireCube(1.0);
	glPopMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glPushMatrix();
	glScalef(0.5, 0.5, 1.25);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

<br />
Example of Camera movements

	void moveBackword()
	{
		//Write your code here
		double direction[3];
		direction[0] = center[0] - eye[0];
		direction[1] = center[1] - eye[1];
		direction[2] = center[2] - eye[2];
		float speed = 0.1;
		eye[0] -= direction[0] * speed;
		eye[1] -= direction[1] * speed;
		eye[2] -= direction[2] * speed;

		center[0] -= direction[0] * speed;
		center[1] -= direction[1] * speed;
		center[2] -= direction[2] * speed;
	}

<br  />


# Sample results
Full Robot <br />
![GitHub Logo](/images/FullRobot1.png) <br  />

Some hand movements <br />
![GitHub Logo](/images/HandMovement1.png) <br  />
![GitHub Logo](/images/HandMovement2.png) <br  />
![GitHub Logo](/images/HandMovement3.png) <br  />

Some legs movements <br />
![GitHub Logo](/images/legMovement1.png) <br  />
![GitHub Logo](/images/legMovement2.png) <br  />
![GitHub Logo](/images/legMovement3.png) <br  />
![GitHub Logo](/images/legMovement4.png) <br  />

## Some camera movements 

Move right and left <br  />
![GitHub Logo](/images/rightAndleft1.png) <br  />
![GitHub Logo](/images/rightAndleft2.png) <br  />

Move up and down <br  />
![GitHub Logo](/images/Up.png) <br  />
![GitHub Logo](/images/down.png) <br  />

Move forward and backword <br  />
![GitHub Logo](/images/Forward.png) <br  />
![GitHub Logo](/images/Back.png) <br  />

# Issues faced
Faced some problems while applying the rotations but overcomed it after focusing for several hours and it was solved successfully<br  />