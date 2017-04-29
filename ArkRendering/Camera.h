#pragma once

#include "Mat4.h"
#include "Vec3.h"
#include "Vec2.h"

class ArkWindow;

class Camera
{
public:
	enum CameraTypes
	{
		Perspective,
		Orthographic
	};
	Camera(ArkWindow * window, CameraTypes cameraType, float fov, float nearPlane, float farPlane, Vec2 screenOrigin, Vec2 percScreenDim);

	Mat4 getProjectionMatrix() const		{ return mProjection; }
	Mat4 getViewMatrix() const				{ return mView; }
	Mat4 getCameraViewingMatrix() const		{ return mProjection * mView; }

	void refreshCamera();
	void setNearPlane	(float nearPlane)	{ mProjectionDirty = true; mNearPlane = nearPlane; }
	void setFarPlane	(float farPlane)	{ mProjectionDirty = true; mFarPlane = farPlane; }
	void setFieldOfView	(float fov)			{ mProjectionDirty = true; mFov = fov; }
	void setScreenOrigin(Vec2 newOrigin)	{ mProjectionDirty = true; mAnchor = newOrigin; }
	void setPercentageOfScreenDim(Vec2 perc){ mProjectionDirty = true; mScreenDim = perc; }

	void setTarget(Vec3 newTarget)			{ mViewDirty = true; mTarget = newTarget; }
	void setPosition(Vec3 newPosition)		{ mViewDirty = true; mPosition = newPosition; }

	void setWindow(ArkWindow * window) { m_window = m_window; }

	float getNearPlane() const		{ return mNearPlane; }
	float getFarPlane() const		{ return mFarPlane; }
	float getFieldOfView() const	{ return mFov; }

	Vec2 getScreenOrigin() const			{ return mAnchor; }
	Vec2 getPercentageOfScreenDim() const	{ return mScreenDim; }

	Vec3 getTarget() const		{ return mTarget; }
	Vec3 getPosition() const	{ return mPosition; }

private:
	void recalculateProjectionMatrix();
	void recalculateViewMatrix();

	Vec3 mPosition;
	Vec3 mTarget;	// TODO (AD) This should be a forward vector based on camera rotation

	CameraTypes mProjectionType;
	Mat4 mProjection;
	Mat4 mView;
	float mFov;
	float mNearPlane;
	float mFarPlane;
	Vec2 mAnchor;
	Vec2 mScreenDim;

	bool mProjectionDirty;
	bool mViewDirty;

	ArkWindow * m_window;
};