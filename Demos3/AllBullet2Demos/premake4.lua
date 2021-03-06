	
		project "App_AllBullet2Demos"

		language "C++"
				
		kind "ConsoleApp"
		targetdir "../../bin"

  	includedirs {
                ".",
                "../../src",
                "../../btgui"
                }

		initOpenGL()
		initGlew()
			
		links{"gwen", "OpenGL_Window","OpenGL_TrueTypeFont","BulletSoftBody","BulletDynamics","BulletCollision","LinearMath"}
		
		files {
		"**.cpp",
		"**.h",
		"../bullet2/BasicDemo/Bullet2RigidBodyDemo.cpp",
		"../bullet2/BasicDemo/Bullet2RigidBodyDemo.h",
		"../bullet2/FeatherstoneMultiBodyDemo/BulletMultiBodyDemos.cpp",
		"../bullet2/FeatherstoneMultiBodyDemo/BulletMultiBodyDemos.h",
		"../bullet2/FeatherstoneMultiBodyDemo/MultiDofDemo.cpp",
		"../bullet2/FeatherstoneMultiBodyDemo/MultiDofDemo.h",
		"../bullet2/BasicDemo/BasicDemo.cpp",
		"../bullet2/BasicDemo/BasicDemo.h",
		"../bullet2/RagdollDemo/RagdollDemo.cpp",
		"../bullet2/RagdollDemo/RagdollDemo.h",
		"../../src/Bullet3Common/**.cpp",
 		"../../src/Bullet3Common/**.h",
		"../../btgui/Timing/b3Clock.cpp",
		"../../btgui/Timing/b3Clock.h",
		"../GpuDemos/gwenUserInterface.cpp",
		"../GpuDemos/gwenUserInterface.h"
		}

if os.is("Linux") then links{"X11"} end
if os.is("MacOSX") then
                        links{"Cocoa.framework"}
end
