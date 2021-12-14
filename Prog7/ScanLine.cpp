#include<stdlib.h>
#include<gl/glut.h>
#include<algorithm>
#include<iostream>
#include<windows.h>
using namespace std;
float points[100][2];
int n,m;
float intx[200] = { 0 };
int wx = 500, wy = 500;
void edgedetect(float x1, float y1, float x2, float y2, int s) {
	if (y2 < y1) {
		float temp;
		temp = y2; y2 = y1; y1 = temp;
		temp = x2; x2 = x1; x1 = temp;
	}
	if (s > y1 && s < y2) {
		intx[m++] = x1 + (s - y1) * (x2 - x1) / (y2 - y1);
	}
}
void scanlinefill() {
	for (int scan = 0; scan <=500; scan++) {
		m = 0;
		for (int i = 0; i < n; i++) {
			edgedetect(points[i][0], points[i][1], points[(i + 1) % n][0], points[(i + 1) % n][1], scan);
		}
		sort(intx, (intx + m));
		if (m >= 2) {
			for (int i = 0; i < m; i += 2)
			{
				Sleep(100);
				glColor3f(0.0, 1.0, 0.0);
				glBegin(GL_LINES);
				glVertex2f(intx[i], scan);
				glVertex2f(intx[i+1], scan);
				glEnd();
				glFlush();
			}
		}
	}
}

void display_filled_polygon() {

	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(points[i][0], points[i][1]);
	glEnd();
	scanlinefill();
}

void main(int argc, char* argv[]) {
	printf("Enter no. of sides: \n");
	scanf_s("%d", &n);
	printf("Enter coordinates of endpoints: \n");
	for (int i = 0; i < n; i++)
	{
		printf("X-coord Y-coord: \n");
		scanf_s("%f %f", &points[i][0], &points[i][1]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("ScanLine");
	glutDisplayFunc(display_filled_polygon);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0, 500, 0, 500);
	glutMainLoop();

}