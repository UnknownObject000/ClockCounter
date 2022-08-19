/*
* Application Communication Interface - Full Version
* Copyright (c) 2022-2032 UnknownObject
*/

#pragma once
#pragma warning(disable : 26812)
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <sstream>
#include <json/json.h>
#include <curl/curl.h>
#include <webcc/logger.h>
#include <webcc/server.h>
#include <webcc/response_builder.h>

constexpr auto ACI_UA = "libcurl/7.68.0 (Windows NT 10.0; Win64; x64) UnknownNetworkService/2.01 (Application Communication Interface; Localhost-Only)";

//Common types
using JsonValue = Json::Value;
using JsonReader = Json::Reader;
//Client-only types
using ClientCallback = void(*)(JsonValue);
using ClientDataGroup = std::vector<std::string>;
using ClientDataPair = std::pair<std::string, std::string>;
template<typename T> using ClassClientCallback = void(T::*)(JsonValue);
//Server-only types
using ServerInputCallback = void(*)(JsonValue);
using ServerDataQueue = std::vector<std::string>;
using ResponseFunction = std::string(*)(std::string);
using StaticDataResponder = std::map<std::string, std::string>;
using DynamicDataResponder = std::map<std::string, ResponseFunction>;

//Common classes
class JsonUnicodeWriter
{
private:
	Json::StreamWriterBuilder jswb;
public:
	JsonUnicodeWriter();
public:
	std::string write(JsonValue root);
};

//------------------------------------------Client Classes------------------------------------------
class ClientDataEncoder
{
public:
	static std::string Encode(std::string item, std::string data);
	static std::string Encode(std::string item);
	static JsonValue Decode(std::string str);
	static ClientDataPair Decode(JsonValue root);
	static ClientDataGroup DecodeGroup(JsonValue root);
};

class ACIClient
{
private:
	CURL* curl;
	int ServerPort;
private:
	static size_t process_data(void* buffer, size_t size, size_t nmemb, void* user_p);
public:
	ACIClient(int server_port = 10000);
	~ACIClient();
public:
	bool SendData(std::string item, std::string data, ClientCallback cb_func = nullptr);
	template<typename T> bool SendData(std::string item, std::string data, ClassClientCallback<T> cb_func, T* class_pointer);
	bool RequestData(std::string item, std::string data, ClientCallback cb_func = nullptr);
	template<typename T> bool RequestData(std::string item, std::string data, ClassClientCallback<T> cb_func, T* class_pointer);
	bool RequestData(std::string item, ClientCallback cb_func = nullptr);
	template<typename T> bool RequestData(std::string item, ClassClientCallback<T> cb_func, T* class_pointer);
	bool RequestQuquedData(ClientCallback cb_func = nullptr);
	template<typename T> bool RequestQuquedData(ClassClientCallback<T> cb_func, T* class_pointer);
};
//----------------------------------------Client Classes End----------------------------------------

//------------------------------------------Server Classes------------------------------------------
class ServerDataEncoder
{
public:
	static std::string Encode(std::string item, std::string data);
	static JsonValue Decode(std::string str);
	static std::string EncodeResponse(std::string error, ServerDataQueue data = ServerDataQueue());
};

class ServerDataStorage
{
private:
	static ServerDataQueue DataQueue;
	static StaticDataResponder SDR_Input;
	static StaticDataResponder SDR_Output;
	static DynamicDataResponder DDR_Output;
public:
	static void GlobalClear();
	static void DataQueueClear();
	static void SDR_InputClear();
	static void SDR_OutputClear();
	static void DDR_OutputClear();
	static void DataQueueAdd(std::string data);
	static void SDRInputAdd(std::string item, std::string resp);
	static void SDROutputAdd(std::string item, std::string resp);
	static void DDROutputAdd(std::string item, ResponseFunction resfunc);
	static ServerDataQueue GetDataQueue();
	static StaticDataResponder GetSDR_Input();
	static StaticDataResponder GetSDR_Output();
	static DynamicDataResponder GetDDR_Output();
	static bool SDRInputExist(std::string item);
	static bool SDROutputExist(std::string item);
	static bool DDROutputExist(std::string item);
	static std::string SDRInputGetValue(std::string item);
	static std::string SDROutputGetValue(std::string item);
	static ResponseFunction DDROutputGetValue(std::string item);
};

class ServerInputHandler : public webcc::View
{
private:
	ServerInputCallback InputCallback;
public:
	ServerInputHandler(ServerInputCallback cb_input = nullptr);
public:
	webcc::ResponsePtr Handle(webcc::RequestPtr request) override;
};

class ServerOutputHandler : public webcc::View
{
public:
	webcc::ResponsePtr Handle(webcc::RequestPtr request) override;
};

class ServerSideOutputHandler : public webcc::View
{
public:
	webcc::ResponsePtr Handle(webcc::RequestPtr request) override;
};

class ACIServer
{
private:
	bool CallbackEnabled;
	webcc::Server* ccServer;
	std::thread ServerThread;
	ServerInputCallback InputCallback;
	const webcc::Strings methods = { "GET","POST","PUT","HEAD","DELETE" };
private:
	static void ServerThreadFunction(webcc::Server* server, int worker_thread, int loop_thread);
public:
	ACIServer(int port = 10000, bool enable_callback = false, ServerInputCallback cb_func = nullptr);
	~ACIServer();
public:
	void Run(int worker_thread = 1, int loop_thread = 1);
	void ThreadRun(int worker_thread = 1, int loop_thread = 1);
	void Stop();
	bool EnableCallback(ServerInputCallback cb_func = nullptr);
	bool SetCallbackFunction(ServerInputCallback cb_func);
	bool DisableCallback();
	void OutputQueueAdd(std::string content);
	void OutputQueueClear();
};
//----------------------------------------Server Classes End----------------------------------------

#ifndef _DEBUG
#pragma comment(lib, "ACIFullVersion.lib")
#else
#pragma comment(lib, "ACIFullVersiond.lib")
#endif