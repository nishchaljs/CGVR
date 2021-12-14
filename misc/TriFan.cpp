//TriFan

#include<Windows.h>
#include<gl/glut.h>
void display3()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	//glBegin(GL_TRIANGLE_STRIP);
	glPointSize(50);

	glColor3d(1.0f, 0.0f, 0.0f);
	glVertex2d(-0.5f, 0.0f);
	glColor3d(0.0f, 1.0f, 0.0f);
	glVertex2d(0.0f, 0.5f);
	glColor3d(0.0f, 0.0f, 1.0f);
	glVertex2d(0.5f, 0.0f);
	glColor3d(1.0f, 1.0f, 0.0f);
	glVertex2d(0.0f, -0.5f);
	glColor3d(0.0f, 1.0f, 1.0f);
	glVertex2d(-0.25f, -0.75f);


	glEnd();
	glFlush();

}
int main2(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Draw TriangleFan");
	glutInitWindowSize(320, 320);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(display3);
	glutMainLoop();
	return 0;
}