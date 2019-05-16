/*******************************
Name: Bryan Cagle
Class: CSCE 4230.001
Due Date: 02-18-2016
Description: The purpose of this program
is to create an interactive pendulum that
can be rotated in either direction at user
input

Created from source code of double.c as base
*******************************/

#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;
static double r=1.0,l=8.0,speed=2.0;

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);

	//Draws the anchor point
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2d(0,0);
	glEnd();

	//Draws the wire
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2d(0,0);
	glVertex2d(0,-l);
	glEnd();

	//Draws the hexagon bob
	glPointSize(1.0);
	glBegin(GL_POLYGON);
	glVertex2d(-0.5*r,-l+r); //top left
	glVertex2d(0.5*r,-l+r); //top right
	glVertex2d(r,-l); //right
	glVertex2d(0.5*r,-l-r); //bottom right
	glVertex2d(-0.5*r,-l-r); //bottom left
	glVertex2d(-r,-l); //left
	glEnd();

   glPopMatrix();

   glutSwapBuffers();
}

//Called if the rotate counter-clockwise function is called.
//Spin speed is variable-based, while the direction is indicated by +
void spinDisplayCCW(void)
{
   spin = spin + speed;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

//Called if the rotate clockwise function is called.
//Spin speed is variable-based, while the direction is indicated by -
void spinDisplayCW(void)
{
	spin = spin - speed;
	if(spin < -360.0)
	spin = spin + 360.0;
	glutPostRedisplay();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void reshape(int w, int h)
{
	//Creates a square viewport that will scale the image when the window is
	//increased so that the viewport stays square and the image is not stretched or
	//compressed
   	if(w>h)
	glViewport(((w-h)/2),0,h,h);
	else
	glViewport(0,((h-w)/2),w,w);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.3*l, 1.3*l, -1.3*l, 1.3*l, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplayCCW);
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

void MenuSelect(int idCommand)
{
	//Each menu selection has a seperate purpose for each action on the pendulum
        switch(idCommand)
        {
                case '+':
                        glutIdleFunc(spinDisplayCCW); //calls spin counterclockwise function
                        break;
                case '-':
                        glutIdleFunc(spinDisplayCW); //calls spin clockwise function
                        break;
                case 'w':
                        speed+=1; //increases the rotation speed by 1
                        break;
                case 's':
                        if(speed>0) //decreases the rotation speed by 1 as long as it is rotating
                        speed-=1;
                        break;
                case 'd':
                        l+=1; //increases length of pendulum by 1
                        break;
                case 'a':
                        if(l>0) //decreases  length of pendulum by 1 as long as the length is at least 0
                        l-=1;
                        break;
                case 32:
                        glutIdleFunc(NULL); //stops the rotation
                        break;
                case 27: exit(0); break; //ends program
                default: break;
        }
}

void keyboard(unsigned char key, int x, int y)
{
	//each keypress function redirects to the menu select
	switch(key){
		case '+':
			MenuSelect('+');
			break;
		case '-':
			MenuSelect('-');
			break;
		case 'w':
			MenuSelect('w');
			break;
		case 's':
			MenuSelect('s');
			break;
		case 'd':
			MenuSelect('d');
			break;
		case 'a':
			MenuSelect('a');
			break;
		case 32:
			MenuSelect(32);
			break;
		case 27:
			MenuSelect(27);
			break;
		default: break;
	}
}

int BuildMenu(void)
{
	int menu;
	menu=glutCreateMenu(MenuSelect);
	glutAddMenuEntry("Spin Counter-Clockwise (+)",'+');
	glutAddMenuEntry("Spin Clockwise (-)", '-');
	glutAddMenuEntry("Increase Speed +1 (w)", 'w');
	glutAddMenuEntry("Decrease Speed -1 (s)", 's');
	glutAddMenuEntry("Increase Length +1 (d)", 'd');
	glutAddMenuEntry("Decrease Length -1 (a)", 'a');
	glutAddMenuEntry("Stop Spinning (space)", 32);
	glutAddMenuEntry("Exit Program (ESC)", 27);
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (900, 900); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Rotating Pendulum");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	BuildMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); //uses the mouse click to create menu
   glutMainLoop();
   return 0;
}
