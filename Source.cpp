//Triangle

#include <Windows.h>
#include <gl/glut.h>

void display1() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glPointSize(50);
	glColor3f(0.5f, 0.5f, 0.0f);

	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush();
}

int main1(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("OPenGL Setup TEst");
	glutInitWindowSize(320, 320);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(display1);
	glutMainLoop();
	return 0;
}