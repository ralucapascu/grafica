#include<windows.h>
#include <gl/freeglut.h>
#include <math.h>
#include<iostream>
#include <cstdlib> 
#include <MMSystem.h>
using namespace std;

// Initializari ptr meniu
enum {
	Opt1, Opt2, Opt3
};

int rendermode = Opt1;

void menu(int selection)
{
	rendermode = selection;
	glutPostRedisplay();
}

class scrPt
{
public:
	GLint x, y;
};

static GLfloat rotTheta = 0.0;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
GLuint regHex1;
GLuint regHex2;
GLuint regHex3;
GLuint regHex4;
GLuint regHex5;
GLuint regHex7;
GLuint regHex8;
GLuint regHex9;
GLuint regHex10;
GLuint regHexr, regHex2r, regHex2extrar, regHex3r, regHex4r, regHex4rextrar, regHex5r, regHex6r, regHex7r, regHex8r, regHex9r, regHex10r, regHex11r;
const double TWO_PI = 6.2831853;

int z, c, b, randn;
int pesti_prinsi[300];

double k = 0.0;
double i = 0.0;
double alpha = 1.0;
double beta = 0.3;

float mi, mingei = 1, ml = 1, mingel = 1;
float k_peste = 0.0;
float k_peste_prins = 0.0;
float miscare_laterala = -200.0;
float miscare_verticala_undita = 1.0;
float transf_hook = 0.0; //cu cat este mutat hook-ul de la undita
float misca_pestele = 0.0; // misca pestele prins in undita
float coordX1_peste_prins = -2000.0;
float coordY1_peste_prins = -2000.0;
float coordX2_peste_prins = -2000.0;
float coordY2_peste_prins = -2000.0;
float transf_hook_prindere = 0.0;
float miscare_laterala_prindere = 0.0;
float x_values_pesti[1000] = { 150, 560, 760, 1000, 1105, 1200, 1290, 1370, 1500, 1600, 1800, 1850, 2000, 2100, 2200, 2300, 2400, 2450, 2500, 2600, 2700, 2800, 2900 };
float y_values_pesti[1000] = { 200, 250, 300, 100, 360, 240, 130 , 350, 245, 222, 303, 145, 180, 340, 190, 268, 388, 122, 225, 343, 280, 140, 277 };
float x_values_bombe[1000] = { 1200, 1000 };
float y_values_bombe[1000] = { 340, 500 };
float score = 0.0;
float transf_scor = 0.0;

bool stopGame = false;
bool prins_peste = false;

void deseneazaAvion() {

	//------------------declaratii liste
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
	regHex7 = glGenLists(1);
	glNewList(regHex7, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 100 * cos(hexTheta) + 900;
		hexVertex.y = 50 * sin(hexTheta) + 530;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex8 = glGenLists(1);
	glNewList(regHex8, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 13 * cos(hexTheta) + 1010;
		hexVertex.y = 13 * sin(hexTheta) + 530;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex9 = glGenLists(1);
	glNewList(regHex9, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.83, 1);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 10 * cos(hexTheta) + 880;
		hexVertex.y = 10 * sin(hexTheta) + 450;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();


	regHex10 = glGenLists(1);
	glNewList(regHex10, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(0.57, 0.51, 0.3);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 10 * cos(hexTheta) + 900;
		hexVertex.y = 10 * sin(hexTheta) + 450;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();
	// ------------- linia u de la aripa sus
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(950, 500);
	glVertex2f(900, 620);
	glEnd();

	glCallList(regHex7); //trunchi
	//roti
	glLineWidth(20);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(880, 460);
	glVertex2f(890, 480);

	glVertex2f(890, 480);
	glVertex2f(900, 460);
	glEnd();

	glCallList(regHex9);
	glCallList(regHex10);
	//----- bara pt aripa de sus cealalta + bara spoiler

	glLineWidth(10); //aripa sus
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(900, 560);
	glVertex2f(870, 620);
	glEnd();

	glLineWidth(10);  // bara spoiler
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(810, 530);
	glVertex2f(750, 580);
	glEnd();
	//acoperis frontal
		//-- paravan fata
	glColor3f(0.65, 0.23, 0.77);
	glBegin(GL_POLYGON);
	glVertex2f(840, 580);
	glVertex2f(960, 630);
	glVertex2f(940, 640);
	glVertex2f(830, 610);
	glEnd();

	//spoiler
	glColor3f(0.65, 0.23, 0.77);
	glBegin(GL_POLYGON);
	glVertex2f(710, 550);
	glVertex2f(810, 600);
	glVertex2f(780, 620);
	glVertex2f(680, 580);
	glEnd();

	//aripa 
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.50, 0.0);
	glVertex2f(860, 520);
	glVertex2f(910, 520);
	glVertex2f(910, 540);
	glVertex2f(860, 540);
	glEnd();

	// elice, cei 3 pasi
	//---------elice sus    
	glBegin(GL_POLYGON);
	glColor3f(0.85, 0.20, 0.65);
	glVertex2f(1000, 490);
	glVertex2f(1020, 490);
	glVertex2f(1020, 570);
	glVertex2f(1000, 570);
	glEnd();
	//--------elice jos
	glBegin(GL_POLYGON);
	glColor3f(0.85, 0.20, 0.65);
	glVertex2f(970, 520);
	glVertex2f(1050, 520);
	glVertex2f(1050, 540);
	glVertex2f(970, 540);
	glEnd();

	// ---punct elice
	glCallList(regHex8);

	//banner
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(800, 530);
	glVertex2f(600, 530);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(400, 480);
	glVertex2f(600, 480);
	glVertex2f(600, 580);
	glVertex2f(400, 580);
	glEnd();
	glPointSize(30.0);
	glColor3f(0.8, 0.1, 0.5);
	glRasterPos2i(420, 555);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'D');
	glRasterPos2i(450, 555);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glRasterPos2i(480, 555);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');

	glRasterPos2i(460, 520);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '&');
	glRasterPos2i(480, 485);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
	glRasterPos2i(510, 485);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');

	glRasterPos2i(540, 485);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');

	/*glRasterPos2i(520, 500);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glRasterPos2i(540, 500);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'N');
	glRasterPos2i(560, 500);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
	glRasterPos2i(580, 500);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '?');*/


	//glutSwapBuffers();
	//glFlush();
}

void omu(float u, float p, float o) {

	glColor3f(u, p, o);
	glBegin(GL_TRIANGLES);
	glVertex2i(450, 442);
	glVertex2i(480, 442);
	glVertex2i(465, 462);
	glEnd();

	//cap
	glColor3f(1, 0.6, 0.70);
	glCallList(regHex4);


	//ochii
	glPointSize(3);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(469, 468);
	glVertex2i(459, 468);
	glEnd();

	//gura
	glLineWidth(1.2);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(457, 463);
	glVertex2f(459, 460);
	glVertex2f(459, 460);
	glVertex2f(469, 460);
	glVertex2f(469, 460);
	glVertex2f(471, 463);
	glEnd();

	//maini
	glLineWidth(2);
	glColor3f(1, 0.6, 0.70);
	glBegin(GL_LINES);
	glVertex2f(472, 452);
	glVertex2f(482, 462);
	glVertex2f(457, 452);
	glVertex2f(447, 442);
	glEnd();

	//picioare
	glLineWidth(2);
	glColor3f(1, 0.6, 0.70);
	glBegin(GL_LINES);
	glVertex2f(460, 442);
	glVertex2f(460, 432);
	glVertex2f(470, 442);
	glVertex2f(470, 432);
	glEnd();

	//balon
	glLineWidth(3);
	glColor3f(0.3, 0.2, 0.8);
	glBegin(GL_LINES);
	glVertex2f(482, 462);
	glVertex2f(492, 482);
	glEnd();

}

void sezatoare() {


	glLineWidth(0.7);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(1070, 805);
	glVertex2f(1075, 805);
	glVertex2f(1075, 800);
	glVertex2f(1070, 800);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(1075, 800);
	glVertex2f(1070, 790);
	glVertex2f(1065, 790);
	glVertex2f(1070, 800);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(1075, 800);
	glVertex2f(1075, 797);
	glVertex2f(1070, 790);
	glVertex2f(1070, 787);
	glVertex2f(1065, 790);
	glVertex2f(1065, 787);
	glEnd();
	glFlush();


}

void umbrela() {
	glCallList(regHex2);//umbrela


	glDisable(GL_POINT_SMOOTH);
	glPointSize(50.0);//acoperire umbrela
	glPushMatrix();
	glBegin(GL_POINTS);
	glColor3f(0.99, 0.8, 0.6);
	glVertex2i(200, 477);
	glEnd();


	glColor3f(1, 1, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(199, 506.5);
	glVertex2i(199, 480);
	glEnd();
	glPopMatrix();
}

void construiesteValoriPesti() {
	for (int i = 3000; i <= 100000; i += 100) {
		x_values_pesti[i / 100] = i;
		y_values_pesti[i / 100] = 100 + rand() % 221;
	}
}

void construiesteValoriBombe() {
	for (int i = 2000; i <= 100000; i += 1000) {
		x_values_bombe[i / 100] = i;
		y_values_bombe[i / 100] = 250 + rand() % 221;
	}
}

void init(void)
{

	glClearColor(0.02, 0.208, 0.384, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);
	construiesteValoriPesti();
	construiesteValoriBombe();
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;


	regHex1 = glGenLists(1);

	glNewList(regHex1, GL_COMPILE);

	glBegin(GL_POLYGON);

	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = 100 + 170 * cos(hexTheta);
		hexVertex.y = 600 + 170 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}

	glEnd();

	glEndList();

	regHex2 = glGenLists(1);

	glNewList(regHex2, GL_COMPILE);

	/*glBegin(GL_POLYGON);

	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = 100 + 170 * cos(hexTheta);
		hexVertex.y = 600 + 170 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}

	glEnd();*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 100;
		hexVertex.x = 200 + 20 * cos(hexTheta);
		hexVertex.y = 500 + 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.99, 0.8, 0.6);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 100;
		hexVertex.x = 200 + 5 * cos(hexTheta) + 0.5;
		hexVertex.y = 500 + 5 * sin(hexTheta) + 2;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 100;
		hexVertex.x = 200 + 5 * cos(hexTheta) + 12.5;
		hexVertex.y = 500 + 5 * sin(hexTheta) + 2;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 100;
		hexVertex.x = 200 + 5 * cos(hexTheta) - 11.5;
		hexVertex.y = 500 + 5 * sin(hexTheta) + 2;
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();

	glEndList();
	regHex3 = glGenLists(1);

	glNewList(regHex3, GL_COMPILE);

	glBegin(GL_POLYGON);

	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = 228 + 2 * cos(hexTheta);
		hexVertex.y = 850 + 10 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}

	glEnd();

	glEndList();
	regHex4 = glGenLists(1);

	glNewList(regHex4, GL_COMPILE);

	glBegin(GL_POLYGON);

	for (k = 0; k < 500; k++)
	{
		hexTheta = TWO_PI * k / 500;
		hexVertex.x = 465 + 10 * cos(hexTheta);
		hexVertex.y = 465 + 10 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}

	glEnd();

	glEndList();

	regHex5 = glGenLists(1);
	glNewList(regHex5, GL_COMPILE);
	srand(time(0));
	glBegin(GL_POLYGON);
	for (k = 0; k < 400; k++)
	{
		glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
		hexTheta = TWO_PI * k / 10;
		hexVertex.x = 150 * 0 + 10 * cos(hexTheta);
		hexVertex.y = 298 * 0 + 10 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();
	//----------------------------------------------cercurile cu r pt part2
	regHexr = glGenLists(1);
	glNewList(regHexr, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 500; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 150 * cos(hexTheta);
		hexVertex.y = 75 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex2r = glGenLists(1);
	glNewList(regHex2r, GL_COMPILE);
	glColor3f(0.96, 0.99, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 500; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 15 * cos(hexTheta);
		hexVertex.y = 15 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex2extrar = glGenLists(1);
	glNewList(regHex2extrar, GL_COMPILE);
	glColor3f(1.0, 0.84, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 500; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 20 * cos(hexTheta);
		hexVertex.y = 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();



	regHex3r = glGenLists(1);
	glNewList(regHex3r, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 150 * cos(hexTheta);
		hexVertex.y = 75 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex4r = glGenLists(1);
	glNewList(regHex4r, GL_COMPILE);
	glColor3f(0.96, 0.99, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 15 * cos(hexTheta);
		hexVertex.y = 15 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex4rextrar = glGenLists(1);
	glNewList(regHex4rextrar, GL_COMPILE);
	glColor3f(1.0, 0.84, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 20 * cos(hexTheta);
		hexVertex.y = 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex5r = glGenLists(1);
	glNewList(regHex5r, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 20 * cos(hexTheta);
		hexVertex.y = 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex6r = glGenLists(1);
	glNewList(regHex6r, GL_COMPILE);
	glColor3f(0.96, 0.99, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 1000; k++)
	{
		hexTheta = TWO_PI * k / 1000;
		hexVertex.x = 20 * cos(hexTheta);
		hexVertex.y = 20 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();

	regHex11r = glGenLists(1);

	glNewList(regHex11r, GL_COMPILE);

	glBegin(GL_POLYGON);
	glColor3f(1, 0.80, 0.29);
	for (k = 0; k < 100; k++)
	{
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = 170 * cos(hexTheta);
		hexVertex.y = 170 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}

	glEnd();

	glEndList();
}
// ---------------------------------adaugari pt part 2

//vizor partea de sus submarin
void subp1() {
	//submarin v1

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1230, 600);
	glVertex2f(1175, 600);
	glVertex2f(1175, 580);
	glVertex2f(1200, 580);
	glVertex2f(1200, 550);
	glVertex2f(1230, 550);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(1175, 600);
	glVertex2f(1175, 580);
	glVertex2f(1200, 580);
	glEnd();

}


//desenare prelungire vizor
void subp2() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1200, 550);
	glVertex2f(1230, 550);
	glVertex2f(1230, 500);
	glVertex2f(1200, 500);
	glEnd();

}

//pt desenare cupola submarin

void subp3() {
	int dist = -120;
	glCallList(regHexr);
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(dist, 0, 0);
		glCallList(regHex2extrar);
		glCallList(regHex2r);
		glPopMatrix();
		dist += 60;
	}

}

void subp4() {
	int dist = -120;
	glCallList(regHex3r);
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(dist, 0, 0);
		glCallList(regHex4rextrar);
		glCallList(regHex4r);
		glPopMatrix();
		dist += 60;
	}

}
/// gata desenarea cupolei submarin
boolean neaparut = true;
float h = 0, h2 = 0, orizontala = 0;
float xsoare = 500;
float ysoare = 1000;


void deseneazaScena3(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	//apa - pe care nu s-au sinchisit sa o deseneze
   //culoare aleasa este ce am primit cautand water color in rgb
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.83, 0.94, 0.97);
	glVertex2f(-20, 0);
	glVertex2f(1500, 0);
	glVertex2f(1500, 900);
	glVertex2f(-20, 900);
	glEnd();



	glEnd();
	//---------------------------------------------barca 
	glPushMatrix();

	glTranslated(420, 80, 0);
	glTranslated(k, 100.0, 0.0);
	glTranslated(-420, -80, 0);
	glColor3f(0.8, 0.00, 0.4);
	glBegin(GL_POLYGON); //barca 
	glVertex2f(300, 100);
	glVertex2f(500, 100);
	glVertex2f(450, 70);
	glVertex2f(350, 70);
	glEnd();

	glColor3f(0.67, 0.05, 0.001);
	glBegin(GL_TRIANGLES);
	glVertex2f(300, 105);
	glVertex2f(400, 105);
	glVertex2f(400, 160);
	glEnd();

	glLineWidth(5);
	glColor3f(0.33, 0.33, 0.34);
	glBegin(GL_LINES);
	glVertex2f(420, 100);
	glVertex2f(420, 155);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(440, 100);
	glVertex2f(440, 155);
	glEnd();
	glPopMatrix();


	glColor3f(0.53, 0.74, 0.96); // cer
	glBegin(GL_TRIANGLES);
	glVertex2i(-30, 600);
	glVertex2i(-30, 900);
	glVertex2i(1200, 900);
	glEnd();

	// soarele
	glPushMatrix();
	glTranslated(xsoare, ysoare, 0);
	glCallList(regHex11r);
	glPopMatrix();

	glColor3f(0.03, 0.61, 0.16);
	glBegin(GL_POLYGON); //iarba
	glVertex2i(-30, 600);
	glVertex2i(-30, 300);
	glVertex2i(1500, 900);
	glVertex2i(1200, 900);
	glEnd();
	//-----------------------------------copac
	glLineWidth(7);
	glColor3f(0.4, 0.27, 0.11);
	glBegin(GL_LINES);
	glVertex2f(1300, 830);
	glVertex2f(1300, 850);
	glEnd();

	glColor3f(0.07, 0.36, 0.12);
	glBegin(GL_TRIANGLES);
	glVertex2i(1280, 850);
	glVertex2i(1320, 850);
	glVertex2i(1300, 895);
	glEnd();



	//-----------------------------------casa 
	glColor3f(0.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(1200, 820); //colt stanga jos
	glVertex2i(1230, 820); //colt dreapta jos
	glVertex2i(1230, 850); //colt dreapta sus
	glVertex2i(1200, 850); //colt stanga sus
	glEnd();
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(1200, 850);
	glVertex2i(1230, 850);
	glVertex2i(1215, 870);
	glEnd();
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON); // usa casa
	glVertex2i(1212, 820); //colt stanga jos + 12
	glVertex2i(1218, 820); //colt dreapta jos + 18
	glVertex2i(1218, 840); //colt dreapta sus + h= 20
	glVertex2i(1212, 840); //colt stanga sus + h = 20
	glEnd();
	//-------------------------------------


	// reflector

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(400, 500);
	glVertex2i(450, 525);
	glVertex2i(450, 575);
	glVertex2i(400, 550);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(400, 550);
	glVertex2i(450, 575);
	glVertex2i(450, 600);
	glVertex2i(400, 575);
	glEnd();

	if (neaparut == true) {
		if (h < 10) {
			glPushMatrix();
			glTranslated(0, h, 0); //ridic capatul vizorului
			subp1();
		}
		glPopMatrix();
		if (h >= 10 && h < 20) {
			glTranslated(0, h, 0); //ridic capatul vizorului

			glPushMatrix();
			glTranslated(1255, 550, 0);
			glRotated(180, 0, 0, 1);
			glRotated(180, 1, 0, 0);
			glTranslated(-1175, -550, 0);
			subp1();
			glPopMatrix();

			subp2();	//pun stalpul
			glPopMatrix();

		}

		if (h >= 20 && h < 30) {
			glTranslated(0, h, 0); //ridic capatul vizorului
			subp1();
			subp2();	//pun stalpul
			glPopMatrix();
			glPushMatrix();
			glTranslated(1235, 450, 0);
			subp3();
			glPopMatrix();

		}

		if (h >= 30) {
			glPushMatrix();
			glTranslated(orizontala, 0, 0);
			glPushMatrix();
			glTranslated(0, h, 0); //ridic capatul vizorului
			subp1();
			subp2();	//pun stalpul
			glPopMatrix();
			glPushMatrix();
			glTranslated(1235, 460, 0);
			subp4();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}

		if (orizontala <= -400) {
			neaparut = false;
		}

	}
	else {

		if (h2 >= -10) {
			glPushMatrix();
			glTranslated(0.0, h2, 0.0);

			glPushMatrix();
			glTranslated(orizontala, 0, 0);
			glPushMatrix();
			glTranslated(0, h, 0);
			subp1();
			subp2();
			glPopMatrix();
			glPushMatrix();
			glTranslated(1235, 460, 0);
			subp4();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}
		if (h2 <= -10 && h2 >= -20) {
			glPushMatrix();
			glTranslated(0.0, h2, 0.0);

			glPushMatrix();
			glTranslated(orizontala, 0, 0);
			glPushMatrix();
			glTranslated(0, h, 0);
			subp1();
			subp2();
			glPopMatrix();
			glPushMatrix();
			glTranslated(1235, 460, 0);
			subp3();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}

		if (h2 < -20 && h2 >= -30) {
			glPushMatrix();
			glTranslated(0.0, h2, 0.0);

			glPushMatrix();
			glTranslated(orizontala, 0, 0);
			glPushMatrix();
			glTranslated(0, h, 0);
			subp1();
			subp2();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();


		}
		if (h2 <= 30 && h2 >= -40) {
			glPushMatrix();
			glTranslated(0.0, h2, 0.0);

			glPushMatrix();
			glTranslated(orizontala, 0, 0);
			glPushMatrix();
			glTranslated(0, h, 0);
			subp1();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();

		}

	}



	//glutSwapBuffers();
	//glFlush();
}
void miscaCMP(void)
{
	//miscare barci
	k = k + alpha;
	if (k > 1000.0)
		alpha = -1.0;
	else if (k < 0.0)
		alpha = 1.0;

	if (h <= 30) {
		h += 0.1;
	}
	if (h > 30 && orizontala >= -400) {
		orizontala -= 0.7;
	}

	if (orizontala < -400 && h2 >= -40) {
		h2 -= 0.1;
	}

	if (xsoare > 100) {
		xsoare -= 0.3;
		ysoare = xsoare + 500;
	}


	glutPostRedisplay();
}


int xclick, yclick;

void mouseCMP(int button, int state, int mx, int my)
{

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = -1.0; glutIdleFunc(miscaCMP);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			xclick = mx + 90;
			yclick = 900 - my;//schimbam in functie de ecran
			cout << xclick << " " << yclick << endl;
		}
	default:
		break;
	}
}

void deseneazaPasare() {
	scrPt vertex;
	GLdouble theta;
	GLint p;


	//cap
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (p = 0; p < 500; p++)
	{
		theta = TWO_PI * p / 500;
		vertex.x = 300 + 11 * cos(theta);
		vertex.y = 250 + 11 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	//ochiul
	glPointSize(3);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(305, 252);
	glEnd();

	//cioc
	glColor3f(1, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(310, 245);
	glVertex2i(330, 245);
	glVertex2i(310, 255);
	glEnd();

	//gat
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2i(275, 245);
	glVertex2i(295, 245);
	glVertex2i(295, 255);
	glVertex2i(275, 255);
	glEnd();

	//corp
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	for (p = 0; p < 50; p++)
	{
		theta = TWO_PI * p / 50;
		vertex.x = 245 + 40 * cos(theta);
		vertex.y = 250 + 20 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	//aripa
	glColor3f(1, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(260, 250);
	glVertex2i(220, 250);
	glVertex2i(260, 260);
	glEnd();

	//picioare
	glLineWidth(3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(205, 250);
	glVertex2f(195, 240);

	glVertex2f(205, 250);
	glVertex2f(195, 260);

	glEnd();

}





void desenPasare2(void)
{
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(10.0);
	glPushMatrix();
	glTranslated(xclick, yclick, 0);
	glTranslated(-360, -250, 0);
	deseneazaPasare();
	glPopMatrix();
}


/// ----------------------------adaugari pt part 2 final
void deseneazaAMOGUS() {
	glColor3f(0.9, 0.1, 0.1);//casca
	glBegin(GL_POLYGON);
	glVertex2f(z, c);
	glVertex2f(z + 5, c - 1);
	glVertex2f(z + 8, c - 4);
	glVertex2f(z + 10, c - 8);
	glVertex2f(z + 10, c - 15);
	glVertex2f(z - 10, c - 15);
	glVertex2f(z - 10, c - 8);
	glVertex2f(z - 8, c - 4);
	glVertex2f(z - 5, c - 1);
	glEnd();

	glLineWidth(2);
	glColor3f(0, 0, 0);//casca contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z, c);
	glVertex2f(z + 5, c - 1);
	glVertex2f(z + 8, c - 4);
	glVertex2f(z + 10, c - 8);
	glVertex2f(z + 10, c - 15);
	glVertex2f(z - 10, c - 15);
	glVertex2f(z - 10, c - 8);
	glVertex2f(z - 8, c - 4);
	glVertex2f(z - 5, c - 1);
	glEnd();

	glColor3f(0, 0, 1);//vizor
	glBegin(GL_POLYGON);
	glVertex2f(z + 8, c - 4);
	glVertex2f(z + 11, c - 4);
	glVertex2f(z + 13, c - 5);
	glVertex2f(z + 14, c - 7);
	glVertex2f(z + 12, c - 10);
	glVertex2f(z + 9, c - 10.5);
	glVertex2f(z + 3, c - 10.5);
	glVertex2f(z + 1, c - 9);
	glVertex2f(z, c - 7);
	glVertex2f(z + 1, c - 4);
	glVertex2f(z + 4, c - 4);
	glEnd();



	glColor3f(0, 0, 0);//vizor contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z + 8, c - 4);
	glVertex2f(z + 11, c - 4);
	glVertex2f(z + 13, c - 5);
	glVertex2f(z + 14, c - 7);
	glVertex2f(z + 12, c - 10);
	glVertex2f(z + 9, c - 10.5);
	glVertex2f(z + 3, c - 10.5);
	glVertex2f(z + 1, c - 9);
	glVertex2f(z, c - 7);
	glVertex2f(z + 1, c - 4);
	glVertex2f(z + 4, c - 4);
	glEnd();

	glColor3f(0.9, 0.1, 0.1);//corp
	glBegin(GL_POLYGON);
	glVertex2f(z + 10, c - 15);
	glVertex2f(z + 10, c - 31);

	glVertex2f(z - 10, c - 31);
	glVertex2f(z - 10, c - 15);

	glEnd();

	glColor3f(0, 0, 0); //corp contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z + 10, c - 15);
	glVertex2f(z + 10, c - 31);
	glVertex2f(z - 10, c - 31);
	glVertex2f(z - 10, c - 15);
	glEnd();

	glColor3f(0.9, 0.1, 0.1);//pcioar1
	glBegin(GL_POLYGON);
	glVertex2f(z + 10, c - 31);
	glVertex2f(z + 10, c - 35);
	glVertex2f(z + 4, c - 35);
	glVertex2f(z + 4, c - 31);
	glEnd();

	glColor3f(0, 0, 0); //pcioar1 contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z + 10, c - 31);
	glVertex2f(z + 10, c - 35);
	glVertex2f(z + 4, c - 35);
	glVertex2f(z + 4, c - 31);
	glEnd();

	glColor3f(0.9, 0.1, 0.1);//pcioar2
	glBegin(GL_POLYGON);
	glVertex2f(z - 10, c - 31);
	glVertex2f(z - 10, c - 35);
	glVertex2f(z - 4, c - 35);
	glVertex2f(z - 4, c - 31);
	glEnd();

	glColor3f(0, 0, 0); //pcioar2 contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z - 10, c - 31);
	glVertex2f(z - 10, c - 35);
	glVertex2f(z - 4, c - 35);
	glVertex2f(z - 4, c - 31);
	glEnd();

	//glColor3f(0.9, 0.1, 0.1);//corp+ pcioare
	//glBegin(GL_POLYGON);
	//glVertex2f(z + 10, c - 15);
	//glVertex2f(z + 10, c - 35);
	//glVertex2f(z + 4, c - 35);
	//glVertex2f(z + 4, c - 31);
	//glVertex2f(z - 4, c - 31);
	//glVertex2f(z - 4, c - 35);
	//glVertex2f(z - 10, c - 35);
	//glVertex2f(z - 10, c - 15);

	//glEnd();

	glColor3f(0.9, 0.1, 0.1);//jetpack 
	glBegin(GL_POLYGON);

	glVertex2f(z - 10, c - 13);
	glVertex2f(z - 15, c - 14);
	glVertex2f(z - 15, c - 24);
	glVertex2f(z - 10, c - 25);
	glEnd();

	glColor3f(0, 0, 0); //jetpack  contur
	glBegin(GL_LINE_LOOP);
	glVertex2f(z - 10, c - 31);
	glVertex2f(z - 10, c - 35);
	glVertex2f(z - 4, c - 35);
	glVertex2f(z - 4, c - 31);
	glEnd();


}
int genereazaafon() {
	int nrrandom = rand() % (1 - 0 + 1) + 0;
	return nrrandom;
}

void deseneazaScena2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	glBegin(GL_POLYGON);

	//glColor3f(212.0, 241.0, 249.0);
	// ^^^^^^ nu stiu de voi dar mie imi deseneaza alb, cica e cyan, asa ca am ales altceva

	glColor3f(0.80, 0.70, 0.98); // tot alb ? nani

	glVertex2f(-20, 0);
	glVertex2f(1500, 0);
	glVertex2f(1500, 900);
	glVertex2f(-20, 900);
	glEnd();



	glMatrixMode(GL_MODELVIEW);

	//---------------------------------------------barca 
	glPushMatrix();

	glTranslated(420, 80, 0);
	glTranslated(k, 100.0, 0.0);
	glTranslated(-420, -80, 0);
	glColor3f(0.015, 0.007, 0.58);
	glBegin(GL_POLYGON); //barca 
	glVertex2f(300, 100);
	glVertex2f(500, 100);
	glVertex2f(450, 70);
	glVertex2f(350, 70);
	glEnd();


	glColor3f(0.67, 0.05, 0.001);
	glBegin(GL_TRIANGLES);
	glVertex2f(300, 105);
	glVertex2f(400, 105);
	glVertex2f(400, 160);
	glEnd();

	glLineWidth(5);
	glColor3f(0.33, 0.33, 0.34);
	glBegin(GL_LINES);
	glVertex2f(420, 100);
	glVertex2f(420, 155);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(440, 100);
	glVertex2f(440, 155);
	glEnd();
	glPopMatrix();


	glColor3f(1, 0.67, 0.29); // cer
	glBegin(GL_TRIANGLES);
	glVertex2i(-30, 600);
	glVertex2i(-30, 900);
	glVertex2i(1200, 900);
	glEnd();

	glColor3f(1, 0.80, 0.29);
	glCallList(regHex1);
	glPopMatrix();





	glColor3f(0.99, 0.8, 0.6);
	glBegin(GL_POLYGON); //plaja
	glVertex2i(-30, 600);
	glVertex2i(-30, 300);
	glVertex2i(1500, 900);
	glVertex2i(1200, 900);
	glEnd();



	glCallList(regHex2);//umbrela


	glDisable(GL_POINT_SMOOTH);
	glPointSize(50.0);//acoperire umbrela

	glBegin(GL_POINTS);
	glColor3f(0.99, 0.8, 0.6);
	glVertex2i(200, 477);
	glEnd();



	glColor3f(1, 1, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(199, 506.5);
	glVertex2i(199, 480);
	glEnd();

	//-----------------------------------copac

	glLineWidth(7);
	glColor3f(0.4, 0.27, 0.11);
	glBegin(GL_LINES);
	glVertex2f(1300, 830);
	glVertex2f(1300, 860);
	glEnd();

	glColor3f(0.07, 0.36, 0.12);
	glBegin(GL_POLYGON);
	glVertex2f(1300, 853);
	glVertex2f(1295, 851);
	glVertex2f(1289, 847);
	glVertex2f(1289, 854);
	glVertex2f(1283, 852);
	glVertex2f(1287, 859);
	glVertex2f(1293, 861);
	glVertex2f(1289, 864);
	glVertex2f(1283, 864);
	glVertex2f(1289, 867);
	glVertex2f(1297, 866);
	glVertex2f(1302, 871);
	glVertex2f(1310, 872);
	glVertex2f(1307, 868);
	glVertex2f(1305, 863);
	glVertex2f(1312, 863);
	glVertex2f(1317, 860);
	glVertex2f(1310, 858);
	glVertex2f(1316, 850);
	glVertex2f(1310, 852);
	glVertex2f(1304, 854);
	glEnd();


	//-----------------------------------casa 

	glColor3f(0.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(1200, 820); //colt stanga jos
	glVertex2i(1230, 820); //colt dreapta jos
	glVertex2i(1230, 850); //colt dreapta sus
	glVertex2i(1200, 850); //colt stanga sus
	glEnd();
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(1200, 850);
	glVertex2i(1230, 850);
	glVertex2i(1215, 870);
	glEnd();
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON); // usa casa
	glVertex2i(1212, 820); //colt stanga jos + 12
	glVertex2i(1218, 820); //colt dreapta jos + 18
	glVertex2i(1218, 840); //colt dreapta sus + h= 20
	glVertex2i(1212, 840); //colt stanga sus + h = 20
	glEnd();

	//-------------------------------------
	//BALENUUU

	glColor3f(0.001, 0.53, 0.98);

	glBegin(GL_POLYGON);
	glVertex2i(770, 300);//E
	glVertex2i(725, 340);
	glVertex2i(695, 423);
	glVertex2i(741, 512);
	glVertex2i(853, 538);
	glVertex2i(977, 516);
	glVertex2i(1051, 426);//O
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(1051, 426);//O
	glVertex2i(1163, 390);
	glVertex2i(1178, 300);
	glVertex2i(770, 300);//E
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(1163, 390);//P
	glVertex2i(1192, 546);
	glVertex2i(1235, 535);
	glVertex2i(1226, 334);
	glVertex2i(1178, 300);//K1

	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(1192, 546);
	glVertex2i(1144, 583);
	glVertex2i(1136, 637);
	glVertex2i(1187, 618);
	glVertex2i(1227, 566);
	glVertex2i(1237, 617);

	glVertex2i(1285, 617);
	glVertex2i(1279, 572);
	glVertex2i(1235, 535);
	glVertex2i(1226, 334);
	glVertex2i(1178, 300);

	glEnd();


	//----------------------

	glEnable(GL_POINT_SMOOTH); // Ociu
	glPointSize(80.0);
	glBegin(GL_POINTS);
	glEnable(GL_POINT_SMOOTH);
	glColor3f(1, 1, 1);
	glVertex2i(800, 459);
	glEnd();

	glPushMatrix();
	glTranslated(k / 70, 0, 0.0);
	glPointSize(30.0);// Pupila
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2i(790, 449);
	glEnd();
	glPopMatrix();
	glPointSize(1);
	glColor3f(0.001, 0.40, 0.98);
	glBegin(GL_POLYGON);
	glVertex2i(710, 380);
	glVertex2i(790, 380);


	glVertex2i(770, 300);
	glVertex2i(725, 340);
	glEnd();
	glBegin(GL_POLYGON);

	glVertex2i(790, 380);
	glVertex2i(793, 400);
	glVertex2i(793, 400);
	glVertex2i(840, 400);
	glVertex2i(830, 350);
	glVertex2i(770, 300);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex2i(934, 325);
	glVertex2i(962, 308);
	glVertex2i(979, 266);
	glVertex2i(936, 284);


	glEnd();
	deseneazaAMOGUS();
	//AVION

	glPushMatrix();
	glTranslated(100, 0, 0);
	umbrela();
	glTranslated(-100, 0, 0);
	umbrela();
	glTranslated(-100, 0, 0);
	umbrela();
	glTranslated(0, 100, 0);
	umbrela();
	glTranslated(100, 0, 0);
	umbrela();
	glTranslated(100, 0, 0);
	umbrela();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 0);
	glTranslated(-850, -310, 0);
	sezatoare();
	glTranslated(-40, 0, 0);
	sezatoare();
	glTranslated(-60, 0, 0);
	sezatoare();
	glTranslated(-40, 0, 0);
	sezatoare();
	glTranslated(200, 0, 0);
	sezatoare();
	glTranslated(40, 0, 0);
	sezatoare();
	glTranslated(0, 100, 0);
	sezatoare();
	glTranslated(-40, 0, 0);
	sezatoare();
	glTranslated(-200, 0, 0);
	sezatoare();
	glTranslated(40, 0, 0);
	sezatoare();
	glTranslated(100, 0, 0);
	sezatoare();
	glTranslated(-40, 0, 0);
	sezatoare();
	glPopMatrix();

	srand(time(0));

	glPushMatrix();
	glTranslated(0, 100, 0);
	omu((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);//1
	glTranslated(100, 20, 0);
	omu((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);//2
	glTranslated(160, 140, 0);
	omu((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);//3
	glTranslated(90, 40, 0);
	omu((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);//4
	glTranslated(90, -50, 0);
	omu((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);//5

	glPopMatrix();

	glPushMatrix();

	glTranslated(ml, 0, 0);
	glTranslated(488, 610, 0);
	glRotated(mi, 0, 0, 1);

	glCallList(regHex5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-300, 0, 0);
	glTranslated(b, 0.0, 0.0);

	if (genereazaafon() == 1) {

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2i(217, 862);
		glVertex2i(223, 858);
		glVertex2i(224, 853);
		glVertex2i(224, 848);
		glVertex2i(223, 841);
		glVertex2i(217, 838);

		glEnd();


		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2i(202, 866);
		glVertex2i(217, 862);
		glVertex2i(217, 838);
		glVertex2i(202, 835);

		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2i(202, 866);
		glVertex2i(195, 867);
		glVertex2i(185, 863);
		glVertex2i(163, 865);
		glVertex2i(147, 870);
		glVertex2i(129, 868);
		glVertex2i(120, 868);
		glVertex2i(105, 864);
		glVertex2i(109, 857);
		glVertex2i(122, 849);
		glVertex2i(146, 836);
		glVertex2i(155, 834);
		glVertex2i(186, 834);
		glVertex2i(202, 835);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2i(120, 868);
		glVertex2i(110, 880);
		glVertex2i(98, 883);
		glVertex2i(105, 864);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2i(109, 857);
		glVertex2i(103, 853);
		glVertex2i(122, 849);

		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2i(151, 855);
		glVertex2i(176, 853);
		glVertex2i(186, 850);
		glVertex2i(192, 846);
		glVertex2i(186, 842);
		glVertex2i(176, 840);
		glVertex2i(133, 838);

		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2i(224, 853);
		glVertex2i(228, 852);
		glVertex2i(228, 849);
		glVertex2i(224, 848);


		glEnd();

		glColor3f(0, 0, 1);
		glCallList(regHex3);
		//glPopMatrix();




		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(105, 864);
		glVertex2i(70, 864);
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2i(70, 875);
		glVertex2i(70, 850);
		glVertex2i(-60, 850);
		glVertex2i(-60, 875);
		glEnd();

		glColor3f(0, 0, 1);
		glRasterPos2i(-55, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
		glRasterPos2i(-35, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
		glRasterPos2i(-15, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Q');
		glRasterPos2i(5, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '&');
		glRasterPos2i(25, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'L');
		glRasterPos2i(40, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'U');
		glRasterPos2i(58, 855);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');

		glPopMatrix();
	}
	else {
		//glScaled(0.5, 0.5, 1);
		glTranslated(-900, 200, 0);
		deseneazaAvion();
		glPopMatrix();
	}


	glutSwapBuffers();
	glFlush();
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}

bool verificaDacaBombaPescuita(float x1, float x2, float y1, float y2, int i) {
	if (!prins_peste && 540.0 + miscare_laterala > x1 + k_peste && 540.0 + miscare_laterala < x2 + k_peste
		&& 540.0 + transf_hook > y1 && 540.0 + transf_hook < y2) {
		return true;
	}
	return false;
}

// ----------------------------------------------------------------------------------BOMBA
void deseneazaBomba(int coordX = 800, int coordY = 300, int index = 0) {
	scrPt vertex;
	GLdouble theta;
	GLint p;

	if (verificaDacaBombaPescuita(coordX - 40, coordX + 80, coordY - 130, coordY - 10, index)) {
		stopGame = true;
		char _score[10];
		_itoa_s(score, _score, 10);
		char text[50] = "GAME OVER\nYour score: ";
		strcat_s(text, _score);
		RenderString(650.0f, 500.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)text);
	}

	glPushMatrix();

	glTranslatef(k_peste, 0.0, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(coordX, coordY);
	glVertex2f(coordX + 40, coordY);
	glVertex2f(coordX + 40, coordY - 40);
	glVertex2f(coordX, coordY - 40);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (p = 0; p < 50; p++)
	{
		theta = TWO_PI * p / 50;
		vertex.x = coordX + 20 + 60 * cos(theta);
		vertex.y = coordY - 70 + 60 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (p = 0; p < 50; p++)
	{
		theta = TWO_PI * p / 50;
		vertex.x = coordX - 5 + 10 * cos(theta);
		vertex.y = coordY - 40 + 10 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glLineWidth(4);
	glColor3f(0.396, 0.263, 0.129);
	glBegin(GL_LINES);
	glVertex2f(coordX + 20, coordY);
	glVertex2f(coordX + 20, coordY + 20);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (p = 0; p < 50; p++)
	{
		theta = TWO_PI * p / 50;
		vertex.x = coordX + 20 + 5 * cos(theta);
		vertex.y = coordY + 25 + 5 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glPopMatrix();
}

void deseneazaBombe() {
	for (int i = 0; i < sizeof x_values_bombe / sizeof x_values_bombe[0]; i++) {
		deseneazaBomba(x_values_bombe[i], y_values_bombe[i], i);
	}
}

////----------------------------------------------------------------LUNA
void deseneazaLuna() {
	scrPt vertex;
	GLdouble theta;
	GLint k;

	glColor3f(0.8471, 0.8392, 0.7961);
	glBegin(GL_POLYGON);
	for (k = 0; k < 500; k++)
	{
		theta = TWO_PI * k / 500;
		vertex.x = 1300 + 100 * cos(theta);
		vertex.y = 775 + 100 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
	for (k = 0; k < 500; k++)
	{
		theta = TWO_PI * k / 500;
		vertex.x = 1250 + 100 * cos(theta);
		vertex.y = 825 + 100 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();
}

bool verificaDacaPestePescuit(float x1, float x2, float y1, float y2, int i) {
	float misca_pestele = 0.0;
	if ((prins_peste && coordX1_peste_prins == x_values_pesti[i] - 20 && coordX2_peste_prins == x_values_pesti[i] + 20 && coordY1_peste_prins == y_values_pesti[i] - 20 && coordY2_peste_prins == y_values_pesti[i] + 20)) {
		return true;
	}
	if ((prins_peste && (coordX1_peste_prins != x_values_pesti[i] - 20 || coordX2_peste_prins != x_values_pesti[i] + 20 || coordY1_peste_prins != y_values_pesti[i] - 20 || coordY2_peste_prins != y_values_pesti[i] + 20))) {
		return false;
	}
	if (540.0 + miscare_laterala > x1 + k_peste && 540.0 + miscare_laterala < x2 + k_peste
		&& 540.0 + transf_hook > y1 && 540.0 + transf_hook < y2) {
		prins_peste = true;
		coordX1_peste_prins = x_values_pesti[i] - 20;
		coordX2_peste_prins = x_values_pesti[i] + 20;
		coordY1_peste_prins = y_values_pesti[i] - 20;
		coordY2_peste_prins = y_values_pesti[i] + 20;
		transf_hook_prindere = transf_hook;
		miscare_laterala_prindere = miscare_laterala;
		k_peste_prins = k_peste;
		return true;
	}
	return false;
}

bool verificaDacaPesteAjunsPeBarca(float x1, float x2, float y1, float y2, int i) {
	float misca_pestele = 0.0;
	if ((prins_peste && coordX1_peste_prins == x_values_pesti[i] - 20 && coordX2_peste_prins == x_values_pesti[i] + 20 && coordY1_peste_prins == y_values_pesti[i] - 20 && coordY2_peste_prins == y_values_pesti[i] + 20) && miscare_verticala_undita < 1.0) {
		prins_peste = false;
		coordX1_peste_prins = -2000.0;
		coordY1_peste_prins = -2000.0;
		coordX2_peste_prins = -2000.0;
		coordY2_peste_prins = -2000.0;
		pesti_prinsi[i] = 1;
		score += 300.0;
		return true;
	}
	return false;
}

////-----------------------------------------------------------------------PESTE
void deseneazaPeste(int coordX = 800, int coordY = 300, int index = 0) {
	scrPt vertex;
	GLdouble theta;
	GLint p;
	float misca_pestele = 0.0;
	float misca_pestele_laterala = 0.0;
	if (prins_peste) {
		glPushMatrix();
		glTranslatef(0.0, transf_scor, 0.0);
		RenderString(1200.0f, 825.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"+300");
		transf_scor += 0.001;
		glPopMatrix();
	}
	else {
		transf_scor = 0.0;
	}
	if (verificaDacaPesteAjunsPeBarca(coordX - 40, coordX + 40, coordY - 20, coordY + 20, index)) {
		misca_pestele = -5000.0;
		misca_pestele_laterala = -5000.0;
	}
	else if (verificaDacaPestePescuit(coordX - 40, coordX + 40, coordY - 20, coordY + 20, index)) {
		misca_pestele = transf_hook - transf_hook_prindere;
		misca_pestele_laterala = k_peste_prins + miscare_laterala - miscare_laterala_prindere;
	}
	else {
		misca_pestele_laterala = k_peste;
	}

	glPushMatrix();

	glTranslatef(misca_pestele_laterala, misca_pestele, 0.0);

	//coada peste
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.3, 0.7);
	glVertex2f(coordX + 20, coordY);
	glVertex2f(coordX + 70, coordY + 30);
	glVertex2f(coordX + 70, coordY - 30);
	glEnd();

	//aripa peste
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.3, 0.7);
	glVertex2i(coordX, coordY + 35);
	glVertex2i(coordX + 15, coordY + 15);
	glVertex2i(coordX - 15, coordY + 15);
	glEnd();

	//oval peste
	glColor3f(1, 0.3, 0.5);
	glBegin(GL_POLYGON);
	for (p = 0; p < 50; p++)
	{
		theta = TWO_PI * p / 50;
		vertex.x = coordX + 40 * cos(theta);
		vertex.y = coordY + 20 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	//solzi peste
	glLineWidth(1);
	glColor3f(1, 0.35, 0.7);
	glBegin(GL_LINES);
	glVertex2f(coordX, coordY + 2);
	glVertex2f(coordX + 15, coordY + 7);
	glVertex2f(coordX, coordY + 2);
	glVertex2f(coordX + 15, coordY - 3);
	glEnd();

	glLineWidth(1);
	glColor3f(1, 0.35, 0.7);
	glBegin(GL_LINES);
	glVertex2f(coordX + 6, coordY + 2);
	glVertex2f(coordX + 21, coordY + 7);
	glVertex2f(coordX + 6, coordY + 2);
	glVertex2f(coordX + 21, coordY + 7);
	glEnd();


	//ochi peste
	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(coordX - 30, coordY + 5);
	glEnd();

	glPopMatrix();
}

////------------------------------------------------------------------------ BANC PESTI
void deseneazaBancPesti() {

	for (int i = 0; i < sizeof x_values_pesti / sizeof x_values_pesti[0]; i++) {
		if (pesti_prinsi[i] != 1)
			deseneazaPeste(x_values_pesti[i], y_values_pesti[i], i);
	}
}

////------------------------------------------------------------------------STELUTA
void deseneazaSteluta(float x, float y) {
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);

	glVertex2f(x, y);
	glVertex2f(x + 5, y + 10);
	glVertex2f(x + 10, y);
	glVertex2f(x + 20, y - 5);
	glVertex2f(x + 10, y - 10);
	glVertex2f(x + 5, y - 20);
	glVertex2f(x, y - 10);
	glVertex2f(x - 10, y - 5);

	glEnd();
}


////------------------------------------------------------------------------PERDEA STELE
void deseneazaPerdeaDeStelute() {
	float x_values[] = { 0, 55, 0, 290, 78, 124, 230, 215, 180, 340, 450, 550, 650, 760, 880, 1000, 37, 85, 378, 481, 500, 290, 584, 690, 720, 800, 915, 1100, 1050, 965, 1450, 1190, 1120, 1420 };
	float y_values[] = { 675, 700, 850, 775, 870, 670, 723, 815, 766, 679, 723, 845, 765, 880, 769, 845, 777, 800, 790, 788, 845, 875, 699, 704, 780, 699, 744, 778, 690, 870, 757, 670, 860, 888 };

	for (int i = 0; i < sizeof x_values / sizeof x_values[0]; i++) {
		deseneazaSteluta(x_values[i], y_values[i]);
	}
}

////------------------------------------------------------------------------------COPACI
void deseneazaCopac(float x, float y) {
	glLineWidth(7);
	glColor3f(0.8, 0.4, 0.2);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x, y + 20);
	glEnd();

	glColor3f(0.15, 0.7, 0.25);
	glBegin(GL_TRIANGLES);
	glVertex2i(x - 20, y + 20);
	glVertex2i(x + 20, y + 20);
	glVertex2i(x, y + 65);
	glEnd();
}

////----------------------------------------------------------------------------CODRU
void deseneazaCodru() {
	float x_values[] = { 1050, 1284, 1450, 1157, 957, 874, 1300, 1400 }; // (-30;1500)
	float y_values[] = { 560, 570, 580, 590, 600, 610, 620, 630, 530 }; // (550;650)

	for (int i = 0; i < sizeof x_values / sizeof x_values[0]; i++) {
		deseneazaCopac(x_values[i], y_values[i]);
	}

}

////------------------------------------------------------------------------------COPIL
void deseneazaCopil() {
	scrPt vertex;
	GLdouble theta;
	GLint c;

	//corp
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(635, 622);
	glVertex2i(665, 622);
	glVertex2i(650, 642);
	glEnd();

	//cap
	glColor3f(0.8471, 0.8392, 0.7961);
	glBegin(GL_POLYGON);
	for (c = 0; c < 500; c++)
	{
		theta = TWO_PI * c / 500;
		vertex.x = 650 + 10 * cos(theta);
		vertex.y = 650 + 10 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	//ochii
	glPointSize(3);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(645, 652);
	glVertex2i(655, 652);
	glEnd();

	//gura
	glLineWidth(1.2);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(645, 644);
	glVertex2f(655, 644);
	glEnd();

	//maini
	glLineWidth(2);
	glColor3f(0.89, 0.82, 0.768);
	glBegin(GL_LINES);
	glVertex2f(655, 632);
	glVertex2f(665, 642);
	glVertex2f(645, 632);
	glVertex2f(640, 622);
	glEnd();

	//picioare
	glLineWidth(2);
	glColor3f(0.89, 0.82, 0.768);
	glBegin(GL_LINES);
	glVertex2f(645, 622);
	glVertex2f(645, 612);
	glVertex2f(655, 622);
	glVertex2f(655, 612);
	glEnd();

	//balon
	glLineWidth(3);
	glColor3f(0.3, 0.2, 0.8);
	glBegin(GL_LINES);
	glVertex2f(665, 642);
	glVertex2f(675, 662);
	glEnd();

	glColor3f(0.54, 0.2, 0.5);
	glBegin(GL_POLYGON);
	for (c = 0; c < 500; c++)
	{
		theta = TWO_PI * c / 500;
		vertex.x = 669 + 9 * cos(theta);
		vertex.y = 669 + 9 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

}

void miscaPeste(void)
{
	if (!stopGame) {
		//miscare pesti
		k_peste = k_peste - beta;
		if (k_peste < -20.0)
			beta = 0.3;
		else if (k_peste > 1000.0)
			beta = -0.3;

		glutPostRedisplay();
	}

}

void deseneazaScena(void)
{
	scrPt vertex;
	GLdouble theta;
	GLint c;

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glLoadIdentity();

	//-----------------------------------iarba
	glColor3f(0.0, 0.3216, 0.1294);
	glBegin(GL_POLYGON);
	glVertex2i(-30, 650);
	glVertex2i(-30, 550);
	glVertex2i(1500, 550);
	glVertex2i(1500, 650);
	glEnd();

	//-----------------------------------cer
	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2i(-30, 650);
	glVertex2i(-30, 900);
	glVertex2i(1500, 900);
	glVertex2i(1500, 650);
	glEnd();


	//-----------------------------------codru
	deseneazaCodru();

	//---------------------------------------------barca 
	glPushMatrix();

	glTranslated(miscare_laterala, 100.0, 0.0);
	glColor3f(0.015, 0.007, 0.58);
	glBegin(GL_POLYGON); //barca 
	glVertex2f(300, 430);
	glVertex2f(500, 430);
	glVertex2f(450, 400);
	glVertex2f(350, 400);
	glEnd();

	glColor3f(0.67, 0.05, 0.001);
	glBegin(GL_TRIANGLES);
	glVertex2f(300, 435);
	glVertex2f(400, 435);
	glVertex2f(400, 490);
	glEnd();

	glLineWidth(5);
	glColor3f(0.33, 0.33, 0.34);
	glBegin(GL_LINES);
	glVertex2f(420, 430);
	glVertex2f(420, 485);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(440, 430);
	glVertex2f(440, 485);
	glEnd();

	//corp
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(450, 442);
	glVertex2i(480, 442);
	glVertex2i(465, 462);
	glEnd();

	//cap
	glColor3f(0.8471, 0.8392, 0.7961);
	glBegin(GL_POLYGON);
	for (c = 0; c < 500; c++)
	{
		theta = TWO_PI * c / 500;
		vertex.x = 465 + 10 * cos(theta);
		vertex.y = 465 + 10 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();


	//ochii
	glPointSize(3);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(469, 468);
	glVertex2i(459, 468);
	glEnd();

	//gura
	glLineWidth(1.2);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(459, 460);
	glVertex2f(469, 460);
	glEnd();

	//maini
	glLineWidth(2);
	glColor3f(0.89, 0.82, 0.768);
	glBegin(GL_LINES);
	glVertex2f(472, 452);
	glVertex2f(482, 462);
	glVertex2f(457, 452);
	glVertex2f(447, 442);
	glEnd();

	//picioare
	glLineWidth(2);
	glColor3f(0.89, 0.82, 0.768);
	glBegin(GL_LINES);
	glVertex2f(460, 442);
	glVertex2f(460, 432);
	glVertex2f(470, 442);
	glVertex2f(470, 432);
	glEnd();

	//----------------------------------undita
	glLineWidth(3);
	glColor3f(0.3, 0.2, 0.8);
	glBegin(GL_LINES);
	glVertex2f(482, 462);
	glVertex2f(540, 510);
	glEnd();

	glPushMatrix();

	glTranslatef(540.0, 510.0, 0.0);
	glScalef(1.0, miscare_verticala_undita, 1.0);
	glTranslatef(-540.0, -510.0, 0.0);

	glLineWidth(3);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(540, 510);
	glVertex2f(540, 450);
	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0, transf_hook, 0.0);

	glLineWidth(2);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(540, 450);
	glVertex2f(540, 440);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (c = 0; c < 500; c++)
	{
		theta = TWO_PI * c / 500;
		vertex.x = 542 + 10 * cos(theta);
		vertex.y = 434 + 10 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glColor3f(0.02, 0.208, 0.384);
	glBegin(GL_POLYGON);
	for (c = 0; c < 500; c++)
	{
		theta = TWO_PI * c / 500;
		vertex.x = 547 + 10 * cos(theta);
		vertex.y = 435 + 10 * sin(theta);
		glVertex2i(vertex.x, vertex.y);
	}
	glEnd();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//-----------------------------------luna
	deseneazaLuna();

	//-----------------------------------banc pesti
	glPushMatrix();
	deseneazaBancPesti();
	glPopMatrix();

	//------------------------------------------BOMBE
	glPushMatrix();
	deseneazaBombe();
	glPopMatrix();

	//-----------------------------------perdea stele
	deseneazaPerdeaDeStelute();


	////-----------------------------------casa 
	glColor3f(0.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(1000, 620); //colt stanga jos
	glVertex2i(1030, 620); //colt dreapta jos
	glVertex2i(1030, 650); //colt dreapta sus
	glVertex2i(1000, 650); //colt stanga sus
	glEnd();
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(1000, 650);
	glVertex2i(1030, 650);
	glVertex2i(1015, 670);
	glEnd();
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON); // usa casa
	glVertex2i(1012, 620); //colt stanga jos + 12
	glVertex2i(1018, 620); //colt dreapta jos + 18
	glVertex2i(1018, 640); //colt dreapta sus + h= 20
	glVertex2i(1012, 640); //colt stanga sus + h = 20
	glEnd();

	////-----------------------------------copil
	deseneazaCopil();

	char _score[10];
	_itoa_s(score, _score, 10);
	char text[50] = "Your score: ";
	strcat_s(text, _score);
	RenderString(1200.0f, 800.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)text);

	miscaPeste();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void miscad(void)
{
	//miscare barci
	k = k + alpha;
	if (k > 1000.0)
		alpha = -2.0;
	else if (k < 0.0)
		alpha = 2.0;


	ml = ml + mingel;
	if (ml > 100)
		mingel = -1;
	else if (ml < 0)
		mingel = 1;

	mi = mi + 1;
	//if (mi >=20 )
	//	mingei = -0.2;
	//else if (mi <= 0)
	//	mingei = 0.2;

	b = b + 20;
	if (b > 2300) {
		randn = genereazaafon();
		b = -300;
	}


	glutPostRedisplay();
}

void miscas(void)
{
	//miscare barci
	k = k + alpha;
	if (k < 0.0)
		alpha = 2.0;
	else if (k > 1000.0)
		alpha = -2.0;

	ml = ml + mingel;
	if (ml < 0)
		mingel = 1;
	else if (ml > 100)
		mingel = -1;

	mi = mi + 1;
	/*if (mi <= 0)
		mingei = 0.2;
	else if (mi >=20)
		mingei = -0.2;*/
	b = b + 20;
	if (b > 2300) {
		randn = genereazaafon();
		b = -300;
	}

	glutPostRedisplay();
}


void mouse(int button, int state, int mx, int my)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			alpha = -1.0;
			b = -300;
			glutIdleFunc(miscas);

		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			//alpha = 1.0; glutIdleFunc(miscad);
			break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			z = mx - 20;
			c = 900 - my;//schimbam in functie de ecran
		}
		break;
	default:
		break;
	}
}

void miscaStanga() {
	if (miscare_laterala - 3 > -300.0)
		miscare_laterala -= 3;
	glutPostRedisplay();
}

void miscaDreapta() {
	if (miscare_laterala + 3 < 950.0)
		miscare_laterala += 3;
	glutPostRedisplay();
}

void miscaUnditaJos() {
	if (transf_hook > -450) {
		miscare_verticala_undita += 0.1;
		transf_hook -= 6.0;
	}
	glutPostRedisplay();
}

void miscaUnditaSus() {
	if (miscare_verticala_undita >= 1.0) {
		miscare_verticala_undita -= 0.1;
		transf_hook += 6.0;
	}
	glutPostRedisplay();
}

void keyboard(int key, int x, int y)
{
	if (!stopGame) {
		switch (key) {
		case GLUT_KEY_LEFT:
			miscaStanga();
			break;
		case GLUT_KEY_RIGHT:
			miscaDreapta();
			break;
		case GLUT_KEY_DOWN:
			miscaUnditaJos();
			break;
		case GLUT_KEY_UP:
			miscaUnditaSus();
			break;
		}
	}
}

// aici zic sa fie optiunile din meniu care apeleaza functiile
//respective desenarii pt un anumit scenariu
void controller() {
	switch (rendermode) {
	case Opt1:
		deseneazaScena();
		break;

	case Opt2:
		//functia respectiva de desenare..
		deseneazaScena3();
		glutMouseFunc(mouseCMP);
		desenPasare2();
		glutSwapBuffers();
		glFlush();
		break;

	case Opt3:
		deseneazaScena2();
		deseneazaAMOGUS();
		glutMouseFunc(mouse);
		//functia de desenare respectiva , etc.
		break;
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lac cu barcute");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(controller);
	glutSpecialFunc(keyboard);
	glutCreateMenu(menu);
	glutAddMenuEntry("Mini-game", Opt1);
	glutAddMenuEntry("Scena 1", Opt2);
	glutAddMenuEntry("Scena 2", Opt3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	//glutMouseFunc(mouse);

	PlaySoundA("C:\\Users\\Raluca\\Downloads\\sleepy_fish.wav", NULL, SND_ASYNC);

	glutMainLoop();
}