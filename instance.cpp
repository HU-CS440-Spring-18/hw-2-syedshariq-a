#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>


int SCREEN_H = 500; int SCREEN_W = 500;
const GLfloat angleRad = 3.14159 / 180;
void map_point(float px,float py, float qx, float qy, float ax, float ay, float bx, float by, float x, float y, float &_x, float &_y)
{
    /*
    x = a*px+(1-a)*qx
    x = a*px + qx - a*qx
    x = qx + a*px - a*qx
    x = qx + a(px - qx)
    a = (x - qx) / (px - qx)

    _x = a*ax+(1-a)*bx
    _y = b*ay+(1-b)*by */

    float a = (x - qx) / (px - qx);
    float b = (y - qy) / (py - qy);
    _x = a * ax + (1 - a) * bx;
    _y = b * ay + (1 - b) * by;

}

class rect
{
public:
    rect(GLfloat _x,GLfloat _y,GLfloat _h,GLfloat _w,GLfloat _angle=0){x=_x;y=_y;h=_h;w=_w;angle=_angle;}
    void transform(int choice, GLfloat par1, GLfloat par2=0)
    {
        if (choice == 0) // rotate
            {angle += par1;}
        if (choice == 1) // scale
            {w*=par1;h*=par2;}
        if (choice == 2) // translate
            {x+=par1;y+=par2;}
    }
    void draw();
private:
    GLfloat x,y,h,w,angle; // x,y height,width,angle
};

void drawPoint(GLfloat x,GLfloat y)
{
    GLfloat x1,y1;
    map_point(0,0,SCREEN_W,SCREEN_H,-1,1,1,-1,x,y,x1,y1);
    glVertex2f(x1,y1);
    std::cout<<x1<<" "<<y1<<"\n";
}

void rect::draw()
{
    glPushMatrix();
    glRotated(angle,0,0,1);
    glBegin(GL_LINES);
    drawPoint(x,y);
    drawPoint(x,y+h);
    glEnd();
    glBegin(GL_LINES);
    drawPoint(x,y+h);
    drawPoint(x+w,y+h);
    glEnd();
    glBegin(GL_LINES);
    drawPoint(x+w,y+h);
    drawPoint(x+w,y);
    glEnd();
    glBegin(GL_LINES);
    drawPoint(x+w,y);
    drawPoint(x,y);
    glEnd();
    glPopMatrix();

}

void display()
{
// GL stuff.
// equilateral triangle
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //nose
    rect* r = new rect(200,200,25,25,45); // nose
    r->draw();
    r->transform(2,-50,-50); // face
    r->transform(1,5,5);
    r->draw();
    r->transform(0,-45); // right eye
    r->transform(1,0.15,0.15);
    r->transform(2,65,60);
    r->draw();
    r->transform(2,-50,0); //left eye
    r->draw();
    r->transform(1,3,1); // mouth
    r->transform(2,5,68);
    r->draw();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_W,SCREEN_H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("6: Color bars");
    glutDisplayFunc(display);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_W,0,SCREEN_H,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 0;
}
