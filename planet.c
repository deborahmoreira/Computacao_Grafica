#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
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
GLuint tplu,tmoon,tsun,tearth,tmercu,tven,tmars,tjup,tsat,tura,tnep;
GLUquadric* sphere;
// Abilita as luzes
void init(void) 
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
   
	GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);
	
	glLightfv(GL_LIGHT3, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light1_specular);
	

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_TEXTURE_2D);

}

//Carrega os arquivos de textura, pode ser encontrado no http://www.cppblog.com/doing5552/archive/2009/01/08/71532.aspx
int power_of_two(int n)
{
    if (n <= 0)
        return 0;
    return (n & (n - 1)) == 0;
}
GLuint LoadTexture(const char* filename)
{

    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint  texture_ID = 0;

    
    FILE* pFile = fopen(filename, "rb");
    if (pFile == 0)
        return 0;

    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, 54, SEEK_SET);

    
    {
        GLint line_bytes = width * 3;
        while (line_bytes % 4 != 0)
            ++line_bytes;
        total_bytes = line_bytes * height;
    }

    
    pixels = (GLubyte*)malloc(total_bytes);
    if (pixels == 0)
    {
        fclose(pFile);
        return 0;
    }

    
    if (fread(pixels, total_bytes, 1, pFile) <= 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    
    // Para a compactibidade com a versão antiga do OpenGL
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if (!power_of_two(width)
            || !power_of_two(height)
            || width > max
            || height > max)
        {
            const GLint new_width = 512;
            const GLint new_height = 512; // set the picture to 512*512
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;

            
            new_line_bytes = new_width * 3;
            while (new_line_bytes % 4 != 0)
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;

            
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if (new_pixels == 0)
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }

            
            gluScaleImage(GL_RGB,
                width, height, GL_UNSIGNED_BYTE, pixels,
                new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

            
            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }

    
    glGenTextures(1, &texture_ID);
    if (texture_ID == 0)
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    free(pixels);
    return texture_ID;

}

void init_LoadTexture()
{
   // Texturas do Sistema Solar
   tsun = LoadTexture("pictures/sol.bmp");
   tmercu = LoadTexture("pictures/mercurio.bmp");
   tven = LoadTexture("pictures/venus.bmp");
   tearth = LoadTexture("pictures/terra.bmp");
   tmoon = LoadTexture("pictures/lua.bmp");
   tmars = LoadTexture("pictures/marte.bmp");
   tjup = LoadTexture("pictures/jupiter.bmp");
   tsat = LoadTexture("pictures/saturno.bmp");
   tura = LoadTexture("pictures/urano.bmp");
   tnep = LoadTexture("pictures/neptuno.bmp");
   tplu = LoadTexture("pictures/plutao.bmp");
}

// Define a Iluminação do Sol, gera os planetas com suas texturas
void display(void)
{
   GLfloat light_position1[] = { 5.0, 5.0, -6.0, 1.0 };
   GLfloat light_position2[] = { -5.0, 5.0, -6.0, 1.0 };
   GLfloat light_position3[] = { -5.0, -5.0, -6.0, 1.0 };
   GLfloat light_position4[] = { 5.0, -5.0, -6.0, 1.0 };

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glTranslatef(0.0, 0.0, 0.0);
  
   glColor3f (1.0, 1.0, 0.0);
   
   glLightfv (GL_LIGHT0, GL_POSITION, light_position1);
   glLightfv (GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv (GL_LIGHT2, GL_POSITION, light_position3);
   glLightfv (GL_LIGHT3, GL_POSITION, light_position4);
   
   glPopMatrix();
   
   // Sol
   glPushMatrix();
   //glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tsun);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 5, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Mercurio
   glPushMatrix();
   glRotatef ((GLfloat) yearMercurio, 0.0, 1.0, 0.0); // define orbita
   glTranslatef (6.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayMercurio, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tmercu);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.07, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Venus
   glPushMatrix();
   glRotatef ((GLfloat) yearVenus, 0.0, 1.0, 0.0);
   glTranslatef (7.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayVenus, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tven);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.1, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   // Terra
   glPushMatrix();
   glRotatef ((GLfloat) yearEarth, 0.0, 1.0, 0.0);
   glTranslatef (9.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayEarth, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tearth);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.2, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   // Lua
   glPushMatrix();
   glRotatef ((GLfloat) yearMoon, 0.0, 1.0, 0.0);
   glTranslatef (9.5, 0.0, 0.0);
   glRotatef ((GLfloat) dayEarth, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tmoon);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.05, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
	
   // Marte
   glPushMatrix();
   glRotatef ((GLfloat) yearMarte, 0.0, 1.0, 0.0);
   glTranslatef (11.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayMarte, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tmars);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.27, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Jupiter
   glPushMatrix();
   glRotatef ((GLfloat) yearJupiter, 0.0, 1.0, 0.0);
   glTranslatef (20.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayJupiter, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tjup);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 2, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Saturno
   glPushMatrix();
   glRotatef ((GLfloat) yearSaturno, 0.0, 1.0, 0.0);
   glTranslatef (30.0, 0.0, 0.0);
   glRotatef ((GLfloat) daySaturno, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tsat);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.8, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   // Urano
   glPushMatrix();
   glRotatef ((GLfloat) yearUrano, 0.0, 1.0, 0.0);
   glTranslatef (40.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayUrano, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tura);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.3, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Netuno
   glPushMatrix();
   glRotatef ((GLfloat) yearNetuno, 0.0, 1.0, 0.0);
   glTranslatef (50.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayNetuno, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tnep);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 1.2, 50, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // Plutão
   glPushMatrix();
   glRotatef ((GLfloat) yearPluto, 0.0, 1.0, 0.0);
   glTranslatef (60.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayPluto, 0.0, 1.0, 0.0);
   glEnable(GL_TEXTURE_2D);
   gluQuadricDrawStyle(sphere, GLU_FILL);
   glBindTexture(GL_TEXTURE_2D, tplu);
   gluQuadricTexture(sphere, GL_TRUE);
   gluQuadricNormals(sphere, GLU_FLAT);
   gluSphere(sphere, 0.5, 10, 50);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   glPushMatrix();
   glutSwapBuffers();
}
// Rotação do Sistema
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
// Camera
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0); //angulo
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 25.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // visao da camera
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		//melhora a qualidade dos gráficos
}
// Controla a rotação e translação dos planetas
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
   
   glEnable(GL_DEPTH_TEST);
   sphere = gluNewQuadric();
   glEnable(GL_TEXTURE_2D);
   
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1920, 1080); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (argv[0]);
   
   init();
   init_LoadTexture();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
