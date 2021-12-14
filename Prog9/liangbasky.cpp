#include<stdio.h>
#include<gl/glut.h>
float cords[100][4];
int xminl, yminl, xmaxl, ymaxl, xvminl, yvminl, xvmaxl, yvmaxl;
int numlinesl;
int cliptest(float p, float q, float* u1, float* u2) {
	float r;
	if (p) r = q/p;
	if (p < 0) {
		if (r > *u1) *u1 = r;
		if (r > *u2) return 0;
	}
	else if (p > 0) {
		if (r < *u2) *u2 = r;
		if (r < *u1) return 0;
	}
	else {
		if (q < 0)
			return 0;
	}
	return 1;
}
void liangclip(float x1, float y1, float x2, float y2) {
	float dx = x2 - x1, dy = y2 - y1,u1=0.0,u2=1.0;
	if(cliptest(-dx,x1-xminl,&u1,&u2))
		if(cliptest(dx,xmaxl-x1,&u1,&u2))
			if(cliptest(-dy,y1-xminl,&u1,&u2))
				if (cliptest(dy, xmaxl - y1, &u1, &u2))
				{
					if (u2 < 1.0) {
						x2 = x1 + u2 * dx;
						y2 = y1 + u2 * dy;
					}
					if (u1 > 0.0) {
						x1 = x1 + u1 * dx;
						y1 = y1 + u1 * dy;
					}

					float sx = (xvmaxl - xvminl) / (xmaxl - xminl);
					float sy = (yvmaxl - yvminl) / (ymaxl - yminl);
					float xv1 = xvminl + sx * (x1 - xminl);
					float yv1 = yvminl + sy * (y1 - yminl);
					float xv2 = xvminl + sx * (x2 - xminl);
					float yv2 = yvminl + sy * (y2 - yminl);

					glBegin(GL_LINES);
					glVertex2f(xv1, yv1);
					glVertex2f(xv2, yv2);
					glEnd();
					glFlush();
				}
}
void liangdisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xminl, yminl);
	glVertex2f(xminl, ymaxl);
	glVertex2f(xmaxl, ymaxl);
	glVertex2f(xmaxl, yminl);
	glEnd();

	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvminl, yvminl);
	glVertex2f(xvminl, yvmaxl);
	glVertex2f(xvmaxl, yvmaxl);
	glVertex2f(xvmaxl, yvminl);
	glEnd();

	for (int i = 0; i < numlinesl; i++) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(cords[i][0], cords[i][1]);
		glVertex2f(cords[i][2], cords[i][3]);
		glEnd();
		glFlush();
	}

	for (int i = 0; i < numlinesl; i++) {
		glColor3f(0.0, 1.0, 0.0);
		liangclip(cords[i][0], cords[i][1], cords[i][2], cords[i][3]);
	}

	glFlush();
}
void liangreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	printf("Enter Window Coordinates:\n");
	scanf_s("%d%d%d%d", &xminl, &yminl, &xmaxl, &ymaxl);
	printf("Enter ViewPort Coordinates:\n");
	scanf_s("%d%d%d%d", &xvminl, &yvminl, &xvmaxl, &yvmaxl);
	printf("Enter Number of Lines:\n");
	scanf_s("%d", &numlinesl);
	for (int i = 0; i < numlinesl; i++) {
		printf("Enter x1 y1 x2 y2:\n");
		scanf_s("%f%f%f%f", &cords[i][0], &cords[i][1], &cords[i][2], &cords[i][3]);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CohenSuther");
	glutDisplayFunc(liangdisplay);
	gluOrtho2D(0, 500, 0, 500);
	glutReshapeFunc(liangreshape);
	glutMainLoop();
	return  0;
	return 0;
}