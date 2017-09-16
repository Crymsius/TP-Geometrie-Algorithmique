#include "gldisplay.h"
#include <vector>
#include <iostream>
#define POINTS 6000
#define CONTROL_VERTICES 4

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f)
{
    mesh.ReadFromOFF("/Users/crymsius/Desktop/Boulot/Master/ID3D/MGA/TP/DisplayMesh/DisplayMesh/queen.off");
   // mesh.ReadFromOFF("/Users/crymsius/Documents/Xcode/GeomMath/testGeomMath/test.off");
}

void GLDisplay::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
//    gasket.draw();

    drawMesh();
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-1.5f, 1.5f, -1.5f, 1.5f, -1.5f, 1.5f);
    //glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angle += (position.x() - _position.x());

        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _position = event->pos();
}

void GLDisplay::drawMesh()
{
    glBegin(GL_TRIANGLES);

    const std::vector<Vertex> vertices = mesh._Vertices();
    const std::vector<Face> faces = mesh._Faces();
    for(unsigned i = 0; i < faces.size(); ++i)
    {
        for (unsigned j = 0; j < faces[i].nbIndicesPerFace; ++j)
        {
            glVertex3f(vertices[faces[i].indices[j]].position.x,
                       vertices[faces[i].indices[j]].position.y,
                       vertices[faces[i].indices[j]].position.z);
        }
    }

    glEnd();
}
