#include<stdio.h>
#include<gl/glut.h>
int flag = 0;
int x1, x2, y1, y2;

void bresdrawpixel(int x, int y) {
	printf("Draw Pixel was called\n");
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void drawbresline(int x1, int x2, int y1, int y2) {
	int dx = x2 - x1, dy = y2 - y1;
	if (dx == 0) {
		for (int i = 0; i <= dy; i++)
			bresdrawpixel(x1, y1 + i);
			return ;
	}

	if (dy == 0) {
		for (int i = 0; i <= dx; i++)
			bresdrawpixel(x1+i, y1);
		return;
	}
	int inx = 1, iny = 1;
	if (dx < 0)
		dx = -dx;
	if(x2<x1)
		inx=-1;
	if (dy < 0)
		dy = -dy;
	if (y2 < y1)
		iny = -1;

	if (dx > dy) {
		int e = 2 * dy - dx;
		int inc1 = 2 * (dy - dx);
		int inc2 = 2 * dy;
		int x=x1, y=y1;
		for (int i = 0; i <= dx; i++) {
			if (e > 0) {
				e += inc1;
				y += iny;
			}
			else {
				e += inc2;
			}
			x += inx;
			bresdrawpixel(x, y);
		}
	}

	else{
		int e = 2 * dx - dy;
		int inc1 = 2 * (dx - dy);
		int inc2 = 2 * dx;
		int x = x1, y = y1;
		for (int i = 0; i <= dy; i++) {
			if (e > 0) {
				e += inc1;
				x += inx;
			}
			else {
				e += inc2;
			}
			y += iny;
			bresdrawpixel(x, y);
		}
	}

	glFlush();
}
void bresDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,0.0,0.0);
	gluOrtho2D(0, 500, 0, 500);
	//glColor3f(0, 0, 1);
	glFlush();
}
void bresMouse(int button, int state, int x, int y) {
	if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag==0){
		x1 = x;
		y1 = 500 - y ;
		printf("X1=%d, Y1=%d\n", x1, y1);
		flag = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1) {
		x2 = x;
		y2 = 500 - y;
		flag = 0;
		printf("X2=%d, Y2=%d\n", x2, y2);
		drawbresline(x1, x2, y1, y2);
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bres Line");
	glutDisplayFunc(bresDisplay);
	glutMouseFunc(bresMouse);
	//bresinit();
	glutMainLoop();
	return 0;
}