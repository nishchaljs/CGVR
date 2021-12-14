#include<stdio.h>
#include<gl/glut.h>
#include<gl/glut.h>

GLfloat theta[] = { 0,0,0 };
int axis = 1;
void delay(int x) {
	for (x; x > 0; x--)
		for (int i = 0; i < 100000000; i++);
}
void cubedisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glTranslatef(150, 150, -50);
	if (axis == 0) {
		glRotatef(theta[axis], 1, 0, 0);
	}
	if (axis == 1) {
		glRotatef(theta[axis], 0, 1, 0);
	}
	if (axis == 2) {
		glRotatef(theta[axis], 0, 0, 1);
	}
	glTranslatef(-150, -150, 50);


	glBegin(GL_QUADS);
	//1st face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100, 100, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(100, 200, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(200, 200, 0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(200, 100, 0);

	//2nd face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100, 100, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(100, 200, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(100, 200,-100);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(100, 100, -100);

	//3rd face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100, 100, -100);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(100, 200, -100);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(200, 200, -100);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(200, 100, -100);

	//4th face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(200, 200, -100);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(200, 100, -100);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(200, 100, 0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(200, 200, 0);

	//5th face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(200, 200, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(200, 200, -100);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(100, 200, -100);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(100, 200, 0);

	//6th face
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(100, 100, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(100, 100, -100);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(200, 100, -100);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(200, 100, 0);
	glEnd();

	glFlush();
}

void idlecube() {
	delay(2);
	theta[axis] = 5;
	glutPostRedisplay();
}

void cubemouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 1;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 2;
}

void cubereshape(int w, int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2 * (float)h / (float)w, -2, 2*(float)h / (float)w, -h, h);
	else
		glOrtho(-2, 2 * (float)w / (float)h, -2, -2 * (float)w / (float)h, -w, w);
	glMatrixMode(GL_MODELVIEW);
	//glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CUBE");
	glutDisplayFunc(cubedisplay);
	glutIdleFunc(idlecube);
	glutMouseFunc(cubemouse);
	glOrtho(0, 300, 0, 300, -300, 300);
	glutReshapeFunc(cubereshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}