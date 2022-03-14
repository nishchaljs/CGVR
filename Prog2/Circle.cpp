//BresCircle
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
int xc=0, yc=0, r=0, choice=0, click=0;
void plot(int h, int k, int x, int y) {
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2d(x+h, y+k);
	glVertex2d(-x+h, y+k);
	glVertex2d(x +h, -y+k);
	glVertex2d(-x+h, -y+k);
	glVertex2d(y+h, x+k);
	glVertex2d(-y+h, x+k);
	glVertex2d(y+h, -x+k);
	glVertex2d(-y+h, -x+k);
	glEnd();
	glFlush();
}
void bres(int h, int k, int r) {
	int y = r, x = 0, e = 1 - r;
	while (y > x) {
		plot(h, k, x, y);
		if (e < 0) {
			e += 2 * x + 3;
		}
		else {
			e += 2 * (x-y) + 5;
			y--;
		}
		x++;
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
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click==0) {
		xc = x;
		yc = 500 - y;
		click = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && click == 1) {
		x = x;
		y = 500 - y;
		int r = sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
		bres(xc, yc, r);
		click = 0;
	}
	glutPostRedisplay();
}
void display() {
	glClearColor(1, 1, 1, 1);
	bres(xc, yc, r);
	glFlush();
	glutPostRedisplay();
}

void display2() {
	glClearColor(1, 1, 1, 1);
	glFlush();
	glutPostRedisplay();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bres Circle");
	glOrtho(0,500,0,500,0,500);
	glClear(GL_COLOR_BUFFER_BIT);
	printf("Enter 1 for Keyboard, 2 for mouse\n");
	scanf_s("%d", &choice);
	if (choice == 1) {
		printf("Enter Centre X Y and Radius R\n");
		scanf_s("%d%d%d", &xc, &yc, &r);
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutMainLoop();
	}
	else {
		
		glutDisplayFunc(display2);
		glutMouseFunc(mouse);
		glutReshapeFunc(reshape);
		glutMainLoop();
	}

}
