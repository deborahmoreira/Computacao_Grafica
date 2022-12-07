#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
// gcc -o planet planet.c -lm -lGL -lGLU -lglut
static int year = 0, day = 0;
static int yearEarth = 0, dayEarth = 0;
static int yearMercurio = 0, dayMercurio = 0;
static int yearVenus = 0, dayVenus = 0;
static int yearMarte = 0, dayMarte = 0;
static int yearMoon = 0;
static int yearJupiter = 0, dayJupiter = 0, yearSaturno = 0, daySaturno = 0;
static int yearUrano = 0, dayUrano = 0, yearNetuno = 0, dayNetuno = 0;
static int yearPluto = 0, dayPluto = 0;
static GLfloat spin = 0.0;
GLuint tex;
GLUquadric* sphere;

void init(void) 
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   //GLfloat light_position[] = { 5.0, 0.0, -2.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   
	GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 0.0 };
	//GLfloat light1_position[] = { 5.0, 0.0, -2.0, 1.0 };
	//GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);
	
	glLightfv(GL_LIGHT3, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light1_specular);
	
	//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);

	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	//glEnable(GL_LIGHT1);

   //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable(GL_LIGHT2);
   glEnable(GL_LIGHT3);
   //glEnable(GL_DEPTH_TEST);
   //

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_TEXTURE_2D);

}

void display(void)
{
   GLfloat light_position1[] = { 5.0, 0.0, -2.0, 1.0 };
   GLfloat light_position2[] = { -5.0, 0.0, -2.0, 1.0 };
   GLfloat light_position3[] = { 0.0, 5.0, -2.0, 1.0 };
   GLfloat light_position4[] = { 0.0, -5.0, -2.0, 1.0 };
   
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glTranslatef(0.0, 0.0,-2.0);
  
   glColor3f (1.0, 1.0, 0.0);
   
   glLightfv (GL_LIGHT0, GL_POSITION, light_position1);
   glEnable(GL_LIGHT0);
   //glPopMatrix();
   
   //glPushMatrix();
   glLightfv (GL_LIGHT1, GL_POSITION, light_position2);
   glEnable(GL_LIGHT1);
   
   glLightfv (GL_LIGHT2, GL_POSITION, light_position3);
   glEnable(GL_LIGHT2);
   
   glLightfv (GL_LIGHT3, GL_POSITION, light_position4);
   glEnable(GL_LIGHT3);
   
   glPopMatrix();
   
   glPushMatrix();
   //glRotatef((GLfloat) day, 0, 1, 0);
   glColor3f(1.0,1.0,0.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 5, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearMercurio, 0.0, 1.0, 0.0); // define orbita
   glTranslatef (6.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayMercurio, 0.0, 1.0, 0.0);
   glColor3f(1.0, 0.0, 0.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   //gluQuadricTexture(sphere, GL_TRUE);
   //gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.07, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearVenus, 0.0, 1.0, 0.0);
   glTranslatef (7.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayVenus, 0.0, 1.0, 0.0);
   glColor3f(0.0, 1.0, 0.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.1, 50, 50);
   glPopMatrix();
   
   glPushMatrix();
   glRotatef ((GLfloat) yearEarth, 0.0, 1.0, 0.0);
   glTranslatef (9.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayEarth, 0.0, 1.0, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.2, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearMoon, 0.0, 1.0, 0.0);
   glTranslatef (9.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayEarth, 0.0, 1.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.05, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearMarte, 0.0, 1.0, 0.0);
   glTranslatef (11.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayMarte, 0.0, 1.0, 0.0);
   glColor3f(1.0, 0.5, 0.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.27, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearJupiter, 0.0, 1.0, 0.0);
   glTranslatef (20.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayJupiter, 0.0, 1.0, 0.0);
   glColor3f(1.0, 0.5, 1.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 2, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearSaturno, 0.0, 1.0, 0.0);
   glTranslatef (30.0, 0.0, 0.0);
   glRotatef ((GLfloat) daySaturno, 0.0, 1.0, 0.0);
   glColor3f(1.0, 0.8, 0.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.8, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearUrano, 0.0, 1.0, 0.0);
   glTranslatef (40.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayUrano, 0.0, 1.0, 0.0);
   glColor3f(1.0, 1.0, 0.7);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.3, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearNetuno, 0.0, 1.0, 0.0);
   glTranslatef (50.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayNetuno, 0.0, 1.0, 0.0);
   glColor3f(0.0, 0.0, 1.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.2, 50, 50);
   glPopMatrix();

   glPushMatrix();
   glRotatef ((GLfloat) yearPluto, 0.0, 1.0, 0.0);
   glTranslatef (60.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayPluto, 0.0, 1.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tex);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.5, 10, 50);
   glPopMatrix();
   
   glPushMatrix();
   glutSwapBuffers();
}

void spinDisplay(void)
{
	     day = (day + 10) % 360;

        dayMercurio = (dayMercurio + 25) % 360;
        yearMercurio = (yearMercurio + 25) % 360;
        dayVenus = (dayVenus + 15) % 360;
        yearVenus = (yearVenus + 15) % 360;
        dayMarte = (dayMarte + 9) % 360;
        yearMarte = (yearMarte + 9) % 360;
        dayEarth = (dayEarth + 10) % 360;
        yearEarth = (yearEarth + 10) % 360;
        yearMoon = (yearEarth) % 360;
        // planetas gasosos são mais lentos
        yearJupiter = (yearJupiter + 5) % 360;
        dayJupiter = (dayJupiter + 5) % 360;
        yearSaturno = (yearSaturno + 4) % 360;
        daySaturno = (daySaturno + 4) % 360;
        yearUrano = (yearUrano + 3) % 360;
	     dayUrano = (dayUrano + 3) % 360;
        yearNetuno = (yearNetuno + 2) % 360;
        dayNetuno = (dayNetuno + 2) % 360;
        yearPluto = (yearPluto + 1) % 360;
        dayPluto = (dayPluto + 1) % 360;
   	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0); //angulo
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // visao da camera
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		//melhora a qualidade dos gráficos
}
////////////////////////
void make_tex(void)
{
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
	for (int x = 0; x < 255; x++) {
	    unsigned char *p = data[y][x];
	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
	}
    }
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
////////////////////////
void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd': /*d */
         day = (day + 10) % 360;
         dayMercurio = (dayMercurio + 25) % 360;
         dayVenus = (dayVenus + 15) % 360;
         dayMarte = (dayMarte + 9) % 360;
         dayEarth = (dayEarth + 10) % 360;
         dayJupiter = (dayJupiter + 5) % 360;
         daySaturno = (daySaturno + 4) % 360;
         dayUrano = (dayUrano + 3) % 360;
         dayNetuno = (dayNetuno + 2) % 360;
         dayPluto = (dayPluto + 1) % 360;
         glutPostRedisplay();
         break;
      case 'a':
         
         day = (day + 10) % 360;

         dayMercurio = (dayMercurio + 25) % 360;
         yearMercurio = (yearMercurio + 25) % 360;
         dayVenus = (dayVenus + 15) % 360;
         yearVenus = (yearVenus + 15) % 360;
         dayMarte = (dayMarte + 9) % 360;
         yearMarte = (yearMarte + 9) % 360;
         dayEarth = (dayEarth + 10) % 360;
         yearEarth = (yearEarth + 10) % 360;
         yearMoon = (yearEarth) % 360;
         // planetas gasosos são mais lentos
         yearJupiter = (yearJupiter + 5) % 360;
         dayJupiter = (dayJupiter + 5) % 360;
         yearSaturno = (yearSaturno + 4) % 360;
         daySaturno = (daySaturno + 4) % 360;
         yearUrano = (yearUrano + 3) % 360;
         dayUrano = (dayUrano + 3) % 360;
         yearNetuno = (yearNetuno + 2) % 360;
         dayNetuno = (dayNetuno + 2) % 360;
         yearPluto = (yearPluto + 1) % 360;
         dayPluto = (dayPluto + 1) % 360;
         glutPostRedisplay();
         break;
      case 'q':
	   glutIdleFunc(spinDisplay);
  	 break;
      case 'w':
	   glutIdleFunc(NULL);
  	 break;
      default:
         break;
        
   }
}

int main(int argc, char** argv)
{
   //
   glEnable(GL_DEPTH_TEST);
   make_tex();
   sphere = gluNewQuadric();
   glEnable(GL_TEXTURE_2D);
   //
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1920, 1080); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
