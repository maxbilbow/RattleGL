//
//  cStuff.c
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#import <GLUT/GLUT.h>
#import <GLKit/GLKit.h>
#import <SceneKit/SceneKit.h>
#import "RMXMaths.h"
#import <RattleGL-Swift.h>
#import "cStuff.h"


void RMXMakeLookAtGL(void (* lookAt)(double eyeX, double eyeY, double eyez,
                                     double centerX, double centerY, double centerZ,
                                     double upX, double upY, double upZ),double eyeX, double eyeY, double eyez,
                     double centerX, double centerY, double centerZ,
                     double upX, double upY, double upZ) { 
    lookAt(eyeX,eyeY,eyez,
           centerX,centerY,centerZ,
           upX,upY,upZ);
    
}

void RMXGLKMakeLookAt(GLKBaseEffect * effect,RMXCamera * view) {
    effect.transform.modelviewMatrix = GLKMatrix4MakeLookAt(view.eye.x, view.eye.y, view.eye.z,
                                 view.center.x, view.center.y, view.center.z,
                                 view.up.x, view.up.y, view.up.z );
}


void RMXGLMakeLookAt(RMXCamera * view) {
    gluLookAt(view.eye.x, view.eye.y, view.eye.z,
              view.center.x, view.center.y, view.center.z,
              view.up.x, view.up.y, view.up.z );

}


void RMXGLMaterialfv(int32_t a,int32_t b, GLKVector4 color){
    glMaterialfv(a,b,color.v);
}

void RMXGLTranslate(RMXVector3 v){
    glTranslatef(v.x, v.y, v.z);
}

void RMXGLShine(int32_t a, int32_t b, GLKVector4 color) {
    glLightfv(a, b, color.v);
}

void RMXGLRender(void (*render)(float),float size) {
    render(size);
}

void RMXGLCenter(void (*center)(int,int),int x, int y){
    center(x,y);
}

void RMXCGGetLastMouseDelta(int * x, int * y) {
    CGGetLastMouseDelta(x,y);
}

GLKVector4 RMXRandomColor() {
    //float rCol[4];
    GLKVector4 rCol = GLKVector4Make(0,0,0,0);
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol.v[i] = (rand() % 800)/500;
        
        rCol.v[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
        //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
        return rCol;
}

void RMXGLPostRedisplay(){
    glutPostRedisplay();
}

void RMXGLMakePerspective(float fovy, float aspect, float near, float far){
    gluPerspective(fovy, aspect, near, far);
}

void RMXGlutSwapBuffers(){
    glutSwapBuffers();
}

void RMXGlutInit(int argc, char * argv[]){
    glutInit(&argc, argv);
}

void RMXGlutInitDisplayMode(unsigned int mode){
    glutInitDisplayMode(mode);
}
void RMXGlutEnterGameMode(){
    glutEnterGameMode();
}

void RMXGlutMakeWindow(int posx,int posy, int w, int h, const char * name){
    glutInitWindowPosition(posx,posy);
    glutInitWindowSize(w,h);
    glutCreateWindow(name);
}

void RMXGLRegisterCallbacks(void *display,void *reshape){
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
}