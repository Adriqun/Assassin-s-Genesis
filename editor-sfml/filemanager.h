#pragma once
#include "thread.h"
#include <fstream>
#include <direct.h>
#include <string>
// #include <chrono>				// std::chrono::seconds
// #include <mutex>				// std::mutex, std::unique_lock
// #include <condition_variable>	// std::condition_variable, std::cv_status

// File Manager do saving, opening, refreshing and creating on another thread.
class FileManager
{
	enum STATUS
	{
		EMPTY = 0,
		PROCESSING,
		SUCCESS,
		WARNING,
		FAILURE
	};

	int saveVersion;
	int loadVersion;
	int status;
	std::string msg;
	
	std::string dirPath;
	std::vector<std::string> dirVec;
	std::fstream file;
	std::vector<std::string> content;
	std::string filePath;
	cmm::Thread thread;

	// std::mutex mtx;
	// std::condition_variable cv;

public:
	FileManager();
	~FileManager();
private:
	void free();
public:
	void clear();		// remove content and remove path
	void mechanics();	// used only to free thread

	void setFilePath(std::string newPath);
	void setDirectoryPath(std::string newPath);
	void setContent(std::vector<std::string> newContent);
	const std::string& getFilePath() const;
	const std::string& getDirectoryPath() const;
	const std::vector<std::string>& getContent() const;
	const std::vector<std::string>& getDirectories() const;
	void push(const std::string &line);
	void pop();

	void save();
	void open();
	void create(std::string newPath);
	void copy();
	void rename(std::string newPath);
	void deletee();
	void refresh();
	
	bool checkIfFileExists(std::string newPath);
	bool isNewSaveVersion();	// tells if content is different than content inside of file
	bool isNewLoadVersion();	// same but with loading
	bool isStatus() const;
	bool isProcessing();
	bool isSuccess();
	bool isWarning();
	bool isFailure();
	
	// void notify_one();	// by this you enable thread to continue task after processing status
	const std::string& getMessage() const;
	std::string substr(std::string str);
	void freeThread();
private:
	void savePrivate();
	void openPrivate();
	void createPrivate(std::string newPath);
	void copyPrivate();
	void renamePrivate(std::string newPath);
	void deletePrivate();
	void refreshPrivate();

	bool saveSupport(std::vector<std::string>& content, std::string &filePath);
	bool openSupport(std::vector<std::string>& newContent);
	bool refreshSupport();
};