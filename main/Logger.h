#pragma once

#include <deque>
#include <list>
#include <string>
#include <fstream>

enum _eLogLevel
{
	LOG_NORM=0,
	LOG_ERROR,
	LOG_STATUS,
};

enum _eLogFileVerboseLevel
{
	VBL_ALL=0,
	VBL_STATUS_ERROR,
	VBL_ERROR,
};

class CLogger
{
public:
	struct _tLogLineStruct
	{
		time_t logtime;
		_eLogLevel level;
		std::string logmessage;
		_tLogLineStruct(const _eLogLevel nlevel, const std::string &nlogmessage);
	};

	CLogger(void);
	~CLogger(void);

	void SetOutputFile(const char *OutputFile);
	void SetVerboseLevel(_eLogFileVerboseLevel vLevel);

	void Log(const _eLogLevel level, const char* logline, ...);
	void LogNoLF(const _eLogLevel level, const char* logline, ...);

	void LogSequenceStart();
	void LogSequenceAdd(const char* logline);
	void LogSequenceAddNoLF(const char* logline);
	void LogSequenceEnd(const _eLogLevel level);

	std::list<_tLogLineStruct> GetLog();
private:
	boost::mutex m_mutex;
	std::ofstream m_outputfile;
	std::deque<_tLogLineStruct> m_lastlog;
	bool m_bInSequenceMode;
	std::stringstream m_sequencestring;
	_eLogFileVerboseLevel m_verbose_level;
};
extern CLogger _log;
