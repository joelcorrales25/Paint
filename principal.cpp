#include "principal.h"
#include "ui_principal.h"


Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    //instanciar el objeto imagen
    m_imagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);

    //Rellenar de blanco
    m_imagen->fill(Qt::white);

    //Instanciar el objeto painter
    m_painter = new QPainter(m_imagen);
    m_painter->setRenderHint(QPainter::Antialiasing);
    m_color = Qt::black;
    m_width = DEFAULT_ANCHO;
    m_opcion = 1;
    m_permiso=false;
}

Principal::~Principal()
{
    delete ui;
    delete m_painter;
    delete m_imagen;
}

/**
 * @brief Principal::paintEvent Se ejecuta cada vez que se redibuja la interfaz
 * @param event
 */
void Principal::paintEvent(QPaintEvent *event)
{
    //Crear otro painter
    QPainter painter(this);
    //Dibujar la imagen
    painter.drawImage(0,0,*m_imagen);
    //Aceptar el evento
    event->accept();
}
void Principal::mousePressEvent(QMouseEvent *event)
{
    m_permiso=true;
    m_ptInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{

    if(m_opcion==1){
        m_ptFinal = event->pos();
        QPen pincel;
        pincel.setColor(m_color);
        pincel.setWidth(m_width);
        m_painter->setPen(pincel);
        m_painter->drawLine(m_ptInicial,m_ptFinal);
        update();
        m_ptInicial=m_ptFinal;

    }
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    //Lineas
    if(m_opcion==2){
        m_permiso = false;
        // Capturar el punto donde se suelta el mouse
        m_ptFinal= event->pos();
        //Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(m_color);
        pincel.setWidth(m_width);
        //Dibujar lineas
        m_painter->setPen(pincel);
        m_painter->drawLine(m_ptInicial,m_ptFinal);
        //Actualizar
        update();
        // Aceptar el evento
        event->accept();
    }
    //Rectangulo
    if(m_opcion==3){
        m_permiso = false;
        // Capturar el punto donde se suelta el mouse
        m_ptFinal = event->pos();
        //Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(m_color);
        pincel.setWidth(m_width);
        //Dibujar rectangulos
        QRect rectangulo (m_ptInicial, m_ptFinal);
        m_painter->setPen(pincel);
        m_painter->drawRect(rectangulo);
        //Actualizar
        update();
        // Aceptar el evento
        event->accept();
    }
    //Circunferencia
    if(m_opcion==4){
        m_permiso = false;
        // Capturar el punto donde se suelta el mouse
        m_ptFinal = event->pos();
        //Crear un pincel y establecer atributos
        QPen pincel;
        pincel.setColor(m_color);
        pincel.setWidth(m_width);
        //Dibujar circunferencias
        QRectF circulos (m_ptInicial, m_ptFinal);
        m_painter->setPen(pincel);
        m_painter->drawEllipse(circulos);
        //Actualizar
        update();
        // Aceptar el evento
        event->accept();
    }
}

void Principal::on_actionLibre_triggered()
{
    m_opcion = 1;
}

void Principal::on_actionLineas_triggered()
{
    m_opcion = 2;
    m_toogle = true;
}

void Principal::on_actionRectangulo_triggered()
{
    m_opcion = 3;
}

void Principal::on_actionCirculo_triggered()
{
    m_opcion = 4;
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionNuevo_triggered()
{
    m_imagen->fill(Qt::white);
    m_color = Qt::black;
    m_width = DEFAULT_ANCHO;
    m_opcion = 1;
    update();

}

void Principal::on_actionGuardar_triggered()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();

    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath();

    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Guardar Imagen",pathArchivo,"Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (m_imagen->save(nombreArchivo))
            QMessageBox::information(this,"Guardar Imagen","Archivo Almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,"Guardar Imagen","No se pudo Almacenar la Imagen");
    }

}

void Principal::on_actionAncho_triggered()
{
    m_width = QInputDialog::getInt(this, "Ancho del pincel", "Inserte el ancho del pincel",1,1,10);
}


void Principal::on_actionColor_triggered()
{
    m_color = QColorDialog::getColor(m_color,this,"Color del pincel");
}
