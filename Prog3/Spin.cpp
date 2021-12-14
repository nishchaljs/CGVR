#include<stdio.h>
#include<gl/glut.h>
float spinangle_s = 2, spinangle_d = 0.02;
int t,id1,id2;
void delayspin(int t) {
	for (t; t > 0; t--)
		for (int i = 0; i < 100000000; i++);
}
void spindoubledisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MATRIX_MODE);
	glLoadIdentity();
	glRotatef(spinangle_d, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(0, 100);
	glVertex2f(100, 0);
	glVertex2f(0, -100);
	glVertex2f(-100, 0);
	glEnd();
	glutSwapBuffers();
	glFlush();
	
}
void spinsingledisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(spinangle_s, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(0, 100);
	glVertex2f(100, 0);
	glVertex2f(0, -100);
	glVertex2f(-100, 0);
	glEnd();
	glFlush();
}
void idlespin() {
	delayspin(1);
	spinangle_d += 1;
	if (spinangle_d > 360)
		spinangle_d -= 360;
	glutSetWindow(id2);
	glutPostRedisplay();
}
void spinmousedouble(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutIdleFunc(idlespin);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		glutIdleFunc(NULL);
}
void spinmousesingle(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		spinangle_s += 2;
		if (spinangle_s > 360)
			spinangle_s -= 360;
		glutSetWindow(id1);
		glutPostRedisplay();
	}
}

void spinreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	id1 = glutCreateWindow("Spin Single");
	glutDisplayFunc(spinsingledisplay);
	glutMouseFunc(spinmousesingle);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(-250, 250, -250, 250);

	id2 = glutCreateWindow("Spin DOuble");
	glutDisplayFunc(spindoubledisplay);
	glutMouseFunc(spinmousedouble);
	t = id1;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(-250, 250, -250, 250);
	
	glutReshapeFunc(spinreshape);
	glutMainLoop();
	return 0;
}