#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
void spheredisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, 0, -1);
	glRotatef(-90.0, 0, 1, 0);
	float pi = 3.14;
	for (int phi = -80; phi <= 80; phi += 20) {
		float phi_r = phi *pi / 180;
		float phi_r20 = (phi + 20) * pi / 180;
		glBegin(GL_QUAD_STRIP);
		for (int theta = -180; theta <= 180; theta += 20) {
			float t_r = theta * pi / 180;
			float x = cos(t_r) * cos(phi_r);
			float y = sin(t_r) * cos(phi_r);
			float z = sin(phi_r);
			glVertex3f(x, y, z);

			x = cos(t_r) * cos(phi_r20);
			y = sin(t_r) * cos(phi_r20);
			z = sin(phi_r20);
			glVertex3f(x, y, z);
		}
		glEnd();
	}

	//poles
	float phi_r = 80 * pi / 180;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 1);
	for (int theta = -180; theta <= 180; theta += 20) {
		float t_r = theta * pi / 180;
		float x = cos(t_r) * cos(phi_r);
		float y = sin(t_r) * cos(phi_r);
		float z = sin(phi_r);
		glVertex3f(x, y, z);
	}
	glEnd();

	//poles
	phi_r = -80 * pi / 180;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -1);
	for (int theta = -180; theta <= 180; theta += 20) {
		float t_r = theta * pi / 180;
		float x = cos(t_r) * cos(phi_r);
		float y = sin(t_r) * cos(phi_r);
		float z = sin(phi_r);
		glVertex3f(x, y, z);
	}
	glEnd();
	glFlush();
}
void spherereshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (float)h / (float)w, 2 * (float)h / (float)w, -h, h);
	else
		glOrtho(-2 * (float)w / (float)h, 2 * (float)w / (float)h, -2, 2, -w, w);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("SPHERE");
	glutDisplayFunc(spheredisplay);
	gluOrtho2D(-1,1,-1,1);
	glutReshapeFunc(spherereshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}