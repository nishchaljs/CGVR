#include<stdio.h>
#include<gl/glut.h>
void rect(int x, int y, int r, int h) {
	glBegin(GL_LINE_LOOP);
	glVertex2d(x,y);
	glVertex2d(x+r, y);
	glVertex2d(x+r, y+h);
	glVertex2d(x, y+h);
	glEnd();
}
void plot(int h, int k, int x, int y) {
	glBegin(GL_POINTS);
	glVertex2d(x + h, y + k);
	glVertex2d(-x + h, y + k);
	glVertex2d(-x + h, -y + k);
	glVertex2d(x + h, -y + k);
	glVertex2d(y + h, x + k);
	glVertex2d(-y + h, x + k);
	glVertex2d(y + h, -x + k);
	glVertex2d(-y + h, -x + k);
	glEnd();
}
void bres(int h, int k, int r) {
	int x = 0, y = r, e = 1 - r;
	while (y > x) {
		plot(h,k,x, y);
		if (e < 0) {
			e += 2 * x + 3;
		}
		else {
			e += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
	glFlush();
}
void display1() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	int x = 250, y = 250, r = 100, h=100, i=0;
	for (i = 0; i < h; i += 5) {
		bres(x , y + i, r);
	}
	y = y + i;
	for (i = 0; i <= r; i += 2) {
		bres(x, y , r-i);
	}
	glFlush();
	//glutPostRedisplay();
}

void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	int x = 250, y = 250, r = 100, h = 50, i = 0;
	for (i = 0; i < h; i += 3) {
		rect(x+i, y + i, r, h);
	}
	y = y + i; x = x + i;
	glBegin(GL_QUADS);
	glVertex2d(x, y);
	glVertex2d(x + 100, y);
	glVertex2d(x + 100, y + 50);
	glVertex2d(x, y + 50);
	glEnd();
	glFlush();
	//glutPostRedisplay();
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
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glOrtho(0, 500, 0, 500, 0, 500);

	glutCreateWindow("Cylinder");
	glutDisplayFunc(display1);
	glutReshapeFunc(reshape);
	

	glutCreateWindow("Parallelopiped");
	glutDisplayFunc(display2);
	glutReshapeFunc(reshape);

	glutMainLoop();
}
