
#ifndef MULTI_DOF_DEMO_H
#define MULTI_DOF_DEMO_H

#include "BulletMultiBodyDemos.h"
#include "BulletDynamics/Featherstone/btMultiBody.h"

struct SimpleGuiHandler;				//forward declaration for friendness

class MultiDofDemo : public FeatherstoneDemo1
{
protected:
	btAlignedObjectArray<btMultiBody*> m_multiBodies;
	
public:

	MultiDofDemo(SimpleOpenGL3App* app);
	virtual ~MultiDofDemo();


	static BulletDemoInterface* MyCreateFunc(SimpleOpenGL3App* app)
	{
		return new MultiDofDemo(app);
	}
	
	virtual void	initPhysics();
	virtual void	initGUI(GwenUserInterface *pGUI);

	virtual void	stepSimulation(float deltaTime);

	btMultiBody* createFeatherstoneMultiBody_testMultiDof(class btMultiBodyDynamicsWorld* world, int numLinks, const btVector3& basePosition, const btVector3 &baseHalfExtents, const btVector3 &linkHalfExtents, bool spherical = false, bool floating = false);
	void addColliders_testMultiDof(btMultiBody *pMultiBody, btMultiBodyDynamicsWorld *pWorld, const btVector3 &baseHalfExtents, const btVector3 &linkHalfExtents);
	void addBoxes_testMultiDof();

	friend struct SimpleGuiHandler;
};

struct SimpleGuiHandler
{
	static MultiDofDemo *m_pDemo;	

	//
	static void onGravityToggle(int buttonId, int state);
	static void onDampingToggle(int buttonId, int state);

private:
	SimpleGuiHandler();
};

#endif //MULTI_DOF_DEMO_H

