//
//  ShapeObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_ShapeObject_h
#define OpenGL_2_0_ShapeObject_h


#endif
class ShapeObject : public Particle {
protected:
    //GLKVector4 position;
    float size =1;
    GLKVector4 color = GLKVector4Make(1,1, 1, 10);
    const float nill[4] = {0,0,0,0};
    float rotation = 0;
    bool isRotating = false;

    GLKVector3 rAxis = GLKVector3Make(0,0,1);
public:
    void draw(void (*drawMe)(float size)){
        glPushMatrix();
       
        glRotatef(rotation, rAxis.x, rAxis.y, rAxis.z);
        
        glPushMatrix();
        
        glTranslatef(anchor.x,anchor.y, anchor.z);
        glTranslatef(position.x,position.y,position.z);
        setMaterial();
        drawMe(size);
        unsetMaterial();
        
        //glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }

    
    bool temp = true;
    void animate(){
        if (temp) tester.checks[9] += "\nSHAPE:\n" + toString();
        if (isRotating) rotation += dt;//*dift;// * 30;
        Particle::animate();
    }

    virtual void setMaterial(){
        //glMaterialfv(GL_FRONT,GL_EMISSION, color.v);
    }
    
    virtual void unsetMaterial(){
        //glMaterialfv(GL_FRONT, GL_EMISSION,nill);
    }
    
    float * getColorfv(){
        return color.v;
    }
    
    void setColor(float * color){
        this->color = GLKVector4MakeWithArray(color);
    }
    
    void setrAxis(GLKVector3 axis){
        rAxis = axis;
    }
    
    void setTranslation(GLKVector3 vector){
        
    }
};