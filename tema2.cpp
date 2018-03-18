
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <cmath>
#include "glut.h"
const double EulerConstant = std::exp(1.0);
// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
   double xmax, ymax, xmin, ymin;
   double a = 1, b = 2;
   double pi = 4 * atan(1.0);
   double ratia = 0.01; // ratia = 0.05
   double t;

   // calculul valorilor maxime/minime ptr. x si y
   // aceste valori vor fi folosite ulterior la scalare
   xmax = a - b - 1;
   xmin = a + b + 1;
   ymax = ymin = 0;
   for (t = - pi/2 + 3 * ratia; t < pi / 2 - 3 * ratia; t += ratia) {
      double x1, y1, x2, y2;
      x1 = a + b * cos(t);
      xmax = (xmax < x1) ? x1 : xmax;
      xmin = (xmin > x1) ? x1 : xmin;

      x2 = a - b * cos(t);
      xmax = (xmax < x2) ? x2 : xmax;
      xmin = (xmin > x2) ? x2 : xmin;

      y1 = a * tan(t) + b * sin(t);
      ymax = (ymax < y1) ? y1 : ymax;
      ymin = (ymin > y1) ? y1 : ymin;

      y2 = a * tan(t) - b * sin(t);
      ymax = (ymax < y2) ? y2 : ymax;
      ymin = (ymin > y2) ? y2 : ymin;
   }

   xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
   ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();

   glBegin(GL_LINE_STRIP); 
   for (t = - pi/2 + ratia; t < pi / 2; t += ratia) {
      double x1, y1, x2, y2;
      x1 = (a + b * cos(t)) / xmax;
      x2 = (a - b * cos(t)) / xmax;
      y1 = (a * tan(t) + b * sin(t)) / ymax;
      y2 = (a * tan(t) - b * sin(t)) / ymax;

      glVertex2f(x2,y2);
   }
   glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
   double pi = 4 * atan(1.0);
   double xmax = 8 * pi;
   double ymax = exp(1.1);
   double ratia = 0.05;

   // afisarea punctelor propriu-zise precedata de scalare
   glColor3f(1,0.1,0.1); // rosu
   glBegin(GL_LINE_STRIP); 
   for (double x = 0; x < xmax; x += ratia) {
      double x1, y1;
      x1 = x / xmax;
      y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

      glVertex2f(x1,y1);
   }
   glEnd();
}


void Display3() {
	double xmax, ymax, xmin, ymin;
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double t;

	xmax = -1e100;
	xmin = 1e100;
	ymax = -1e100;
	ymin = 1e100;
	for (t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a * cos(t) + b) * cos(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = 2 * (a * cos(t) + b) * sin(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a * cos(t) + b) * cos(t) / (xmax + 0.1);
		y = 2 * (a * cos(t) + b) * sin(t) / (ymax + 0.3);

		glVertex2d(x, y);
	}
	glEnd();
}

void Display4() {
	double xmax, ymax, xmin, ymin;
	double a = 0.1, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.01;
	double t;

	xmax = a - b;
	xmin = a - b;
	ymax = a + 1;
	ymin = a - 1;
	for (t = -10 + ratia; t <= 10; t += ratia) {
		double x, y;
		x = -a * t - b * sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = -a - b * sin(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	printf("xmax %f", xmax);
	printf("ymax %f", ymax);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -10 + ratia; t <= 10; t += ratia) {
		double x, y;
		x = (-a * t + b * sin(t)) / xmax;
		y = (-a - b * cos(t)) / ymax + 0.2;

		glVertex2d(x* 0.8, y * 0.8);
	}
	glEnd();
}

void Display5() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = 1;
	xmin = -1;
	ymax = 1;
	ymin = 1;
	for (t = 0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R + r) * cos((r / R) * t) - r * cos(t + (r / R)*t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = (R + r) * sin((r / R) * t) - r * sin(t + (r / R)*t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R + r) * cos((r / R) * t) - r * cos(t + (r / R)*t);
		y1 = (R + r) * sin((r / R) * t) - r * sin(t + (r / R)*t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display6() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = 1;
	xmin = -1;
	ymax = 1;
	ymin = 1;
	for (t = 0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R - r) * cos((r / R) * t) - r * cos(t - (r / R)*t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = (R - r) * sin((r / R) * t) - r * sin(t - (r / R)*t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R - r) * cos((r / R) * t) - r * cos(t - (r / R)*t);
		y1 = (R - r) * sin((r / R) * t) - r * sin(t - (r / R)*t);
		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display7() {
	double xmax, ymax, xmin, ymin;
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t, r1, r2;

	xmax = -1e100;
	xmin = 1e100;
	ymax = -1e100;
	ymin = 1e100;
	
	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {

		r1 = a * (sqrt(2 * cos(2 * t)));
		r2 = -a * (sqrt(2 * cos(2 * t)));

		double x1, y1, x2, y2;
		x1 = r1 * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = r1 * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		x2 = r2 * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;


		y2 = r2 * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;

	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 4; t <= pi / 4; t += ratia) {
		double x1, y1, x2, y2;
		r1 = a * (sqrt(2 * cos(2 * t)));
		x1 = (r1 * cos(t));// / xmax;
		y1 = (r1 * sin(t));// / ymax;
		glVertex2f(x1, y1);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	
	for (t = -pi / 4; t <= pi / 4; t += ratia) {
		double x1, y1, x2, y2;
		r2 = -a * (sqrt(2 * cos(2 * t)));
		x2 = (r2 * cos(t));// / xmax;
		y2 = (r2 * sin(t));// / ymax;
		glVertex2f(x2, y2);
	}
	
	glEnd();
	
}

void Display8() {
	double xmax, ymax, xmin, ymin;
	double a = 0.02;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t, r;

	xmax = a;
	xmin = a * EulerConstant;
	ymax = a;
	ymin = -a;
	
	for (t = 0 + ratia; t < 100; t += ratia) {
		double x1, y1;
		r = a * (pow(EulerConstant, 1 + t));
		x1 = r * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;
		y1 = r * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0 + ratia; t < 2.9; t += ratia) {
		double x1, y1;
		r = a * (pow(EulerConstant, 1 + t));
		x1 = r * cos(t);
		y1 = r * sin(t);
		glVertex2f(x1, y1);
	}

	glEnd();
}

void Display9() {
	double xmax = 20;
	double ymax = 1;
	double ratia = 0.05;

	for (double x = ratia; x <= xmax; x += ratia) {
		ymax = ymax < (fabs(floor(x + 0.5) - x) / x) ? (fabs(floor(x + 0.5) - x) / x) : ymax;
	}

	ymax = 1.05;
	printf("ymax %f", ymax);
	
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);

	for (double x = 0; x <= xmax; x += ratia) {
		double y1;
		double x1;
		if (x == 0) {
			x1 = 0;
			y1 = 1 / ymax;
		}
		else {
			x1 = x * 1.0 / xmax;
			y1 = (fabs(floor(x + 0.5) - x) / x) / ymax;

		}
		glVertex2d(x1 * 0.9, y1 * 0.9);
	}
	glEnd();
}

void Display10() {
	float a = 0.2;
	float pi = acos(-1);
	float ratia = 0.025;
	float t;

	glColor3f(1, 0.1, 0.1);
	
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + 1e-7; t < -pi / 6; t += ratia) {
		float x, y;
		x = (a / (4 * pow(cos(t), 2) - 3));
		y = ((a * tan(t)) / (4 * pow(cos(t), 2) - 3));
		glVertex2f(x, y);
	}
	glEnd();

	for (t = - 1.5 * pi / 6; t < - pi / 6; t += ratia) {
		float x, y, next_x, next_y;
		x = a / (4 * pow(cos(t), 2) - 3);
		y = (a * tan(t)) / (4 * pow(cos(t), 2) - 3);

		next_x = a / (4 * pow(cos(t + 0.01), 2) - 3);
		next_y = (a * tan(t + 0.01)) / (4 * pow(cos(t + 0.01), 2) - 3);

		glBegin(GL_TRIANGLES);
		glVertex2f(-1.0, 1.0);
		glVertex2f(x, y);
		glVertex2f(next_x, next_y);
		glEnd();
	}
	
	for (t = -pi / 2 + 1e-7; t < - 2.5 * pi / 6; t += ratia) {
		float x, y, next_x, next_y;
		x = a / (4 * pow(cos(t), 2) - 3);
		y = (a * tan(t)) / (4 * pow(cos(t), 2) - 3);

		next_x = a / (4 * pow(cos(t + 0.01), 2) - 3);
		next_y = (a * tan(t + 0.01)) / (4 * pow(cos(t + 0.01), 2) - 3);

		glBegin(GL_TRIANGLES);
		glVertex2f(-1.0, 1.0);
		glVertex2f(x, y);
		glVertex2f(next_x, next_y);
		glEnd();
	}
	
}

void Init(void) {

   glClearColor(1.0,1.0,1.0,1.0);

   glLineWidth(1);

//   glPointSize(4);

   glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   switch(prevKey) {
   case '1':
      Display1();
      break;
   case '2':
      Display2();
      break;
   case '3':
	  Display3();
	  break;
   case '4':
	   Display4();
	   break;
   case '5':
	   Display5();
	   break;
   case '6':
	   Display6();
	   break;
   case '7':
	   Display7();
	   break;
   case '8':
	   Display8();
	   break;
   case '9':
	   Display9();
	   break;
   case '0':
	   Display10();
	   break;
   default:
	   break;
   }

   glFlush();
}

void Reshape(int w, int h) {
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
   prevKey = key;
   if (key == 27) // escape
      exit(0);
   glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

   glutInit(&argc, argv);
   
   glutInitWindowSize(dim, dim);

   glutInitWindowPosition(100, 100);

   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutCreateWindow (argv[0]);

   Init();

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(KeyboardFunc);
   
   glutMouseFunc(MouseFunc);

   glutDisplayFunc(Display);
   
   glutMainLoop();

   return 0;
}
