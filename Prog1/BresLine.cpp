//bres_line - prog1
#include<gl/glut.h>
#include<stdio.h>
int x1=0, x2=0, y1=0, y2=0, choice=0, click=0;
void bres(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1, dy = y2 - y1, i=0, incx=1, incy=1;
	if (dx == 0) {
		glBegin(GL_POINTS);
		for (i = 0; i <= (y2 - y1); i++) {
			glVertex2d(x1, y1 + i);
		}
		glEnd();
		glFlush();
	}
	if (dy == 0) {
		glBegin(GL_POINTS);
		for (i = 0; i <= (x2 - x1); i++) {
			glVertex2d(x1+i, y1);
		}
		glEnd();
		glFlush();
	}
	if (dx < 0) {
		incx = -1;
		dx = -dx;
	}
	if (dy < 0) {
		incy = -1;
		dy = -dy;
	}
	if (dy < dx) {
		int e = 2 * dy - dx;
		int inc1 = 2 * dy;
		int inc2 = 2 * (dy - dx);
		int x = x1, y = y1;
		glBegin(GL_POINTS);
		for (i = 0; i <= dx; i++) {
			glVertex2d(x, y);
			if (e < 0) {
				e += inc1;
			}
			else {
				e += inc2;
				y+=incy;
			}
			x+=incx;
		}
		glEnd();
		glFlush();
	}

	else {
		int e = 2 * dx - dy;
		int inc1 = 2 * dx;
		int inc2 = 2 * (dx - dy);
		int x = x1, y = y1;
		glBegin(GL_POINTS);
		for (i = 0; i <= dy; i++) {
			glVertex2d(x, y);
			if (e < 0) {
				e += inc1;
			}
			else {
				e += inc2;
				x+=incx;
			}
			y+=incy;
		}
		glEnd();
		glFlush();
	}

}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click==0) {
		x1 = x;
		y1 = 500 - y;
		click = 1;
		printf("%d %d\n", x1, y1);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click == 1) {
		x2 = x;
		y2 = 500 - y;
		click = 0;
		printf("%d %d\n", x2, y2);
		bres(x1, y1, x2, y2);
	}

}

void display() {
	glClearColor(1, 1, 1, 1);
	bres(x1, y1, x2, y2);
	glFlush();
	glutPostRedisplay();
}

void display1() {
	glClearColor(1, 1, 1, 1);
	glFlush();
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bres_line");
	glOrtho(0, 500, 0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);

	printf("Enter 1 for keyboard input, 2 for mouse input:\n");
	scanf_s("%d", &choice);
	if (choice == 1) {
		printf("Enter coordinates X1 Y1 X2 Y2\n");
		scanf_s("%d%d%d%d", &x1, &y1, &x2, &y2);
		glutDisplayFunc(display);
		glutMainLoop();
	}
	else {
		glutDisplayFunc(display1);
		glutMouseFunc(mouse);
		glutMainLoop();
	}
}
