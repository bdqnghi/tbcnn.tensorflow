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

///Auxilary helper functions class.
class CPPCORESHARED_EXPORT Helper
{
public:
	///Updates random number generator using a seed caclualted from the current time and process ID.
	static void randomInit();
	///Returns a random number in the given range
	static double randomNumber(double min, double max);
	///Returns a random string.
	static QString randomString(int length, const QString& chars="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", bool init=true);
	///Returns the elapsed time as a human-readable string.
	static QByteArray elapsedTime(QTime elapsed, bool only_seconds = false);

	///Converts a QString/QByteArray to an integer. Throws an error if the conversion fails.
	template <typename T>
	static int toInt(const T& str, const QString& name = "string", const QString& line = "")
	{
		bool ok = false;
		int result = str.trimmed().toInt(&ok);
		if (!ok) THROW(ArgumentException, "Could not convert " + name + " '" + str + "' to integer" + (line.isEmpty() ? "" : "  - line: " + line));
		return result;
	}
	///Converts a QString/QByteArray to a double. Throws an error if the conversion fails.
	template <typename T>
	static double toDouble(const T& str, const QString& name = "string", const QString& line = "")
	{
		bool ok = false;
		double result = str.trimmed().toDouble(&ok);
		if (!ok) THROW(ArgumentException, "Could not convert " + name + " '" + str + "' to double" + (line.isEmpty() ? "" : "  - line: " + line));
		return result;
	}

	///Returns an opened file pointer, or throws an error if it cannot be opened.
	static QSharedPointer<QFile> openFileForReading(QString file_name, bool stdin_if_empty=false);
	///Returns an opened file pointer, or throws an error if it cannot be opened.
	static QSharedPointer<QFile> openFileForWriting(QString file_name, bool stdout_if_file_empty=false, bool append=false);

	///Loads a text file. If @p trim_lines is given, the lines are trimmed. If @p skip_header_char is given, header lines starting with that character are skipped. If @p skip_empty_lines is given, empty lines are skipped.
	static QStringList loadTextFile(QSharedPointer<QFile> file, bool trim_lines = false, QChar skip_header_char = QChar::Null, bool skip_empty_lines = false);
	///Convenience overload for loadTextFile.
	static QStringList loadTextFile(QString file_name, bool trim_lines = false, QChar skip_header_char = QChar::Null, bool skip_empty_lines = false);
	///Stores a string list as a text file. To each line '\n' is appended as newline character.
	static void storeTextFile(QSharedPointer<QFile> file, const QStringList& lines);
	///Convenience overload for storeTextFile.
	static void storeTextFile(QString file_name, const QStringList& lines);

	///Returns the contents of a file as a string. Throws an error if the file cannot be opened.
	static QString fileText(QString filename);
	///Creates a text file if it does not exist. Throws an error if the file cannot be opened for writing.
	static void touchFile(QString filename);

	///Returns a temporary file name. Make sure you delete the file when it is no longer needed to avoid name clashes!
	static QString tempFileName(QString extension, int length=16);

	///Find files (recursively).
	static QStringList findFiles(const QString& directory, const QString& pattern, bool recursive);
	///Find folders (recursively).
	static QStringList findFolders(const QString& directory, const QString& pattern, bool recursive);

	///Returns the Levenshtein-distance of two strings.
	static int levenshtein(const QString& s1, const QString& s2);

	///Gets the user name of the current user from the environment variables.
	static QString userName();

	///Returns the current date and time in the given format. If the format is a empty string, the ISO format "yyyy-MM-ddTHH:mm:ss" is returned.
	static QString dateTime(QString format = "dd.MM.yyyy hh:mm:ss");

	///Checks if a file is writable (or if the folder is writable in case the file does not exist)
	static bool isWritable(QString filename);

	///Retruns the canonical (relative or absolute) file path for Windows.
	static QString canonicalPath(QString filename);

protected:
	///Constructor declared away.
	Helper() = delete;
};

#endif // HELPER_H
