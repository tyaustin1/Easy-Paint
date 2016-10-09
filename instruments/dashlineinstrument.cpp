
#include "dashlineinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>

DashlineInstrument::DashlineInstrument(QObject *parent) :
AbstractInstrument(parent)
{
}

void DashlineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		mStartPoint = mEndPoint = event->pos();
		imageArea.setIsPaint(true);
		mImageCopy = *imageArea.getImage();
		makeUndoCommand(imageArea);
	}
}

void DashlineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		mEndPoint = event->pos();
		imageArea.setImage(mImageCopy);
		if (event->buttons() & Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->buttons() & Qt::RightButton)
		{
			paint(imageArea, true);
		}
	}
}

void DashlineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		imageArea.setImage(mImageCopy);
		if (event->button() == Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->button() == Qt::RightButton)
		{
			paint(imageArea, true);
		}
		imageArea.setIsPaint(false);
	}
}

void DashlineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
	if (isSecondaryColor)
	{
		painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}
	else
	{
		painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	}

	/*if (mStartPoint != mEndPoint)
	{
		painter.drawLine(mStartPoint, mEndPoint);
	}*/
	//@haque: dash line tools implementation
	if (mStartPoint != mEndPoint)
	{
		//Get distance in the standard way
		float distance = sqrt(pow(mStartPoint.x() - mEndPoint.x(), 2) + pow(mStartPoint.y() - mEndPoint.y(), 2));

		float sep = 4.0f / distance; //This determins how frequent the lines are
		QPoint currentStart = mStartPoint; //Starting point for each line, starting with starting point of big line.
		QPoint currentEndingPoint;
		QPoint tmepEndPoint = mStartPoint + (1 + sep)*(mEndPoint - mStartPoint); //Were the line ends plus an extra
		//segment(sep) so that the line is
		//connectd all the way to mouse
		bool odd = false; //variable that is used to determin if we are drawing, we draw only every other time

		for (float subPoint = 0; subPoint < 1; subPoint += sep)
		{
			odd = !odd;//Switch bool
			//Start the current segment at a point based on what subPoint we are at
			currentStart = mStartPoint + subPoint*(tmepEndPoint - mStartPoint);
			//End the current segment at a point based on what subPoint we are at
			currentEndingPoint = mStartPoint + (subPoint + sep)*(tmepEndPoint - mStartPoint);
			if (odd)//If we are drawing
			{
				painter.drawLine(currentStart, currentEndingPoint);//Draw it
			}
		}
	}


	if (mStartPoint == mEndPoint)
	{
		painter.drawPoint(mStartPoint);
	}
	imageArea.setEdited(true);
	
	painter.end();
	imageArea.update();
}
