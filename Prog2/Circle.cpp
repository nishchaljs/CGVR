#include<stdio.h>
#include<math.h>
#include<gl/glut.h>
int cx, cy, rx, ry,cflag=0;
void circledisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(5.0);
	glFlush();
}
void plotcirclepixel(int h, int k, int x, int y) {
	printf("I am printing pixels\n");
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glVertex2f(x + h, y + k);
	glVertex2f(x + h, -y + k);
	glVertex2f(-x + h, y + k);
	glVertex2f(-x + h, -y + k);
	glVertex2f(y + h, x + k);
	glVertex2f(-y + h, x + k);
	glVertex2f(y + h, -x + k);
	glVertex2f(-y + h, -x + k);
	glEnd();
}
void drawcircle(int r) {
	int x1 = 0, y1 = r, d = 1 - r;
	while (y1 > x1) {
		plotcirclepixel(cx, cy, x1, y1);
		if (d < 0) {
			d += 2 * x1 + 3;
		}
		else {
			d += 2 * (x1 - y1) + 5;
			y1--;
		}
		x1++;
	}
	plotcirclepixel(cx, cy, x1, y1);
	glFlush();
}
void circlemouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && cflag==0) {
		cx = x;
		cy = 500-y;
		printf("Circle Center: %d %d\n", cx, cy);
		cflag = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && cflag == 1) {
		rx = x;
		ry = 500 - y;
		cflag = 0;
		int r = sqrt((cx - rx) * (cx - rx) + (cy - ry) * (cy - ry));
		printf("Circle radius: %d\n", r);
		drawcircle(r);
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Circle");
	glutDisplayFunc(circledisplay);
	glutMouseFunc(circlemouse);
	gluOrtho2D(0, 500, 0, 500);
	glutMainLoop();
	return 0;
}