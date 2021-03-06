#include <WCCOAJavaManager.hxx>
#include <WCCOAJavaResources.hxx>
#include <../LibJava/Java.hxx>
#include <at_rocworks_oa4j_jni_Manager.h>

#include <DpIdentifierVar.hxx>
#include <MsgItcDispatcher.hxx>

//------------------------------------------------------------------------------------------------
// JAVA JNI startup

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiStartup
(JNIEnv *env, jobject jobj, jint jtype, jobjectArray jargv, jboolean connectToData, jboolean connectToEvent)
{
	int len = env->GetArrayLength(jargv);
	char **argv = (char **)malloc(len * sizeof(char *));
	for (int i = 0; i < len; i++)
	{
		jobject jstr = env->GetObjectArrayElement(jargv, i);
		Java::copyJavaStringToString(env, (jstring)jstr, &argv[i]);
		env->DeleteLocalRef(jstr);
	}

	std::cout << "Startup Java/WinCCOA connection..." << std::endl;

	WCCOAJavaResources::init(len, argv);

	if (jtype == API_MAN)
	{
		WCCOAJavaManager::startupManager(len, argv, env, jobj, API_MAN, connectToData, connectToEvent);
		std::cout << "Startup Java/WinCCOA API connection...done " << std::endl;
		return 0;
	}
	else
	if (jtype == DB_MAN) {
		WCCOAJavaManager::startupManager(len, argv, env, jobj, DB_MAN, connectToData, connectToEvent);
		std::cout << "Startup Java/WinCCOA DB connection...done " << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Unknown ManagerType " << jtype << std::endl;
		return -1;
	}
}

//------------------------------------------------------------------------------------------------
// JAVA JNI shutdown

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiShutdown
(JNIEnv *, jobject)
{
	Manager::closeConnection(*(WCCOAJavaManager::thisManager->getFirstConnection()));
	return 0;
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dispatch


JNIEXPORT void JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDispatch
(JNIEnv *env, jobject obj, jint jsec, jint jusec)
{
	WCCOAJavaManager::thisManager->javaDispatch(env, obj, jsec, jusec);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpGet/dpSet

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpGet
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpGet(env, obj, jHdl, dps);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpSet
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpSet(env, obj, jHdl, dps);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpSetTimed
(JNIEnv *env, jobject obj, jobject jHdl, jobject jTimeVar, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpSetTimed(env, obj, jHdl, jTimeVar, dps);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpConnect

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpConnect
(JNIEnv *env, jobject obj, jobject jHdl, jstring dp)
{
	return WCCOAJavaManager::thisManager->javaDpConnect(env, obj, jHdl, dp);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpDisconnect
(JNIEnv *env, jobject obj, jobject jHdl, jstring dp)
{
	return WCCOAJavaManager::thisManager->javaDpDisconnect(env, obj, jHdl, dp);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpConnectArray

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpConnectArray
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpConnect(env, obj, jHdl, dps);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpDisconnectArray
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpDisconnect(env, obj, jHdl, dps);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI alertConnectArray

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiAlertConnect
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaAlertConnect(env, obj, jHdl, dps);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiAlertDisconnect
(JNIEnv *env, jobject obj, jobject jHdl, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaAlertDisconnect(env, obj, jHdl, dps);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpQuery

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpQuery
(JNIEnv *env, jobject obj, jobject jHdl, jstring jQuery)
{
	return WCCOAJavaManager::thisManager->javaDpQuery(env, obj, jHdl, jQuery);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpGetPeriod
JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpGetPeriod
(JNIEnv *env, jobject obj, jobject jHdl, jobject tStart, jobject tStop, jint num, jobjectArray dps)
{
	return WCCOAJavaManager::thisManager->javaDpGetPeriod(env, obj, jHdl, tStart, tStop, num, dps);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI dpQueryConnect

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpQueryConnectSingle
(JNIEnv *env, jobject obj, jobject jHdl, jboolean jValues, jstring jQuery)
{
	return WCCOAJavaManager::thisManager->javaDpQueryConnect(env, obj, jHdl, jValues, jQuery, true);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpQueryConnectAll
(JNIEnv *env, jobject obj, jobject jHdl, jboolean jValues, jstring jQuery)
{
	return WCCOAJavaManager::thisManager->javaDpQueryConnect(env, obj, jHdl, jValues, jQuery, false);
}

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpQueryDisonnect
(JNIEnv *env, jobject obj, jobject jHdl)
{
	return WCCOAJavaManager::thisManager->javaDpQueryDisconnect(env, obj, jHdl);
}

//------------------------------------------------------------------------------------------------
// JAVA JNI GetLogPath

JNIEXPORT jstring JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetLogPath
(JNIEnv *env, jobject obj)
{
	CharString path = WCCOAJavaResources::getLogDir();
	jstring js = env->NewStringUTF(path);
	return js;
}

JNIEXPORT jstring JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetDataPath
(JNIEnv *env, jobject obj)
{
	CharString path = WCCOAJavaResources::getDataDir();
	jstring js = env->NewStringUTF(path);
	return js;
}

JNIEXPORT jstring JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetConfigValue
(JNIEnv *env, jobject obj, jstring jkey)
{
	CharString *key = Java::convertJString(env, jkey);
	const char *value = WCCOAJavaResources::getConfigValue(key->c_str());
	jstring js = value == 0 ? 0 : env->NewStringUTF(value);
	delete key;
	return js;
}

//------------------------------------------------------------------------------------------------
// JAVA JNI DpMsgHotLink

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiSendArchivedDPs
(JNIEnv *env, jobject, jobject jDynVar, jboolean isAlert)
{
	TimeVar now = TimeVar();
	DynVar *dynvar = (DynVar*)Java::convertJVariable(env, jDynVar);

	DpMsgHotLink *msg = new DpMsgHotLink;
	msg->setOriginTime(now);

	//Make the first Entry with Dpidentifier = NULL and the TimeVar
	if (!isAlert)
	{
		DpHLGroup *first = new DpHLGroup();
		const DpIdentifier *empty = new DpIdentifier();
		first->appendItem(*empty, now);
		msg->appendGroup(first);
	}

	//Append the other Elements with the valid DpIdentifications
	int idx = 0;
	for (Variable* varPtr = dynvar->getFirstVar(); varPtr; varPtr = dynvar->getNextVar())
	{
		if (msg == NULL)
		{
			msg = new DpMsgHotLink();
		}
		DpHLGroup *entry = new DpHLGroup();
		DpIdentifierVar *dpIdVarPtr = ((DpIdentifierVar*)varPtr);
		std::cout << "apiSendDpMsgHotLink " << dpIdVarPtr << std::endl;
		if (!isAlert)
		{
			entry->appendItem(dpIdVarPtr->getValue(), new TimeVar(TimeVar::NullTimeVar));
		}
		else 
		{
			entry->appendItem(dpIdVarPtr->getValue(), now);
		}
		msg->appendGroup(entry);

		if ((++idx % 1024) == 0)
		{
			WCCOAJavaManager::thisManager->send(*msg, WCCOAJavaManager::dataId);
			delete msg;
			msg = NULL;
		}
	}

	//Send the last one with an empty dpidentifier
	if (msg == NULL)
	{
		msg = new DpMsgHotLink();
	}
	DpHLGroup *last = new DpHLGroup();
	const DpIdentifier *empty = new DpIdentifier();
	last->appendItem(*empty, now);

	if (!isAlert) {
		const DpIdentifier *empty = new DpIdentifier();
		last->appendItem(*empty, new TimeVar(TimeVar::NullTimeVar));
	}

	msg->appendGroup(last);

	int ret = WCCOAJavaManager::thisManager->send(*msg, WCCOAJavaManager::dataId);

	delete msg;
	return ret;
}

//------------------------------------------------------------------------------------------------
// JAVA JNI GetIdSet

JNIEXPORT jobjectArray JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetIdSet
(JNIEnv *env, jobject obj, jstring jpattern)
{
	jboolean patternIsCopy;
	const char *pattern = env->GetStringUTFChars(jpattern, &patternIsCopy);

	PVSSlong count;
	DpIdentifier *list;
	Manager::getIdSet(pattern, list, count);

	// create java string[]
	jclass cls = env->FindClass("java/lang/String");
	jobjectArray jarr = env->NewObjectArray(count, cls, (jobject)NULL);

	// add datapoints to java array
	CharString dpName;
	for (int i = 0; i < count; i++)
	{
		list[i].convertToString(dpName);
		jstring jstr = Java::convertToJava(env, &dpName);
		env->SetObjectArrayElement(jarr, i, jstr);
		env->DeleteLocalRef(jstr);
		//std::cout << "apiDpConnectLogger " << dpName << std::endl;
	}

	env->ReleaseStringUTFChars(jpattern, pattern);
	env->DeleteLocalRef(cls);
	delete [] list;
	//if (patternIsCopy) delete pattern;
	return jarr;
}

JNIEXPORT jobjectArray JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetIdSetOfType
(JNIEnv *env, jobject obj, jstring jpattern, jstring jtype)
{
	jboolean patternIsCopy, typeIsCopy;
	const char *pattern = env->GetStringUTFChars(jpattern, &patternIsCopy);
	const char *type = env->GetStringUTFChars(jtype, &typeIsCopy);

	DpTypeId dptype;
	Manager::getTypeId(type, dptype);

	jclass cls = env->FindClass("java/lang/String");
	jobjectArray jarr;
	if (dptype == 0)
	{
		// create empty java string[]
		jarr = env->NewObjectArray(0, cls, (jobject)NULL);
	}
	else
	{
		PVSSlong count;
		DpIdentifier *list;
		Manager::getIdSet(pattern, list, count, dptype);

		// create java string[]		
		jarr = env->NewObjectArray(count, cls, (jobject)NULL);

		// add datapoints to java array
		CharString dpName;
		for (int i = 0; i < count; i++)
		{
			list[i].convertToString(dpName);
			jstring jstr = Java::convertToJava(env, &dpName);
			env->SetObjectArrayElement(jarr, i, jstr);
			env->DeleteLocalRef(jstr);
			//std::cout << "apiDpConnectLogger " << dpName << std::endl;
		}
		delete[] list;
	}
	env->ReleaseStringUTFChars(jpattern, pattern);
	env->ReleaseStringUTFChars(jtype, type);
	env->DeleteLocalRef(cls);
	//if (typeIsCopy) delete type; // crashes
	//if (patternIsCopy) delete pattern; // crashes
	return jarr;
}

//------------------------------------------------------------------------------------------------
// JAVA JNI apiProcessHotlinkGroup

JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiProcessHotlinkGroup
(JNIEnv *env, jobject obj, jint jHdl, jlong jGroup)
{
	return WCCOAJavaManager::thisManager->javaProcessHotLinkGroup(env, obj, jHdl, jGroup);
}

//------------------------------------------------------------------------------------------------
/*
* Class:     at_rocworks_oa4j_jni_Manager
* Method:    apiDpGetComment
* Signature: (Lat/rocworks/oa4j/base/JDpId;)Lat/rocworks/oa4j/var/LangTextVar;
*/
JNIEXPORT jobject JNICALL Java_at_rocworks_oa4j_jni_Manager_apiDpGetComment
(JNIEnv *env, jobject obj, jobject jDpId)
{
	DpIdentifier *dpid = new DpIdentifier();
	Java::convertJDpIdentifierToDpIdentifier(env, jDpId, *dpid);
	LangTextVar *comment = new LangTextVar();
	jobject jComment = NULL;
	if (WCCOAJavaManager::thisManager->dpGetComment(*dpid, *comment) == DpIdentOK) {
		VariablePtr varptr = comment;
		jComment = Java::convertToJava(env, varptr);
	}
	delete comment;
	delete dpid;
	return jComment;
}

//------------------------------------------------------------------------------------------------

/*
* Class:     at_rocworks_oa4j_jni_Manager
* Method:    apiSetManagerState
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_at_rocworks_oa4j_jni_Manager_apiSetManagerState
(JNIEnv *env, jobject obj, jint state)
{
	WCCOAJavaManager::thisManager->setManagerState(static_cast<WCCOAJavaManager::ManagerState>(state));
}

/*
* Class:     at_rocworks_oa4j_jni_Manager
* Method:    getHostNr
* Signature: ()Z
*/
JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiGetConnectionState
(JNIEnv *env, jobject obj)
{
	ManagerIdentifier man(EVENT_MAN, 0);
	if (MsgItcDispatcher::instance()->getConnectionState(man))
		return 1;
	else {
		man.toggleReplica();
		if (MsgItcDispatcher::instance()->getConnectionState(man))
			return 2;
		else
			return 0;
	}
}

/*
* Class:     at_rocworks_oa4j_jni_Manager
* Method:    getActiveHostNr
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_at_rocworks_oa4j_jni_Manager_apiIsActiveConnection
(JNIEnv *env, jobject obj)
{
	ManagerIdentifier man(EVENT_MAN, 0);
	if (MsgItcDispatcher::instance()->isActiveConnection(man))
		return 1;
	else {
		man.toggleReplica();
		if (MsgItcDispatcher::instance()->isActiveConnection(man))
			return 2;
		else
			return 0;
	}
}