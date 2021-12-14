#include<stdio.h>
#include<gl/glut.h>
int polysize, clipsize;
int polypoints[100][2];
int clippoints[100][2];
int xintercept(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int n = (x1 * y2 - x2 * y1) * (x3 - x4) - (x3 * y4 - x4 * y3) * (x1 - x2);
	int c = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return n / c;
}
int yintercept(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int n = (x1 * y2 - x2 * y1) * (y3 - y4) - (x3 * y4 - x4 * y3) * (y1 - y2);
	int c = (x1 - x2) * (y3 - y4) - (x3 - x4) * (y1 - y2);
	return n / c;
}
void clip(int x1, int y1, int x2, int y2) {
	int newpoints[100][2];
	int newsize = 0;
	for (int i = 0; i < polysize; i++) {
		int k = (i + 1) % polysize;
		int ix = polypoints[i][0], iy = polypoints[i][1], kx = polypoints[k][0], ky = polypoints[k][1];
		int iloc = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
		int kloc = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);
		if (iloc < 0 && kloc < 0) {
			newpoints[newsize][0] = kx;
			newpoints[newsize++][1] = ky;
		}
		else if (iloc >= 0 && kloc < 0) {
			newpoints[newsize][0] = xintercept(x1, y1, x2, y2, ix, iy, kx, ky);
			newpoints[newsize++][1] = yintercept(x1, y1, x2, y2, ix, iy, kx, ky);
			newpoints[newsize][0] = kx;
			newpoints[newsize++][1] = ky;
		}
		else if (iloc < 0 && kloc >= 0) {
			newpoints[newsize][0] = xintercept(x1, y1, x2, y2, ix, iy, kx, ky);
			newpoints[newsize++][1] = yintercept(x1, y1, x2, y2, ix, iy, kx, ky);
		}
	}
	polysize = newsize;
	for (int i = 0; i < polysize; i++) {
		polypoints[i][0] = newpoints[i][0];
		polypoints[i][1] = newpoints[i][1];
	}
}
void polyclipdisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < polysize; i++) {
		glVertex2f(polypoints[i][0], polypoints[i][1]);
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < clipsize; i++) {
		glVertex2f(clippoints[i][0], clippoints[i][1]);
	}
	glEnd();

	for (int i = 0; i < clipsize; i++) {
		int k = (i + 1) % clipsize;
		clip(clippoints[i][0], clippoints[i][1], clippoints[k][0], clippoints[k][1]);
	}
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < polysize; i++) {
		glVertex2f(polypoints[i][0], polypoints[i][1]);
	}
	glEnd();
	glFlush();
}
int main(int argc, char** argv) {
	printf("Enter size of polygon:\n");
	scanf_s("%d", &polysize);
	for (int i = 0; i < polysize; i++) {
		printf("Enter Poly Vertices:\n");
		scanf_s("%d%d", &polypoints[i][0], &polypoints[i][1]);
	}
	printf("Enter size of clip window:\n");
	scanf_s("%d", &clipsize);
	for (int i = 0; i < clipsize; i++) {
		printf("Enter Clip Vertices:\n");
		scanf_s("%d%d", &clippoints[i][0], &clippoints[i][1]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Polygon Clip");
	glutDisplayFunc(polyclipdisplay);
	gluOrtho2D(0, 500, 0, 500);
	glutMainLoop();
	return 0;
}