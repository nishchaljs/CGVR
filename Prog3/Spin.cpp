#include<stdio.h>
#include<gl/glut.h>
float alpha = 0.0, beta=0.0, click2=0;
void draw_rect() {
	glBegin(GL_QUADS);
	glColor3d(1, 0, 0);
	glVertex2d(200, 200);

	glColor3d(0, 1, 0);
	glVertex2d(300, 200);

	glColor3d(0, 0, 1);
	glVertex2d(300, 300);

	glColor3d(1, 0, 1);
	glVertex2d(200, 300);
	glEnd();
	glFlush();
}
void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(250, 250, 0);
	glRotatef(beta, 0, 0, 1);
	glTranslatef(-250, -250, 0);
	draw_rect();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void display1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(250, 250, 0);
	glRotatef(alpha, 0, 0, 1);
	glTranslatef(-250, -250, 0);
	draw_rect();
	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}
void mouse1(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		alpha += 2;
	}
	glutPostRedisplay();
}
void mouse2(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (click2 == 0)
			click2 = 1;
		else
			click2 = 0;
	}
	glutPostRedisplay();
}
void idle1() {
	
		glutPostRedisplay();

}
void idle2() {
	if (click2 == 1) {
		beta += 2;
		glutPostRedisplay();
	}
	else {
		//
		glutPostRedisplay();
	}
	
}
void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glOrtho(0, 500, 0, 500, 0, 500);
	
	int w1 = glutCreateWindow("Still");
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);
	glutIdleFunc(idle1);
	glutReshapeFunc(reshape);


	int w2 = glutCreateWindow("Spin");
	glutDisplayFunc(display2);
	glutMouseFunc(mouse2);
	glutIdleFunc(idle2);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
