#include<stdio.h>
#include<gl/glut.h>
int xmin, ymin, xmax, ymax, xvmin, yvmin, xvmax, yvmax,numlines;
float points[100][4];
int TOP = 1, BOTTOM = 2, LEFT = 8, RIGHT = 4;
int computecode(float x1, float y1) {
	int code = 0;
	if (y1 > ymax)
		code |= TOP;
	if (y1 < ymin)
		code |= BOTTOM;
	if (x1 > xmax)
		code |= RIGHT;
	if (x1 < xmin)
		code |= LEFT;
	return code;
}
void cohenclip(float x1, float y1, float x2, float y2) {
	int code1 = computecode(x1, y1);
	int code2 = computecode(x2, y2);
	int outcode = 0; float x, y;
	bool done = false, accept = false;
	do {
		if (!(code1 | code2)) {
			accept = true;
			done = true;
		}
		else if (code1 & code2) {
			done = true;
		}
		else {
			outcode = code1 ? code1 : code2;
			if (outcode & TOP) {
				y = ymax;
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
			}
			else if (outcode & BOTTOM) {
				y = ymin;
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
			}
			else if (outcode & LEFT) {
				x = xmin;
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
			}
			else {
				x = xmax;
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
			}

			if (outcode == code1) {
				x1 = x;
				y1 = y;
				code1 = computecode(x1, y1);
			}
			else {
				x2 = x;
				y2 = y;
				code2 = computecode(x2, y2);
			}
		}

	} while (!done);
	printf("OUT OF WHILE LOOP\n");

	if (accept) {
		float sx = (xvmax - xvmin) / (xmax - xmin);
		float sy = (yvmax - yvmin) / (ymax - ymin);
		float xv1 = xvmin + (x1 - xmin) * sx;
		float yv1 = yvmin + (y1 - ymin) * sy;
		float xv2 = xvmin + (x2 - xmin) * sx;
		float yv2 = yvmin + (y2 - ymin) * sy;

		//plot
		printf("PLOTTING CLIPPED LINE\n");
		glBegin(GL_LINES);
		glVertex2f(xv1, yv1);
		glVertex2f(xv2, yv2);
		glEnd();
		glFlush();
	}

}
void cohensuthdisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmin, ymax);
	glVertex2f(xmax, ymax);
	glVertex2f(xmax, ymin);
	glEnd();

	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin, yvmin);
	glVertex2f(xvmin, yvmax);
	glVertex2f(xvmax, yvmax);
	glVertex2f(xvmax, yvmin);
	glEnd();

	for (int i = 0; i < numlines; i++) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(points[i][0], points[i][1]);
		glVertex2f(points[i][2], points[i][3]);
		glEnd();
		glFlush();
	}

	for (int i = 0; i < numlines; i++) {
		glColor3f(0.0, 1.0, 0.0);
		cohenclip(points[i][0], points[i][1], points[i][2], points[i][3]);
	}

	glFlush();
}
void cohenreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	printf("Enter Window Coordinates:\n");
	scanf_s("%d%d%d%d", &xmin, &ymin, &xmax, &ymax);
	printf("Enter ViewPort Coordinates:\n");
	scanf_s("%d%d%d%d", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("Enter Number of Lines:\n");
	scanf_s("%d", &numlines);
	for (int i = 0; i < numlines; i++) {
		printf("Enter x1 y1 x2 y2:\n");
		scanf_s("%f%f%f%f", &points[i][0], &points[i][1], &points[i][2], &points[i][3]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CohenSuther");
	glutDisplayFunc(cohensuthdisplay);
	gluOrtho2D(0, 500, 0, 500);
	glutReshapeFunc(cohenreshape);
	glutMainLoop();
	return  0;
}