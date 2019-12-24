//========= Copyright Valve Corporation ============//

#ifndef DEVICE_VR_OPENVR_TEST_TEST_HELLOVR_H
#define DEVICE_VR_OPENVR_TEST_TEST_HELLOVR_H

/*  #include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#if defined( OSX )
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>
#include <OpenGL/glu.h>
// Apple's version of glut.h #undef's APIENTRY, redefine it
#define APIENTRY
#else
#include <GL/glu.h>
#endif */
#include <stdio.h>
#include <string>
#include <cstdlib>
// #include <cstdarg>

// #include <openvr.h>
#include "third_party/openvr/src/headers/openvr.h"

// #include "shared/lodepng.h"
#include "shared/Matrices.h"
#include "shared/Vectors.h"
// #include "shared/pathtools.h"

/* #if defined(POSIX)
#include "unistd.h"
#endif */

Matrix4 makePerspectiveMatrix(float left, float right, float top, float bottom, float n, float f);

//-----------------------------------------------------------------------------
// Purpose:
//------------------------------------------------------------------------------
class CMainApplication
{
public:
	CMainApplication( /*int argc, char *argv[]*/ );
	virtual ~CMainApplication();

	bool BInit();
  bool init2();
  // bool ConnectToVRRuntime();
	bool BInitGL();
	bool BInitCompositor();

	void Shutdown();

	// void RunMainLoop();
	// bool HandleInput();
	void ProcessVREvent( const vr::VREvent_t & event );
	// void RenderFrame();
  
  void PreRender();
  void PostRender(uintptr_t texId);

	// bool SetupTexturemaps();

	/* void SetupScene();
	void AddCubeToScene( Matrix4 mat, std::vector<float> &vertdata );
	void AddCubeVertex( float fl0, float fl1, float fl2, float fl3, float fl4, std::vector<float> &vertdata ); */

	// void RenderControllerAxes();

	bool SetupStereoRenderTargets();
	// void SetupCompanionWindow();
	void SetupCameras();

	// void RenderStereoTargets();
	// void RenderCompanionWindow();
	// void RenderScene( vr::Hmd_Eye nEye );

	Matrix4 GetHMDMatrixProjectionEye( vr::Hmd_Eye nEye );
	void GetProjectionRaw( vr::Hmd_Eye nEye, float* l, float* r, float* t, float* b );
	Matrix4 GetHMDMatrixPoseEye( vr::Hmd_Eye nEye );
	Matrix4 GetCurrentViewProjectionMatrix( vr::Hmd_Eye nEye );
	void UpdateHMDMatrixPose();

	Matrix4 ConvertSteamVRMatrixToMatrix4( const vr::HmdMatrix34_t &matPose );

	// GLuint CompileGLShader( const char *pchShaderName, const char *pchVertexShader, const char *pchFragmentShader );
	// bool CreateAllShaders();

	// CGLRenderModel *FindOrLoadRenderModel( const char *pchRenderModelName );

  vr::IVRSystem *m_pHMD;
	vr::IVRCompositor *m_pCompositor;

private: 
	bool m_bDebugOpenGL;
	bool m_bVerbose;
	bool m_bPerf;
	bool m_bVblank;
	bool m_bGlFinishHack;

	std::string m_strDriver;
	std::string m_strDisplay;
	vr::TrackedDevicePose_t m_rTrackedDevicePose[ vr::k_unMaxTrackedDeviceCount ];
	Matrix4 m_rmat4DevicePose[ vr::k_unMaxTrackedDeviceCount ];
	
	/* struct ControllerInfo_t
	{
		vr::VRInputValueHandle_t m_source = vr::k_ulInvalidInputValueHandle;
		vr::VRActionHandle_t m_actionPose = vr::k_ulInvalidActionHandle;
		vr::VRActionHandle_t m_actionHaptic = vr::k_ulInvalidActionHandle;
		Matrix4 m_rmat4Pose;
		CGLRenderModel *m_pRenderModel = nullptr;
		std::string m_sRenderModelName;
		bool m_bShowController;
	};

	enum EHand
	{
		Left = 0,
		Right = 1,
	};
	ControllerInfo_t m_rHand[2]; */

/* private: // SDL bookkeeping
	SDL_Window *m_pCompanionWindow;
	uint32_t m_nCompanionWindowWidth;
	uint32_t m_nCompanionWindowHeight;

	SDL_GLContext m_pContext; */

private: // OpenGL bookkeeping
	int m_iTrackedControllerCount;
	int m_iTrackedControllerCount_Last;
	int m_iValidPoseCount;
	int m_iValidPoseCount_Last;
	bool m_bShowCubes;
	Vector2 m_vAnalogValue;

	std::string m_strPoseClasses;                            // what classes we saw poses for this frame
	char m_rDevClassChar[ vr::k_unMaxTrackedDeviceCount ];   // for each device, a character representing its class

	int m_iSceneVolumeWidth;
	int m_iSceneVolumeHeight;
	int m_iSceneVolumeDepth;
	float m_fScaleSpacing;
	float m_fScale;
	
	int m_iSceneVolumeInit;                                  // if you want something other than the default 20x20x20
	
	float m_fNearClip;
	float m_fFarClip;

	float m_eyeWidth;

	/* GLuint m_iTexture;

	unsigned int m_uiVertcount;

	GLuint m_glSceneVertBuffer;
	GLuint m_unSceneVAO;
	GLuint m_unCompanionWindowVAO;
	GLuint m_glCompanionWindowIDVertBuffer;
	GLuint m_glCompanionWindowIDIndexBuffer;
	unsigned int m_uiCompanionWindowIndexSize;

	GLuint m_glControllerVertBuffer;
	GLuint m_unControllerVAO;
	unsigned int m_uiControllerVertcount; */

	Matrix4 m_mat4HMDPose;
	Matrix4 m_mat4eyePosLeft;
	Matrix4 m_mat4eyePosRight;

	Matrix4 m_mat4ProjectionCenter;
	Matrix4 m_mat4ProjectionLeft;
	Matrix4 m_mat4ProjectionRight;

	/* struct VertexDataScene
	{
		Vector3 position;
		Vector2 texCoord;
	};

	struct VertexDataWindow
	{
		Vector2 position;
		Vector2 texCoord;

		VertexDataWindow( const Vector2 & pos, const Vector2 tex ) :  position(pos), texCoord(tex) {	}
	};

	GLuint m_unSceneProgramID;
	GLuint m_unCompanionWindowProgramID;
	GLuint m_unControllerTransformProgramID;
	GLuint m_unRenderModelProgramID;

	GLint m_nSceneMatrixLocation;
	GLint m_nControllerMatrixLocation;
	GLint m_nRenderModelMatrixLocation;

	struct FramebufferDesc
	{
		GLuint m_nDepthBufferId;
		GLuint m_nRenderTextureId;
		GLuint m_nRenderFramebufferId;
		GLuint m_nResolveTextureId;
		GLuint m_nResolveFramebufferId;
	};
	FramebufferDesc leftEyeDesc;

	bool CreateFrameBuffer( int nWidth, int nHeight, FramebufferDesc &framebufferDesc ); */
	
	uint32_t m_nRenderWidth;
	uint32_t m_nRenderHeight;

	// std::vector< CGLRenderModel * > m_vecRenderModels;

	/* vr::VRActionHandle_t m_actionHideCubes = vr::k_ulInvalidActionHandle;
	vr::VRActionHandle_t m_actionHideThisController = vr::k_ulInvalidActionHandle;
	vr::VRActionHandle_t m_actionTriggerHaptic = vr::k_ulInvalidActionHandle;
	vr::VRActionHandle_t m_actionAnalongInput = vr::k_ulInvalidActionHandle;

	vr::VRActionSetHandle_t m_actionsetDemo = vr::k_ulInvalidActionSetHandle; */
  
  vr::VROverlayHandle_t m_ulOverlayHandle;
  ID3D11Resource *m_overlayTexture;
  uint32_t m_overlayTextureWidth;
  uint32_t m_overlayTextureHeight;
  ETextureType m_overlayTextureAPIType;
  EColorSpace m_overlayTextureColorSpace;
  VRTextureBounds_t m_overlayTextureBounds;
  vr::HmdError m_eLastHmdError;
  
  // custom
  // int texWidth;
  // int texHeight;
};

#endif