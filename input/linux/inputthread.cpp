#include "inputthread.h"
#include "absval.h"
#include "inputthreadprivate.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QEvent>

#include <core/debughelper.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>

#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array) ((array[LONG(bit)] >> OFF(bit)) & 1)

using namespace GluonInput;

InputThread::InputThread(const QString &devicePath, QObject * parent)
		: QThread(parent)
{
	d = new InputThreadPrivate();
	d->m_devicePath = devicePath;
	openDevice(devicePath);
}

InputThread::~InputThread()
{
	close(d->m_fd);
}

void InputThread::run()
{
	while (1)
	{
		struct input_event ev;
		int rd = read(d->m_fd, &ev, sizeof(struct input_event));
		if (rd >= (int) sizeof(struct input_event))
		{
		  #warning emit events instead
			//InputEvent *event = new InputEvent(ev.code, ev.value, QEvent::Type(QEvent::User + ev.type));
			//QCoreApplication::postEvent(parent(), event);
		}
	}
}

bool InputThread::openDevice(const QString& devicePath)
{
	d->m_fd = -1;
	if ((d->m_fd = open(devicePath.toUtf8(), O_RDONLY)) < 0)
	{
		qDebug() << "Could not read device " << devicePath;
		return false;
	}

	readInformation();
	return true;
}

void InputThread::enable()
{
	if (!this->isRunning())
	{
		this->start();
	}
}

void InputThread::disable()
{
	if (this->isRunning())
	{
		this->stop();
	}
}

void InputThread::readInformation()
{
	if (!QFile::exists(d->m_devicePath))
	{
		qDebug() << "m_devicePath does not exist";
		d->m_error = true;
		d->m_msgError += "device url does not exist \n";
		return;
	}

	int m_fd = -1;
	if ((m_fd = open(d->m_devicePath.toUtf8(), O_RDONLY)) < 0)
	{
		qDebug() << "Could not open device" << d->m_devicePath;
		d->m_error = true;
		d->m_msgError += "could not open the device \n";
		return;
	}

	if (ioctl(m_fd, EVIOCGID, &d->m_device_info))
	{
		qDebug() << "Could not retrieve information of device" << d->m_devicePath;
		d->m_msgError += "could not retrieve information of device\n";
		d->m_error = true;
		return;
	}

	char name[256] = "Unknown";
	if (ioctl(m_fd, EVIOCGNAME(sizeof(name)), name) < 0)
	{
		qDebug() << "could not retrieve name of device" << d->m_devicePath;
		d->m_msgError += "cannot retrieve name of device\n";
		d->m_error = true;
		return;
	}
	d->m_deviceName = QString(name);

	///this next bit can be shared across platform
	unsigned long bit[EV_MAX][NBITS(KEY_MAX)];
	int abs[5];
	memset(bit, 0, sizeof(bit));
	ioctl(m_fd, EVIOCGBIT(0, EV_MAX), bit[0]);

	d->m_buttonCapabilities.clear();
	d->m_absAxisInfos.clear();

	for (int i = 0; i < EV_MAX; i++)
	{
		if (test_bit(i, bit[0]))
		{
			if (!i)
			{
				continue;
			}

			ioctl(m_fd, EVIOCGBIT(i, KEY_MAX), bit[i]);
			for (int j = 0; j < KEY_MAX; j++)
			{
				if (test_bit(j, bit[i]))
				{
					if (i == EV_KEY)
					{
						d->m_buttonCapabilities.append(j);
					}

					if (i == EV_REL)
					{
						d->m_relAxisCapabilities.append(j);
					}

					if (i == EV_ABS)
					{
						ioctl(m_fd, EVIOCGABS(j), abs);
						AbsVal cabs(0, 0, 0, 0);
						for (int k = 0; k < 5; k++)
						{
							if ((k < 3) || abs[k])
							{
								switch (k)
								{
									case 0:
										cabs.value = abs[k];
										break;
									case 1:
										cabs.min = abs[k];
										break;
									case 2:
										cabs.max = abs[k];
										break;
									case 3:
										cabs.fuzz = abs[k];
										break;
									case 4:
										cabs.flat = abs[k];
										break;
								}
							}
						}
						d->m_absAxisCapabilities.append(j);
						d->m_absAxisInfos[j] = cabs;
					}
				}
			}
		}
	}

	//===============Find Force feedback ?? ===============

	close(m_fd);

	d->m_deviceType = GluonInput::UnknownDevice;

	if (d->m_buttonCapabilities.contains(BTN_STYLUS))
	{
		d->m_deviceType  = GluonInput::TabletDevice;
	}

	if (d->m_buttonCapabilities.contains(BTN_STYLUS)
			|| d->m_buttonCapabilities.contains(ABS_PRESSURE))
	{
		d->m_deviceType  = GluonInput::MouseDevice;
	}

	if (d->m_buttonCapabilities.contains(BTN_TRIGGER))
	{
		d->m_deviceType  = GluonInput::JoystickDevice;
	}

	if (d->m_buttonCapabilities.contains(BTN_MOUSE))
	{
		d->m_deviceType  = GluonInput::MouseDevice;
	}

	if (d->m_buttonCapabilities.contains(KEY_ESC))
	{
		d->m_deviceType  = GluonInput::KeyboardDevice;
	}
}

int InputThread::getJoystickXAxis()
{
	return ABS_X;
}

int InputThread::getJoystickYAxis()
{
	return ABS_Y;
}

int InputThread::getJoystickZAxis()
{
	return ABS_Z;
}

void InputThread::stop()
{
	this->quit();
}

int InputThread::vendor()const
{
	return d->m_vendor;
}

int InputThread::product()const
{
	return d->m_product;
}

int InputThread::version()const
{
	return d->m_version;
}

int InputThread::bustype()const
{
	return d->m_bustype;
}

QList<int> InputThread::buttonCapabilities()const
{
	return d->m_buttonCapabilities;
}

QList<int> InputThread::absAxisCapabilities()const
{
	return d->m_absAxisCapabilities;
}

QList<int> InputThread::relAxisCapabilities()const
{
	return d->m_relAxisCapabilities;
}

AbsVal InputThread::axisInfo(int axisCode) const
{
	return d->m_absAxisInfos[axisCode];
}

const QString InputThread::deviceName() const
{
	return d->m_deviceName;
}

GluonInput::DeviceFlag InputThread::deviceType()const
{
	return d->m_deviceType;
}

bool InputThread::isEnabled() const
{
	return this->isRunning();
}

bool InputThread::error()
{
	return d->m_error;
}

QString InputThread::msgError()
{
	return d->m_msgError;
}

void InputThread::closeDevice()
{
	close(d->m_fd);
}

#include "inputthread.moc"
