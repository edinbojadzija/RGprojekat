#include <GL/glut.h>

GLfloat ex=0,ey=0,ez=5, Width, Height;
GLfloat trans=0;
GLfloat rot=0.0,scl=1.0;
bool pause = false;
bool view = 1;
int a=1;
bool svjetlo1 = false;
bool svjetlo2 = false;
bool Mat1 = false;
bool Mat2 = false;


void prvimaterijal() // prvi materijal
{
    GLfloat mat_ambient[] = {0.2,0.2,0.2,1.0};
    GLfloat mat_diffuse[] = {0.2,0.8,0.7,1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

}

void drugimaterijal() // drugi materijal
{
    GLfloat mat_ambient[] = {0.2,0.2,0.2,1.0};
    GLfloat mat_diffuse[] = {1.0,0.0,0.3,1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat mat_specular[] = {0.0,0.0,0.0,1.0};

    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

}

void material_default()  // treci materijal
{
        GLfloat mat_ambient[] = {0.2,0.2,0.2,1.0};
        GLfloat mat_diffuse[] = {0.1,0.1,0.1,1.0};
        GLfloat mat_shininess[] = {100.0};
        GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};

        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

//crtanje objekata
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(ex,ey,ez,0,0,2,0,1,0); //funkcija za pomjeranje kamere

    if(Mat1)
    {
        prvimaterijal();
    }
    else if(Mat2)
    {
        drugimaterijal();
    }
    else{
    material_default();
    }

    glutWireTorus(0.1,0.5,15,20); //crtanje torusa

    glPushMatrix();
    glutWireSphere(0.3,15,20); //crtanje sredisnje sfere
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0,0.0,0.0);

    glRotatef(rot,0.0,0.0,1.0);// rotiranje kocke
    glutSolidCube(0.2); // crtanje kocke
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.0,0.0,0.0);
    glScalef(scl,scl,scl); // skaliranje cajnika
    glutSolidTeapot(0.2); // crtanje cajnika

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,0.8,0.0);
    glTranslatef(0.0,0.0,trans); // transliranje
    glutSolidSphere(0.2,15,30);  // crtanje lopte

    glPopMatrix();


    glPopMatrix();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}

void reshape(int x,int y)  // reshape funkcija
{
    glViewport(0,0,(GLint)x,(GLint) y);
    Width = x;
    Height = y;
    if(view)
    {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLfloat)x/(GLfloat)y,1.0,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }
}


void resetView()
{
    view = 1;
    reshape(Width,Height);
}


void Ortho(){
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5,5,-5,5,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    view=0;
}

void Frustum(){
{
    glMatrixMode(GL_PROJECTION);
    glFrustum(-2,2,-2,2,3.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    view = 0;
}
}

void animacija1() // koristi se pri animaciji ka odredenoj tacki
{
    trans+=0.003;
    scl+=0.002;
    rot+=2;
}

void animacija2() // koristi se pri animaciji od određene tačke
{
    trans-=0.003;
    scl-=0.002;
    rot-=2;
}

void idle() // funkcija koja se koristi kako bi se izvrsila animacija
{
    switch (a)
    {
        case 1:
        animacija1();
        if(trans>=1.5)
        {
            a=2;
        }
        break;

    case 2:
    animacija2();
    if(trans<=0.3)
    {
        a=1;
    }
    break;
    default:
    break;

}
  glutPostRedisplay();
}


void prvosvjetlo()  // prvo svjetlo
{
    GLfloat ambientl1[] = {1.0,1.0,1.0,1.0};
    GLfloat diffusel1[] = {0.3,0.3,0.3,1.0};
    GLfloat positionl1[] = {3.0,3.0,3.0,1.0};

    glLightfv(GL_LIGHT1,GL_AMBIENT,ambientl1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,diffusel1);
    glLightfv(GL_LIGHT1,GL_POSITION,positionl1);

}

void drugosvjetlo() // drugo svjetlo
{

    GLfloat ambientL2[] = {1.0,0.0,1.0,1.0};
    GLfloat diffuseL2[] = {0.2,0.2,0.2,1.0};
    GLfloat specularL2[] = {1.0,1.0,1.0,1.0};
    GLfloat positionL2[] = {10.0,20.0,10.0,1.0};

    glLightfv(GL_LIGHT2,GL_AMBIENT,ambientL2);
    glLightfv(GL_LIGHT2,GL_DIFFUSE,diffuseL2);
    glLightfv(GL_LIGHT2,GL_SPECULAR,specularL2);
    glLightfv(GL_LIGHT2,GL_POSITION,positionL2);

}

void trecesvjetlo()  // trece svjetlo
{
    GLfloat ambientL3[] = {1.0,1.0,0.2,1.0};
    GLfloat diffuseL3[] = {0.5,0.5,0.2,1.0};
    GLfloat positionL3[] = {3.0,3.0,3.0,1.0};

    glLightfv(GL_LIGHT3,GL_AMBIENT,ambientL3);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,diffuseL3);
    glLightfv(GL_LIGHT3,GL_POSITION,positionL3);
}


void init()
{
    glClearColor(0.0,0.0,0.0,1.0);

    prvosvjetlo();
    drugosvjetlo();
    trecesvjetlo();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

}


void keyboardFunc(unsigned char key,int x,int y) {
    switch(key)
    {
        case 27:
        exit(0);
        break;

        case 'o':
        case 'O':
        Ortho(); //ortogonalna projekcija - gledanje objekata "pravo"
        break;

        case 'f':
        case 'F':
        Frustum(); //perspektivna projekcija
        break;

        case 'r':
        case 'R':
        resetView();
        break;

        case 'a':
        glutIdleFunc(idle);  //pokretanje animacije
        break;

        case 'A':
        glutIdleFunc(NULL);  //zaustavljanje animacije
        break;

        case '0':
        {
            if(!svjetlo1)
            {
                glDisable(GL_LIGHT1);
                glEnable(GL_LIGHT2);
            }
            else
            {
                glDisable(GL_LIGHT2);
                glEnable(GL_LIGHT1);
            }
            svjetlo1= !svjetlo1;
            break;

        }

        case '1':
        {
            if(!svjetlo2)
            {
                glDisable(GL_LIGHT1);
                glEnable(GL_LIGHT3);

            }
            else
            {
                glDisable(GL_LIGHT3);
                glEnable(GL_LIGHT1);
            }
            svjetlo2 = !svjetlo2;
            break;

        }
          case '2':
        {
            if(Mat1 == false)
            {
               Mat1 = true;
            }
            else
            {
                Mat1 = false;
            }

            break;
        }

        case '3':
        {
        if(Mat2 == false)
        {
            Mat2 = true;
        }
        else
        {
            Mat2 = false;
        }

        break;
        }

        default:
        break;

    }
    glutPostRedisplay();
}


void specialkeyFunc(int key, int x, int y) // funkcija za pomjeranje kamere
{
    switch (key)
    {
        case GLUT_KEY_UP:  //pomjeranje gore
        ey+=0.1;
        break;

        case GLUT_KEY_DOWN: //pomjeranje dole
        ey-=0.1;
        break;

        case GLUT_KEY_LEFT: //pomjeranje lijevo
        ex-=0.1;
        break;

        case GLUT_KEY_RIGHT: //pomjeranje desno
        ex+=0.1;
        break;

        default:
        break;
    }
    glutPostRedisplay();
}



void mouseFunc(int button,int state,int x,int y){
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){ //lijevi klik rotira gornji objekat
    rot += 30.0;
}
if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){ //desni klik skalira
    scl += 0.2;
}
if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP){ //srednji klik translira po z osi
     trans += 1.0;
}
glutPostRedisplay();
}



int main(int argc,char **argv){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(800,800);
glutCreateWindow("Racunarska grafika - projekat");
init();
glutSpecialFunc(specialkeyFunc);
glutKeyboardFunc(keyboardFunc);
glutMouseFunc(mouseFunc);
glutDisplayFunc(display);
glutReshapeFunc(reshape);

glutMainLoop();
}

















