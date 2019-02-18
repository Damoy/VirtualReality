#include "light.h"

Light::Light(){
    m_ambientColor = QColor(42, 42, 42, 255);
    m_diffuseColor = QColor(255, 255, 255, 255);
    m_specularColor = QColor(255, 255, 0, 255);
    m_position = QVector3D(0, 0, 10);
    m_specularStrength = 250.0f;
}

QColor Light::ambientColor() const
{
    return m_ambientColor;
}

void Light::setAmbientColor(QColor ambientColor)
{
    m_ambientColor = ambientColor;
}

QColor Light::diffuseColor() const
{
    return m_diffuseColor;
}

void Light::setDiffuseColor(QColor diffuseColor)
{
    m_diffuseColor = diffuseColor;
}

QColor Light::specularColor() const
{
    return m_specularColor;
}

void Light::setSpecularColor(QColor specularColor)
{
    m_specularColor = specularColor;
}

QVector3D Light::position() const
{
    return m_position;
}

void Light::setPosition(const QVector3D &position)
{
    m_position = position;
}

float Light::specularStrength() const
{
    return m_specularStrength;
}

void Light::setSpecularStrength(float specularStrength)
{
    m_specularStrength = specularStrength;
}
