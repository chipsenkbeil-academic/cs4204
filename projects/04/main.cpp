#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include "lib_soil/SOIL.h"
#include "textfile.h"

// The number of points to divide the grid into
const float gridSize = 100;

double rho = 0, theta = 0;
int lastX, lastY;
GLenum shaderProgram;
char *vertProgFileName, *fragProgFileName;
int skyTex, leafTex;
GLint leafUniformPos, skyUniformPos;
GLint tUniformPos;
GLuint displayList;

void setShaders();
void display();

int LoadTexture( const char *Filename )
{
    int returnTex = SOIL_load_OGL_texture (
        Filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );

    if (returnTex == 0)
        return 0;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, returnTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return returnTex;
}


double clip(double x, double a, double b) {
   double y = (x>a)?x:a;
   return (y<b)?y:b;
}

void initGL()
{
   GLfloat pos[] = {7.0, 2.0, 3.0, 1.0};
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT,GL_DIFFUSE);
   GLfloat black[4] = {0,0,0,0};
   glMaterialfv(GL_FRONT,GL_AMBIENT,black);
   glMaterialfv(GL_FRONT,GL_SPECULAR,black);
   glLightfv(GL_LIGHT0, GL_POSITION, pos);

   glEnable(GL_DEPTH_TEST);

   printf("Loading textures\n");

   if(!(skyTex = LoadTexture("sky.bmp")))
      exit(1);
   if(!(leafTex = LoadTexture("leaf.bmp")))
      exit(1);

   	glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	setShaders();
	   
	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	display();
	glEndList();
}


void Reshape(int w, int h) {

   const double aspect = w/(double)h;

   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60, aspect, 1, 200);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0,0,-10);
}


void mouseButton(int button, int state, int x, int y) {
   switch(button) {
      case GLUT_LEFT_BUTTON:
         if(state == GLUT_DOWN) {
            lastX = x;
            lastY = y;
         }
         break;
      case GLUT_RIGHT_BUTTON:
         if(state == GLUT_DOWN) {
         }
         glutPostRedisplay();
         break;
   }
}

void motion(int x, int y) {
   double dx = x-lastX, dy = y-lastY;
   lastX = x;
   lastY = y;

   theta += dx;
   rho += dy;

   rho = clip(rho, -90, 90);
   glutPostRedisplay();
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   const float size = 5.0;
   const float du = 2*size/gridSize, dv = 2*size/gridSize;

   glColor3f(0, 1, 0);
   for(float u = -size; u <= size; u += du) {
      glBegin(GL_TRIANGLE_STRIP);
      for(float v = -size; v <= size; v += dv) {
		 glTexCoord2f( (u+5.0f)/10.0f, (v+5.0f)/10.0f );
         glVertex2f(u, v);
		 glTexCoord2f( (u+du+5.0f)/10.0f, (v+5.0f)/10.0f );
         glVertex2f(u+du, v);
      }
      glEnd();
   }

   glUseProgram(0);
   glPopMatrix();

   glColor3f(0, 1, 0);
   glBegin(GL_LINES);
   glVertex3f(-5,0,0);
   glVertex3f(5,0,0);
   glVertex3f(0,-5,0);
   glVertex3f(0,5,0);
   glEnd();
}

void renderScene(void)
{
   float t = glutGet(GLUT_ELAPSED_TIME) * -0.001f;

   glMatrixMode(GL_MODELVIEW);

   glPushMatrix();
   glRotatef(rho,1,0,0);
   glRotatef(theta,0,1,0);

   glColor3f(1,0,0);
   
   glUseProgram(shaderProgram);
   glUniform1f(tUniformPos, t);

   glCallList(displayList);

   glutSwapBuffers();
}


#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}


void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}



void setShaders() {

	char *vs = NULL,*fs = NULL;
	GLenum v,f;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("water_ripple.vert");
	fs = textFileRead("water_ripple.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderInfoLog(v);
	printShaderInfoLog(f);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,v);
	glAttachShader(shaderProgram,f);

	glLinkProgram(shaderProgram);
	printProgramInfoLog(shaderProgram);

	leafUniformPos = glGetUniformLocation(shaderProgram, "leaf");
	skyUniformPos = glGetUniformLocation(shaderProgram, "sky");
	tUniformPos = glGetUniformLocation(shaderProgram, "t");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyTex);
	glUniform1i(skyUniformPos, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, leafTex);
	glUniform1i(leafUniformPos, 1);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,640);
	glutCreateWindow("GLSL Test");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(mouseButton);
	glutMotionFunc(motion);

	initGL();

	glutMainLoop();

	return 0;
}

