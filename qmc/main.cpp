#include "MainWindow.h"
#include <QtWidgets/QApplication>

//LOCAL INFO: how to push (if I ever forget it): TeamExplorer->Sync->Actions:OpenInCommandPrompt->RunCommand:"git push"

static QSurfaceFormat createSurfaceFormat()
{
	QSurfaceFormat format;
	format.setSamples(4);
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 0);
	format.setSwapBehavior(QSurfaceFormat::SwapBehavior::SingleBuffer);
	return format;
}

int main(int argc, char *argv[])
{
	qputenv("QT_ANGLE_PLATFORM", "d3d11");
	QApplication a(argc, argv);
	QSurfaceFormat::setDefaultFormat(createSurfaceFormat());
	QOpenGLContext *context = new QOpenGLContext;
	context->create();
	MainWindow w(context);
	w.resize(QSize(1280, 720));
	w.show();
	int iRes = a.exec();
	delete context;
	return iRes;
}
