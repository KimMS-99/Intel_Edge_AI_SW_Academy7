#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QProcess process;
    // Set the program to execute (e.g., 'ls' on Linux/macOS, 'dir' on Windows)
    // and its arguments.

	QString webcamProgram = "/home/ubuntu/mjpg-streamer-master/mjpg_streamer";
	QStringList webcamArg = {"-i", "/home/ubuntu/mjpg-streamer-master/input_uvc.so", "-o", "/home/ubuntu/mjpg-streamer-master/output_http.so -w /home/ubuntu/mjpg-streamer-master/www"};

	process.start(webcamProgram, webcamArg);
    // Wait for the process to start.
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return 1;
    }

    // Wait for the process to finish.
    if (!process.waitForFinished(-1)) {
        qDebug() << "Process did not finish:" << process.errorString();
        return 1;
    }

    // Read the standard output of the process.
    QByteArray output = process.readAllStandardOutput();
    qDebug() << "Process Output:\n" << output;

    // Read the standard error of the process.
    QByteArray errorOutput = process.readAllStandardError();
    if (!errorOutput.isEmpty()) {
        qDebug() << "Process Error Output:\n" << errorOutput;
    }

    return 0;
}
