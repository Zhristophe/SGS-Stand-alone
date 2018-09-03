#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsObject>

class Button : public QGraphicsObject
{
    Q_OBJECT

public:
    Button(const QString &text);
    QRectF boundingRect() const { return QRectF(-m_width / 2, -m_height / 2, m_width, m_height); }

    void resize(qreal w, qreal h);
    void resize(QSizeF size);

public slots:
    void slotShow() { show(); }
    void slotHide() { hide(); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
    qreal m_width, m_height;
    QString text;

signals:
    void clicked();
};

#endif // BUTTON_H
