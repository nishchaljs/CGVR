#include<stdio.h>
#include<gl/glut.h>
int cube[8][3] = { {1,1,1},{1,1,-1},{-1,1,-1},{-1,1,1},{-1,-1,1},{1,-1,1},{1,-1,-1},{-1,-1,-1} };
int axes=0; float alpha = 2;

void draw_cube() {

	glBegin(GL_QUADS);
	glColor3d(1, 0, 0);
	glVertex3iv(cube[0]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[1]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[2]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[3]);

	glColor3d(1, 0, 0);
	glVertex3iv(cube[4]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[5]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[6]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[7]);
	
	glColor3d(1, 0, 0);
	glVertex3iv(cube[0]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[1]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[6]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[5]);

	glColor3d(1, 0, 0);
	glVertex3iv(cube[0]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[5]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[4]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[3]);
	
	glColor3d(1, 0, 0);
	glVertex3iv(cube[3]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[4]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[7]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[2]);

	glColor3d(1, 0, 0);
	glVertex3iv(cube[2]);
	glColor3d(0, 1, 0);
	glVertex3iv(cube[1]);
	glColor3d(0, 0, 1);
	glVertex3iv(cube[6]);
	glColor3d(1, 0, 1);
	glVertex3iv(cube[7]);
	glEnd();
	glFlush();

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(axes==0)
		glRotatef(alpha, 1,0,0);
	else if (axes == 1)
		glRotatef(alpha, 0, 1, 0);
	if (axes == 2)
		glRotatef(alpha, 0, 0, 1);
	draw_cube();
	glFlush();
	glutPostRedisplay();	
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		axes = 0;
		glutPostRedisplay();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		axes = 1;
		glutPostRedisplay();
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		axes = 2;
		glutPostRedisplay();
	}
	
}
void reshape(int w, int h) {
	glViewport(0,0,w,h);
	printf("%d %d\n", w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5 * (float)w / (float)h, 5 * (float)w / (float)h, -5,5, -w, w);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}
void idle() {
	if (alpha >= 360) {
		alpha -= 360;
	}
	alpha += 0.2;
	glutPostRedisplay();
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Color Cube");
	glutDisplayFunc(display);
	glOrtho(-5, 5, -5, 5, -5, 5);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
