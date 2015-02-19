//
//  PointOfView.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_PointOfView_h
#define OpenGL_2_0_PointOfView_h


#endif

class PointOfView {
    
public:
    virtual GLKVector3 getEye(){
        cout << "EYE not overriden" << endl;
        return GLKVector3Make(0,0,0);
    }
    
    virtual GLKVector3 getCenter(){
        cout << "CENTER not overriden" << endl;
        return GLKVector3Make(0,0,1);
    }
    
    virtual GLKVector3 getUp(){
        cout << "UP not overriden" << endl;
        return GLKVector3Make(0,1,0);
    }
   
    template<typename Thing, typename Number>
    Thing makeLookAt(Thing (*lookAt)(Number eyeX,Number eyeY, Number eyeZ, Number cx,Number cy, Number cz, Number ux,Number uy, Number uz )){
        return (Thing)lookAt(
                             getEye().x,   getEye().y,     getEye().z,
                             getCenter().x, getCenter().y, getCenter().z,
                             getUp().x,     getUp().y,     getUp().z
                             );
    }
    
    
    
    template <typename Thing, typename Number>
    Thing makePerspective(Thing (*make)(Number fovyRadians, Number aspect, Number nearZ, Number farZ), float m, int width, int height){//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
        
        return (Thing)make(60*m ,width / height, 1.0, 1000.0);
    }
    
//    template<typename Number>
//    GLKMatrix4 setMatrix(GLKMatrix4 (*lookAt)(Number eyeX,Number eyeY, Number eyeZ, Number cx,Number cy, Number cz, Number ux,Number uy, Number uz )) {
//        return this->makeLookAt<GLKMatrix4>(lookAt);
//    }

    
    string toString(){
        string s = "Camera Attributes: ";
        s +=
         "\n      EYE: " + to_string(getEye().x) + ", " + to_string(getEye().y) + ", " + to_string(getEye().z) + ", " +
         "\n   CENTRE: " + to_string(getCenter().x) + ", " + to_string(getCenter().y) + ", " + to_string(getCenter().z) + ", "
         "\n       UP: " + to_string(getUp().x) +  ", " + to_string(getUp().y) +  ", " + to_string(getUp().z) +  ", ";
        return s;
    }
};