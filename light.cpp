#define GLUT_DISABLE_ATEXIT_HACK

#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 500;
const int maxn = 1500;

struct Point
{
	double x, y, z;

	Point()
	{ x = 0, y = 0, z = 0; }

	Point(double x, double y, double z) : x(x), y(y), z(z)
	{};
} point[maxn];

GLfloat LightAmbient1[] = {0, 0, 1, 1};
GLfloat LightDiffuse1[] = {0, 0, 1, 1};
GLfloat LightPosition1[] = {0, 0, 0, 1};
GLfloat Mat_specular1[] = {1, 1, 1, 1};
GLfloat Mat_shininess1[] = {50};
GLfloat LightAmbient2[] = {0, 1, 0, 1};
GLfloat LightDiffuse2[] = {0, 1, 0, 1};
GLfloat LightPosition2[] = {1, 1, 1, 1};
GLfloat Mat_specular2[] = {0, 0, 1, 1};
GLfloat Mat_shininess2[] = {50};
GLfloat LightAmbient3[] = {1, 0, 0, 1};
GLfloat LightDiffuse3[] = {1, 0, 0, 1};
GLfloat LightPosition3[] = {1, 0, 0, 1};
GLfloat Mat_specular3[] = {-1, 1, 1, 1};
GLfloat Mat_shininess3[] = {50};

struct Face
{
	int a, b, c, d;

	Face()
	{ a = 0, b = 0, c = 0, d = 0; }

	Face(int a, int b, int c, int d) : a(a), b(b), c(c), d(d)
	{}
} face[maxn];

int n, m;

void init()
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess3);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient3);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse3);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition3);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

void get_rotate_z(Point &p, double rad)
{
	const double tmp = p.x * cos(rad) + p.y * sin(rad);
	p.y = p.x * (-sin(rad)) + p.y * cos(rad);
	p.x = tmp;
}

void get_rotate_y(Point &p, double rad)
{
	const double tmp = p.x * cos(rad) + p.z * sin(rad);
	p.z = p.x * (-sin(rad)) + p.z * cos(rad);
	p.x = tmp;
}

void get_rotate_x(Point &p, double rad)
{
	const double tmp = p.y * cos(rad) + p.z * sin(rad);
	p.z = p.y * (-sin(rad)) + p.z * cos(rad);
	p.y = tmp;
}

static int angle = 0;

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i = 1; i <= n; i++)
	{
		glColor3f(1, 1, 1);
		if(face[i].d == 0) glBegin(GL_TRIANGLES);
		else glBegin(GL_POLYGON);
		glVertex3f(point[face[i].a].x, point[face[i].a].y, point[face[i].a].z);
		glVertex3f(point[face[i].b].x, point[face[i].b].y, point[face[i].b].z);
		glVertex3f(point[face[i].c].x, point[face[i].c].y, point[face[i].c].z);
		if(face[i].d)
			glVertex3f(point[face[i].d].x, point[face[i].d].y, point[face[i].d].z);
		glEnd();
	}
	glFlush();
}

void changePoint(int x, int y, double &vx, double &vy)
{
	vx = x, vy = HEIGHT - y;
	vx -= (double) WIDTH / 2.0;
	vy -= (double) HEIGHT / 2.0;
	vx /= (double) WIDTH / 2.0;
	vy /= (double) HEIGHT / 2.0;
}

void rotate_x(double rad)
{
	for(int i = 1; i <= m; i++)
		get_rotate_x(point[i], rad);
}

void rotate_y(double rad)
{
	for(int i = 1; i <= m; i++)
		get_rotate_y(point[i], rad);
}

void rotate_z(double rad)
{
	for(int i = 1; i <= m; i++)
		get_rotate_z(point[i], rad);
}

void move_x(double del)
{
	for(int i = 1; i <= m; i++)
		point[i].x += del;
}

void move_y(double del)
{
	for(int i = 1; i <= m; i++)
		point[i].y += del;
}

void KeyBoards(unsigned char key, int x, int y)
{
	printf("Key: %c,x:%d y:%d\n", key, x, y);
	if(key == 'w')
		move_y(0.01);
	if(key == 's')
		move_y(-0.01);
	if(key == 'a')
		move_x(-0.01);
	if(key == 'd')
		move_x(0.01);
	if(key == 'x')
		rotate_x(acos(-1) / 100);
	if(key == 'y')
		rotate_y(acos(-1) / 100);
	if(key == 'z')
		rotate_z(acos(-1) / 100);
	display();
}

int main(int argc, char *argv[])
{
	fstream input1("1.dat");
	input1 >> n >> m;
	cout << n << m << endl;
	for(int i = 1, k; i <= n; i++)
	{
		input1 >> k;
		input1 >> face[i].a >> face[i].b >> face[i].c >> face[i].d;
	}
	input1.close();
	fstream input2("2.dat");
	for(int i = 1, k; i <= m; i++)
	{
		input2 >> k;
		input2 >> point[i].x >> point[i].y >> point[i].z;
		point[i].x /= 250;
		point[i].y /= 100;
		point[i].z /= 100;
	}
	input2.close();
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("test");
	init();
	glutDisplayFunc(&display);
	glutKeyboardFunc(&KeyBoards);
	glutMainLoop();
	return 0;
}
