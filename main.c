//
//  main.c
//  Bresenham
//
//  Created by Mingjia Shi 104467237 on 2018/1/29.
//  Copyright © 2018年 Mingjia Shi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>
#include <math.h>

typedef void (*GLUTdisplayCB) (void);

int xc1,xc2,yc1,yc2;

void myInit(int *, char **, GLUTdisplayCB);
//void myInit(GLUTdisplayCB);
void drawLine(void);

int main(int argc, const char * argv[]) {
    
    myInit(&argc,argv,drawLine);
    
    glutMainLoop();
    
    return 0;
}

void myInit(int *argc, char ** argv,GLUTdisplayCB displayFunc){
    int r = 200, g = 200, b = 200;
    printf("Start point coordinates:\n");
    fflush(stdout);
    scanf("%d %d",&xc1,&yc1);
    
    printf("End point coordinates:\n");
    fflush(stdout);
    scanf("%d %d",&xc2,&yc2);
    
    glutInit(argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    
    glutDisplayFunc(displayFunc);
    
    glClearColor(1.0,1.0,1.0,0.0);
    
    glColor3f(((float) r)/((float) 255.0), ((float) g)/((float) 255.0), ((float) b)/((float) 255.0));
    glPointSize(9.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void drawLine(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int dx,dy,pk,m;
    dx = abs(xc1 - xc2);
    dy = abs(yc1 - yc2);
    pk = 2 * dy - dx;
    if(xc1 != xc2) {
        m = (yc1 - yc2)/(xc1 - xc2);
        int step;
    
        if(m >= 0){
            step = 1;
        }
        else {
            step = -1;
        }
        
        int x,y,xf;
        if(xc1 < xc2) {
            x = xc1;
            y = yc1;
            xf = xc2;
        }
        else {
            x = xc2;
            y = yc2;
            xf = xc1;
        }
    
        while(x <= xf){
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
            x = x + 1;
            if(pk < 0){
                pk = pk + 2 * dy;
            }else {
                y = y + step;
                pk = pk + 2 * dy - 2 * dx;
            }
        }
    }else {
        int x = xc1,y,yf;
        if(yc1 < yc2) {
            y = yc1;
            yf = yc2;
        }
        else {
            y = yc2;
            yf = yc1;
        }
        while(y < yf){
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            glFlush();
            y = y + 1;
        }
    }
}

