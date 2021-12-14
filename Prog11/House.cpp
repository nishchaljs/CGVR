#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
int angle;
float m,c;
void plothouse() {
	glBegin(GL_LINE_LOOP);
	glVertex2f(100, 100);
	glVertex2f(100, 200);
	glVertex2f(150, 250);
	glVertex2f(200, 200);
	glVertex2f(100, 200);
	glVertex2f(200, 200);
	glVertex2f(200, 100);
	glVertex2f(160, 100);
	glVertex2f(160, 150);
	glVertex2f(140, 150);
	glVertex2f(140, 100);
	glVertex2f(160, 100);
	glEnd();
	glFlush();
}
void displayhouse() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	plothouse();
	glFlush();
}
void displayrotate() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	plothouse();

	//rotate
	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-100, -100, 0);
	glColor3f(0.0, 1.0, 1.0);
	plothouse();
	glPopMatrix();
	glFlush();
	
}
void displayreflect() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	plothouse();

	//plot line
	int y1 = m * 200 + c;
	int y2 = m * 400 + c;
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(200, y1);
	glVertex2f(400, y2);
	glEnd();
	glFlush();

	//reflect
	glPushMatrix();
	glTranslatef(0,c,0);
	float theta = atan(m);
	theta = theta * 180 / 3.14;
	glRotatef(theta,0,0,1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, -c, 0);
	glColor3f(0.0, 1.0, 1.0);
	plothouse();
	glPopMatrix();
	glFlush();

}
void housemouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		displayrotate();
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		displayreflect();
	}
}
void housereshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (float)h / (float)w, 2 * (float)h / (float)w, -h, h);
	else
		glOrtho(-2 * (float)w / (float)h, 2 * (float)w / (float)h, -2, 2, -w, w);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	printf("Enter angle\n");
	scanf_s("%d", &angle);

	printf("Enter m and c\n");
	scanf_s("%f%f", &m,&c);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("House");
	glutDisplayFunc(displayhouse);
	glutMouseFunc(housemouse);
	gluOrtho2D(-400, 400, -400, 400);
	glutReshapeFunc(housereshape);
	glutMainLoop();
	return 0;
}