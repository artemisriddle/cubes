/* 
 * Lauren LaGrone
 * 
 * November 6, 2015
 *
 * hellocube.cpp
 *
 * a thrilling display of geometric glory
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <time.h>

bool wire_frame = false;
bool x_rot = true;
bool y_rot = false;
bool z_rot = false;
bool step_up = false;
bool movement = false;

void drawCube();
void display();
void keyboard(unsigned char key, int x, int y);
void idle();
void init();
void assignColors();
void polygon();
void reshape(int width, int height);
void mouse(int button, int state, int x, int y);
void menu(int choice);
void toggleRotate();
void rotationMenu(int choice);
void arrowKeys(int button, int x, int y);

GLfloat verticies [][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			   {1.0,1.0,-1.0},{-1.0,1.0,-1.0},
			   {-1.0,-1.0,1.0},{1.0,-1.0,1.0},
			   {1.0,1.0,1.0},{-1.0,1.0,1.0}};

GLfloat colors [0][3];
GLfloat angle = 0;
GLfloat speed = .5;

GLfloat distance = 8;
GLfloat strafe = 0;
GLfloat height = 0;

int main(int argc, char** argv){
  srand(time(0));
  assignColors();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutCreateWindow("Dancing Cubes");  

  int rot_menu = glutCreateMenu(rotationMenu);
  glutAddMenuEntry("x \t Add X Rotation", 0);
  glutAddMenuEntry("y \t Add Y Rotation", 1);
  glutAddMenuEntry("z \t Add Z Rotation", 2);
  glutAddMenuEntry("r \t Reset to Default", 3);
  glutAddMenuEntry("LMB \t Change Rotation", 4);

  glutCreateMenu(menu);
  glutAddMenuEntry("> \t Increase Speed" ,0);
  glutAddMenuEntry("< \t Decrease Speed", 1);
  glutAddMenuEntry("s \t Stop Rotation", 4);
  glutAddMenuEntry("c \t Change Colors", 2);
  glutAddMenuEntry("m \t Move in Scene", 6);
  glutAddSubMenu("  \t Rotation Settings", rot_menu);
  glutAddMenuEntry("w \t Toggle Wireframe", 3);
  glutAddMenuEntry("q \t Quit", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  
  glutDisplayFunc(display);
  glEnable(GL_DEPTH_TEST);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutSpecialFunc(arrowKeys);

  init(); 
 
  glutMainLoop(); 
}

void polygon(int a, int b, int c, int d){
  glBegin(GL_POLYGON);

  glColor3fv(colors[a]);
  glVertex3fv(verticies[a]);
    
  glColor3fv(colors[b]);
  glVertex3fv(verticies[b]);
    
  glColor3fv(colors[c]);
  glVertex3fv(verticies[c]);
    
  glColor3fv(colors[d]);
  glVertex3fv(verticies[d]);
  glEnd();
}

void drawCube(){
  polygon(0,3,2,1);
  polygon(2,3,7,6);
  polygon(0,4,7,3);
  polygon(1,2,6,5);
  polygon(4,5,6,7);
  polygon(0,1,5,4);
}

void drawCubes(){

  glPushMatrix();
  glTranslatef(3 , 3, -1);
  glRotatef(angle, x_rot, y_rot, z_rot);
  (wire_frame)? glutWireCube(2) : drawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, -3, -1);
  glRotatef(angle, x_rot, y_rot, z_rot);
  (wire_frame)? glutWireCube(2) : drawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(3, -3, -1);
  glRotatef(angle, x_rot, y_rot, z_rot); 
  (wire_frame)? glutWireCube(2) : drawCube();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, 3, -1);
  glRotatef(angle, x_rot, y_rot, z_rot); 
  (wire_frame)? glutWireCube(2) : drawCube();
  glPopMatrix();
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(strafe,height,distance, 0,0,0, 0,1,0);
  drawCubes();

  glFlush();
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  if(key == 'q' || key == 'Q')
    exit(0);
  else if(key == 'w' || key == 'W')
    wire_frame = !wire_frame;
  else if (key == 'c' || key == 'C')
    assignColors();
  else if(key == ',')
    speed -= .5;
  else if(key == '.')
    speed += .5;
  else if(key == 's' || key == 'S')
    speed = 0;
  else if(key == 'x' || key == 'X')
    x_rot = !x_rot;
  else if (key == 'y' || key == 'Y')
    y_rot = !y_rot;
  else if (key == 'z' || key == 'Z')
    z_rot = !z_rot;
  else if (key == 'r' || key == 'R'){
    x_rot = true;
    y_rot = false;
    z_rot = false;
  }
  else if (key == 'm' || key == 'M')
    movement = !movement;
}

void menu(int choice){
  switch(choice){
  case 0: 
    speed += .5;
    break;
  case 1:
    speed -= .5;
    break;
  case 4:
    speed = 0;
    break;
  case 2:
    assignColors();
    break;
  case 3:
    wire_frame = !wire_frame;
    break;
  case 5:
    exit(0);    
  case 6:
    movement = !movement;
    break;
  }
}

void rotationMenu(int choice){
  switch(choice){
  case 0:
    x_rot = !x_rot;
    break;
  case 1:
    y_rot = !y_rot;
    break;
  case 2:
    z_rot = !z_rot;
    break;
  case 3:
    x_rot = true;
    y_rot = false;
    z_rot = false;
    break;
  case 5:
    toggleRotate();
  }
}

void idle(){
  angle += speed;
  
  if(angle > 365)
    angle -= 365;

  glutPostRedisplay();
}

void init(){
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void assignColors(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 3; j++){
      //blatantly stolen from a stackoverflow question. random floating points.
      colors[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
  }
}

void reshape(int w, int h){
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0,1.0,1.0,30.0);
  glMatrixMode(GL_MODELVIEW);
}

void mouse (int button, int state, int x, int y){
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    toggleRotate();
  }
}

void toggleRotate(){
  if(x_rot){
    x_rot = !x_rot;
    y_rot = !y_rot;
  }
  else if (y_rot){
    y_rot = !y_rot;
    z_rot = !z_rot;
  }
  else{
    z_rot = !z_rot;
    x_rot = !x_rot;
  }
}

void arrowKeys(int button, int x, int y){
  if(movement){
    switch(button){
    case GLUT_KEY_UP:
      distance -= .35;
      break;
    case GLUT_KEY_DOWN:
      distance += .35;
      break;
    case GLUT_KEY_RIGHT:
      strafe += .35;
      break;
    case GLUT_KEY_LEFT:
      strafe -= .35;
      break;
    }
    if(step_up){
      height += .5;
      if(height > 1)
	step_up = false;
    }else{
      height -= .5;
      if(height < 0)
        step_up = true;
    } 
  }
}
