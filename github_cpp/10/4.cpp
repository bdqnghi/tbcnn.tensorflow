#ifndef HELPER_H
#define HELPER_H

#include "cppCORE_global.h"
#include "Exceptions.h"
#include <QTime>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QSharedPointer>


class CPPCORESHARED_EXPORT Helper
{
public:
	
	static void randomInit();
	
	static double randomNumber(double min, double max);
	
	static QString randomString(int length, const QString& chars="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", bool init=true);
	
	static QByteArray elapsedTime(QTime elapsed, bool only_seconds = false);

	
	template <typename T>
	static int toInt(const T& str, const QString& name = "string", const QString& line = "")
	{
		bool ok = false;
		int result = str.trimmed().toInt(&ok);
		if (!ok) THROW(ArgumentException, "Could not convert " + name + " '" + str + "' to integer" + (line.isEmpty() ? "" : "  - line: " + line));
		return result;
	}
	
	template <typename T>
	static double toDouble(const T& str, const QString& name = "string", const QString& line = "")
	{
		bool ok = false;
		double result = str.trimmed().toDouble(&ok);
		if (!ok) THROW(ArgumentException, "Could not convert " + name + " '" + str + "' to double" + (line.isEmpty() ? "" : "  - line: " + line));
		return result;
	}

	
	static QSharedPointer<QFile> openFileForReading(QString file_name, bool stdin_if_empty=false);
	
	static QSharedPointer<QFile> openFileForWriting(QString file_name, bool stdout_if_file_empty=false, bool append=false);

	
	static QStringList loadTextFile(QSharedPointer<QFile> file, bool trim_lines = false, QChar skip_header_char = QChar::Null, bool skip_empty_lines = false);
	
	static QStringList loadTextFile(QString file_name, bool trim_lines = false, QChar skip_header_char = QChar::Null, bool skip_empty_lines = false);
	
	static void storeTextFile(QSharedPointer<QFile> file, const QStringList& lines);
	
	static void storeTextFile(QString file_name, const QStringList& lines);

	
	static QString fileText(QString filename);
	
	static void touchFile(QString filename);

	
	static QString tempFileName(QString extension, int length=16);

	
	static QStringList findFiles(const QString& directory, const QString& pattern, bool recursive);
	
	static QStringList findFolders(const QString& directory, const QString& pattern, bool recursive);

	
	static int levenshtein(const QString& s1, const QString& s2);

	
	static QString userName();

	
	static QString dateTime(QString format = "dd.MM.yyyy hh:mm:ss");

	
	static bool isWritable(QString filename);

	
	static QString canonicalPath(QString filename);

protected:
	
	Helper() = delete;
};

#endif 
