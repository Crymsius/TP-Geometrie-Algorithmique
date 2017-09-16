#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
//#include <gasket.h>
#include <QMouseEvent>
#include "/Users/crymsius/Documents/Xcode/GeomMath/Mesh.h"

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int w, int h);

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    void drawMesh();
    Mesh mesh;
//    Gasket gasket;

    float _angle;
    QPoint _position;
    
signals:
    
public slots:
    
};

#endif // GLDISPLAY_H
