#include"camera.h"

Camera::Camera(float x, float y)
{
	m_view.setCenter(x, y);
}

void Camera::update(float x, float y)
{
	m_view.setCenter(x, y);
}