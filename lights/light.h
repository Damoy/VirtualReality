#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>
#include <QVector3D>

class Light {

private:
    QColor m_ambientColor;
    QColor m_diffuseColor;
    QColor m_specularColor;
    QVector3D m_position;
    float m_specularStrength;

public:
    Light();

    QColor ambientColor() const;
    void setAmbientColor(QColor ambientColor);

    QColor diffuseColor() const;
    void setDiffuseColor(QColor diffuseColor);

    QColor specularColor() const;
    void setSpecularColor(QColor specularColor);

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    float specularStrength() const;
    void setSpecularStrength(float m_specularStrength);
};

#endif // LIGHT_H
