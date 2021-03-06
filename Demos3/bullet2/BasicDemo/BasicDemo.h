#ifndef BASIC_DEMO_H
#define BASIC_DEMO_H

#include "LinearMath/btVector3.h"
#include "Bullet2RigidBodyDemo.h"



class BasicDemo : public Bullet2RigidBodyDemo
{

public:

	static BulletDemoInterface* MyCreateFunc(SimpleOpenGL3App* app)
	{
		return new BasicDemo(app);
	}

	BasicDemo(SimpleOpenGL3App* app);
	virtual ~BasicDemo();
	
	void	createGround(int cubeShapeId);

	void	initPhysics();
	void	exitPhysics();
	void	renderScene();
	void	stepSimulation(float dt);
};


#endif //BASIC_DEMO_H
