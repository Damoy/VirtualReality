// FORNALI Damien
// Master 2 - IFI, Nice-Sophia-Antipolis University, 2019
// -------------

#include "camera.h"

Camera::Camera(){
    m_fov = 30.0f;
    m_aspect_ratio = 4 / 3.0f;
    m_zmin = 0.1f;
    m_zmax = 1000.0f;

    m_position = QVector3D(0, 0, 4);
    m_target = QVector3D(0, 0, 0);
    m_up = QVector3D(0, 1, 0);
}

QMatrix4x4 Camera::projection(){
    QMatrix4x4 projectionMatrix = QMatrix4x4();
    projectionMatrix.perspective(m_fov, m_aspect_ratio, m_zmin, m_zmax);
    return projectionMatrix;
}

QMatrix4x4 Camera::view(){
    QMatrix4x4 viewMatrix = QMatrix4x4();
    viewMatrix.lookAt(m_position, m_target, m_up); // + m_position
    return viewMatrix;
}

GLfloat Camera::fov() const
{
    return m_fov;
}

void Camera::setFov(GLfloat fov)
{
    m_fov = fov;
}

GLfloat Camera::aspect_ratio() const
{
    return m_aspect_ratio;
}

void Camera::setAspect_ratio(GLfloat aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
}

GLfloat Camera::zmin() const
{
    return m_zmin;
}

void Camera::setZmin(GLfloat zmin)
{
    m_zmin = zmin;
}

GLfloat Camera::zmax() const
{
    return m_zmax;
}

void Camera::setZmax(GLfloat zmax)
{
    m_zmax = zmax;
}

QVector3D Camera::position() const
{
    return m_position;
}

void Camera::setPosition(const QVector3D &position)
{
    m_position = position;
}

QVector3D Camera::target() const
{
    return m_target;
}

void Camera::setTarget(const QVector3D &target)
{
    m_target = target;
}

QVector3D Camera::up() const
{
    return m_up;
}

void Camera::setUp(const QVector3D &up)
{
    m_up = up;
}
