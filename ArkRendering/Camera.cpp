#include "Camera.h"
#include "ArkMath.h"
#include "OpenGLRenderer.h"

Camera::Camera(ArkWindow * window, CameraTypes cameraType, float fov, float nearPlane, float farPlane, Vec2 screenOrigin, Vec2 percScreenDim)
	: mProjectionType(cameraType)
	, mFov(fov)
	, mNearPlane(nearPlane)
	, mFarPlane(farPlane)
	, mAnchor(screenOrigin)
	, mScreenDim(percScreenDim)
	, mProjectionDirty(true)
	, mViewDirty(true)
	, m_window(window)
{
	refreshCamera();
}



void Camera::refreshCamera()
{
	 if ( mProjectionDirty ) 
		 recalculateProjectionMatrix();

	 if ( mViewDirty )
		 recalculateViewMatrix();
}



void Camera::recalculateProjectionMatrix()
{
	if(mProjectionType == Perspective )
		mProjection = ArkMath::perspective(ArkMath::toRadians(mFov), m_window->aspectRatio(), mNearPlane, mFarPlane);

	mProjectionDirty = false;
}



void Camera::recalculateViewMatrix()
{
	mView = ArkMath::lookAt(mPosition, mTarget, Vec3(0, 1, 0));
	mViewDirty = false;
}