#include "gldisplay.h"
#include <vector>
#include <iostream>
#define POINTS 6000
#define CONTROL_VERTICES 4

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent),
    _angle(0.0f)
{
//    mesh.ReadFromOFF("/Users/crymsius/Desktop/Boulot/Master/ID3D/MGA/TP/DisplayMesh/DisplayMesh/queen.off");
//        mesh.ReadFromOFF("/Users/crymsius/Documents/Xcode/GeomMath/testGeomMath/cube.off");

//    mesh.ReadFromPoints("/Users/crymsius/Documents/Xcode/GeomMath/testGeomMath/cloud_500.points");
    mesh.ReadFromPoints("/Users/crymsius/Documents/Xcode/GeomMath/testGeomMath/test_crust/line2.points");


    mesh.lawsonAll();
    shape = mesh.crust();
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

    if (displayswitch) {
        drawMesh();
    } else {
        drawShape();
    }
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glOrtho(-1.f, 1.f, -1.f, 1.f, 0.f, 0.f);
//    glOrtho(-1.5f, 1.5f, -1.5f, 1.5f, -1.5f, 1.5f);
    //glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
//    if( event != NULL ) {
//        QPoint position = event->pos();

//        _angle += (position.x() - _position.x());

//        _position = position;

//        updateGL();
//    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        displayswitch = !displayswitch;

//        _position = event->pos();
//        std::cout << "x : "<< _position.x()/320. - 1. << "  y : " << - (_position.y()/320. - 1.) << std::endl;
//        Vertex v;
//        v.position.x = _position.x()/320. - 1.;
//        v.position.y = - (_position.y()/320. - 1.);
//        v.position.z = 0;
//        mesh.inserer_sommet_delaunay_incr(v);
//        shape = mesh.crust();
        updateGL();
    }
}

void GLDisplay::keyPressEvent(QKeyEvent *event)
{
//    if( event != NULL ) {
//       shape = mesh.crust();
//       updateGL();
//    }

}

void GLDisplay::drawShape()
{
    const std::vector<Vertex> vertices = mesh._Vertices();
    const std::vector<std::pair<unsigned, unsigned>> aretes = shape.aretes;

    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.8);
    for(unsigned i = 0; i < aretes.size(); ++i)
    {
        glVertex3f(vertices[aretes[i].first].position.x,
                   vertices[aretes[i].first].position.y,
                   vertices[aretes[i].first].position.z);
        glVertex3f(vertices[aretes[i].second].position.x,
                   vertices[aretes[i].second].position.y,
                   vertices[aretes[i].second].position.z);
    }
    glEnd();
}

void GLDisplay::drawMesh()
{


//    Vertex v;
//    v.position.x = - 0.5;
//    v.position.y = - 0.5;
//    v.position.z = 0.;



    const std::vector<Vertex> vertices = mesh._Vertices();
    const std::vector<Face> faces = mesh._Faces();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
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

    glColor3f(0.0, 0.5, 1.0);
    for(unsigned i = 0; i < faces.size(); ++i)
    {
        glBegin(GL_LINE_LOOP);


            glVertex3f(vertices[faces[i].indices[0]].position.x,
                       vertices[faces[i].indices[0]].position.y,
                       vertices[faces[i].indices[0]].position.z);
            glVertex3f(vertices[faces[i].indices[1]].position.x,
                       vertices[faces[i].indices[1]].position.y,
                       vertices[faces[i].indices[1]].position.z);
            glVertex3f(vertices[faces[i].indices[2]].position.x,
                       vertices[faces[i].indices[2]].position.y,
                       vertices[faces[i].indices[2]].position.z);
            glEnd();
    }


//    glBegin(GL_LINES);
//    glPointSize(12);
//    glColor3f(1.0, 0.0, 0.0);
//    for(unsigned i = 0; i < faces.size(); ++i)
//    {
//        Cercle circle(faces[i], mesh);
//        for(unsigned j = 0; j <faces[i].facesAdjacentes.size(); ++j ) {
//            if (faces[i].facesAdjacentes[j] != -1) {
//                Cercle circleOp(faces[faces[i].facesAdjacentes[j]], mesh);
//                glVertex3f(circleOp.centre().x,
//                           circleOp.centre().y,
//                           circleOp.centre().z);
//                glVertex3f(circle.centre().x,
//                           circle.centre().y,
//                           circle.centre().z);
//            }
//        }
//    }
//    glEnd();


    glBegin(GL_POINTS);
    glPointSize(3);
    glColor3f(1.0, 0.0, 0.0);
    for(unsigned i = 0; i < faces.size(); ++i)
    {
        Cercle circle(faces[i], mesh);

                glVertex3f(circle.centre().x,
                           circle.centre().y,
                           circle.centre().z);


    }
    glEnd();




}
