#include "mirror.h"
#include "../imagearea.h"
#include <QLabel>
#include <Qwidget>
#include <QLayout>
#include <QPushbutton>
#include <QInputDialog>
#include <qmessagebox.h>
#include <QCoreapplication>
#include <math.h>

Mirror::Mirror(QObject *parent) :
	AbstractEffect(parent)
{
}

void Mirror::applyEffect(ImageArea &imageArea)
{

	QMessageBox msgBox;
	msgBox.setText("Mirror Image");
	msgBox.setInformativeText("Which half of the image would you like to mirror?");
	QPushButton *connectButton = msgBox.addButton(tr("Top"), QMessageBox::ActionRole);
	QPushButton *connectButton2 = msgBox.addButton(tr("Bottom"), QMessageBox::ActionRole);
	

	msgBox.exec();

	if (msgBox.clickedButton() == connectButton) {
		
		//Clear Bottom half
		for (int i(0); i < imageArea.getImage()->width(); i++)
		{
			for (int y(imageArea.getImage()->height()); y < imageArea.getImage()->height() / 2; y++)
			{
				QRgb pixel(0);
				imageArea.getImage()->setPixel(i, y + imageArea.getImage()->height() / 2, pixel);
			}
		}

		//Read top half and place pixels on bottom half
		for (int i(0); i < imageArea.getImage()->width(); i++)
		{
			for (int y(0); y < imageArea.getImage()->height() / 2; y++)
			{
				QRgb pixel(imageArea.getImage()->pixel(i, y));

				imageArea.getImage()->setPixel(i, imageArea.getImage()->height() - y, pixel);
			}
		}
		imageArea.setEdited(true);
		imageArea.update();
	}
	else if (msgBox.clickedButton() == connectButton2) {
		//Clear top half
		for (int i(0); i < imageArea.getImage()->width(); i++)
		{
			for (int y(0); y < imageArea.getImage()->height() / 2; y++)
			{
				
				QRgb pixel(0);

				imageArea.getImage()->setPixel(i, y, pixel);
			}
		}

		for (int i(0); i < imageArea.getImage()->width(); i++)
		{
			for (int y(imageArea.getImage()->height() / 2); y < imageArea.getImage()->height(); y++)
			{
				QRgb pixel(imageArea.getImage()->pixel(i, y));
				
				imageArea.getImage()->setPixel(i, 0 + imageArea.getImage()->height() - y , pixel);
			}
		}
		imageArea.setEdited(true);
		imageArea.update();

	}

	
	
}















