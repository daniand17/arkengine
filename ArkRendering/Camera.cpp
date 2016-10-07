#include "Camera.h"
#include "ArkMath.h"
#include "OpenGLRenderer.h"

Camera::Camera(CameraTypes cameraType, float fov, float nearPlane, float farPlane, Vec2 screenOrigin, Vec2 percScreenDim)
	: mProjectionType(cameraType)
	, mFov(fov)
	, mNearPlane(nearPlane)
	, mFarPlane(farPlane)
	, mAnchor(screenOrigin)
	, mScreenDim(percScreenDim)
	, mProjectionDirty(true)
	, mViewDirty(true)
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
	OpenGLRenderer const * renderer = OpenGLRenderer::Instance();

	ArkWindow const * win = renderer->GetWindowHandle();

	if(mProjectionType == Perspective )
		mProjection = ArkMath::perspective(ArkMath::toRadians(mFov), win->aspectRatio(), mNearPlane, mFarPlane);

	mProjectionDirty = false;
}

void Camera::recalculateViewMatrix()
{
	mView = ArkMath::lookAt(mPosition, mTarget, Vec3(0, 1, 0));
	mViewDirty = false;
}