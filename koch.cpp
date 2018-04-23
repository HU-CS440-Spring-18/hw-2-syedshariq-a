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

int SCREEN_W = 500,SCREEN_H = 500;
void display();
void kochLine(GLfloat A[2], GLfloat B[2]);
void drawLine(GLfloat A[2], GLfloat B[2]);
void kochSnowflake(GLfloat P[2],GLfloat Q[2],GLfloat R[2],int depth);
void KochLine(GLfloat A[2], GLfloat B[2],int depth);
const GLfloat degToRad = 3.14159 / 180;

void map_point(float px,float py, float qx, float qy, float ax, float ay, float bx, float by, float x, float y, float &_x, float &_y)
{
    float a = (x - qx) / (px - qx);
    float b = (y - qy) / (py - qy);
    _x = a * ax + (1 - a) * bx;
    _y = b * ay + (1 - b) * by;

}


void kochLine(GLfloat v0[2], GLfloat v1[2])
{
// segment endpoints.
// begin transformations.
    /* Transformation magic. */
    /* Assign v0, v1; only once. */
    drawLine(v0, v1);
    /* Transformation magic. */
    drawLine(v0, v1);
    /* Transformation magic. */
    drawLine(v0, v1);
    /* Transformation magic. */
    drawLine(v0, v1);
// end transformations.
}

void calcNewPoint(GLfloat v0[2],GLfloat result[2],GLfloat dist,GLfloat angle)
{
	GLfloat angleRad = angle*degToRad;
	result[0] = v0[0] + dist*cos(angleRad);
	result[1] = v0[1] + dist*sin(angleRad);
}


void KochLine(GLfloat A[2], GLfloat B[2],int depth)
{

	GLfloat angleRad = atan2(B[1] - A[1], B[0] - A[0]);
	GLfloat angle = angleRad / degToRad;
	GLfloat dist = sqrt((B[1]-A[1])*(B[1]-A[1])+(B[0]-A[0])*(B[0]-A[0]))/3;
	GLfloat v0[2], vA[2],vB[2],vC[2],v1[2];
    v0[0] = A[0]; v0[1] = A[1];
    calcNewPoint(v0,vA,dist,angle);
    calcNewPoint(vA,vB,dist,angle+60);
    calcNewPoint(vB,vC,dist,angle-60);
    v1[0] = B[0]; v1[1] = B[1];
	if (depth == 0)
	{
		drawLine(v0,v1);
	}
	else if (depth == 1)
	{
	    std::cout<<"Dist "<<dist<<"\nV0 "<<v0[0]<<" "<<v0[1]<<"\nVA "<<vA[0]<<" "<<vA[1]<<"\nVB "<<vB[0]<<" "<<vB[1]<<"\nVC "<<vC[0]<<" "<<vC[1]<<"\nV1 "<<v1[0]<<" "<<v1[1]<<"\n";
		drawLine(v0,vA);
		drawLine(vA,vB);
		drawLine(vB,vC);
		drawLine(vC,v1);
		return;
	}
	else
	{
		KochLine(v0,vA,depth-1);
        KochLine(vA,vB,depth-1);
        KochLine(vB,vC,depth-1);
        KochLine(vC,v1,depth-1);
	}
}

void drawLine(GLfloat A[2], GLfloat B[2])
{
    GLfloat v0[2],v1[2];
    std::cout<<"Before"<<A[0]<<" "<<A[1]<<" "<<B[0]<<" "<<B[1]<<std::endl;
    map_point(0,0,SCREEN_W,SCREEN_H,-1,1,1,-1,A[0],A[1],v0[0],v0[1]);
    map_point(0,0,SCREEN_W,SCREEN_H,-1,1,1,-1,B[0],B[1],v1[0],v1[1]);
    std::cout<<"After"<<v0[0]<<" "<<v0[1]<<" "<<v1[0]<<" "<<v1[1]<<std::endl;

    glBegin(GL_LINES);
    glVertex2fv(v0);
    glVertex2fv(v1);
    glEnd();
}


void kochSnowflake(GLfloat P[2],
                   GLfloat Q[2],
                   GLfloat R[2],int depth)
{
    KochLine(P, Q, depth);
    KochLine(Q, R, depth);
    KochLine(R, P, depth);
}

GLfloat** points(GLfloat v[3][2],GLfloat ans[3][2],GLfloat incx, GLfloat incy)
{
    for (int i = 0; i < 3; ++i)
    {
        ans[i][0] = v[i][0] + incx;
        ans[i][1] = v[i][1] + incy;
    }
}
void display()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

// equilateral triangle
    GLfloat v[3][2] = {{5,14},
    {25, 48.64},
    {45, 14}},v1[3][2],v2[3][2],v3[3][2];
// begin transformations.
    /* Transformation magic. */
    kochSnowflake(v[0], v[1], v[2],0);
    points(v,v1,50,0);
    kochSnowflake(v1[0], v1[1], v1[2],1);
    points(v,v2,0,50);
    kochSnowflake(v2[0], v2[1], v2[2],2);
    points(v,v3,50,50);
    kochSnowflake(v3[0], v3[1], v3[2],3);

    /* Transformation magic. */
    //kochSnowflake(v[0], v[1], v[2],0);
    /* Transformation magic. */
    //kochSnowflake(v[0], v[1], v[2],0);
    /* Transformation magic. */
    //kochSnowflake(v[0], v[1], v[2],0);
// end transformations.
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_W,SCREEN_H);
    glutInitWindowPosition(50,50);
    glutCreateWindow("6: Color bars");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
