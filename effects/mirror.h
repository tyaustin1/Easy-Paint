#ifndef MIRROR_H
#define MIRROR_H
#include "abstracteffect.h"
#include <QPushButton>
#include <QSlider>
#include <QtCore/QObject>


class Mirror : public AbstractEffect
{
	Q_OBJECT
public:
	explicit Mirror(QObject *parent = 0);

	void applyEffect(ImageArea &imageArea);

private:
	QSlider *mIntensitySlider;
};

#endif 














