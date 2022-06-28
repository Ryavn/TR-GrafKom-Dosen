//Gedung FEB UKSW
//Arya Tevin Budiman (672020005)
//Tristan Gaizka Mulyadi (672020006)
//Rizky Bagus Pratama (672020311)

#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

#define DEGREES_PER_PIXEL 0.6f
#define UNITS_PER_PIXEL 0.5f
#define ZOOM_FACTOR 0.08f

typedef struct
{
    bool leftButton;
	bool rightButton;
	int x;
	int y;
}

MouseState;
MouseState mouseState = { false, false, 0, 0 };

/* setting angles rotasi */
float xRotate = 0, yRotate = 0;

/* setting posisi kamera dan orientasi  */
GLfloat eye[] = { 0, 0, 60 };
GLfloat at[] = { 0, 0, 0 };

void ShapeTest()
{
    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        // Axis-x
            glVertex3f(-1000, 0, 0);
            glVertex3f(1000, 0, 0);
        // Axis-y
            glVertex3f(0, -1000, 0);
            glVertex3f(0, 1000, 0);
        // Axis-z
            glVertex3f(0, 0, -1000);
            glVertex3f(0, 0, 1000);
    glEnd();

	glBegin(GL_QUADS);
        // DEPAN
        glColor3f(1, 0, 0);
            glVertex3f(-5, 5, 5);
            glVertex3f(5, 5, 5);
            glVertex3f(5, -5, 5);
            glVertex3f(-5, -5, 5);
        // BELAKANG
            glVertex3f(-5, 5, -5);
            glVertex3f(5, 5, -5);
            glVertex3f(5, -5, -5);
            glVertex3f(-5, -5, -5);
        // ATAS
        glColor3f(0, 1, 0);
            glVertex3f(-5, 5, -5);
            glVertex3f(5, 5, -5);
            glVertex3f(5, 5, 5);
            glVertex3f(-5, 5, 5);
        // KANAN
            glVertex3f(-5, 5, 5);
            glVertex3f(-5, 5, -5);
            glVertex3f(-5, -5, -5);
            glVertex3f(-5, -5, 5);
    glEnd();
}

void DrawScene()
{
	/* Setting rotasi di sumbu X dan Y */
	glRotatef(xRotate, 0, 1, 0);
	glRotatef(yRotate, 1, 0, 0);

	ShapeTest();
}


void Display(void)
{
	/* Menggambar buffer sebelumnya */
	glDrawBuffer(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* (Re)posisi atau memposisikan ulang posisi kamera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

	DrawScene();

	glFlush();
	glutSwapBuffers();
}

void SpecialKey(int key, int x, int y)
{
    switch (key) {
	case GLUT_KEY_LEFT:
        eye[0] = eye[0] + UNITS_PER_PIXEL;
		at[0] = at[0] + UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_RIGHT:
		eye[0] = eye[0] - UNITS_PER_PIXEL;
		at[0] = at[0] - UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_UP:
		eye[1] = eye[1] - UNITS_PER_PIXEL;
		at[1] = at[1] - UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_DOWN:
		eye[1] = eye[1] + UNITS_PER_PIXEL;
		at[1] = at[1] + UNITS_PER_PIXEL;
		break;
	case GLUT_KEY_END:	/* zoom out */
		eye[0] = (1 + ZOOM_FACTOR) * eye[0] - at[0] * ZOOM_FACTOR;
		eye[1] = (1 + ZOOM_FACTOR) * eye[1] - at[1] * ZOOM_FACTOR;
		eye[2] = (1 + ZOOM_FACTOR) * eye[2] - at[2] * ZOOM_FACTOR;
		break;
	case GLUT_KEY_HOME: /* zoom in */
		eye[0] = (1 - ZOOM_FACTOR) * eye[0] + at[0] * ZOOM_FACTOR;
		eye[1] = (1 - ZOOM_FACTOR) * eye[1] + at[1] * ZOOM_FACTOR;
		eye[2] = (1 - ZOOM_FACTOR) * eye[2] + at[2] * ZOOM_FACTOR;
		break;
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
    case 'a':
    case 'A':
        SpecialKey(GLUT_KEY_LEFT, 0, 0);
		break;
    case 'd':
    case 'D':
        SpecialKey(GLUT_KEY_RIGHT, 0, 0);
		break;
    case 'w':
    case 'W':
        SpecialKey(GLUT_KEY_UP, 0, 0);
		break;
    case 's':
    case 'S':
        SpecialKey(GLUT_KEY_DOWN, 0, 0);
		break;
	case '+':	SpecialKey(GLUT_KEY_HOME, 0, 0);
		break;
	case '-':	SpecialKey(GLUT_KEY_END, 0, 0);
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.leftButton = true;
		else
			mouseState.leftButton = false;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.rightButton = true;
		else
			mouseState.rightButton = false;
	}

	// update posisi mouse, supaya gampang tracking/atau membaca pergerakan mouse untuk rotasi
	mouseState.x = x;
	mouseState.y = y;
}

void MouseMove(int x, int y)
{
	/* Hitung perpindahan posisi dalam pergerakan */
	int xDelta = mouseState.x - x;
	int yDelta = mouseState.y - y;

	/* Posisi mouse */
	mouseState.x = x;
	mouseState.y = y;

	/* Kalo tombol kiri mouse diklik, lakukan rotasi jika mouse digerakan */
	if (mouseState.leftButton)
    {
		xRotate -= xDelta * DEGREES_PER_PIXEL;
		yRotate -= yDelta * DEGREES_PER_PIXEL;
	}

	/* Kalo tombol kanan mouse diklik, lakukan translasi jika mouse digerakan */
	else if (mouseState.rightButton)
    {
		eye[0] += xDelta * UNITS_PER_PIXEL;
		eye[1] -= yDelta * UNITS_PER_PIXEL;
		at[0] += xDelta * UNITS_PER_PIXEL;
		at[1] -= yDelta * UNITS_PER_PIXEL;
	}
	glutPostRedisplay();
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	/* Setting proyeksi perspective */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, 1.0f, 0.1f, 1000.0f);

	/* Setting posisi kamera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], 0, 1, 0);

	/* Aktifkan hidden--surface--removal */
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Gedung FEB UKSW");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	myInit();
	glutMainLoop();
}
