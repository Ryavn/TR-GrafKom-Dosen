//Gedung FEB UKSW
//Arya Tevin Budiman (672020005)
//Tristan Gaizka Mulyadi (672020006)
//Rizky Bagus Pratama (672020311)

/*
	note:

	Lantai = y = 0
	Panjang Gedung 200 (-100 ~ 100)
	Tinggi Gedung 80 (0 ~ 80)
	Lebar Gedung 80 (-40 ~ 40)
*/

#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

#define DEGREES_PER_PIXEL 0.6f
#define UNITS_PER_PIXEL 1.5f
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
GLfloat eye[] = { 0, 0, 380 };
GLfloat at[] = { 0, 40, 0 };

void Eksterior(){
	glBegin(GL_LINES);
	// Axis X-Y-Z
	glColor3f(1, 1, 1);
		glVertex3f(-1000, 0, 0);
		glVertex3f(1000, 0, 0);
		glVertex3f(0, -1000, 0);
		glVertex3f(0, 1000, 0);
		glVertex3f(0, 0, -1000);
		glVertex3f(0, 0, 1000);
	glEnd();

	glBegin(GL_QUADS);
       /// ------------------------------ Basic-Wall & Floor
       glColor3f(0.87, 0.80, 0.67);
       //----- Depan
		glVertex3f(-100, 0, 40);
		glVertex3f(-100, 80, 40);
		glVertex3f(100, 80, 40);
		glVertex3f(100, 0, 40);
	//----- Belakang
		glVertex3f(-100, 0, -40);
		glVertex3f(-100, 80, -40);
		glVertex3f(100, 80, -40);
		glVertex3f(100, 0, -40);
	//----- Kiri
		glVertex3f(-100, 0, -40);
		glVertex3f(-100, 80, -40);
		glVertex3f(-100, 80, 40);
		glVertex3f(-100, 0, 40);
	//----- Kiri
		glVertex3f(100, 0, -40);
		glVertex3f(100, 80, -40);
		glVertex3f(100, 80, 40);
		glVertex3f(100, 0, 40);
	//----- Ground
	glColor3f(0.65, 0.71, 0.76);
		glVertex3f(-100 - 20, 0, -40 - 20);
		glVertex3f(100 + 20, 0, -40 - 20);
		glVertex3f(100 + 20, 0, 40 + 20);
		glVertex3f(-100 - 20, 0, 40 + 20);

	/// ------------------------------ Roof
	//----- Platform
	glColor3f(0.58, 0.53, 0.45);
		glVertex3f(-100 - 12, 80, -40 - 12);
		glVertex3f(100 + 12, 80, -40 - 12);
		glVertex3f(100 + 12, 80, 40 + 12);
		glVertex3f(-100 - 12, 80, 40 + 12);
	//----- Sample
	glColor3f(0.78, 0.73, 0.65);
		glVertex3f(-100 + 12, 80 + 0.1, -40 + 18);
		glVertex3f(100 - 12, 80 + 0.1, -40 + 18);
		glVertex3f(100 - 12, 80 + 0.1, 40 - 18);
		glVertex3f(-100 + 12, 80 + 0.1, 40 - 18);
	//----- Grid Bawah
	glColor3f(0.77, 0.52, 0.61);
		// G.B Depan
			glVertex3f(-100 - 12, 80, 40 + 12);
			glVertex3f(-100 + 12, 80 + 15, 40 - 18);
			glVertex3f(100 - 12, 80 + 15, 40 - 18);
			glVertex3f(100 + 12, 80, 40 + 12);
		// G.B Belakang
			glVertex3f(-100 - 12, 80, -40 - 12);
			glVertex3f(100 + 12, 80, -40 - 12);
			glVertex3f(100 - 12, 80 + 15, -40 + 18);
			glVertex3f(-100 + 12, 80 + 15, -40 + 18);
		// G.B Kiri
			glVertex3f(-100 - 12, 80, -40 - 12);
			glVertex3f(-100 + 12, 80 + 15, -40 + 18);
			glVertex3f(-100 + 12, 80 + 15, 40 - 18);
			glVertex3f(-100 - 12, 80, 40 + 12);
		// G.B Kanan
			glVertex3f(100 + 12, 80, 40 + 12);
			glVertex3f(100 - 12, 80 + 15, 40 - 18);
			glVertex3f(100 - 12, 80 + 15, -40 + 18);
			glVertex3f(100 + 12, 80, -40 - 12);
	//----- Grid Atas
	glColor3f(0.70, 0.52, 0.55);
		// G.A Depan
			glVertex3f(-100 + 12, 80 + 15, 40 - 18);
			glVertex3f(-100 + 2, 80 + 35, 0);
			glVertex3f(100 - 2, 80 + 35, 0);
			glVertex3f(100 - 12, 80 + 15, 40 - 18);
		// G.A Belakang
			glVertex3f(-100 + 12, 80 + 15, -40 + 18);
			glVertex3f(-100 + 2, 80 + 35, 0);
			glVertex3f(100 - 2, 80 + 35, 0);
			glVertex3f(100 - 12, 80 + 15, -40 + 18);
		/**
		G.A Samping (Kiri & Kanan) ada di GL_Triangle
		*/
	glEnd();

	glBegin(GL_TRIANGLES);
	/// ------------------------------ Roof (Lanjutan Grid Atas)
	glColor3f(0, 0, 0);
		// Grid Kiri
			glVertex3f(-100 + 12, 80 + 15, -40 + 18);
			glVertex3f(-100 + 12, 80 + 35, 0);
			glVertex3f(-100 + 12, 80 + 15, 40 - 18);
		// Grid Kanan
			glVertex3f(100 - 12, 80 + 15, -40 + 18);
			glVertex3f(100 - 12, 80 + 35, 0);
			glVertex3f(100 - 12, 80 + 15, 40 - 18);
	glEnd();
}

void DrawScene()
{
	/* Setting rotasi di sumbu X dan Y */
	glRotatef(xRotate, 0, 1, 0);
	glRotatef(yRotate, 1, 0, 0);

	Eksterior();
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
	glClearColor(0.1, 0.1, 0.1, 1);

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
