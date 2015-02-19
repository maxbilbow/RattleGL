//
//  World.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_World_h
#define OpenGL_2_0_World_h


#endif
#define W_GRAVITY (0.01/50);
#define W_FRICTION 1.1;


#define VIEWING_DISTANCE_MIN  3.0
#define TEXTURE_ID_CUBE 1

class World : public Physics {
    const float _g = W_GRAVITY;
    const float _f = W_FRICTION;
    void init(){
        for (int i=0;i<NO_OF_SHAPES;++i){
            shapes[i] = new ShapeObject;
            shapes[i]->setPhysics(physics);
            //shapes[i]->setDt(&dt);
        }
        for (int i=0;i<NO_OF_LIGHTS;++i){
            lights[i] = new LightSource;
           // lights[i]
        }

    }
    
protected:
    Physics physics = Physics();
    
    
    
    Observer main = Observer();
    Observer * observers[1];// = new Observer[1];
   
    ShapeObject ground;
    float dt;
public:
    typedef enum {
        BOX1, BOX2, BOX3, BOX4,
        NO_OF_SHAPES
    }Objects;
    
    typedef enum {
        SUN, MOON
        , NO_OF_LIGHTS
    }Lights;
protected:
    ShapeObject * shapes[NO_OF_SHAPES];
    LightSource * lights[NO_OF_LIGHTS];
public: 
    
    
    World(){
        U_GRAVITY = &_g;
        U_FRICTION = &_f;
        observers[0] = &main;
        cout << NO_OF_SHAPES << endl;
        init();
    }
    
    ShapeObject * getShapes(){
        return * shapes;
    }
    
    void setShape(Objects obj , ShapeObject * shape){
        shapes[obj] = shape;
    }
    Observer * getMainObserver(){
        return &main;
    }
    
    void animate(){
        main.animate();
        for(int i=0;i<NO_OF_SHAPES;++i)
            shapes[i]->animate();
    }
    
    Particle * closestObject(){
        int closest = 0; float dista=GLKVector3Distance(main.getCenter(), shapes[0]->getPosition());
        for (int i=1;i<NO_OF_SHAPES;++i){
            float distb = GLKVector3Distance(main.getCenter(), shapes[i]->getPosition());
            string lt = " < ";
            if(distb<dista){
                closest = i;
                //shapes[i];
                lt = " > ";
                // cout << i-1 << ": "<< dista << lt << (i) <<": "<< distb << endl;
                dista = distb;
            }
           
        }
        //cout << "closest: "<< closest << ", dist:" << dista << endl;
        return shapes[closest];
    }
private:
//#ifdef _WIN32
//    last_idle_time = GetTickCount();
//#else
//    gettimeofday (&last_idle_time, NULL);
//#endif
//    struct timeval last_idle_time;
//    struct timeval time_now;
//    timeval get_time_now(){
//        return time_now;
//    }
//    
//    timeval* get_last_idle_time(){
//        return &last_idle_time;
//    }
//    void set_last_idle_time(timeval time){
//        last_idle_time = time;
//    }
};

World world = World();