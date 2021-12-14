#include<stdio.h>
#include<gl/glut.h>

void ppedDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	int x1 = 100, y1 = 100, x2 = 300, y2 = 200;
	for(int i = 0; i < 45; i+=1) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1+i, y1+i);
		glVertex2f(x1 + i, y2 + i);
		glVertex2f(x2 + i, y2 + i);
		glVertex2f(x2 + i, y1 + i);
		glEnd();
	}
	glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2 );
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
		glEnd();
		
	/*for(int i = 0; i >=0; i+=1) {
		if (x1 + i > x2 - i || y1 + i > y2 - i)
			break;
		glBegin(GL_LINE_LOOP);
		glVertex2f(x1 + i, y1 + i);
		glVertex2f(x1 + i, y2 - i);
		glVertex2f(x2 - i, y2 - i);
		glVertex2f(x2 - i, y1 + i);
		glEnd();
	}*/
	glFlush();
}
void draw_pixel(GLint cx, GLint cy)
{
	
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}
void plotpixels(GLint h, GLint k, GLint x, GLint y)
{
	draw_pixel(x + h, y + k);
	draw_pixel(-x + h, y + k);
	draw_pixel(x + h, -y + k);
	draw_pixel(-x + h, -y + k);
	draw_pixel(y + h, x + k);
	draw_pixel(-y + h, x + k);
	draw_pixel(y + h, -x + k);
	draw_pixel(-y + h, -x + k);
}
void drawCircle(GLint x, GLint y, GLint r) {
	int x1 = 0, y1 = r, d = 1-r;
	while (y1 > x1) {
		plotpixels(x, y, x1, y1);
		if (d < 0) {
			d += 2 * x1 + 3;
		}
		else {
			d += 2 * (x1 - y1) + 5;
			--y1;
		}
		++x1;
	}
	plotpixels(x, y, x1, y1);
	glFlush();
}

void cylinderDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);
	GLint x1 = 150, y1 = 150, r = 100;
	for (int i = 0; i < 100; i+=1) {
		drawCircle(x1, y1+i, r);
	}
	/*for (int i = 0; i < r; i+=1)
		drawCircle(x1, y1, r - i);
	for (int i = 0; i < r; i += 1)
		drawCircle(x1, y1+99, r - i);*/
	glFlush();
}
void cpreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (float)h / (float)w, 2 * (float)h / (float)w, -h, h);
	else
		glOrtho(-2 * (float)w / (float)h, 2 * (float)w / (float)h, -2, 2, -w, w);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	int id1 = glutCreateWindow("Cylinder");
	glutDisplayFunc(cylinderDisplay);
	gluOrtho2D(0, 500, 0, 500);
	glutReshapeFunc(cpreshape);

	int id2 = glutCreateWindow("Pped");
	glutDisplayFunc(ppedDisplay);
	gluOrtho2D(0, 500, 0, 500);

	glutReshapeFunc(cpreshape);
	glutMainLoop();
	return 0;
}