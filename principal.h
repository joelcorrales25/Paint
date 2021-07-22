#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#define DEFAULT_ANCHO 2;


QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;

private slots:
    void on_actionLibre_triggered();

    void on_actionLineas_triggered();

    void on_actionRectangulo_triggered();

    void on_actionCirculo_triggered();

    void on_actionSalir_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionAncho_triggered();

    void on_actionColor_triggered();

private:
    Ui::Principal *ui;
    QImage *m_imagen;  //Imagen sobre la cual se va a dibujar
    QPainter *m_painter; //El objeto painter
    QPoint m_ptInicial; //punto inicial para dibujar
    QPoint m_ptFinal; //punto final para dibujar
    QPen pincel;
    QColor m_color; //Color de la linea
    int m_width; //Ancho de la linea
    int m_opcion; //Opcion de dibujo
    bool m_permiso;
    bool m_toogle = true;

};
#endif // PRINCIPAL_H
