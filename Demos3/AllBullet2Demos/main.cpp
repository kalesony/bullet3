#include "../../btgui/OpenGLWindow/SimpleOpenGL3App.h"
#include "Bullet3Common/b3Vector3.h"
#include "assert.h"
#include <stdio.h>

#include "../GpuDemos/gwenUserInterface.h"
#include "BulletDemoEntries.h"

#define DEMO_SELECTION_COMBOBOX 13

void initGUI();

static SimpleOpenGL3App* app=0;
static GwenUserInterface* gui  = 0;
static int sCurrentDemoIndex = 0;
static BulletDemoInterface* sCurrentDemo = 0;
static b3AlignedObjectArray<const char*> allNames;

extern bool useShadowMap;
static bool wireframe=false;
static bool pauseSimulation=false;
void MyKeyboardCallback(int key, int state)
{

	bool handled = false;
	if (sCurrentDemo)
	{
		handled = sCurrentDemo->keyboardCallback(key,state);
	}
	//checkout: is it desired to ignore keys, if the demo already handles them?
	//if (handled)
	//	return;

	if (key=='w' && state)
	{
		wireframe=!wireframe;
		if (wireframe)
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		} else
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}
	if (key=='I' && state)
	{
		pauseSimulation = !pauseSimulation;
	}

	if (key=='s' && state)
	{
		useShadowMap=!useShadowMap;
	}

	if (key==B3G_ESCAPE && app && app->m_window)
	{
		app->m_window->setRequestExit();
	}
	
	b3DefaultKeyboardCallback(key,state);
	
}

static void MyMouseMoveCallback( float x, float y)
{
	bool handled = false;
	if (sCurrentDemo)
		handled = sCurrentDemo->mouseMoveCallback(x,y);
	if (!handled && gui)
		handled = gui->mouseMoveCallback(x,y);
	if (!handled)
		b3DefaultMouseMoveCallback(x,y);
}
static void MyMouseButtonCallback(int button, int state, float x, float y)
{
	bool handled = false;
	//try picking first
	if (sCurrentDemo)
		handled = sCurrentDemo->mouseButtonCallback(button,state,x,y);

	if (!handled && gui)
		handled = gui->mouseButtonCallback(button,state,x,y);

	if (!handled)
		b3DefaultMouseButtonCallback(button,state,x,y);
}

#include <string.h>

void selectDemo(int demoIndex)
{
	sCurrentDemoIndex = demoIndex;
	int numDemos = sizeof(allDemos)/sizeof(BulletDemoEntry);
	if (demoIndex>numDemos)
		demoIndex = 0;

	if (sCurrentDemo)
	{
		sCurrentDemo->exitPhysics();
		app->m_instancingRenderer->removeAllInstances();
		delete sCurrentDemo;
		sCurrentDemo=0;
	}

	if (allDemos[demoIndex].m_createFunc && app)
	{
		sCurrentDemo = (*allDemos[demoIndex].m_createFunc)(app);
		if (sCurrentDemo)
		{
			sCurrentDemo->initPhysics();
			sCurrentDemo->initGUI(gui);
		}
	}
}

void	MyComboBoxCallback(int comboId, const char* item)
{
	printf("comboId = %d, item = %s\n",comboId, item);
	if (comboId==DEMO_SELECTION_COMBOBOX)
	{
		//find selected item
		for (int i=0;i<allNames.size();i++)
		{
			if (strcmp(item,allNames[i])==0)
			{
				initGUI();
				selectDemo(i);
				saveCurrentDemoEntry(sCurrentDemoIndex);
				break;
			}
		}
	}
	
}

void initGUI()
{
	if(gui)
		gui->reset();
	else
	{
		sth_stash* fontstash=app->getFontStash();
		gui = new GwenUserInterface;
		gui->init(app->m_instancingRenderer->getScreenWidth(),app->m_instancingRenderer->getScreenHeight(),fontstash,app->m_window->getRetinaScale());

		int numDemos = sizeof(allDemos)/sizeof(BulletDemoEntry);		
	
		for (int i=0;i<numDemos;i++)
		{
			allNames.push_back(allDemos[i].m_name);
		}
	}
		
	gui->registerComboBox(DEMO_SELECTION_COMBOBOX,allNames.size(),&allNames[0],sCurrentDemoIndex);	
		
	//const char* names2[] = {"comboF", "comboG","comboH"};
	//gui->registerComboBox(2,3,&names2[0],0);

	gui->setComboBoxCallback(MyComboBoxCallback);	
}

int main(int argc, char* argv[])
{
	
	float dt = 1./120.f;
	int width = 1024;
	int height=768;

	app = new SimpleOpenGL3App("AllBullet2Demos",width,height);
	app->m_instancingRenderer->setCameraDistance(13);
	app->m_instancingRenderer->setCameraPitch(0);
	app->m_instancingRenderer->setCameraTargetPosition(b3MakeVector3(0,0,0));
	app->m_window->setMouseMoveCallback(MyMouseMoveCallback);
	app->m_window->setMouseButtonCallback(MyMouseButtonCallback);
	app->m_window->setKeyboardCallback(MyKeyboardCallback);

	GLint err = glGetError();
    assert(err==GL_NO_ERROR);

	initGUI();
	selectDemo(loadCurrentDemoEntry());

	do
	{

		GLint err = glGetError();
		assert(err==GL_NO_ERROR);
		app->m_instancingRenderer->init();
		app->m_instancingRenderer->updateCamera();
		
		app->drawGrid();
		char bla[1024];
		static int frameCount = 0;
		frameCount++;
		sprintf(bla,"Simple test frame %d", frameCount);
		
		app->drawText(bla,10,10);
		if (sCurrentDemo)
		{
			if (!pauseSimulation)
				sCurrentDemo->stepSimulation(1./60.f);
			sCurrentDemo->renderScene();
		}

		static int toggle = 1;
		if (1)
		{
		gui->draw(app->m_instancingRenderer->getScreenWidth(),app->m_instancingRenderer->getScreenHeight());
		}
		toggle=1-toggle;
		app->swapBuffer();
	} while (!app->m_window->requestedExit());

	selectDemo(0);
	delete gui;
	delete app;
	return 0;
}
