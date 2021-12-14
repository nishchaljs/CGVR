#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>
using namespace std;
int iter;
float coord[4][3] = { {0,200,-200},{0,0,200},{200,-200,-200},{-200,-200,-200} };
void drawtriangle(float* p1, float* p2, float* p3, float* p4) {
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(p1);
	glVertex3fv(p3);
	glVertex3fv(p4);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p4);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
}
void drawtetrahedron(float* p1, float* p2, float* p3, float* p4,int  iter ) {
	float mid[6][3];
	if (iter > 0) {
		for (int i = 0; i < 3; i++) {
			mid[0][i] = (p1[i] + p2[i]) / 2;
			mid[1][i] = (p1[i] + p3[i]) / 2;
			mid[2][i] = (p1[i] + p4[i]) / 2;
			mid[3][i] = (p2[i] + p3[i]) / 2;
			mid[4][i] = (p3[i] + p4[i]) / 2;
			mid[5][i] = (p2[i] + p4[i]) / 2;
		}

		drawtetrahedron(p1, mid[0], mid[1], mid[2], iter - 1);
		drawtetrahedron(mid[0], p2, mid[3], mid[5], iter - 1);
		drawtetrahedron(mid[1], mid[3], p3, mid[4], iter - 1);
		drawtetrahedron(mid[2], mid[4], mid[5], p4, iter - 1);
	}
	else
		drawtriangle(p1, p2, p3, p4);
}
void serpdisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	drawtetrahedron(coord[0], coord[1], coord[2], coord[3], iter);
	glEnd();
	glFlush();
}

void serpreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-w/2, w/2, -h/2, h/2, -300, 300);
	else
		glOrtho(-w/2, w/2, -h/2, h/2, -300, 300);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	printf("Enter Iterations\n");
	scanf_s("%d", &iter);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Serpanski");
	glutDisplayFunc(serpdisplay);
	glOrtho(-300, 300, -300, 300, -300, 300);
	glutReshapeFunc(serpreshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}