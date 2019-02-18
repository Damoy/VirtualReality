#include "avion.h"

Avion::Avion() :
    Model::Model(QString("C:/Users/user/Downloads/dev/school/m2/RV/TP8/GeeBee2.x")){
    m_vitesse = 0.0f;
    m_tangage = 0.0f;
    m_lacet = 0.0f;
    m_roulis = 0.0f;
    m_position = QVector3D(0, 0, 0);
}

void Avion::avance(float deltaT){
    // roulis pour tourner sur les cotes (roll)
    // (tangage) pitch pour monter / descendre
    // lacet (yaw) changer de direction
    float deltaVitesse = m_vitesse * deltaT;

//    Camera sphérique:
//    GLfloat x = m_spheriqueTarget.x() + (m_rho * qCos(m_phi) * qCos(m_theta));
//    GLfloat y = m_spheriqueTarget.y() + (m_rho * qSin(m_phi));
//    GLfloat z = m_spheriqueTarget.z() + (m_rho * qCos(m_phi) * qSin(m_theta));

//    Plusieurs essais

//    float dx = deltaVitesse * qCos(qDegreesToRadians(m_lacet)) * qCos(qDegreesToRadians(m_tangage));
//    float dy = deltaVitesse * qSin(qDegreesToRadians(m_lacet)); // m_lacet ?
//    float dz = -deltaVitesse * qCos(qDegreesToRadians(m_lacet)) * qSin(qDegreesToRadians(m_tangage));

//    float dx = deltaVitesse * qCos(qDegreesToRadians(m_lacet))* qCos(qDegreesToRadians(m_tangage));
//    float dy = deltaVitesse * qSin(qDegreesToRadians(m_lacet)) * qSin(qDegreesToRadians(m_tangage));
//    float dz = deltaVitesse * qSin(qDegreesToRadians(m_tangage));

//    float dx = deltaVitesse * qCos(qDegreesToRadians(m_lacet));
//    float dy = deltaVitesse * qSin(qDegreesToRadians(m_lacet));
//    float dz = -deltaVitesse * qCos(qDegreesToRadians(m_lacet)) * qCos(qDegreesToRadians(m_tangage));

    float dx = deltaVitesse * sin(qDegreesToRadians(m_lacet)) * -1;
    float dy = deltaVitesse * qDegreesToRadians(m_tangage);
    float dz = deltaVitesse * cos(qDegreesToRadians(m_lacet)) * -1;

    QVector3D offset = QVector3D(dx, dy, dz);

    m_position += offset;

    for(Mesh* mesh : m_meshes){
        mesh->setPosition(mesh->position() + offset); //
    }

    // helice
    m_meshes.at(2)->rotateOf(0.0f, 0.0f, m_vitesse * 2);

    // m_roulis par 0.98f dans avance, pour l’avion et tous ses Mesh sauf le
    // Mesh n°2 (l’hélice)
    m_roulis *= 0.98f;

    for(int i = 0; i < m_meshes.size(); ++i){
        if(i == 2) continue;
        m_meshes.at(i)->setRoulis(m_meshes.at(i)->roulis() * 0.98f);
    }

    std::cout << "x: " << m_position.x() << ", y: " << m_position.y() << ", z: " << m_position.z() << std::endl;
}

void Avion::accelere(float acc){
    m_vitesse += acc;
}

float Avion::vitesse() const
{
    return m_vitesse;
}

void Avion::setVitesse(float vitesse)
{
    m_vitesse = vitesse;
}
