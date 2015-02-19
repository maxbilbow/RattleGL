//
//  Art.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Art_h
#define OpenGL_2_0_Art_h


#endif

#include "Shapes.h"
#include "LightSource.h"

ShapeObject * sh, * sh2, * sh3, *sh4;
void RenderObjects(void);

float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
float red[4]             = { 1.0, 0.0, 0.0, 1.0 };
float green[4]           = { 0.0, 0.0, 1.0, 1.0 };
float yellow[4]          = { 1.0, 0.0, 1.0, 1.0 };
class Art {
    
    //ShapeObject * shape = new ShapeObject[4];
    
public:
    
    GLfloat x, y, z, d, r,g, b,k;
    typedef enum: GLint{
        XY,
        XZ,
        YX,
        YZ,
        ZX,
        ZY
    } PLANE;
    
    Art(){
        this->x = 0;//45.0f;
        this->y = (GLfloat)250/(GLfloat)250;
        this->z = 0.1f;
        this->d = 100.0f;
        this->r = 0.5f;
        this->g = 0.2f;
        this->b = 0.2f;
        this->k = 0.0f;
       
        /*
        shape[0].setPosition(GLKVector3Make(6,0,0));
        
        shape[1].setPosition(GLKVector3Make(-6,0,0));
        shape[2].setPosition(GLKVector3Make(0,0,6));
        shape[3].setPosition(GLKVector3Make(0,0,6));
                            
        shape[0].setColor(colorBlue);
        shape[1].setColor(colorBronzeDiff);
        shape[2].setColor(green);
        shape[3].setColor(yello);
         */
        
        
    }
    
  
    
    
    void drawCube(void){
        
        //
        glBegin(GL_QUADS);
        // top
        glColor3f(1.0f, 0.0f, 0.0f);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        // front
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        // right
        glColor3f(0.0f, 0.0f, 1.0f);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        // left
        glColor3f(0.0f, 0.0f, 0.5f);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        // bottom
        glColor3f(0.5f, 0.0f, 0.0f);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        
        glEnd();
        
        glBegin(GL_QUADS);
        // back
        glColor3f(0.0f, 0.5f, 0.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        
        glEnd();
    }
   
    void drawPlane(){
        glPushMatrix();
        //glColor4fv(colorBlue);

        glTranslatef(0, -1, 0);
        glBegin(GL_QUADS);
        glVertex3f( -_INFINITY,-0.001, -_INFINITY);
        glVertex3f( -_INFINITY,-0.001,_INFINITY);
        glVertex3f(_INFINITY,-0.001,_INFINITY);
        glVertex3f(_INFINITY,-0.001, -_INFINITY);
        glEnd();
        glPopMatrix();
        
//        glBegin(GL_LINES);
//        for(int i=0;i<=10;i++) {
//            if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
//            glVertex3f(i,0,0);
//            glVertex3f(i,0,10);
//            if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
//            glVertex3f(0,0,i);
//            glVertex3f(10,0,i);
//        };
//        glEnd();
    }
    
    void animate(){
       // shanimate();
        // We don't use bias in the shader, but instead we draw back faces,
        // which are already separated from the front faces by a small distance
        // (if your geometry is made this way)
        //glCullFace(GL_FRONT);
        glClearColor(r, g, b, y);
        glPushMatrix();
        
        RenderObjects();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GLKVector4Make(0.8,0.8,0.8,1).v);
        drawPlane();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorNone);
        
        
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorBlue);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
        glColor4fv(colorBlue);
        glPushMatrix();
        glTranslatef(0, 0, 3);
        //glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
        DrawCubeWithTextureCoords(1.0);//drawCube();
        glPopMatrix();
        
        
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_SPECULAR, sh4->getColorfv());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sh4->getColorfv());
        glTranslatef(0, sin(g_fTeapotAngle2/100)+0.5, -3);
        glPushMatrix();
        //glRotatef(g_fTeapotAngle2,0, 1, 0);
        sh4->draw(DrawCubeWithTextureCoords);
       
        glPopMatrix();
        glPopMatrix();
        
        
        
        glMaterialfv(GL_FRONT, GL_SPECULAR, sh3->getColorfv());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sh3->getColorfv());
        glPushMatrix();
        //glTranslatef(3, 0, 0);
        sh3->draw(DrawCubeWithTextureCoords);
        glPopMatrix();
        
        
        glMaterialfv(GL_FRONT, GL_SPECULAR, sh2->getColorfv());
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sh2->getColorfv());
        glPushMatrix();
        sh2->draw(DrawCubeWithTextureCoords);
        glPopMatrix();
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, sh->getColorfv());
        glMaterialfv(GL_FRONT, GL_SPECULAR, sh->getColorfv());
        sh->draw(DrawCubeWithTextureCoords);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
        
//        for(int i=0;i<sizeof(shape);++i){
//            glMaterialfv(GL_FRONT, GL_DIFFUSE, shape[i].getColorfv());
//            glMaterialfv(GL_FRONT, GL_SPECULAR, shape[i].getColorfv());
//            shape[i].draw(DrawCubeFace);
//            glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
//            glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
//        }
        glPopMatrix();
        
        }
    
};

//Particle pCube = Particle();

void RenderObjects(void)
{
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    // Main object (cube) ... transform to its coordinates, and render
    glRotatef(15, 1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glRotatef(g_fTeapotAngle, 0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    glColor4fv(colorBlue);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
    DrawCubeWithTextureCoords(1.0);
    // Child object (teapot) ... relative transform, and render
    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(g_fTeapotAngle2, 1, 1, 0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glColor4fv(colorBronzeDiff);
    glBindTexture(GL_TEXTURE_2D, 0);
    glutSolidTeapot(0.3);
    glPopMatrix();
    glPopMatrix();

    
}

Art art = Art();


